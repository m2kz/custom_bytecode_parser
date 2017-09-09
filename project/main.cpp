#include <iostream>
#include <vector>
#include "commons.h"
#include "evm_file_header.h"

int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "You did not provide program name.\n");
        exit(1);
    }

    std::string emv_file_path(argv[1]);
    if (is_file(emv_file_path) == false) {
        fprintf(stderr, "You did not provide file path.\n");
        exit(1);
    }
    std::vector<char> buffer;

    read_file_to_buffer(emv_file_path, buffer);

    return 0;
}