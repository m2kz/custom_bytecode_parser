#include <fstream>
#include <algorithm>
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
    Header header;
    header.read_header(buffer);
    Memory memory(header.get_data_size(), header.get_initial_data_size());
    memory.initialize(buffer);
    std::vector<char> input_file_buffer;
    Executor *executor;
    if (argc > 2) {
        std::string input_file_param(argv[2]);
        read_file_to_buffer(input_file_param, input_file_buffer);
        executor = new Executor(buffer, vm_registers, memory, input_file_buffer);
    } else {
        executor = new Executor(buffer, vm_registers, memory);
    }
    set_instruction_memory(memory);
    set_instruction_input_file(input_file_buffer);
    Function main_function(*executor, header.get_size_of_file());
    const int executed_bit = 8 * header_length_in_bytes;
    main_function.set_executed_bit(executed_bit);
    do {
        std::cout << "Enter main thread" << std::endl;
        main_function.process_function();
        std::cout << "Exit main thread" << std::endl;
    } while (!main_function.check_program_end());

    return 0;
}