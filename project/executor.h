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

    void find_param();

    explicit Executor(std::vector<char> &buffer) : buffer_ref(buffer){}
private:
    int actual_byte = 0;
    int actual_bit = 0;
    std::vector<char> operation_buffer;
    Instruction instruction;
    std::vector<std::string> parameters;
    std::vector<char> &buffer_ref;
    int read_bit();
};



#endif //PROJECT_EXECUTOR_H
