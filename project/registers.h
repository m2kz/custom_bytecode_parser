//
// Created by michal on 10.09.17.
//

#ifndef PROJECT_REGISTERS_H
#define PROJECT_REGISTERS_H

#include <cstdint>
#include <string>
#include <vector>

struct VMRegister {
    int64_t value;

    explicit VMRegister(int64_t value): value(value){}
};

static int reg_id_to_vector_id(std::string reg_id) {
    if (reg_id == "0000") return 0;
    if (reg_id == "1000") return 1;
    if (reg_id == "0100") return 2;
    if (reg_id == "1100") return 3;
};

#endif //PROJECT_REGISTERS_H
