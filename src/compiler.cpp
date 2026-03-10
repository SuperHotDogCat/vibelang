#include "compiler.h"
#include "semantics.h"
#include "codegen.h"
#include <iostream>

extern int yyparse();
extern FILE* yyin;
extern std::unique_ptr<novus::Program> root;

namespace novus {

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

void Compiler::compile(const std::string& mainFile) {
    auto mainProgram = parseFile(mainFile);

    // Process imports (recursive)
    std::vector<std::string> toProcess;
    for (auto& imp : mainProgram->imports) {
        toProcess.push_back(static_cast<ImportStmt*>(imp.get())->path);
    }

    while (!toProcess.empty()) {
        std::string path = toProcess.back();
        toProcess.pop_back();
        if (parsedFiles.count(path)) continue;

        auto prog = parseFile(path);
        for (auto& imp : prog->imports) {
            toProcess.push_back(static_cast<ImportStmt*>(imp.get())->path);
        }
        parsedFiles[path] = std::move(prog);
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
