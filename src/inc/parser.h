#ifndef _PARSER_H
#define _PARSER_H

#include <vector>
#include "lexer.h"
#include "data.h"
#include "vm.h"

class Parser {
    std::vector<Token> tokens;

    public:
        Parser(std::vector<Token>);
        std::vector<Inst> parse();
};

#endif