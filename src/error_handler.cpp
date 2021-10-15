#include <iostream>
#include "inc/vm.h"

EHandler::EHandler(EXIT_CODE code, Inst instruction) {
    switch (code) {
        case OK:
            return;
        case STACK_OVERFLOW:
            std::cerr << "ERROR: Stack overflow" << std::endl;
            break;
        case STACK_UNDERFLOW:
            std::cerr << "ERROR: Stack underflow" << std::endl;
            break;
        case DIVISION_BY_ZERO:
            std::cerr << "ERROR: Division by zero" << std::endl;
            break;
        case NOT_IMPLEMENTED:
            std::cerr << "ERROR: Instruction " << Inst::inst_type_as_str(instruction.get_type()) << " not implemented" << std::endl;
            break;
        case CHANGE_CONST_TYPE:
            std::cerr << "ERROR: Trying to change the type of a constant" << std::endl;
            break;
        case CHANGE_CONST_VAL:
            std::cerr << "ERROR: Trying to change the value of a constant" << std::endl;
            break;
        case VAR_NOT_DEFINEDED:
            std::cerr << "ERROR: Var {var} not definded" << std::endl;
            break;
        case TYPE_MISMATCH:
            std::cerr << "ERROR: Type {a} is not the same as type {b}" << std::endl;
            break;
        case ILLEGAL_INST:
            std::cerr << "ERROR: Illegal instruction {inst}" << std::endl;
            break;
    }
    exit(code);
}