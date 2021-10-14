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

class IDENT {
    
    std::string name;
    int adress;
    
    public:
        IDENT();
        IDENT(std::string);
        std::string get_name();
        int get_adress();
        void set_adress(int);

};

class Data {

    IDENT identificator;
    std::string value;
    VAR_TYPE type;

    public:
        Data();
        Data(IDENT, VAR_TYPE, std::string);
        void set_ident(IDENT);
        void set_type(VAR_TYPE);
        void set_val(std::string); 
        IDENT get_ident();
        VAR_TYPE get_type();
        std::string get_val(); 

};

#endif