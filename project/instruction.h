//
// Created by michal on 09.09.17.
//

#ifndef PROJECT_INSTRUCTION_H
#define PROJECT_INSTRUCTION_H

#include <functional>
#include <iostream>
#include <memory>
#include <iomanip>
#include "registers.h"
#include "argument.h"
#include "label.h"

struct Instruction {
    std::string name;
    std::string opcode;
    std::string param_list;
    std::function<void(int64_t, Label &label, std::vector<std::shared_ptr<Argument>> argument)> implementation;
    bool if_return = false;

    ~Instruction() {
        name = "";
        opcode = "";
        param_list = "";
    }
};

static std::vector<Instruction> instructions{{"mov",          "000",    "RR",  [](int64_t, Label &label,
                                                                                  std::vector<std::shared_ptr<Argument>> argument) {
    argument[1].get()->value = argument[0].get()->value;
}},
                                             {"add",          "010001", "RRR", [](int64_t, Label &,
                                                                                  std::vector<std::shared_ptr<Argument>> argument) {
                                                 argument[2].get()->value =
                                                         argument[0].get()->value + argument[1].get()->value;
                                             }
                                             },
                                             {"sub",          "010010", "RRR", [](int64_t, Label &,
                                                                                  std::vector<std::shared_ptr<Argument>> argument) {
                                                 argument[2].get()->value =
                                                         argument[0].get()->value - argument[1].get()->value;
                                             }},
                                             {"div",          "010011", "RRR", [](int64_t, Label &,
                                                                                  std::vector<std::shared_ptr<Argument>> argument) {
                                                 argument[2].get()->value =
                                                         argument[0].get()->value / argument[1].get()->value;
                                             }},
                                             {"mod",          "010100", "RRR", [](int64_t, Label &,
                                                                                  std::vector<std::shared_ptr<Argument>> argument) {
                                                 argument[2].get()->value =
                                                         argument[0].get()->value % argument[1].get()->value;
                                             }},
                                             {"mul",          "010101", "RRR", [](int64_t, Label &,
                                                                                  std::vector<std::shared_ptr<Argument>> argument) {
                                                 argument[2].get()->value =
                                                         argument[0].get()->value * argument[1].get()->value;
                                             }},
                                             {"compare",      "01100",  "RRR", [](int64_t, Label &,
                                                                                  std::vector<std::shared_ptr<Argument>> argument) {
                                                 if (argument[0].get()->value < argument[1].get()->value)
                                                     argument[2].get()->value = -1;
                                                 if (argument[0].get()->value > argument[1].get()->value)
                                                     argument[2].get()->value = 1;
                                                 if (argument[0].get()->value == argument[1].get()->value)
                                                     argument[2].get()->value = 0;
                                             }},
                                             {"hlt",          "10110",  "",    [](int64_t constant, Label &,
                                                                                  std::vector<std::shared_ptr<Argument>> argument) {

                                                 exit(1);

                                             }
                                             },
                                             {"loadConst",    "001",    "CR",  [](int64_t constant, Label &,
                                                                                  std::vector<std::shared_ptr<Argument>> argument) {
                                                 argument[0].get()->value = constant;
                                             }
                                             },
                                             {"consoleWrite", "10011",  "R",   [](int64_t constant, Label &,
                                                                                  std::vector<std::shared_ptr<Argument>> argument) {
                                                 std::cout << std::hex << std::setw(16) << std::setfill('0')
                                                           << argument[0].get()->value << std::endl;
                                             }
                                             },
                                             {"jump",         "01101",  "L",   [](int64_t constant, Label &label,
                                                                                  std::vector<std::shared_ptr<Argument>> argument) {
                                                 label.set_if_jump(true);
                                             }
                                             },
                                             {"jumpEqual",    "01110",  "LRR", [](int64_t constant, Label &label,
                                                                                  std::vector<std::shared_ptr<Argument>> argument) {
                                                 if (argument[0].get()->value == argument[1].get()->value)
                                                     label.set_if_jump(true);
                                                 if (argument[0].get()->value != argument[1].get()->value)
                                                     label.set_if_jump(false);
                                             }
                                             },
                                             {"consoleRead",  "10010",  "R",   [](int64_t constant, Label &label,
                                                                                  std::vector<std::shared_ptr<Argument>> argument) {
                                                 uint32_t value;
                                                 std::cout << "Give value" << std::endl;
                                                 std::cin >> value;
                                                 argument[0].get()->value = value;
                                             }
                                             },
                                             {"call",         "1100",   "L",   [](int64_t constant, Label &label,
                                                                                  std::vector<std::shared_ptr<Argument>> argument) {
                                                 label.set_if_function(true);
                                             }
                                             },
                                             {"ret",          "1101",   "",    [](int64_t constant, Label &label,
                                                                                  std::vector<std::shared_ptr<Argument>> argument) {

                                             }, true
                                             }

};

#endif //PROJECT_OPCODES_H
