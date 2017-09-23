#include "main.h"

int main(int argc, char *argv[]) {

    std::vector<std::shared_ptr<VMRegister>> vm_registers;
    for (int i = 0; i < 16; i++) {
        std::shared_ptr<VMRegister> vm_register{new VMRegister(0)};
        vm_registers.push_back(std::move(vm_register));
    }

    if (argc < 2) {
        fprintf(stderr, "You did not provide program name.\n");
        exit(1);
    }
    std::string emv_file_path(argv[1]);
    if (is_file(emv_file_path) == 0) {
        fprintf(stderr, "You did not provide file path.\n");
        exit(1);
    }

    std::vector<char> buffer;
    read_file_to_buffer(emv_file_path, buffer);
    EvmHeader header;
    header.read_header(buffer);
    Memory memory(header.get_data_size());
    memory.initialize();
    Executor executor(buffer, vm_registers, memory);
    Function main_function(executor, header.get_size_of_file());

    const int executed_bit = 8 * header_length_in_bytes;
    main_function.set_executed_bit(executed_bit);
    do {
        main_function.process_function();
    } while (!main_function.check_program_end());

    return 0;
}