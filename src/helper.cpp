#include <string>
#include <iostream>
#include "inc/helper.h"

bool helper::is_int(std::string str) {
    int start = ( str[0] == '-' ? 1 : 0 );

    for (int i = start;i < str.length();i++)
        if (!isdigit(str[i]))
            return false;

    return ( str.length() == 1 && start == 1 ? false : true );
} 

bool helper::is_double(std::string str) {
    int start = ( str[0] == '-' ? 1 : 0 );

    bool dot = false;

    for (int i = start;i < str.length();i++)
        if (!isdigit(str[i])) {
            if (str[i] == '.' && dot == false)
                dot = true;
            else
                return false;
        }
    
    return dot;
}