//
// Created by michal on 09.09.17.
//

#ifndef PROJECT_INSTRUCTION_H
#define PROJECT_INSTRUCTION_H

#include <functional>
#include <iostream>
#include "registers.h"

struct Instruction {
    std::string name;
    std::string opcode;
    std::string param_list;
    std::function<void(int64_t, int32_t, std::vector<VMRegister>)> implementation;

    ~Instruction() {
        name = "";
        opcode = "";
        param_list = "";
    }
};


static std::vector<Instruction> instructions{{"mov",          "000",    "RR"},
                                             {"add",          "010001", "RRR", [](int64_t, int32_t,
                                                                                  std::vector<VMRegister> vm_register) {
                                                 vm_register[2].value = vm_register[0].value + vm_register[1].value;
                                             }
                                             },
                                             {"sub",          "010010", "RRR", [](int64_t, int32_t,
                                                                                  std::vector<VMRegister> vm_register) {
                                                 vm_register[2].value = vm_register[0].value - vm_register[1].value;
                                             }},
                                             {"div",          "010011", "RRR", [](int64_t, int32_t,
                                                                                  std::vector<VMRegister> vm_register) {
                                                 vm_register[2].value = vm_register[0].value / vm_register[1].value;
                                             }},
                                             {"mod",          "010100", "RRR", [](int64_t, int32_t,
                                                                                  std::vector<VMRegister> vm_register) {
                                                 vm_register[2].value = vm_register[0].value % vm_register[1].value;
                                             }},
                                             {"mul",          "010101", "RRR", [](int64_t, int32_t,
                                                                                  std::vector<VMRegister> vm_register) {
                                                 vm_register[2].value = vm_register[0].value * vm_register[1].value;
                                             }},
                                             {"compare",      "01100",  "RRR", [](int64_t, int32_t,
                                                                                  std::vector<VMRegister> vm_register) {
                                                 if (vm_register[0].value < vm_register[1].value) vm_register[2].value = -1;
                                                 if (vm_register[0].value > vm_register[1].value) vm_register[2].value = 1;
                                                 if (vm_register[0].value == vm_register[1].value) vm_register[2].value = 0;
                                             }},
                                             {"hlt",          "10110",  ""},
                                             {"loadConst",    "001",    "CR",  [](int64_t constant, int32_t,
                                                                                  std::vector<VMRegister> vm_register) {
                                                 vm_register[0].value = constant;
                                             }
                                             },
                                             {"consoleWrite", "10011",  "R",   [](int64_t constant, int32_t,
                                                                                  std::vector<VMRegister> vm_register) {
                                                 std::cout << vm_register[0].value << std::endl;
                                             }
                                             }
};


#endif //PROJECT_OPCODES_H
