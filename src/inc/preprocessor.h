#ifndef _PREPROCESSOR_H
#define _PREPROCESSOR_H

#include <string>

class Preproc {
    std::string input_file;
    std::string output_file;

    public:
        Preproc(std::string);
        Preproc(std::string, std::string);
        std::string preprocess();
};

#endif
