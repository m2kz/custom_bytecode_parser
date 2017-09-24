//
// Created by michal on 24.09.17.
//

#include "instruction.h"

Memory *instruction_memory;
std::vector<char> *instruction_input_file;

void set_instruction_memory(Memory &memory) {
    instruction_memory = &memory;
}

void set_instruction_input_file(std::vector<char> &input_file) {
    instruction_input_file = &input_file;
}