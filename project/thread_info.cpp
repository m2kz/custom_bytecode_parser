//
// Created by michal on 26.09.17.
//

#include "thread_info.h"

int threads_number = 0;

void ThreadInfo::set_executed_bit(int new_executed_bit) {
    executed_bit = new_executed_bit;
}

void ThreadInfo::operator()() {
    execution();
}

void ThreadInfo::process_function() {
    executor.reset();
    executor.set_actual_bit(executed_bit);
    executor.process_instruction();
    set_executed_bit(executor.get_actual_bit());
}

void ThreadInfo::execution() {
    do {
        process_function();
    } while (!check_thread_end());
}

void ThreadInfo::set_thread_id(std::thread::id new_thread_id) {
    thread_id = new_thread_id;
}

std::thread::id ThreadInfo::get_thread_id() {
    return thread_id;
}

bool ThreadInfo::check_thread_end() {
    return thread_end;
}