#include <string>
#include "inc/data.h"

Data::Data() {
    this->identificator = "";
    this->type = VAR_UNDEFINED;
    this->value = "";
}

Data::Data(std::string identificator, VAR_TYPE type, std::string value) {
    this->identificator = identificator;
    this->type = type;
    this->value = value;
}

std::string Data::get_ident() {
    return this->identificator;
}

VAR_TYPE Data::get_type() {
    return this->type;
}

std::string Data::get_val() {
    return this->value;
}

void Data::set_ident(std::string identificator) {
    this->identificator = identificator;
}

void Data::set_type(VAR_TYPE type) {
    this->type = type;
}

void Data::set_val(std::string value) {
    this->value = value;
}