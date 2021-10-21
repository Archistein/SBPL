#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "inc/vm.h"
#include "inc/data.h"
#include "inc/compiler.h"

Compiler::Compiler(std::string binary_code) {
    this->binary_code = binary_code;
}

Compiler::Compiler(std::vector<Inst> program, std::string file_path) {
    this->program = program;
    this->file_path = file_path;
}

void Compiler::compile() {
    
    std::ofstream output_file(this->file_path, std::ios::trunc);

    if (!output_file.good()) {
        std::cerr << "ERROR: Cannot open file " << this->file_path << std::endl;
        exit(-8);
    }

    for (Inst instruction : this->program) {
        output_file  << instruction.get_type() << ":"
                << instruction.get_operand().get_ident() << ":"
                << instruction.get_operand().get_type() << ":" 
                << instruction.get_operand().get_val() << std::endl;
    }

    output_file.close();

}

std::vector<std::string> split_by_character(std::string str, char sep) {

    std::stringstream ss_str(str);
    std::string segment;
    std::vector<std::string> result;

    while(std::getline(ss_str, segment, sep)) {
        result.push_back(segment);
    }

    return result;

}

std::vector<Inst> Compiler::decompile() {

    std::vector<Inst> result;
    std::vector<std::string> word_buff;
    std::string buffer;

    std::ifstream input_file(this->binary_code);

    if (!input_file.good()){
        std::cerr << "ERROR: No such file" << std::endl;
        exit(-7);
    }
    
    INST_TYPE inst_type;
    std::string ident;
    VAR_TYPE var_type;
    std::string val;

    while(std::getline(input_file, buffer)) {
    
        inst_type = INST_EXIT;
        ident = "";
        var_type = VAR_UNDEFINED;
        val = "";

        word_buff = split_by_character(buffer, ':');

        if (std::stoi(word_buff[0]) < 0 || std::stoi(word_buff[0]) > INST_EXIT || std::stoi(word_buff[2]) < 0 || std::stoi(word_buff[2]) > VAR_UNDEFINED) {
            std::cerr << "ERROR: Illegal instruction" << std::endl;
            exit(-9);
        }

        inst_type = static_cast<INST_TYPE>(std::stoi(word_buff[0]));
        ident = word_buff[1];
        var_type = static_cast<VAR_TYPE>(std::stoi(word_buff[2]));

        if (word_buff.size() > 3)
            val = word_buff[3]; 

        result.push_back(Inst(inst_type, Data(ident, var_type, val)));

    }

    input_file.close(); 

    return result;

}