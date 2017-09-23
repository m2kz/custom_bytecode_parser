//
// Created by michal on 21.09.17.
//

#ifndef PROJECT_LABEL_H
#define PROJECT_LABEL_H

#include <cstdint>

class Label {
public:
    Label(uint32_t jump_address, uint32_t call_address) : jump_address(jump_address), call_address(call_address) {}

    void set_if_jump(bool value);

    void set_if_function(bool value);

    bool get_if_jump();

    bool get_if_function();

    int32_t get_jump_address();

    void set_jump_address(uint32_t new_jump_address);

    uint32_t get_call_address();

private:
    bool if_jump = false;
    bool if_function = false;
    uint32_t jump_address = 0;
    uint32_t call_address = 0;
};

#endif //PROJECT_LABEL_H
