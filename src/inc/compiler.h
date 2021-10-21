#ifndef _COMPILER_H
#define _COMPILER_H

#include <string>
#include <vector>
#include "vm.h"

class Compiler {

    std::string binary_code;
    std::string file_path;
    std::vector<Inst> program;
    
    public:
        Compiler(std::string);
        Compiler(std::vector<Inst>, std::string);
        void compile();
        std::vector<Inst> decompile();
};

#endif