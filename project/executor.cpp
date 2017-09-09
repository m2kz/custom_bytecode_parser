//
// Created by michal on 09.09.17.
//
#include <algorithm>
#include "executor.h"
#include "instruction.h"

void Executor::find_instruction(std::vector<char> &buffer) {
    Instruction instrucion;
    bool instruction_found = false;
    std::string opcode;
    do {
        int bit = read_bit(buffer);
        opcode.push_back((char) (bit + '0'));
        std::find_if(instructions.begin(), instructions.end(),
                     [&](const Instruction ins) {
                         if (ins.opcode == opcode) {
                             instrucion = ins;
                             instruction_found = true;
                             return 0;
                         } else {
                             instruction_found = false;
                             return -1;
                         }
                     });
    } while (!instruction_found);
}

void Executor::execute_instruction() {

}

void Executor::find_params(std::vector<char> &buffer) {

}

/*
 * Reads actual value of bit and moves to next
 */
int Executor::read_bit(std::vector<char> &buffer) {
    int mask = 1 << actual_bit;
    int masked_byte = buffer[actual_byte] & mask;
    int bit = masked_byte >> actual_bit;
    if (actual_bit != 7) {
        actual_bit++;
    } else {
        actual_bit = 0;
        actual_byte++;
    }

    return bit;
}