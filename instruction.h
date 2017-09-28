//
// Created by michal on 09.09.17.
//

#ifndef PROJECT_INSTRUCTION_H
#define PROJECT_INSTRUCTION_H

#include <functional>
#include <iostream>
#include <memory>
#include <iomanip>
#include <thread>
#include <mutex>
#include <deque>
#include <pthread.h>
#include "memory.h"
#include "registers.h"
#include "argument.h"
#include "label.h"


void set_instruction_memory(Memory &memory);

void set_instruction_input_file(std::vector<char> &input_file);

extern Memory *instruction_memory;
extern std::vector<char> *instruction_input_file;
extern std::deque<std::pair<int, std::unique_ptr<std::mutex>>> keychain;
extern int threads_number;

struct Instruction {
    std::string name;
    std::string opcode;
    std::string param_list;
    std::function<void(int64_t, Label &label, std::vector<std::shared_ptr<Argument>> argument)> implementation;
    bool if_return = false;
    bool if_join = false;

    ~Instruction() {
        name = "";
        opcode = "";
        param_list = "";
    }
};

static std::vector<Instruction> instructions{{"mov",          "000",    "RR",   [](int64_t, Label &label,
                                                                                   std::vector<std::shared_ptr<Argument>> argument) {
    argument[1].get()->value = argument[0].get()->value;
}},
                                             {"add",          "010001", "RRR",  [](int64_t, Label &,
                                                                                   std::vector<std::shared_ptr<Argument>> argument) {
                                                 argument[2].get()->value =
                                                         argument[0].get()->value + argument[1].get()->value;
                                             }
                                             },
                                             {"sub",          "010010", "RRR",  [](int64_t, Label &,
                                                                                   std::vector<std::shared_ptr<Argument>> argument) {
                                                 argument[2].get()->value =
                                                         argument[0].get()->value - argument[1].get()->value;
                                             }},
                                             {"div",          "010011", "RRR",  [](int64_t, Label &,
                                                                                   std::vector<std::shared_ptr<Argument>> argument) {
                                                 argument[2].get()->value =
                                                         argument[0].get()->value / argument[1].get()->value;
                                             }},
                                             {"mod",          "010100", "RRR",  [](int64_t, Label &,
                                                                                   std::vector<std::shared_ptr<Argument>> argument) {
                                                 argument[2].get()->value =
                                                         argument[0].get()->value % argument[1].get()->value;
                                             }},
                                             {"mul",          "010101", "RRR",  [](int64_t, Label &,
                                                                                   std::vector<std::shared_ptr<Argument>> argument) {
                                                 argument[2].get()->value =
                                                         argument[0].get()->value * argument[1].get()->value;
                                             }},
                                             {"compare",      "01100",  "RRR",  [](int64_t, Label &,
                                                                                   std::vector<std::shared_ptr<Argument>> argument) {
                                                 if (argument[0].get()->value < argument[1].get()->value)
                                                     argument[2].get()->value = -1;
                                                 if (argument[0].get()->value > argument[1].get()->value)
                                                     argument[2].get()->value = 1;
                                                 if (argument[0].get()->value == argument[1].get()->value)
                                                     argument[2].get()->value = 0;
                                             }},
                                             {"hlt",          "10110",  "",     [](int64_t constant, Label &,
                                                                                   const std::vector<std::shared_ptr<Argument>> &argument) {
                                                 if (threads_number == 0)
                                                     exit(1);
                                                 else
                                                     pthread_exit(nullptr);

                                             }
                                             },
                                             {"loadConst",    "001",    "CR",   [](int64_t constant, Label &,
                                                                                   std::vector<std::shared_ptr<Argument>> argument) {
                                                 argument[0].get()->value = constant;
                                             }
                                             },
                                             {"consoleWrite", "10011",  "R",    [](int64_t constant, Label &,
                                                                                   std::vector<std::shared_ptr<Argument>> argument) {
                                                 std::cout << std::hex << std::setw(16) << std::setfill('0')
                                                           << argument[0].get()->value << std::endl;
                                             }
                                             },
                                             {"jump",         "01101",  "L",    [](int64_t constant, Label &label,
                                                                                   const std::vector<std::shared_ptr<Argument>> &argument) {
                                                 label.set_if_jump(true);
                                             }
                                             },
                                             {"jumpEqual",    "01110",  "LRR",  [](int64_t constant, Label &label,
                                                                                   std::vector<std::shared_ptr<Argument>> argument) {
                                                 if (argument[0].get()->value == argument[1].get()->value)
                                                     label.set_if_jump(true);
                                                 if (argument[0].get()->value != argument[1].get()->value)
                                                     label.set_if_jump(false);
                                             }
                                             },
                                             {"consoleRead",  "10010",  "R",    [](int64_t constant, Label &label,
                                                                                   std::vector<std::shared_ptr<Argument>> argument) {
                                                 uint32_t value;
                                                 std::cout << "Give value" << std::endl;
                                                 std::cin >> value;
                                                 argument[0].get()->value = value;
                                             }
                                             },
                                             {"call",         "1100",   "L",    [](int64_t constant, Label &label,
                                                                                   const std::vector<std::shared_ptr<Argument>> &argument) {
                                                 label.set_if_function(true);
                                             }
                                             },
                                             {"ret",          "1101",   "",     [](int64_t constant, Label &label,
                                                                                   const std::vector<std::shared_ptr<Argument>> &argument) {

                                             }, true
                                             },
                                             {"read",         "10000",  "RRRR", [](int64_t constant, Label &label,
                                                                                   std::vector<std::shared_ptr<Argument>> argument) {
                                                 std::vector<unsigned char> tmp(
                                                         instruction_input_file->begin() + argument[0].get()->value,
                                                         instruction_input_file->begin() + argument[0].get()->value +
                                                         argument[1].get()->value);
                                                 instruction_memory->save_data(tmp, argument[2].get()->value);
                                                 if (argument[0].get()->value + argument[1].get()->value <=
                                                     instruction_input_file->size())
                                                     argument[3].get()->value = argument[1].get()->value;
                                                 else
                                                     argument[3].get()->value =
                                                             instruction_input_file->size() - argument[0].get()->value;
                                             }
                                             },
                                             {"createThread", "10100",  "LR",   [](int64_t constant, Label &label,
                                                                                   const std::vector<std::shared_ptr<Argument>> &argument) {
                                                 label.set_if_thread(true);
                                             }
                                             },
                                             {"joinThread",   "10101",  "R",    [](int64_t constant, Label &label,
                                                                                   const std::vector<std::shared_ptr<Argument>> &argument) {

                                             }, false, true
                                             },
                                             {"lock",         "1110",   "R",    [](int64_t constant, Label &label,
                                                                                   const std::vector<std::shared_ptr<Argument>> &argument) {
                                                 for (std::pair<int, std::unique_ptr<std::mutex>> &unique_mutex : keychain) {
                                                     if (unique_mutex.first == argument[0].get()->value) {
                                                         unique_mutex.second->lock();
                                                     } else {
                                                         auto iter = keychain.end();
                                                         keychain.emplace(iter,
                                                                          std::make_pair(
                                                                                  argument[0].get()->value,
                                                                                  std::make_unique<std::mutex>()));
                                                         keychain.end()->second->lock();
                                                     }
                                                 }
                                             }
                                             },
                                             {"unlock",       "1111",   "R",    [](int64_t constant, Label &label,
                                                                                   const std::vector<std::shared_ptr<Argument>> &argument) {
                                                 for (std::pair<int, std::unique_ptr<std::mutex>> &unique_mutex : keychain) {
                                                     if (unique_mutex.first == argument[0].get()->value) {
                                                         unique_mutex.second->unlock();
                                                     }
                                                 }
                                             }
                                             }
};

#endif //PROJECT_OPCODES_H
