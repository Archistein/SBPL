#include <iostream>
#include "inc/vm.h"
#include "inc/data.h"

Inst::Inst(INST_TYPE type, Data operand) {
    this->type = type;
    this->operand = operand;
}

INST_TYPE Inst::get_type() {
    return this->type;
}

Data Inst::get_operand() {
    return this->operand;
}

EXIT_CODE VM::exec_inst(Inst instruction) {
    switch(instruction.get_type()) {

        case INST_PUSH:
            this->Stack.push_back(instruction.get_operand());
            if (!instruction.get_operand().get_ident().get_name().empty()) {
                instruction.get_operand().get_ident().set_adress(Ident_table.size());
                this->Ident_table.push_back(instruction.get_operand().get_ident().get_name());
            }
            return OK;

        case INST_POP:
            if (this->Stack.size() < 1)
                return STACK_UNDERFLOW;

            this->Stack.pop_back();

            return OK;

        case INST_PLUS:
            if (this->Stack.size() < 2)
                return STACK_UNDERFLOW;
            
            return NOT_IMPLEMENTED;

        case INST_MINUS:
            return NOT_IMPLEMENTED;

        case INST_MUL:
            return NOT_IMPLEMENTED;

        case INST_DIV:
            return NOT_IMPLEMENTED;

        case INST_EQ:
            return NOT_IMPLEMENTED;

        case INST_GT:
            return NOT_IMPLEMENTED;

        case INST_LS:
            return NOT_IMPLEMENTED;

        case INST_LE:
            return NOT_IMPLEMENTED;

        case INST_GE:
            return NOT_IMPLEMENTED;

        case INST_ASSIGN:
            if (this->Stack.size() < 2)
                return STACK_UNDERFLOW;

            if (this->Stack[this->Stack.size()-2].get_ident().get_name().empty())
                return CHANGE_CONST_TYPE;
            
            if (this->Stack[this->Stack.size()-2].get_type() != this->Stack[this->Stack.size()-1].get_type())
                return TYPE_MISMATCH;

            this->Stack[this->Stack.size()-2].set_val(this->Stack[Stack.size()-1].get_val());
            this->data_area.push_back(this->Stack[this->Stack.size()-2]);

            this->exec_inst(Inst(INST_POP, Data()));
            this->exec_inst(Inst(INST_POP, Data()));

            return OK;
        
        case INST_JMP:
            return NOT_IMPLEMENTED;

        case INST_IF:
            return NOT_IMPLEMENTED;

        case INST_PUTS:
            return NOT_IMPLEMENTED;

        case INST_INCR:
            return NOT_IMPLEMENTED;

        case INST_DECR:
            return NOT_IMPLEMENTED;

        case INST_SET_TYPE:
            if (this->Stack.size() < 1)
                return STACK_UNDERFLOW;
            
            if (this->Stack[this->Stack.size()-1].get_ident().get_name().empty())
                return CHANGE_CONST_TYPE;

            VAR_TYPE temp;

            if (instruction.get_operand().get_val() == "int")
                /* TODO: implement isInt() */
                temp = VAR_INT;
            else if (instruction.get_operand().get_val() == "double")
                /* TODO: implement isDouble() */
                temp = VAR_DOUBLE;
            else if (instruction.get_operand().get_val() == "char")
                /* TODO: implement isChar() */
                temp = VAR_CHAR;
            else if (instruction.get_operand().get_val() == "string")
                temp = VAR_STRING;
            else 
                return ILLEGAL_INST;

            this->Stack[this->Stack.size()-1].set_type(temp);

            return OK;

        case INST_DUMP_STACK:
            std::cout << "Stack:" << std::endl;
            if (this->Stack.size())
                for(Data d : Stack)
                    std::cout   << "{IDENT:" << d.get_ident().get_name() 
                                << " TYPE:" << d.get_type() 
                                << " VALUE:" << d.get_val() 
                                << "}" 
                                << std::endl; 
            else
                std::cout << "(empty)" << std::endl;

            return OK;

        case INST_DUMP_DATA_AREA:
            std::cout << "Data area:" << std::endl;
            if (this->data_area.size())
                for(Data d : data_area)
                    std::cout   << "{IDENT:" << d.get_ident().get_name() 
                                << " TYPE:" << d.get_type() 
                                << " VALUE:" << d.get_val() 
                                << "}" 
                                << std::endl; 
            else
                std::cout << "(empty)" << std::endl;

            return OK;

    }
    return ILLEGAL_INST;
}

VM::VM(std::vector<Inst> program) {
    for(Inst curr_inst : program) {
        this->exec_inst(curr_inst);
    }
    std::cout << "\nDEBUG INFO: program has terminated" << std::endl;
}