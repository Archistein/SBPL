#ifndef _INST_H
#define _INST_H

#include <string>
#include <vector>
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
        //static std::string inst_type_as_str(INST_TYPE); TODO: implement

};

enum EXIT_CODE {
    OK,
    STACK_OVERFLOW,
    STACK_UNDERFLOW,
    DIVISION_BY_ZERO,
    NOT_IMPLEMENTED,
    CHANGE_CONST_TYPE,
    TYPE_MISMATCH,
    ILLEGAL_INST
};

class VM {
    protected:
        std::vector<Data> Stack;
        std::vector<Data> data_area;
        std::vector<IDENT> Ident_table;

        EXIT_CODE exec_inst(Inst);

    public:
        VM(std::vector<Inst>);
        void eval();
};

#endif