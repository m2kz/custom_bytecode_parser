//
// Created by michal on 16.09.17.
//

#include "memory.h"

void Memory::initialize() {
    stored_data.resize(size);
}

void Memory::save_data(std::vector<char> data, int offset) {
    stored_data.assign(data.begin() + offset, data.end());
}

std::vector<char> Memory::access_data(int offset, DataType data_type) {
    return std::vector<char>(stored_data.begin() + offset, stored_data.begin() + offset + data_type);
}