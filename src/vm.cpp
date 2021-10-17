#include <iostream>
#include <map>
#include "inc/vm.h"
#include "inc/data.h"

#define DEBUG false

Inst::Inst(INST_TYPE type) {
    this->type = type;
    this->operand = Data();
}

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
        case INST_DUP:
            return "INST_DUP";
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
        case INST_JME:
            return "INST_JME";
        case INST_IF:
            return "INST_IF";
        case INST_ELSE:
            return "INST_ELSE";
        case INST_WHILE:
            return "INST_WHILE";
        case INST_BEGIN:
            return "INST_BEGIN";
        case INST_END:
            return "INST_END";
        case INST_PRINT:
            return "INST_PRINT";
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
        case INST_EXIT:
            return "INST_EXIT";
        case INST_DUMP_STACK:
            return "INST_DUMP_STACK";
        case INST_DUMP_DATA_AREA:
            return "INST_DUMP_DATA_AREA";
        default:
            return "UNRECOGNIZED_INST";
    }
}

void VM::set_labels_as_pointers() {
    
    while (inst_pointer < this->program.size()) {
        switch (program[inst_pointer].get_type()) {
            case INST_IF:
            case INST_ELSE:
            case INST_WHILE:
            case INST_BEGIN:
            case INST_END:
                this->labels[program[inst_pointer].get_operand().get_val()] = inst_pointer;
                break;
            default:
                break;
        }
        inst_pointer++;
    }
    
    inst_pointer = 0;
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

        case INST_DUP:
            if (this->Stack.size() < 1)
                return STACK_UNDERFLOW;

            this->exec_inst(Inst(INST_PUSH, this->Stack[this->Stack.size()-1]));

            return OK;

        case INST_PLUS:
            if (this->Stack.size() < 2)
                return STACK_UNDERFLOW;
            
            if (this->Stack[this->Stack.size()-2].get_type() != this->Stack[this->Stack.size()-1].get_type())
                return TYPE_MISMATCH;
            
            if (this->Stack[this->Stack.size()-2].get_type() == VAR_INT) 
                this->Stack[this->Stack.size()-2].set_val(std::to_string(std::stoi(this->Stack[this->Stack.size()-2].get_val()) + std::stoi(this->Stack[this->Stack.size()-1].get_val())));
            else if(this->Stack[this->Stack.size()-2].get_type() == VAR_DOUBLE)
                this->Stack[this->Stack.size()-2].set_val(std::to_string(std::stod(this->Stack[this->Stack.size()-2].get_val()) + std::stod(this->Stack[this->Stack.size()-1].get_val())));
            else
                return OP_NOT_DEF_FOR_THIS_TYPE;
            
            this->exec_inst(Inst(INST_POP));

            return OK;

        case INST_MINUS:
            if (this->Stack.size() < 2)
                return STACK_UNDERFLOW;
            
            if (this->Stack[this->Stack.size()-2].get_type() != this->Stack[this->Stack.size()-1].get_type())
                return TYPE_MISMATCH;
            
            if (this->Stack[this->Stack.size()-2].get_type() == VAR_INT) 
                this->Stack[this->Stack.size()-2].set_val(std::to_string(std::stoi(this->Stack[this->Stack.size()-2].get_val()) - std::stoi(this->Stack[this->Stack.size()-1].get_val())));
            else if(this->Stack[this->Stack.size()-2].get_type() == VAR_DOUBLE)
                this->Stack[this->Stack.size()-2].set_val(std::to_string(std::stod(this->Stack[this->Stack.size()-2].get_val()) - std::stod(this->Stack[this->Stack.size()-1].get_val())));
            else
                return OP_NOT_DEF_FOR_THIS_TYPE;
            
            this->exec_inst(Inst(INST_POP));

            return OK;

        case INST_MUL:
            if (this->Stack.size() < 2)
                return STACK_UNDERFLOW;
            
            if (this->Stack[this->Stack.size()-2].get_type() != this->Stack[this->Stack.size()-1].get_type())
                return TYPE_MISMATCH;
            
            if (this->Stack[this->Stack.size()-2].get_type() == VAR_INT) 
                this->Stack[this->Stack.size()-2].set_val(std::to_string(std::stoi(this->Stack[this->Stack.size()-2].get_val()) * std::stoi(this->Stack[this->Stack.size()-1].get_val())));
            else if(this->Stack[this->Stack.size()-2].get_type() == VAR_DOUBLE)
                this->Stack[this->Stack.size()-2].set_val(std::to_string(std::stod(this->Stack[this->Stack.size()-2].get_val()) * std::stod(this->Stack[this->Stack.size()-1].get_val())));
            else
                return OP_NOT_DEF_FOR_THIS_TYPE;
            
            this->exec_inst(Inst(INST_POP));

            return OK;

        case INST_DIV:
            if (this->Stack.size() < 2)
                return STACK_UNDERFLOW;
            
            if (this->Stack[this->Stack.size()-2].get_type() != this->Stack[this->Stack.size()-1].get_type())
                return TYPE_MISMATCH;

            if (this->Stack[this->Stack.size()-2].get_type() == VAR_INT) {
                if (this->Stack[this->Stack.size()-1].get_val() == "0")
                    return DIVISION_BY_ZERO;
                this->Stack[this->Stack.size()-2].set_val(std::to_string(std::stoi(this->Stack[this->Stack.size()-2].get_val()) / std::stoi(this->Stack[this->Stack.size()-1].get_val())));
            } else if(this->Stack[this->Stack.size()-2].get_type() == VAR_DOUBLE) {
                if (std::stod(this->Stack[this->Stack.size()-1].get_val()) == 0)
                    return DIVISION_BY_ZERO;
                this->Stack[this->Stack.size()-2].set_val(std::to_string(std::stod(this->Stack[this->Stack.size()-2].get_val()) / std::stod(this->Stack[this->Stack.size()-1].get_val())));
            } else
                return OP_NOT_DEF_FOR_THIS_TYPE;
            
            this->exec_inst(Inst(INST_POP));

            return OK;

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

            this->exec_inst(Inst(INST_POP));
            this->exec_inst(Inst(INST_POP));

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

            this->exec_inst(Inst(INST_POP));
            this->exec_inst(Inst(INST_POP));

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

            this->exec_inst(Inst(INST_POP));
            this->exec_inst(Inst(INST_POP));

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
            
            this->exec_inst(Inst(INST_POP));
            this->exec_inst(Inst(INST_POP));

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

            this->exec_inst(Inst(INST_POP));
            this->exec_inst(Inst(INST_POP));

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

            this->exec_inst(Inst(INST_POP));
            this->exec_inst(Inst(INST_POP));

            return OK;
        
        case INST_SET_LABEL:
            if (!instruction.get_operand().get_val().empty()) {
                if (this->labels.find(instruction.get_operand().get_val()) != this->labels.end())
                    return LABEL_EXISTS;

                this->labels[instruction.get_operand().get_val()] = this->inst_pointer;
            } else {
                if (this->Stack.size() < 1)
                    return STACK_UNDERFLOW;

                if (this->Stack[this->Stack.size()-1].get_ident().empty())
                    return ILLEGAL_INST;
                
                this->labels[this->Stack[this->Stack.size()-1].get_val()] = this->inst_pointer;

                this->exec_inst(Inst(INST_POP));
            }
            return OK;

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

            if (this->Stack[this->Stack.size()-1].get_val() != "0" || this->Stack[this->Stack.size()-1].get_val() != "")
                this->inst_pointer = adress;
            
            return OK;
        }

        case INST_IF:
            this->exec_inst(Inst(INST_SET_LABEL, instruction.get_operand()));
            return OK;

        case INST_ELSE:
            this->exec_inst(Inst(INST_SET_LABEL, instruction.get_operand()));
            return OK;

        case INST_WHILE:
            this->exec_inst(Inst(INST_SET_LABEL, instruction.get_operand()));
            return OK;

        case INST_BEGIN:
            if (this->Stack.size() < 1)
                return STACK_UNDERFLOW;
            
            this->exec_inst(Inst(INST_SET_LABEL, instruction.get_operand()));

            if (instruction.get_operand().get_val().substr(0, 2) == "IF") {
                if (this->Stack[this->Stack.size()-1].get_val() == "0" || this->Stack[this->Stack.size()-1].get_val() == "") {
                    if (this->labels.find("IFEND-" + instruction.get_operand().get_val().substr(6, -1)) == this->labels.end())
                        return COMPOUND_OP_NOT_CLOSED;
                    else
                        this->exec_inst(Inst(INST_JMP, Data("", VAR_UNDEFINED, std::to_string(this->labels.find("IFEND-" + instruction.get_operand().get_val().substr(6, -1))->second))));
                }
            }
            else if (instruction.get_operand().get_val().substr(0, 5) == "WHILE") {
                if (this->Stack[this->Stack.size()-1].get_val() == "0" || this->Stack[this->Stack.size()-1].get_val() == "") {
                    if (this->labels.find("WHILEEND-" + instruction.get_operand().get_val().substr(9, -1)) == this->labels.end())
                        return COMPOUND_OP_NOT_CLOSED;
                    else 
                        this->exec_inst(Inst(INST_JMP, Data("", VAR_UNDEFINED, std::to_string(this->labels.find("WHILEEND-" + instruction.get_operand().get_val().substr(9, -1))->second))));
                }  
            }
            
            return OK;
        
        case INST_END:            
            this->exec_inst(Inst(INST_SET_LABEL, instruction.get_operand()));

            if (instruction.get_operand().get_val().substr(0, 2) == "IF") {
                if (this->labels.find("ELSE-" + instruction.get_operand().get_val().substr(6, -1)) != this->labels.end())
                        this->exec_inst(Inst(INST_JMP, Data("", VAR_UNDEFINED, std::to_string(this->labels.find("ELSEEND-" + instruction.get_operand().get_val().substr(6, -1))->second))));
                return OK;
            }
            else if (instruction.get_operand().get_val().substr(0, 5) == "WHILE") {
                this->exec_inst(Inst(INST_JMP, Data("", VAR_UNDEFINED, std::to_string(this->labels.find("WHILE-" + instruction.get_operand().get_val().substr(9, -1))->second))));      
                return OK;
            }
            
            return OK;

        case INST_PRINT:
            if (this->Stack.size() < 1)
                return STACK_UNDERFLOW;

            std::cout << this->Stack[this->Stack.size()-1].get_val();
            
            return OK;

        case INST_PUTS:
            if (this->Stack.size() < 1)
                return STACK_UNDERFLOW;

            std::cout << this->Stack[this->Stack.size()-1].get_val() << std::endl;
            
            return OK;

        case INST_INCR:
            if (this->Stack.size() < 1)
                return STACK_UNDERFLOW;

            if (this->Stack[this->Stack.size()-1].get_ident().empty())
                return CHANGE_CONST_VAL;

            if (this->data_area.find(this->Stack[this->Stack.size()-1].get_ident()) == this->data_area.end())
                return VAR_NOT_DEFINEDED;

            if (this->Stack[this->Stack.size()-1].get_type() != VAR_INT)
                return OP_NOT_DEF_FOR_THIS_TYPE;

            this->exec_inst(Inst(INST_DUP));
            this->exec_inst(Inst(INST_PUSH, Data("", VAR_INT, "1")));
            this->exec_inst(Inst(INST_PLUS));
            this->exec_inst(Inst(INST_ASSIGN));
            
            return OK;

        case INST_DECR:
            if (this->Stack.size() < 1)
                return STACK_UNDERFLOW;

            if (this->Stack[this->Stack.size()-1].get_ident().empty())
                return CHANGE_CONST_VAL;

            if (this->data_area.find(this->Stack[this->Stack.size()-1].get_ident()) == this->data_area.end())
                return VAR_NOT_DEFINEDED;

            if (this->Stack[this->Stack.size()-1].get_type() != VAR_INT)
                return OP_NOT_DEF_FOR_THIS_TYPE;

            this->exec_inst(Inst(INST_DUP));
            this->exec_inst(Inst(INST_PUSH, Data("", VAR_INT, "1")));
            this->exec_inst(Inst(INST_MINUS));
            this->exec_inst(Inst(INST_ASSIGN));
            
            return OK;

        case INST_SET_TYPE:
            if (this->Stack.size() < 1)
                return STACK_UNDERFLOW;
            
            if (this->Stack[this->Stack.size()-1].get_ident().empty())
                return CHANGE_CONST_TYPE;

            VAR_TYPE temp;

            if (instruction.get_operand().get_val() == "int")
                temp = VAR_INT;
            else if (instruction.get_operand().get_val() == "double")
                temp = VAR_DOUBLE;
            else if (instruction.get_operand().get_val() == "char")
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
            
            this->exec_inst(Inst(INST_POP));
            this->exec_inst(Inst(INST_PUSH, this->data_area.find(this->Stack[this->Stack.size()].get_ident())->second));

            return OK;

        case INST_EXIT:
            this->state = false;
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
                for (auto it = this->data_area.begin(); it != this->data_area.end(); it++)
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
    
    this->set_labels_as_pointers();

    while (inst_pointer < this->program.size() || this->state == true) {
        EHandler(this->exec_inst(program[inst_pointer]), program[inst_pointer]);

        if (DEBUG) {
            std::cout << std::endl;
            std::cout << "Instruction: " << Inst::inst_type_as_str(program[inst_pointer].get_type()) << std::endl;
            this->exec_inst(Inst(INST_DUMP_STACK));
            std::cout << std::endl;
        }

        inst_pointer++;
    }

    if (DEBUG) 
        std::cout << "\nDEBUG INFO: program has terminated" << std::endl;
}