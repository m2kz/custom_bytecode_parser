//
// Created by michal on 09.09.17.
//

#ifndef PROJECT_INSTRUCTION_H
#define PROJECT_INSTRUCTION_H

#include <functional>
#include <iostream>
#include <cstdarg>

struct Instruction {
    std::string name;
    std::string opcode;
    std::string param_list;
    std::function<void()> implementation;
};


static std::vector<Instruction> instructions{{"mov",       "000",    "RR"},
                                             {"add",       "010001", "RRR"},
                                             {"sub",       "010010", "RRR"},
                                             {"div",       "010011", "RRR"},
                                             {"mod",       "010100", "RRR"},
                                             {"mul",       "010101", "RRR"},
                                             {"compare",   "01100",  "RRR"},
                                             {"hlt",       "10110",  ""},
                                             {"loadConst", "001",    "CR"}};

#endif //PROJECT_OPCODES_H
