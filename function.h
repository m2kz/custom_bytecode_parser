//
// Created by michal on 09.09.17.
//

#ifndef PROJECT_RUNNER_H
#define PROJECT_RUNNER_H

#include "executor.h"

class Function {
public:
    explicit Function(Executor &executor, int code_length) : executor(executor), code_length(code_length) {}

    explicit Function(Executor &executor, uint32_t call_address, uint32_t return_address) : executor(executor),
                                                                                            call_address(call_address),
                                                                                            return_address(
                                                                                                    return_address) {}

    void set_executed_bit(int executed_bit);

    void process_function();

    bool check_program_end();

    bool check_function_end();

    void set_function_end(bool);

private:

    int executed_bit;
    Executor &executor;
    int code_length;
    uint32_t call_address;
    uint32_t return_address;
    bool function_end = false;

};

#endif //PROJECT_RUNNER_H
