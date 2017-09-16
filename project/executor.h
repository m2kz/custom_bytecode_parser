//
// Created by michal on 09.09.17.
//

#ifndef PROJECT_EXECUTOR_H
#define PROJECT_EXECUTOR_H

#include <vector>
#include <string>
#include "instruction.h"

class Executor {

public:
    int find_instruction();

    void execute_instruction();

    void find_reg_id();

    void find_const_value();

    int get_actual_bit();

    void set_actual_bit(int current_bit);

    void reset();

    explicit Executor(std::vector<char> &buffer, std::vector<std::shared_ptr<VMRegister>> vm_registers) : buffer_ref(buffer),
                                                                                          vm_registers(vm_registers) {}

private:
    int actual_byte = 0;
    int actual_bit = 0;
    Instruction instruction;
    std::vector<std::string> parameters;
    std::vector<char> &buffer_ref;
    std::vector<std::shared_ptr<VMRegister>> vm_registers;

    int read_bit();
};


#endif //PROJECT_EXECUTOR_H
