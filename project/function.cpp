//
// Created by michal on 09.09.17.
//

#include "function.h"

void Function::set_executed_bit(int new_executed_bit) {
    executed_bit = new_executed_bit;
}

void Function::process_function() {
    executor.reset();
    executor.set_actual_bit(executed_bit);
    executor.process_instruction();
    set_executed_bit(executor.get_actual_bit());
}

bool Function::check_program_end() {
    return code_length == (executed_bit / 8);
}

void Function::set_function_end(bool value) {
    function_end = value;
}

bool Function::check_function_end() {
    return function_end;
}

