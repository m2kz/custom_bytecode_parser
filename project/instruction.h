//
// Created by michal on 09.09.17.
//

#ifndef PROJECT_INSTRUCTION_H
#define PROJECT_INSTRUCTION_H

#include <functional>
#include <iostream>
#include <cstdarg>
#include "registers.h"

struct Instruction {
    std::string name;
    std::string opcode;
    std::string param_list;
    std::function<void(int64_t constant,
                       VMRegister &vm_register)> con_reg;
    std::function<void(VMRegister &vm_register1,
                       VMRegister &vm_register2, VMRegister &vm_register3)> reg_reg_reg;
    std::function<void(VMRegister &vm_register1,
                       VMRegister &vm_register2)> reg_reg;
};


static std::vector<Instruction> instructions{{"mov",       "000",    "RR"},
                                             {"add",       "010001", "RRR"},
                                             {"sub",       "010010", "RRR"},
                                             {"div",       "010011", "RRR"},
                                             {"mod",       "010100", "RRR"},
                                             {"mul",       "010101", "RRR"},
                                             {"compare",   "01100",  "RRR"},
                                             {"hlt",       "10110",  ""},
                                             {"loadConst", "001",    "CR", [](int64_t constant,
                                                                              VMRegister &vm_register) { vm_register.value = constant; printf("works"); }}
};

#endif //PROJECT_OPCODES_H
