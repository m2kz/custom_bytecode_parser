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

static int id_to_data_type(std::string &reg_id) {
    if (reg_id == "00") return Byte;
    if (reg_id == "10") return Word;
    if (reg_id == "01") return Dword;
    if (reg_id == "11") return Qword;
}

class Memory {
public:
    explicit Memory(unsigned long size, uint32_t init_data_size) : size(size), init_data_size(init_data_size) {}

    void initialize(std::vector<char> &buffer);

    void save_data(std::vector<unsigned char>, int64_t offset);

    std::vector<unsigned char> access_data(int offset, DataType data_type);

    int64_t memory_to_int(std::vector<unsigned char> memory_slice);

    void update(int64_t value, uint64_t offset, DataType data_type);

private:
    unsigned long size;
    uint32_t init_data_size;
    std::vector<unsigned char> stored_data;
};

#endif //PROJECT_MEMORY_H
