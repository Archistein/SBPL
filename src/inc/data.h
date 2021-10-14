#ifndef _DATA_H
#define _DATA_H

#include <string>

enum VAR_TYPE {
    VAR_UNDEFINED,
    VAR_INT,
    VAR_DOUBLE,
    VAR_CHAR,
    VAR_STRING
};

class Data {

    std::string identificator;
    std::string value;
    VAR_TYPE type;

    public:
        Data();
        Data(std::string, VAR_TYPE, std::string);
        void set_ident(std::string);
        void set_type(VAR_TYPE);
        void set_val(std::string); 
        std::string get_ident();
        VAR_TYPE get_type();
        std::string get_val(); 

};

#endif