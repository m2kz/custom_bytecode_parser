//
// Created by michal on 21.09.17.
//

#include "label.h"
#include "header.h"

void Label::set_if_jump(bool value){
    if_jump = value;
}

void Label::set_if_return(bool value) {
    if_return = value;
}

bool Label::get_if_jump() {
    return if_jump;
}

int32_t Label::get_jump_address() {
    return 8 * header_length_in_bytes + address;
}