#include <iostream>
#include <vector>
#include "inc/vm.h"
#include "inc/data.h"

int main(int argc, char **argv) {
    std::vector<Inst> program = {   
                                    {INST_PUSH, Data("a", VAR_UNDEFINED, "")},
                                    {INST_SET_TYPE, Data("", VAR_UNDEFINED, "int")},
                                    {INST_PUSH, Data("", VAR_INT, "8")},
                                    {INST_ASSIGN},

                                    {INST_PUSH, Data("b", VAR_UNDEFINED, "")},
                                    {INST_SET_TYPE, Data("", VAR_UNDEFINED, "int")},
                                    {INST_PUSH, Data("", VAR_INT, "15")},
                                    {INST_ASSIGN},

                                    {INST_IF, Data("", VAR_UNDEFINED, "IF-1")},

                                    {INST_PUSH, Data("a", VAR_UNDEFINED, "")},
                                    {INST_GET_VAR},

                                    {INST_PUSH, Data("b", VAR_UNDEFINED, "")},
                                    {INST_GET_VAR},

                                    {INST_LS},

                                    {INST_BEGIN, Data("", VAR_UNDEFINED, "IFBEG-1")},

                                    {INST_PUSH, Data("a", VAR_UNDEFINED, "")},
                                    {INST_GET_VAR},

                                    {INST_INCR},

                                    {INST_END, Data("", VAR_UNDEFINED, "IFEND-1")},
                                    
                                    {INST_ELSE, Data("", VAR_UNDEFINED, "ELSE-1")},

                                    {INST_BEGIN, Data("", VAR_UNDEFINED, "ELSEBEG-1")},

                                    {INST_PUSH, Data("b", VAR_UNDEFINED, "")},
                                    {INST_GET_VAR},

                                    {INST_INCR},

                                    {INST_END, Data("", VAR_UNDEFINED, "ELSEEND-1")},

                                    {INST_PUSH, Data("", VAR_STRING, "Hello, World!\n")},
                                    {INST_PUTS},

                                    {INST_PUSH, Data("a", VAR_UNDEFINED, "")},
                                    {INST_GET_VAR},
                                    {INST_PUTS},

                                    {INST_PUSH, Data("", VAR_STRING, "\n")},
                                    {INST_PUTS},

                                    {INST_PUSH, Data("b", VAR_UNDEFINED, "")},
                                    {INST_GET_VAR},
                                    {INST_PUTS},
                                    {INST_EXIT}
                                };

    std::vector<Inst> fib = {
                                {INST_PUSH, Data("a", VAR_UNDEFINED, "")},
                                {INST_SET_TYPE, Data("", VAR_UNDEFINED, "int")},
                                {INST_PUSH, Data("", VAR_INT, "0")},
                                {INST_ASSIGN},

                                {INST_PUSH, Data("b", VAR_UNDEFINED, "")},
                                {INST_SET_TYPE, Data("", VAR_UNDEFINED, "int")},
                                {INST_PUSH, Data("", VAR_INT, "1")},
                                {INST_ASSIGN},
                                
                                {INST_PUSH, Data("i", VAR_UNDEFINED, "")},
                                {INST_SET_TYPE, Data("", VAR_UNDEFINED, "int")},
                                {INST_PUSH, Data("", VAR_INT, "0")},
                                {INST_ASSIGN},

                                {INST_PUSH, Data("", VAR_STRING, "Fibonacci nums:\n")},
                                {INST_PUTS},

                                {INST_WHILE, Data("", VAR_UNDEFINED, "WHILE-1")},

                                {INST_PUSH, Data("i", VAR_UNDEFINED, "")},
                                {INST_GET_VAR},

                                {INST_PUSH, Data("", VAR_INT, "15")},

                                {INST_LS},

                                {INST_BEGIN, Data("", VAR_UNDEFINED, "WHILEBEG-1")},

                                {INST_PUSH, Data("b", VAR_UNDEFINED, "")},
                                {INST_GET_VAR},

                                {INST_PUSH, Data("a", VAR_UNDEFINED, "")},
                                {INST_GET_VAR},

                                {INST_PUSH, Data("b", VAR_UNDEFINED, "")},
                                {INST_GET_VAR},
                                
                                {INST_PLUS},

                                {INST_ASSIGN},

                                {INST_PUSH, Data("a", VAR_UNDEFINED, "")},
                                {INST_GET_VAR},

                                {INST_PUTS},

                                {INST_PUSH, Data("b", VAR_UNDEFINED, "")},
                                {INST_GET_VAR},

                                {INST_PUSH, Data("a", VAR_UNDEFINED, "")},
                                {INST_GET_VAR},

                                {INST_MINUS},

                                {INST_ASSIGN},

                                {INST_PUSH, Data("i", VAR_UNDEFINED, "")},
                                {INST_GET_VAR},

                                {INST_INCR},

                                {INST_PUSH, Data("", VAR_UNDEFINED, " ")},
                                {INST_PUTS},

                                {INST_END, Data("", VAR_UNDEFINED, "WHILEEND-1")},
                                
                                {INST_PUSH, Data("", VAR_UNDEFINED, "\n")},
                                {INST_PUTS},

                                {INST_EXIT}
                            };

    VM Virtual_Machine(fib);
    Virtual_Machine.eval();
    return 0;
}