//
// Created by michal on 09.09.17.
//
#include <algorithm>
#include "executor.h"
#include "registers.h"

const static int ENDIANNESS = 7;

void Executor::find_instruction() {
    Instruction tmp_instrucion;
    bool instruction_found = false;
    std::string opcode;

    auto random = [&opcode](
            const Instruction &ins) {
        auto hur = ins;
        return ins.opcode == opcode;
    };

    do {
        int bit = read_bit();
        opcode.push_back((char) (bit + '0'));
        std::find_if(std::begin(instructions), std::end(instructions), random) != std::end(instructions);
    } while (!instruction_found);
    random;
    instruction = tmp_instrucion;
}

void Executor::execute_instruction() {
    find_instruction();
    int params_number = instruction.param_list.length();
    // TODO: Implement gathering parameters
    int64_t param1;
    VMRegister param2;
    for (int i = 0; i < params_number; i++) {
        if (instruction.param_list[i] == 'R') {
            find_param();
            int vec_id = reg_id_to_vector_id(parameters[i]);
            VMRegister param2 = vm_register[vec_id];
        }
        if (instruction.param_list[i] == 'C') {
            find_param();
            int64_t param1 = 0x100;
        }

    }
    instruction.con_reg(param1, param2);
}

void Executor::find_param() {
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