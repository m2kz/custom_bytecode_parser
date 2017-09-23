//
// Created by michal on 09.09.17.
//
#include <algorithm>
#include <memory>
#include <cstring>
#include "executor.h"
#include "function.h"

std::vector<std::shared_ptr<Function>> functions;

const static int ORDER = 7;

void Executor::process_instruction() {
    int64_t constant_arg = 0;
    Label *label = nullptr;
    std::vector<std::shared_ptr<Argument>> arguments;
    find_instruction();
    auto params_number = instruction.param_list.length();
    for (int i = 0; i < params_number; i++) {
        if (instruction.param_list[i] == 'R') {
            find_argument();
            if (parameters[i].size() == 4) {
                auto argument = create_register_argument(parameters[i]);
                arguments.push_back(std::move(argument));
            }
            if (parameters[i].size() == 6) {
                auto argument = create_memory_argument(parameters[i]);
                arguments.push_back(std::move(argument));
            }
        }
        if (instruction.param_list[i] == 'C') {
            find_const_value();
            constant_arg = (int64_t) std::stol(parameters[i], nullptr, 2);
        }
        if (instruction.param_list[i] == 'L') {
            find_label_address();
            auto label_addr = (uint32_t) std::stol(parameters[i], nullptr, 2);
            label = new Label(label_addr, get_actual_bit());
        }
    }
    std::cout << "Instruction: " << instruction.name << " at: " << std::dec << actual_byte * 8 + actual_bit << std::endl;
    execution(constant_arg, *label, arguments);
    for (std::shared_ptr<Argument> &argument : arguments) {
        if (argument.get()->arg_type == RegisterType) {
            vm_registers[argument.get()->reg_id].get()->update_register_value(argument.get()->value);
        }
        if (argument.get()->arg_type == MemoryType) {
            memory.update(argument.get()->value, argument.get()->offset, argument.get()->data_type);
        }
    }
    if (label != nullptr) {
        bool if_jump = label->get_if_jump();
        if (if_jump) {
            std::cout << "Jump address: " << std::dec << label->get_jump_address() << std::endl;
            set_actual_bit(label->get_jump_address());

        }
        bool if_function = label->get_if_function();
        if (if_function) {
            std::shared_ptr<Function> function{new Function(*this, label->get_jump_address(), label->get_call_address())};
            functions.push_back(function);
            function->set_executed_bit(label->get_jump_address());
            do {
                function->process_function();
            } while (!function->check_program_end());
        }
        delete label;
    }
    if(instruction.if_return) {
        functions.back()->set_function_end(true);
    }

}

void Executor::execution(int64_t constant_arg, Label &label, std::vector<std::shared_ptr<Argument>> arguments) {
    instruction.implementation(constant_arg, label, arguments);
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

std::shared_ptr<Argument> Executor::create_register_argument(std::string &raw_parameter) {
    std::string raw_reg_id = raw_parameter;
    int vec_id = reg_id_to_vector_id(raw_reg_id);
    std::shared_ptr<Argument> argument{new Argument(vec_id, vm_registers[vec_id].get()->value)};
    return argument;
}

std::shared_ptr<Argument> Executor::create_memory_argument(std::string &raw_parameter) {
    std::string raw_data_type = std::string(raw_parameter.begin(), raw_parameter.begin() + 2);
    std::string raw_reg_id = std::string(raw_parameter.begin() + 2, raw_parameter.begin() + 6);
    DataType data_type = (DataType) id_to_data_type(raw_data_type);
    int reg_id = reg_id_to_vector_id(raw_reg_id);
    auto reg_value = (int64_t) vm_registers[reg_id].get()->value;
    std::vector<unsigned char> memory_argument = memory.access_data(reg_value, data_type);
    uint64_t memory_value = memory.memory_to_int(memory_argument);
    std::shared_ptr<Argument> argument{new Argument(data_type, reg_value, memory_value)};
    return argument;
}

void Executor::find_label_address() {
    std::string label_address;
    for (int i = 0; i < 32; i++) {
        int bit = read_bit();
        label_address.push_back((char) (bit + '0'));
    }
    std::reverse(label_address.begin(), label_address.end());
    parameters.push_back(label_address);
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
    } else if (bit == 1) {
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