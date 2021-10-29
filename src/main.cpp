#include <iostream>
#include <vector>
#include "inc/preprocessor.h"
#include "inc/lexer.h"
#include "inc/parser.h"
#include "inc/compiler.h"
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

    if (argc < 3) {
        std::cerr << "ERROR: Too few arguments" << std::endl;
        usage(argv);
        exit(-1);
    } 

    if (argv[1][0] == '-') {
        if (argv[1][1] == 'c') {
            
            if (argc < 4) {
                std::cerr << "ERROR: Too few arguments" << std::endl;
                usage(argv);
                exit(-1);
            } 

            Preproc preprocessor(argv[2]);

            std::string source_code = preprocessor.preprocess();
    
            Tokenizer tokenizer(source_code);
            
            Parser parser(tokenizer.tokenize());

            Compiler compiler(parser.parse(), argv[3]);
            compiler.compile();

        } else if (argv[1][1] == 'v') {

            Compiler compiler(argv[2]);

            VM Virtual_Machine(compiler.decompile());
            Virtual_Machine.eval();

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

    } else {

        std::cerr << "ERROR: Subcommand was expected" << std::endl;
        usage(argv);
        exit(3);

    }

    return 0;
}