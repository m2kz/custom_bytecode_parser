//
// Created by michal on 09.09.17.
//
#include <algorithm>
#include "executor.h"
#include "registers.h"

const static int ENDIANNESS = 7;

void Executor::execute_instruction() {
    find_instruction();
    auto params_number = instruction.param_list.length();
    // TODO: Implement gathering parameters
    int64_t param1;
    VMRegister param2;
    for (int i = 0; i < params_number; i++) {
        if (instruction.param_list[i] == 'R') {
            find_reg_id();
            int vec_id = reg_id_to_vector_id(parameters[i]);
            param2 = vm_register[vec_id];
        }
        if (instruction.param_list[i] == 'C') {
            find_const_value();
            param1 = 0x100;
        }

    }
    instruction.con_reg(param1, param2);
}

int Executor::find_instruction() {
    bool found = false;
    std::string opcode;
    std::vector<Instruction>::iterator instruction_iterator;

    auto run_instruction = [&opcode](
            const Instruction &ins) {
        return ins.opcode == opcode;
    };

    do {
        int bit = read_bit();
        opcode.push_back((char) (bit + '0'));
        instruction_iterator = std::find_if(std::begin(instructions), std::end(instructions), run_instruction);
        found = (instruction_iterator != std::end(instructions));
    } while (!found);
    instruction = *instruction_iterator;
    return 0;
}

void Executor::find_const_value() {
    std::string const_value;
    for (int i = 0; i < 64; i++) {
        int bit = read_bit();
        const_value.push_back((char) (bit + '0'));
    }
    std::reverse(const_value.begin(), const_value.end());
    parameters.push_back(const_value);
}

void Executor::find_reg_id() {
    int bit = read_bit();
    std::string register_index;
    if (bit == 0) {
        for (int i = 0; i < 4; i++) {
            bit = read_bit();
            register_index.push_back((char) (bit + '0'));
        }

    }
    if (bit == 1) {
// TODO: Implement memory access
    }
    parameters.push_back(register_index);
}

/*
 * Reads actual value of bit and moves to next
 */
int Executor::read_bit() {
    int shift_value = ENDIANNESS - actual_bit;
    int mask = 1 << shift_value;
    int masked_byte = buffer_ref[actual_byte] & mask;
    int bit = masked_byte >> shift_value;
    if (actual_bit != 7) {
        actual_bit++;
    } else {
        actual_bit = 0;
        actual_byte++;
    }

    return bit;
}