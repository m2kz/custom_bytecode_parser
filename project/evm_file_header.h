//
// Created by michal on 09.09.17.
//

#ifndef PROJECT_EVM_FILE_HEADER_H
#define PROJECT_EVM_FILE_HEADER_H

#include <cstdint>
#include <vector>

const int magic_number_length = 8;
const int header_param_number = 3;
const int header_param_length = 4;
const int header_length_in_bytes = magic_number_length + header_param_number * header_param_length;


class EvmHeader {

public:
    EvmHeader();

    void read_header(std::vector<char> &buffer);
    uint32_t get_data_size();

private:
    char magic[8];
    uint32_t code_size;
    uint32_t data_size;
    uint32_t initial_data_size;

    void verify(std::vector<char> &buffer);

    uint32_t extract_uint_32_value(std::vector<char> &buffer);
};

#endif //PROJECT_EVM_FILE_HEADER_H
