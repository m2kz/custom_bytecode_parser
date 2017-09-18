//
// Created by michal on 09.09.17.
//

#include "runner.h"

void Runner::set_executed_bit(int new_executed_bit) {
    executed_bit = new_executed_bit;
}

int Runner::get_executed_bit() {
    return executed_bit;
}

void Runner::process_instruction() {
    executor.reset();
    executor.set_actual_bit(executed_bit);
    executor.execute_instruction();
    set_executed_bit(executor.get_actual_bit());
}

bool Runner::check_program_end() {
    if (code_length == (executed_bit/8)) {
        return true;
    } else {
        return false;
    }
}

