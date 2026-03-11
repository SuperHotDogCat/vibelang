#include "compiler.h"
#include "semantics.h"
#include "codegen.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <libgen.h>

extern int yyparse();
extern FILE* yyin;
extern std::unique_ptr<novus::Program> root;

namespace novus {

std::string Compiler::resolvePath(const std::string& path, const std::string& currentFileDir) {
    if (access(path.c_str(), F_OK) == 0) return path;

    if (!currentFileDir.empty()) {
        std::string localPath = currentFileDir + "/" + path;
        if (access(localPath.c_str(), F_OK) == 0) return localPath;
    }

    const char* envPath = getenv("NOVUS_PATH");
    if (!envPath) return path;

    std::stringstream ss(envPath);
    std::string dir;
    while (std::getline(ss, dir, ':')) {
        std::string fullPath = dir + "/" + path;
        if (access(fullPath.c_str(), F_OK) == 0) {
            return fullPath;
        }
    }
    return path;
}

std::unique_ptr<Program> Compiler::parseFile(const std::string& filename) {
    FILE* file = fopen(filename.c_str(), "r");
    if (!file) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    yyin = file;
    if (yyparse() != 0) {
        fclose(file);
        throw std::runtime_error("Parse error in file: " + filename);
    }
    fclose(file);
    return std::move(root);
}

static std::string getDir(const std::string& path) {
    char* cpath = strdup(path.c_str());
    std::string dir = dirname(cpath);
    free(cpath);
    return dir;
}

void Compiler::compile(const std::string& mainFile) {
    auto mainProgram = parseFile(mainFile);
    std::string mainDir = getDir(mainFile);

    // Process imports (recursive)
    std::vector<std::pair<std::string, std::string>> toProcess;
    for (auto& imp : mainProgram->imports) {
        toProcess.push_back({static_cast<ImportStmt*>(imp.get())->path, mainDir});
    }

    while (!toProcess.empty()) {
        auto item = toProcess.back();
        toProcess.pop_back();
        std::string fullPath = resolvePath(item.first, item.second);

        if (parsedFiles.count(fullPath)) continue;

        auto prog = parseFile(fullPath);
        std::string currentDir = getDir(fullPath);
        for (auto& imp : prog->imports) {
            toProcess.push_back({static_cast<ImportStmt*>(imp.get())->path, currentDir});
        }
        parsedFiles[fullPath] = std::move(prog);
    }

    SemanticAnalyzer analyzer;
    analyzer.symbolTable.pushScope();

    // Collect all declarations first
    for (auto& pair : parsedFiles) {
        analyzer.collectDecls(pair.second.get());
    }
    analyzer.collectDecls(mainProgram.get());

    // Analyze all
    for (auto& pair : parsedFiles) {
        analyzer.analyzeOnly(pair.second.get());
    }
    analyzer.analyzeOnly(mainProgram.get());

    CodeGenerator generator;
    for (auto& pair : parsedFiles) {
        generator.generate(pair.second.get());
    }
    generator.generate(mainProgram.get());

    std::string output = mainFile;
    size_t dot = output.find_last_of(".");
    if (dot != std::string::npos) output = output.substr(0, dot);
    output += ".ll";
    generator.save(output);
}

}
