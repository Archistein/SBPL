#include <iostream>
#include <vector>
#include "inc/preprocessor.h"
#include "inc/lexer.h"
#include "inc/vm.h"
#include "inc/data.h"

void usage(char **argv) {
    std::cout << "Usage:" << std::endl;
    std::cout << "      " << argv[0] << " [SUBC] <INPUT> [OUTPUT]" << std::endl;
    std::cout << "Subcommands:" << std::endl;
    std::cout << "      -c to compile the program" << std::endl;
    std::cout << "      -v to execute the program" << std::endl;
    std::cout << "      -E to interrupt compilation after preprocessing (output is required)" << std::endl;
}

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
                                {INST_PRINT},

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

                                {INST_PRINT},

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
                                {INST_PRINT},

                                {INST_END, Data("", VAR_UNDEFINED, "WHILEEND-1")},
                                
                                {INST_PUSH, Data("", VAR_UNDEFINED, "\n")},
                                {INST_PRINT},

                                {INST_EXIT}
                            };
    
    if (argc < 3) {
        std::cerr << "ERROR: Too few arguments" << std::endl;
        usage(argv);
        exit(-1);
    }
    
    if (argv[1][0] == '-') {
        if (argv[1][1] == 'c') {
            
            Preproc preprocessor(argv[2]);

            std::string source_code = preprocessor.preprocess();

            Tokenizer tokenizer(source_code);
            tokenizer.tokenize();

            exit(NOT_IMPLEMENTED);

        } else if (argv[1][1] == 'v') {

            std::cerr << "Execution not implemented" << std::endl;
            exit(NOT_IMPLEMENTED);

        } else if (argv[1][1] == 'E') {

            if (argc < 4)  {
                std::cerr << "ERROR: Too few arguments" << std::endl;
                usage(argv);
                exit(-1);
            }   
                
            Preproc preprocessor(argv[2], argv[3]);
                
            if (preprocessor.preprocess().empty()) {
                std::cerr << "ERROR: " << argv[2] << " doesn't exists" << std::endl;
            }

        } else {

            std::cerr << "ERROR: Unrecognized subcommand" << std::endl;
            usage(argv);
            exit(-2);

        }

    }

    //VM Virtual_Machine(fib);
    //Virtual_Machine.eval();
    return 0;
}