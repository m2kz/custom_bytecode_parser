#include <iostream>
#include <vector>
#include "commons.h"
#include "evm_file_header.h"
#include "executor.h"

int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "You did not provide program name.\n");
        exit(1);
    }
    std::string emv_file_path(argv[1]);
    if (is_file(emv_file_path) == 0) {
        fprintf(stderr, "You did not provide file path.\n");
        exit(1);
    }

    int execution_bit_number;
    std::vector<char> buffer;
    read_file_to_buffer(emv_file_path, buffer);

    EvmHeader header;
    header.read_header(buffer);
    execution_bit_number = header_length_in_bytes * 8;

    Executor executor(buffer);

    return 0;
}