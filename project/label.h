//
// Created by michal on 21.09.17.
//

#ifndef PROJECT_LABEL_H
#define PROJECT_LABEL_H

#include <cstdint>

class Label {
public:
    Label(uint32_t jump_address, int call_address) : jump_address(jump_address), call_address(call_address) {}

    void set_if_jump(bool value);

    void set_if_function(bool value);

    void set_if_thread(bool value);

    bool get_if_jump();

    bool get_if_function();

    uint32_t get_jump_address();

    int get_call_address();

    void set_thread_id_reg();

    int get_thread_id_reg();

    bool get_if_thread();

private:
    bool if_jump = false;
    bool if_function = false;
    bool if_thread = false;
    uint32_t jump_address = 0;
    int call_address = 0;
    int thread_id_reg = 0;
};

#endif //PROJECT_LABEL_H
