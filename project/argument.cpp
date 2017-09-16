//
// Created by michal on 16.09.17.
//

#include "argument.h"

void Argument::access() {
    if (argument_type == RegisterType) {
        std::string raw_reg_id = std::string(raw_argument.begin(), raw_argument.begin() + 3);
        int reg_id = reg_id_to_vector_id(raw_reg_id);
        vm_registers[reg_id].get()->value;
    }
    if (argument_type == MemoryType) {
        std::string raw_data_type = std::string(raw_argument.begin(), raw_argument.begin() + 1);
        std::string raw_offset = std::string(raw_argument.begin() + 2, raw_argument.begin() + 5);
        DataType data_type = (DataType)id_to_data_type(raw_data_type);
        int reg_id = reg_id_to_vector_id(raw_offset);
        int64_t reg_value = vm_registers[reg_id].get()->value;
        memory.access_data(reg_value, data_type);
    }
}