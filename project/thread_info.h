//
// Created by michal on 26.09.17.
//

#ifndef PROJECT_THREAD_H
#define PROJECT_THREAD_H

#include <thread>
#include "executor.h"

static std::hash<std::thread::id> hasher;

class ThreadInfo {
public:

    explicit ThreadInfo(Executor &executor, uint32_t call_address) : executor(executor), call_address(call_address) {}

    void set_executed_bit(int executed_bit);

    void process_function();

    bool check_thread_end();
    
    void execution();

    void set_thread_id(std::thread::id thread_id);

    std::thread::id get_thread_id();

private:

    int executed_bit = 0;
    Executor &executor;
    uint32_t call_address;
    bool thread_end = false;
    std::thread::id thread_id;
};



#endif //PROJECT_THREAD_H
