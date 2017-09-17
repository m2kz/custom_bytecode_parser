//
// Created by michal on 16.09.17.
//

#include "memory.h"

void Memory::initialize() {
    stored_data.resize(size);
}

void Memory::save_data(std::vector<unsigned char> data, int offset) {
    stored_data.assign(data.begin() + offset, data.end());
}

std::vector<unsigned char> Memory::access_data(int offset, DataType data_type) {
    return std::vector<unsigned char>(&stored_data[offset], &stored_data[offset + data_type]);
}