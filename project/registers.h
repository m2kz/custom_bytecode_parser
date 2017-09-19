//
// Created by michal on 10.09.17.
//

#ifndef PROJECT_REGISTERS_H
#define PROJECT_REGISTERS_H

#include <cstdint>
#include <string>
#include <vector>

struct VMRegister {
    int64_t get_register_value();
    void update_register_value(uint64_t new_value);
    uint64_t value;

    explicit VMRegister(uint64_t value): value(value){}
};

static int reg_id_to_vector_id(std::string &reg_id) {
    if (reg_id == "0000") return 0;
    if (reg_id == "1000") return 1;
    if (reg_id == "0100") return 2;
    if (reg_id == "1100") return 3;
    if (reg_id == "0010") return 4;
    if (reg_id == "1010") return 5;
    if (reg_id == "0110") return 6;
    if (reg_id == "1110") return 7;
};

#endif //PROJECT_REGISTERS_H
