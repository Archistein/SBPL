#include <iostream>
#include <vector>
#include <string>
#include "inc/parser.h"
#include "inc/lexer.h"
#include "inc/vm.h"

Parser::Parser(std::vector<Token> tokens) {
    this->tokens = tokens;
}

std::vector<Inst> Parser::parse() {
    std::vector<Inst> result;
    std::vector<INST_TYPE> inst_buffer;
    std::vector<int> if_unclosed;
    std::vector<int> if_closed;
    std::vector<int> else_unclosed;
    std::vector<int> else_closed;

    int if_count = -1;
    int while_count = -1;

    for(Token token : this->tokens) {
        switch (token.get_type()) {
            case TOKEN_IDENT:
                result.push_back(Inst(INST_PUSH, Data(token.get_value(), VAR_UNDEFINED, "")));
                break;
            case TOKEN_INT:
                result.push_back(Inst(INST_PUSH, Data("", VAR_INT, token.get_value())));
                break;
            case TOKEN_DOBULE:
                result.push_back(Inst(INST_PUSH, Data("", VAR_DOUBLE, token.get_value())));
                break;
            case TOKEN_CHAR:
                result.push_back(Inst(INST_PUSH, Data("", VAR_CHAR, token.get_value())));
                break;
            case TOKEN_STRING:
                result.push_back(Inst(INST_PUSH, Data("", VAR_STRING, token.get_value())));
                break;
            case TOKEN_SET_INT:
                result.push_back(Inst(INST_SET_TYPE, Data("", VAR_UNDEFINED, "int")));
                break;
            case TOKEN_SET_DOBULE:
                result.push_back(Inst(INST_SET_TYPE, Data("", VAR_UNDEFINED, "double")));
                break;
            case TOKEN_SET_CHAR:
                result.push_back(Inst(INST_SET_TYPE, Data("", VAR_UNDEFINED, "char")));
                break;
            case TOKEN_SET_STRING:
                result.push_back(Inst(INST_SET_TYPE, Data("", VAR_UNDEFINED, "string")));
                break;
            case TOKEN_POP:
                result.push_back(Inst(INST_POP));
                break;
            case TOKEN_DUP:
                result.push_back(Inst(INST_DUP));
                break;
            case TOKEN_PLUS:
                result.push_back(Inst(INST_PLUS));
                break;
            case TOKEN_MINUS:
                result.push_back(Inst(INST_MINUS));
                break;
            case TOKEN_MUL:
                result.push_back(Inst(INST_MUL));
                break;
            case TOKEN_DIV:
                result.push_back(Inst(INST_DIV));
                break;
            case TOKEN_EQ:
                result.push_back(Inst(INST_EQ));
                break;
            case TOKEN_GT:
                result.push_back(Inst(INST_GT));
                break;
            case TOKEN_LS:
                result.push_back(Inst(INST_LS));
                break;
            case TOKEN_LE:
                result.push_back(Inst(INST_LE));
                break;
            case TOKEN_GE:
                result.push_back(Inst(INST_GE));
                break;
            case TOKEN_ASSIGN:
                result.push_back(Inst(INST_ASSIGN));
                break;
            case TOKEN_SET_LABEL:
                result.push_back(Inst(INST_SET_LABEL));
                break;
            case TOKEN_IF:
                result.push_back(Inst(INST_IF, Data("", VAR_UNDEFINED, "IF-" + std::to_string(++if_count))));
                if_unclosed.push_back(if_count);
                inst_buffer.push_back(INST_IF);
                break;
            case TOKEN_ELSE:
                if (if_closed.size() == 0) {
                    std::cerr << "ERROR: TOKEN_ELSE (parser.cpp)" << std::endl;
                    exit(5);
                }
                inst_buffer.push_back(INST_ELSE);
                result.push_back(Inst(INST_IF, Data("", VAR_UNDEFINED, "ELSE-" + std::to_string(if_closed[( if_closed.size() > 0 ? if_closed.size() - 1 : 0 )]))));
                break;
            case TOKEN_WHILE:
                break;
            case TOKEN_BEGIN:
                if (inst_buffer[( inst_buffer.size() > 0 ? inst_buffer.size() - 1 : 0 )] == INST_IF)
                    result.push_back(Inst(INST_BEGIN, Data("", VAR_UNDEFINED, "IFBEG-" + std::to_string(if_count))));
                else if (inst_buffer[( inst_buffer.size() > 0 ? inst_buffer.size() - 1 : 0 )] == INST_ELSE)
                    result.push_back(Inst(INST_BEGIN, Data("", VAR_UNDEFINED, "ELSEBEG-" + std::to_string(if_closed[( if_closed.size() > 0 ? if_closed.size() - 1 : 0 )]))));
                break;
            case TOKEN_END:
                if (inst_buffer[inst_buffer.size()-1] == INST_IF) {
                    result.push_back(Inst(INST_END, Data("", VAR_UNDEFINED, "IFEND-" + std::to_string(if_unclosed[( if_unclosed.size() > 0 ? if_unclosed.size() - 1 : 0 )]))));
                    if_closed.push_back(if_unclosed[( if_unclosed.size() > 0 ? if_unclosed.size() - 1 : 0 )]);
                    if_unclosed.pop_back();
                } else if (inst_buffer[inst_buffer.size()-1] == INST_ELSE) {
                    result.push_back(Inst(INST_END, Data("", VAR_UNDEFINED, "ELSEEND-" + std::to_string(if_closed[( if_closed.size() > 0 ? if_closed.size() - 1 : 0 )]))));
                }
                inst_buffer.pop_back();
                break;
            case TOKEN_PRINT:
                result.push_back(Inst(INST_PRINT));
                break;
            case TOKEN_PUTS:
                result.push_back(Inst(INST_PUTS));
                break;
            case TOKEN_INCR:
                result.push_back(Inst(INST_INCR));
                break;
            case TOKEN_DECR:
                result.push_back(Inst(INST_DECR));
                break;
            case TOKEN_GET_VAR:
                result.push_back(Inst(INST_GET_VAR));
                break;
            case TOKEN_EXIT:
                result.push_back(Inst(INST_EXIT));
                break;
        }
    }
    
    result.push_back(Inst(INST_EXIT));

    for(Inst instruction : result) {
        if (instruction.get_type() == INST_IF || instruction.get_type() == INST_ELSE || instruction.get_type() == INST_BEGIN || instruction.get_type() == INST_END)
        std::cout << Inst::inst_type_as_str(instruction.get_type()) << "  " << instruction.get_operand().get_val() << std::endl;
    }

    return result;
}