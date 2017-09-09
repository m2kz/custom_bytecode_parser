//
// Created by michal on 09.09.17.
//

#ifndef PROJECT_EVM_FILE_HEADER_H
#define PROJECT_EVM_FILE_HEADER_H

#include <cstdint>
#include <vector>

class EvmHeader {

public:
    EvmHeader();

    void read_header(std::vector<char> &buffer);

private:
    char magic[8];
    uint32_t code_size;
    uint32_t data_size;
    uint32_t initial_data_size;

    void verify(std::vector<char> &buffer);

    uint32_t extract_uint_32_value(std::vector<char> &buffer);
};

#endif //PROJECT_EVM_FILE_HEADER_H
