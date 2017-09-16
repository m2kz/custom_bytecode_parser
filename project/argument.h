//
// Created by michal on 16.09.17.
//

#ifndef PROJECT_ARGUMENT_H
#define PROJECT_ARGUMENT_H

#include <memory>
#include "registers.h"
#include "memory.h"

enum ArgumentType {
    RegisterType,
    MemoryType
};

/*
 * Storing argument and its type. Used to unify different type of argument received from one source.
 */

struct Argument {
public:
    void access();
private:
    std::vector<char> raw_argument;
    std::vector<std::shared_ptr<VMRegister>> vm_registers;
    Memory memory;
    ArgumentType argument_type;
};

#endif //PROJECT_ARGUMENT_H
