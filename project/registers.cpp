//
// Created by michal on 19.09.17.
//

#include "registers.h"

int64_t VMRegister::get_register_value() {
    return value;
}

void VMRegister::update_register_value(uint64_t new_value) {
    value = new_value;
}
