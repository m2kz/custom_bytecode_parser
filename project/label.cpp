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

uint32_t Label::get_jump_address() {
    return 8 * header_length_in_bytes + jump_address;
}

int Label::get_call_address() {
    return call_address;
}