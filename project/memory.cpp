//
// Created by michal on 16.09.17.
//

#include <sstream>
#include <cstring>
#include <algorithm>
#include "memory.h"

void Memory::initialize(std::vector<char> &buffer) {
    stored_data.resize(size);
    if (init_data_size > 0) {
        std::vector<char> temp_stored_data(buffer.end() - init_data_size, buffer.end());
        for (auto i = 0; i < init_data_size; i++) {
            stored_data[i] = temp_stored_data[i];
        }
    }
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

uint64_t Memory::memory_to_int(std::vector<unsigned char> memory_slice) {
    std::stringstream ss;
    std::string string_argument;
    for (unsigned char cell : memory_slice) {
        int cell_int = (int) cell;
        ss << std::hex << cell_int;
        if (cell_int == 0) {
            ss << std::hex << cell_int;
        }
        string_argument += ss.str();
        ss.str("");
    }
    const char *const_argument = string_argument.c_str();
    uint64_t memory_value = (uint64_t) strtoull(const_argument, nullptr, 16);
    return memory_value;
}

void Memory::update(uint64_t value, int offset, DataType data_type) {
    std::string string_value = std::to_string(value);
    std::vector<unsigned char> data;
    if (data_type == Byte) {
        int8_t value = (int8_t) atoll(string_value.c_str());
        if (data.size() < sizeof(value))
            data.resize(sizeof(value));
        std::memcpy(data.data(), &value, sizeof(value));
    }
    if (data_type == Word) {
        int16_t value = (int16_t) atoll(string_value.c_str());
        if (data.size() < sizeof(value))
            data.resize(sizeof(value));
        std::memcpy(data.data(), &value, sizeof(value));
    }
    if (data_type == Dword) {
        int32_t value = (int32_t) atoll(string_value.c_str());
        if (data.size() < sizeof(value))
            data.resize(sizeof(value));
        std::memcpy(data.data(), &value, sizeof(value));
    }
    if (data_type == Qword) {
        uint64_t value = (uint64_t) strtoull(string_value.c_str(), nullptr, 10);
        if (data.size() < sizeof(value))
            data.resize(sizeof(value));
        std::memcpy(data.data(), &value, sizeof(value));
    }
    std::reverse(data.begin(), data.end());
    save_data(data, offset);
}