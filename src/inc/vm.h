#ifndef _INST_H
#define _INST_H

#include <string>
#include <vector>
#include <map>
#include "data.h"

enum INST_TYPE {
    INST_PUSH,
    INST_POP,   
    INST_PLUS,
    INST_MINUS,
    INST_MUL,
    INST_DIV,
    INST_EQ,
    INST_GT,
    INST_LS,
    INST_LE,
    INST_GE,
    INST_ASSIGN,
    INST_JMP,
    INST_IF,
    INST_PUTS,
    INST_INCR,
    INST_DECR,
    INST_SET_TYPE,
    INST_GET_VAR,
    INST_DUMP_STACK,
    INST_DUMP_DATA_AREA
};

class Inst {
    
    INST_TYPE type;
    Data operand;
    
    public:
        Inst(INST_TYPE, Data);
        INST_TYPE get_type();
        Data get_operand();
        static std::string inst_type_as_str(INST_TYPE);

};

enum EXIT_CODE {
    OK,
    STACK_OVERFLOW,
    STACK_UNDERFLOW,
    DIVISION_BY_ZERO,
    NOT_IMPLEMENTED,
    CHANGE_CONST_TYPE,
    CHANGE_CONST_VAL,
    VAR_NOT_DEFINEDED,
    TYPE_MISMATCH,
    ILLEGAL_INST
};

struct EHandler {
    EHandler(EXIT_CODE, Inst);
};

class VM {
    protected:
        std::vector<Data> Stack;
        std::map<std::string, Data> data_area;

        EXIT_CODE exec_inst(Inst);

    public:
        VM(std::vector<Inst>);
        void eval();
};

#endif