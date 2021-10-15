#include <iostream>
#include <map>
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

std::string Inst::inst_type_as_str(INST_TYPE instruction) {
    switch(instruction) {
        case INST_PUSH:
            return "INST_PUSH";
        case INST_POP:
            return "INST_POP";
        case INST_PLUS:
            return "INST_PLUS";
        case INST_MINUS:
            return "INST_MINUS";
        case INST_MUL:
            return "INST_MUL";
        case INST_DIV:
            return "INST_DIV";
        case INST_EQ:
            return "INST_EQ";
        case INST_GT:
            return "INST_GT";
        case INST_LS:
            return "INST_LS";
        case INST_LE:
            return "INST_LE";
        case INST_GE:
            return "INST_GE";
        case INST_ASSIGN:
            return "INST_ASSIGN";
        case INST_JMP:
            return "INST_JMP";
        case INST_IF:
            return "INST_IF";
        case INST_PUTS:
            return "INST_PUTS";
        case INST_INCR:
            return "INST_INCR";
        case INST_DECR:
            return "INST_DECR";
        case INST_SET_TYPE:
            return "INST_SET_TYPE";
        case INST_GET_VAR:
            return "INST_GET_VAR";
        case INST_DUMP_STACK:
            return "INST_DUMP_STACK";
        case INST_DUMP_DATA_AREA:
            return "INST_DUMP_DATA_AREA";
        default:
            return "UNRECOGNIZED_INST";
    }
}

EXIT_CODE VM::exec_inst(Inst instruction) {
    switch(instruction.get_type()) {

        case INST_PUSH:
            this->Stack.push_back(instruction.get_operand());

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
        {
            if (this->Stack.size() < 2)
                return STACK_UNDERFLOW;

            if (this->Stack[this->Stack.size()-2].get_type() != this->Stack[this->Stack.size()-1].get_type())
                return TYPE_MISMATCH;

            std::string left_operand = this->Stack[this->Stack.size()-2].get_val(),
                        right_operand = this->Stack[this->Stack.size()-1].get_val();

            bool flag = false;

            switch (this->Stack[this->Stack.size()-2].get_type()) {
                case VAR_INT:
                    if (std::stoi(left_operand) == std::stoi(right_operand))
                        flag = true;
                    break;
                case VAR_DOUBLE:
                    if (std::stod(left_operand) == std::stod(right_operand))
                        flag = true;
                    break;
                default:
                    if (left_operand == right_operand)
                        flag = true;
                    break;
            }  

            if (flag)
                this->exec_inst(Inst(INST_PUSH, Data("", VAR_INT, "1")));
            else
                this->exec_inst(Inst(INST_PUSH, Data("", VAR_INT, "0"))); 

            return OK;
        }

        case INST_GT:
        {
            if (this->Stack.size() < 2)
                return STACK_UNDERFLOW;

            if (this->Stack[this->Stack.size()-2].get_type() != this->Stack[this->Stack.size()-1].get_type())
                return TYPE_MISMATCH;
            
            std::string left_operand = this->Stack[this->Stack.size()-2].get_val(),
                        right_operand = this->Stack[this->Stack.size()-1].get_val();

            bool flag = false;

            switch (this->Stack[this->Stack.size()-2].get_type()) {
                case VAR_INT:
                    if (std::stoi(left_operand) > std::stoi(right_operand))
                        flag = true;
                    break;
                case VAR_DOUBLE:
                    if (std::stod(left_operand) > std::stod(right_operand))
                        flag = true;
                    break;
                default:
                    if (left_operand > right_operand)
                        flag = true;
                    break;
            }  

            if (flag)
                this->exec_inst(Inst(INST_PUSH, Data("", VAR_INT, "1")));
            else
                this->exec_inst(Inst(INST_PUSH, Data("", VAR_INT, "0")));

            return OK;
        }

        case INST_LS:
        {
            if (this->Stack.size() < 2)
                return STACK_UNDERFLOW;

            if (this->Stack[this->Stack.size()-2].get_type() != this->Stack[this->Stack.size()-1].get_type())
                return TYPE_MISMATCH;

            std::string left_operand = this->Stack[this->Stack.size()-2].get_val(),
                        right_operand = this->Stack[this->Stack.size()-1].get_val();

            bool flag = false;

            switch (this->Stack[this->Stack.size()-2].get_type()) {
                case VAR_INT:
                    if (std::stoi(left_operand) < std::stoi(right_operand))
                        flag = true;
                    break;
                case VAR_DOUBLE:
                    if (std::stod(left_operand) < std::stod(right_operand))
                        flag = true;
                    break;
                default:
                    if (left_operand < right_operand)
                        flag = true;
                    break;
            }  

            if (flag)
                this->exec_inst(Inst(INST_PUSH, Data("", VAR_INT, "1")));
            else
                this->exec_inst(Inst(INST_PUSH, Data("", VAR_INT, "0"))); 

            return OK;
        }

        case INST_LE:
        {
            if (this->Stack.size() < 2)
                return STACK_UNDERFLOW;
            
            if (this->Stack[this->Stack.size()-2].get_type() != this->Stack[this->Stack.size()-1].get_type())
                return TYPE_MISMATCH;

            std::string left_operand = this->Stack[this->Stack.size()-2].get_val(),
                        right_operand = this->Stack[this->Stack.size()-1].get_val();

            bool flag = false;

            switch (this->Stack[this->Stack.size()-2].get_type()) {
                case VAR_INT:
                    if (std::stoi(left_operand) <= std::stoi(right_operand))
                        flag = true;
                    break;
                case VAR_DOUBLE:
                    if (std::stod(left_operand) <= std::stod(right_operand))
                        flag = true;
                    break;
                default:
                    if (left_operand <= right_operand)
                        flag = true;
                    break;
            }  

            if (flag)
                this->exec_inst(Inst(INST_PUSH, Data("", VAR_INT, "1")));
            else
                this->exec_inst(Inst(INST_PUSH, Data("", VAR_INT, "0")));

            return OK;
        }

        case INST_GE:
        {
            if (this->Stack.size() < 2)
                return STACK_UNDERFLOW;

            if (this->Stack[this->Stack.size()-2].get_type() != this->Stack[this->Stack.size()-1].get_type())
                return TYPE_MISMATCH;

            std::string left_operand = this->Stack[this->Stack.size()-2].get_val(),
                        right_operand = this->Stack[this->Stack.size()-1].get_val();

            bool flag = false;

            switch (this->Stack[this->Stack.size()-2].get_type()) {
                case VAR_INT:
                    if (std::stoi(left_operand) >= std::stoi(right_operand))
                        flag = true;
                    break;
                case VAR_DOUBLE:
                    if (std::stod(left_operand) >= std::stod(right_operand))
                        flag = true;
                    break;
                default:
                    if (left_operand >= right_operand)
                        flag = true;
                    break;
            }  

            if (flag)
                this->exec_inst(Inst(INST_PUSH, Data("", VAR_INT, "1")));
            else
                this->exec_inst(Inst(INST_PUSH, Data("", VAR_INT, "0"))); 

            return OK;
        }

        case INST_ASSIGN:
            if (this->Stack.size() < 2)
                return STACK_UNDERFLOW;

            if (this->Stack[this->Stack.size()-2].get_ident().empty())
                return CHANGE_CONST_TYPE;
            
            if (this->Stack[this->Stack.size()-2].get_type() != this->Stack[this->Stack.size()-1].get_type())
                return TYPE_MISMATCH;

            this->Stack[this->Stack.size()-2].set_val(this->Stack[Stack.size()-1].get_val());
            this->data_area[this->Stack[this->Stack.size()-2].get_ident()] = this->Stack[this->Stack.size()-2];

            this->exec_inst(Inst(INST_POP, Data()));
            this->exec_inst(Inst(INST_POP, Data()));

            return OK;
        
        case INST_SET_LABEL:
            return NOT_IMPLEMENTED;

        case INST_JMP:
        {
            int adress = std::stoi(instruction.get_operand().get_val());
            if (adress < 0 || adress > this->program.size() - 1)
                return SEGMENTATION_FAULT;

            this->inst_pointer = adress;
            
            return OK;
        }

        case INST_JME:
        {   
            if (this->Stack.size() < 1)
                return STACK_UNDERFLOW;

            int adress = std::stoi(instruction.get_operand().get_val());
            if (adress < 0 || adress > this->program.size() - 1)
                return SEGMENTATION_FAULT;

            this->inst_pointer = adress;
            
            return OK;
        }

        case INST_IF:
            return NOT_IMPLEMENTED;

        case INST_ELSE:
            return NOT_IMPLEMENTED;

        case INST_WHILE:
            return NOT_IMPLEMENTED;

        case INST_BEGIN:
            return NOT_IMPLEMENTED;
        
        case INST_END:
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
            
            if (this->Stack[this->Stack.size()-1].get_ident().empty())
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
        
        case INST_GET_VAR:
            if (this->Stack.size() < 1)
                return STACK_UNDERFLOW;

            if (this->Stack[this->Stack.size()-1].get_ident().empty())
                return CHANGE_CONST_VAL;

            if (this->data_area.find(this->Stack[this->Stack.size()-1].get_ident()) == this->data_area.end())
                return VAR_NOT_DEFINEDED;
            
            this->exec_inst(Inst(INST_POP, Data()));
            this->exec_inst(Inst(INST_PUSH, this->data_area.find(this->Stack[this->Stack.size()].get_ident())->second));

            return OK;

        case INST_DUMP_STACK:
            std::cout << "Stack:" << std::endl;
            if (this->Stack.size())
                for (Data d : Stack)
                    std::cout   << "{IDENT:" << d.get_ident() 
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
                for (auto it = data_area.begin(); it != data_area.end(); it++)
                    std::cout   << "{IDENT:" << it->first 
                                << " TYPE:" << it->second.get_type() 
                                << " VALUE:" << it->second.get_val() 
                                << "}" 
                                << std::endl; 
            else
                std::cout << "(empty)" << std::endl;

            return OK;

    }
    return ILLEGAL_INST;
}

VM::VM(std::vector<Inst> program) : inst_pointer(0) {
    this->program = program;
}

void VM::eval() {

    while (inst_pointer < this->program.size()) {
        if (program[inst_pointer].get_type() == INST_IF || program[inst_pointer].get_type() == INST_ELSE || program[inst_pointer].get_type() == INST_WHILE || program[inst_pointer].get_type() == INST_BEGIN || program[inst_pointer].get_type() == INST_END)
            program[inst_pointer].get_operand().set_val(std::to_string(inst_pointer));

        EHandler(this->exec_inst(program[inst_pointer]), program[inst_pointer]);
        inst_pointer++;
    }

    std::cout << "\nDEBUG INFO: program has terminated" << std::endl;
}