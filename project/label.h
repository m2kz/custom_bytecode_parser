//
// Created by michal on 21.09.17.
//

#ifndef PROJECT_LABEL_H
#define PROJECT_LABEL_H

#include <cstdint>

class Label {
public:
    Label(uint32_t address) : address(address) {}
    void set_if_jump(bool value);
    void set_if_return(bool value);
    bool get_if_jump();
    int32_t get_jump_address();

private:
    bool if_jump = false;
    bool if_return = false;
    uint32_t address;
};

#endif //PROJECT_LABEL_H
