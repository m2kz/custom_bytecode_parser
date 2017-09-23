//
// Created by michal on 21.09.17.
//

#include "label.h"
#include "header.h"

void Label::set_if_jump(bool value){
    if_jump = value;
}

void Label::set_if_function(bool value) {
    if_function = value;
}

bool Label::get_if_jump() {
    return if_jump;
}

bool Label::get_if_function() {
    return if_function;
}

int32_t Label::get_jump_address() {
    return 8 * header_length_in_bytes + jump_address;
}

void Label::set_jump_address(uint32_t new_jump_address) {
    jump_address = new_jump_address;
}

uint32_t Label::get_call_address() {
    return call_address;
}