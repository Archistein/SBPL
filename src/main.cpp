#include <iostream>
#include <vector>
#include "inc/vm.h"
#include "inc/data.h"

int main(int argc, char **argv) {
    std::vector<Inst> program = {   
                                    {INST_PUSH, Data("a", VAR_UNDEFINED, "")},
                                    {INST_SET_TYPE, Data("", VAR_UNDEFINED, "int")},
                                    {INST_PUSH, Data("", VAR_INT, "8")},
                                    {INST_ASSIGN, Data()},

                                    {INST_PUSH, Data("b", VAR_UNDEFINED, "")},
                                    {INST_SET_TYPE, Data("", VAR_UNDEFINED, "int")},
                                    {INST_PUSH, Data("", VAR_INT, "15")},
                                    {INST_ASSIGN, Data()},

                                    {INST_PUSH, Data("a", VAR_UNDEFINED, "")},
                                    {INST_GET_VAR, Data()},

                                    {INST_PUSH, Data("b", VAR_UNDEFINED, "")},
                                    {INST_GET_VAR, Data()},

                                    {INST_DUMP_STACK, Data()},
                                    {INST_DUMP_DATA_AREA, Data()},
                                };
    VM eval(program);
    return 0;
}