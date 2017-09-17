//
// Created by michal on 16.09.17.
//

#include "memory.h"

void Memory::initialize() {
    stored_data.resize(size);
}

void Memory::save_data(std::vector<unsigned char> data, int offset) {
    for (int i = size, y = data.size(); y != 0; i--, y--) {
        stored_data[i - 1 - offset] = data[y - 1];
    }
}

std::vector<unsigned char> Memory::access_data(int offset, DataType data_type) {
    std::vector<unsigned char> accessed_data;
    for (int i = 0; i < data_type; i++) {
        auto value = stored_data[size - data_type - offset + i];
        accessed_data.push_back(value);
    }
    return accessed_data;
}