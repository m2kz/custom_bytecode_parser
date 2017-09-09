//
// Created by michal on 09.09.17.
//

#include "evm_file_header.h"

EvmHeader::EvmHeader() {
    magic[0] = '\0';
    code_size = 0;
    data_size = 0;
    initial_data_size = 0;
}

int EvmHeader::read_header(std::vector<char> buffer) {
    return 0;
}

int EvmHeader::verify() {

}