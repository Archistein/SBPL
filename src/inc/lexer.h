#ifndef _LEXER_H
#define _LEXER_H

#include <string>
#include <vector>

enum TOKEN_TYPE {
    TOKEN_IDENT,
    TOKEN_INT,
    TOKEN_DOBULE,
    TOKEN_CHAR,
    TOKEN_STRING,
    TOKEN_SET_INT,
    TOKEN_SET_DOBULE,
    TOKEN_SET_CHAR,
    TOKEN_SET_STRING,
    TOKEN_POP,
    TOKEN_DUP, 
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MUL,
    TOKEN_DIV,
    TOKEN_EQ,
    TOKEN_GT,
    TOKEN_LS,
    TOKEN_LE,
    TOKEN_GE,
    TOKEN_ASSIGN,
    TOKEN_SET_LABEL,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_WHILE,
    TOKEN_BEGIN,
    TOKEN_END,
    TOKEN_PRINT,
    TOKEN_PUTS,
    TOKEN_INCR,
    TOKEN_DECR,
    TOKEN_GET_VAR,
    TOKEN_EXIT
};

class Token {

    TOKEN_TYPE type;
    std::string value;

    public:
        Token(TOKEN_TYPE);
        Token(TOKEN_TYPE, std::string);
        TOKEN_TYPE get_type();
        std::string get_value();
};

class Tokenizer {

    std::string source;

    public:
        Tokenizer(std::string);
        std::vector<Token> tokenize();
};

#endif