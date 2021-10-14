#include <string>
#include "inc/data.h"

IDENT::IDENT() {
    this->name = "";
    this->adress = -1;
}

IDENT::IDENT(std::string name) {
    this->name = name;
}

void IDENT::set_adress(int adress) {
    this->adress = adress;
}

std::string IDENT::get_name() {
    return this->name;
}

int IDENT::get_adress() {
    return this->adress;
}

Data::Data() {
    this->identificator = IDENT();
    this->type = VAR_UNDEFINED;
    this->value = "";
}

Data::Data(IDENT identificator, VAR_TYPE type, std::string value) {
    this->identificator = identificator;
    this->type = type;
    this->value = value;
}

IDENT Data::get_ident() {
    return this->identificator;
}

VAR_TYPE Data::get_type() {
    return this->type;
}

std::string Data::get_val() {
    return this->value;
}

void Data::set_ident(IDENT identificator) {
    this->identificator = identificator;
}

void Data::set_type(VAR_TYPE type) {
    this->type = type;
}

void Data::set_val(std::string value) {
    this->value = value;
}