//
// Created by michal on 16.09.17.
//

#ifndef PROJECT_ARGUMENT_H
#define PROJECT_ARGUMENT_H

#include <memory>
#include "registers.h"
#include "memory.h"

enum ArgType {
    RegisterType,
    MemoryType
};

class ArgumentRegister {
public:
    ArgumentRegister() {}

    explicit ArgumentRegister(int reg_id) : reg_id(reg_id) {}

    int reg_id;
private:

};

class ArgumentMemory {
public:
    ArgumentMemory() {}

    explicit ArgumentMemory(DataType data_type, int offset) : data_type(data_type), offset(offset) {}

    DataType data_type;
    int offset;
private:

};


class Argument : public ArgumentMemory, public ArgumentRegister {
public:
    explicit Argument(int reg_id, uint64_t value) : ArgumentRegister(reg_id), value(value), arg_type(RegisterType) {}

    explicit Argument(DataType data_type, int offset, uint64_t value) : ArgumentMemory(data_type, offset),
                                                                            value(value), arg_type(MemoryType) {}

    int64_t value;
    ArgType arg_type;

private:

};

#endif //PROJECT_ARGUMENT_H
