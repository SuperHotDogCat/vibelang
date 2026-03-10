#ifndef COMPILER_H
#define COMPILER_H

#include "ast.h"
#include <string>
#include <memory>
#include <map>

namespace novus {

class Compiler {
public:
    std::unique_ptr<Program> parseFile(const std::string& filename);
    void compile(const std::string& mainFile);

private:
    std::map<std::string, std::unique_ptr<Program>> parsedFiles;
};

}

#endif
