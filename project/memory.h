//
// Created by michal on 16.09.17.
//

#ifndef PROJECT_MEMORY_H
#define PROJECT_MEMORY_H

#include <vector>
#include <string>

enum DataType {
    Byte = 1,
    Word = 2,
    Dword = 4,
    Qword = 8
};

static int id_to_data_type(std::string reg_id) {
    if (reg_id == "00") return Byte;
    if (reg_id == "10") return Word;
    if (reg_id == "01") return Dword;
    if (reg_id == "11") return Qword;
}

class Memory {
public:
    explicit Memory(unsigned long size) : size(size) {}

    void initialize();

    void save_data(std::vector<unsigned char>, int offset);

    std::vector<unsigned char> access_data(int offset, DataType data_type);

    uint64_t memory_to_int(std::vector<unsigned char> memory_slice);

    void int_to_memory(int64_t memory_int);

private:
    unsigned long size;
    std::vector<unsigned char> stored_data;
};

#endif //PROJECT_MEMORY_H
