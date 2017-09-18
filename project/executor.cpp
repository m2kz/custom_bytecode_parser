//
// Created by michal on 09.09.17.
//
#include <algorithm>
#include <memory>
#include <cstring>
#include "executor.h"
#include "argument.h"
#include "commons.h"

const static int ORDER = 7;

void Executor::execute_instruction() {
    int64_t constant_arg;
    std::vector<std::shared_ptr<Argument>> arguments;
    int32_t label_arg;
    find_instruction();
    auto params_number = instruction.param_list.length();
    for (int i = 0; i < params_number; i++) {
        if (instruction.param_list[i] == 'R') {
            find_argument();
            if (parameters[i].size() == 4) {
                std::string raw_reg_id = parameters[i];
                int vec_id = reg_id_to_vector_id(raw_reg_id);
                std::shared_ptr<Argument> argument{new Argument(vec_id, vm_registers[vec_id].get()->value)};
                arguments.push_back(std::move(argument));
            }
            if (parameters[i].size() == 6) {
                std::string raw_data_type = std::string(parameters[i].begin(), parameters[i].begin() + 2);
                std::string raw_reg_id = std::string(parameters[i].begin() + 2, parameters[i].begin() + 6);
                DataType data_type = (DataType) id_to_data_type(raw_data_type);
                int reg_id = reg_id_to_vector_id(raw_reg_id);
                int64_t reg_value = vm_registers[reg_id].get()->value;
                std::vector<unsigned char> memory_argument = memory.access_data(reg_value, data_type);
                uint64_t memory_value = memory.memory_to_int(memory_argument);
                std::shared_ptr<Argument> argument{new Argument(data_type, reg_value, memory_value)};
                arguments.push_back(std::move(argument));
            }
        }
        if (instruction.param_list[i] == 'C') {
            find_const_value();
            int64_t int_val = std::stol(parameters[i], nullptr, 2);
            constant_arg = int_val;
        }

    }
    instruction.implementation(constant_arg, label_arg, arguments);
    for (std::shared_ptr<Argument> argument : arguments) {
        if (argument.get()->arg_type == RegisterType) {
            vm_registers[argument.get()->reg_id]->value = argument.get()->value;
        }
        if (argument.get()->arg_type == MemoryType) {
            std::string string_value = std::to_string(argument.get()->value);
            std::vector<unsigned char> data;
            if (argument.get()->data_type == Byte) {
                int8_t value = (int8_t) atoll(string_value.c_str());
                if (data.size() < sizeof(value))
                    data.resize(sizeof(value));
                std::memcpy(data.data(), &value, sizeof(value));
            }
            if (argument.get()->data_type == Word) {
                int16_t value = (int16_t) atoll(string_value.c_str());
                if (data.size() < sizeof(value))
                    data.resize(sizeof(value));
                std::memcpy(data.data(), &value, sizeof(value));
            }
            if (argument.get()->data_type == Dword) {
                int32_t value = (int32_t) atoll(string_value.c_str());
                if (data.size() < sizeof(value))
                    data.resize(sizeof(value));
                std::memcpy(data.data(), &value, sizeof(value));
            }
            if (argument.get()->data_type == Qword) {
                uint64_t value = (uint64_t)strtoull(string_value.c_str(), nullptr, 10);
                if (data.size() < sizeof(value))
                    data.resize(sizeof(value));
                std::memcpy(data.data(), &value, sizeof(value));
            }
            std::reverse(data.begin(), data.end());
            memory.save_data(data, argument.get()->offset);
        }
    }
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

void Executor::process_register_argument(std::string raw_parameter) {

}

void Executor::process_memory_argument(std::string raw_parameter) {

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

void Executor::find_argument() {
    int bit = read_bit();
    std::string register_index;
    if (bit == 0) {
        for (int i = 0; i < 4; i++) {
            bit = read_bit();
            register_index.push_back((char) (bit + '0'));
        }
    }
    if (bit == 1) {
        for (int i = 0; i < 6; i++) {
            bit = read_bit();
            register_index.push_back((char) (bit + '0'));
        }
    }
    parameters.push_back(register_index);
}

/*
 * Reads actual value of bit and moves to next
 */

int Executor::read_bit() {
    int shift_value = ORDER - actual_bit;
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

void Executor::set_actual_bit(int current_bit) {
    actual_byte = current_bit / 8;
    actual_bit = current_bit % 8;
}

int Executor::get_actual_bit() {
    return 8 * actual_byte + actual_bit;
}

void Executor::reset() {
    actual_bit = 0;
    actual_byte = 0;
    parameters.clear();
}