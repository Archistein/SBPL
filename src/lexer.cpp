#include <vector>
#include <iostream>
#include <algorithm>
#include "inc/lexer.h"
#include "inc/helper.h"

Token::Token(TOKEN_TYPE type) {
    this->type = type;
    this->value = "";
}

Token::Token(TOKEN_TYPE type, std::string value) {
    this->type = type;
    this->value = value;
}

TOKEN_TYPE Token::get_type() {
    return this->type;
}

std::string Token::get_value() {
    return this->value;
}

Tokenizer::Tokenizer(std::string source) {
    this->source = source;
}

std::vector<Token> Tokenizer::tokenize() {
    std::vector<Token> result;

    std::string word_buffer;    

    bool quotes = false;

    for (char c : this->source) {
        
        if (c == '\"' || c == '\'')
            quotes = !quotes;

        if ((c != ' ' && c != '\n' && c != '\t') || quotes)
            word_buffer += c;
        else {
            if (!word_buffer.empty()) {

                if (helper::is_int(word_buffer))
                    result.push_back(Token(TOKEN_INT, word_buffer));

                else if (helper::is_double(word_buffer))
                    result.push_back(Token(TOKEN_DOBULE, word_buffer));
                
                else if (word_buffer[0] == '\'')
                    result.push_back(Token(TOKEN_CHAR, word_buffer.substr(1, word_buffer.length()-2)));

                else if (word_buffer[0] == '\"')
                    result.push_back(Token(TOKEN_STRING, word_buffer.substr(1, word_buffer.length()-2)));

                else if (word_buffer == "int")
                    result.push_back(Token(TOKEN_SET_INT));
                
                else if (word_buffer == "double")
                    result.push_back(Token(TOKEN_SET_DOBULE));

                else if (word_buffer == "char")
                    result.push_back(Token(TOKEN_SET_CHAR));

                else if (word_buffer == "string")
                    result.push_back(Token(TOKEN_SET_STRING));

                else if (word_buffer == "pop")
                    result.push_back(Token(TOKEN_POP));
                
                else if (word_buffer == "dup")
                    result.push_back(Token(TOKEN_DUP));

                else if (word_buffer == "+")
                    result.push_back(Token(TOKEN_PLUS));

                else if (word_buffer == "-")
                    result.push_back(Token(TOKEN_MINUS));

                else if (word_buffer == "*")
                    result.push_back(Token(TOKEN_MUL));

                else if (word_buffer == "/")
                    result.push_back(Token(TOKEN_DIV));

                else if (word_buffer == "==")
                    result.push_back(Token(TOKEN_EQ));

                else if (word_buffer == ">")
                    result.push_back(Token(TOKEN_GT));

                else if (word_buffer == "<")
                    result.push_back(Token(TOKEN_LS));

                else if (word_buffer == "<=")
                    result.push_back(Token(TOKEN_LE));

                else if (word_buffer == ">=")
                    result.push_back(Token(TOKEN_GE));

                else if (word_buffer == "=")
                    result.push_back(Token(TOKEN_ASSIGN));
                
                else if (word_buffer == "goto")
                    result.push_back(Token(TOKEN_GOTO));

                else if (word_buffer == "if")
                    result.push_back(Token(TOKEN_IF));

                else if (word_buffer == "else")
                    result.push_back(Token(TOKEN_ELSE));

                else if (word_buffer == "while")
                    result.push_back(Token(TOKEN_WHILE));

                else if (word_buffer == "{")
                    result.push_back(Token(TOKEN_BEGIN));

                else if (word_buffer == "}")
                    result.push_back(Token(TOKEN_END));

                else if (word_buffer == "print")
                    result.push_back(Token(TOKEN_PRINT));

                else if (word_buffer == "puts")
                    result.push_back(Token(TOKEN_PUTS));

                else if (word_buffer == "++")
                    result.push_back(Token(TOKEN_INCR));

                else if (word_buffer == "--")
                    result.push_back(Token(TOKEN_DECR));

                else if (word_buffer == "exit")
                    result.push_back(Token(TOKEN_EXIT));

                else {
                    if (word_buffer[word_buffer.length() - 1] == '$') {
                        result.push_back(Token(TOKEN_IDENT, word_buffer.substr(0, word_buffer.length()-1)));
                        result.push_back(Token(TOKEN_GET_VAR));
                    } else if (word_buffer[word_buffer.length() - 1] == ':') {
                        result.push_back(Token(TOKEN_SET_LABEL, word_buffer.substr(0, word_buffer.length()-1)));
                    } else 
                        result.push_back(Token(TOKEN_IDENT, word_buffer));
                }
            }
            word_buffer = "";
        }

    }

    if (quotes) {
        std::cerr << "ERROR: Quotes are not closed" << std::endl;
        exit(-5);
    }

    return result;
}