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
    void find_instruction(std::vector<char> &buffer);

    void execute_instruction();

    void find_params(std::vector<char> &buffer);


private:
    int actual_byte;
    int actual_bit;
    std::vector<char> operation_buffer;
    std::string instruction;
    std::vector<char> parameters;

    int read_bit(std::vector<char> &buffer);
};

#endif //PROJECT_EXECUTOR_H
