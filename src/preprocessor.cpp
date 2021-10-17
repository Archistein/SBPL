#include <iostream>
#include <string>
#include <map>
#include <regex>
#include <fstream>
#include "inc/preprocessor.h"

Preproc::Preproc(std::string input) {
    this->input_file = input;
}

Preproc::Preproc(std::string input, std::string output) {
    this->input_file = input;
    this->output_file = output;
}

std::string Preproc::preprocess() {
    std::map<std::string, std::string> constans;
    std::string buffer;
    std::string result;

    std::ifstream file(input_file);

    if (!file.good())
        return "";

    std::string const_name;
    std::string const_value;

    int pointer;

    while(std::getline(file, buffer)) {
        const_name = "";
        const_value = "";

        pointer = -1;
        
        for (int i = 0;i < buffer.length();i++) {
            if (buffer[i] == '#') {
                if (buffer.substr(1,6) != "define") {
                    std::cerr << "ERROR: Unrecognized preprocessor directive" << std::endl;
                    exit(-4);
                }

                int spaces = 0;
                for (char c : buffer.substr(8, -1)) {
                    if (c == ' ') {
                        spaces += 1;
                        
                        if (spaces > 1)
                            break;

                        continue;
                    }

                    if (spaces == 0)
                        const_name += c;
                    else
                        const_value += c;
                }

                constans[const_name] = const_value;

                pointer = i;
                break;
            } 
            else if (buffer[i] == '/' && buffer[i+1] == '/') {
                pointer = i;
                break;
            }
        }

        if (pointer > 0)
            buffer = ( !buffer.empty() && buffer != "\n" ? buffer.substr(0, pointer) + '\n' : "" );
        else if (pointer == 0)
            buffer = "";
        else
            buffer = buffer + '\n';

        for (auto it = constans.begin();it != constans.end();it++) {
            buffer = std::regex_replace(buffer, std::regex(it->first), it->second);
        }
        
        result += buffer;
    }

    file.close();
    
    if (!this->output_file.empty()) {
        std::ofstream out(this->output_file);
        out << result;
        out.close();
    }

    return result;
}