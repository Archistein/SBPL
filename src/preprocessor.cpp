#include <iostream>
#include <string>
#include <map>
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

    std::ifstream file(input_file);

    if (!file.good())
        return "";

    std::string const_name;
    std::string const_value;

    while(std::getline(file, buffer)) {
        const_name = "";
        const_value = "";

        int pointer = -1;
        
        for (int i = 0;i < buffer.length();i++) {
            if (buffer[i] == '#') {
                if (buffer.substr(1,6) != "define") {
                    std::cerr << "ERROR: Unrecognized preprocessor directive" << std::endl;
                    exit(-4);
                }

                int flag = 0;
                for (char c : buffer.substr(8, -1)) {
                    if (c == ' ') {
                        flag += 1;
                        
                        if (flag > 1)
                            break;

                        continue;
                    }
                    
                    if (flag == 0)
                        const_name += c;
                    else
                        const_value += c;
                }

                constans[const_name] = const_value;

                pointer = i;
                break;
            }
            else if (buffer[i] == '/') {
                pointer = i;
                break;
            }
        }

        if (pointer >= 0)
            std::cout << buffer.substr(0, pointer) << std::endl;
        else
            std::cout << buffer << std::endl;
    }

    file.close();
    
    for (auto it = constans.begin(); it != constans.end(); it++)
                    std::cout   << "Name: " << it->first 
                                << " Value: " << it->second
                                << std::endl; 

    return "NOT_IMPLEMENTED";
}