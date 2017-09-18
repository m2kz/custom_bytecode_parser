//
// Created by michal on 09.09.17.
//

#ifndef PROJECT_RUNNER_H
#define PROJECT_RUNNER_H

#include "executor.h"

class Runner {
public:
    explicit Runner(Executor &executor, int code_length) : executor(executor), code_length(code_length) {}

    void set_executed_bit(int executed_bit);

    int get_executed_bit();

    void process_instruction();

    bool check_program_end();

private:

    int executed_bit;
    Executor &executor;
    int code_length;

};

#endif //PROJECT_RUNNER_H
