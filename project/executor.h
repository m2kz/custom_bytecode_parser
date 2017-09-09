//
// Created by michal on 09.09.17.
//

#ifndef PROJECT_EXECUTOR_H
#define PROJECT_EXECUTOR_H

#include <vector>
#include <string>
#include "opcodes.h"

class Executor {

public:
    void read_instruction(std::vector<char>);

private:
    int start_byte;
    std::vector<char> operation_buffer;
    std::string instruction;
    std::vector<char> parameters;
};

#endif //PROJECT_EXECUTOR_H
