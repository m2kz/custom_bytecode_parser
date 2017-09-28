//
// Created by michal on 09.09.17.
//

#include <sys/stat.h>
#include <fstream>
#include <vector>
#include <iostream>

int is_file(std::string &file_path) {
    struct stat sb{};

    return stat(file_path.c_str(), &sb) == 0 && S_ISREG(sb.st_mode);
}

int read_file_to_buffer(std::string &file_path, std::vector<char> &buffer) {

    std::ifstream file(file_path, std::ios::binary);
    file.seekg(0, std::ios::end);
    long file_size = file.tellg();
    file.seekg(0, std::ios::beg);
    buffer.resize((unsigned long)file_size);
    file.read(&(buffer[0]), file_size);
    file.close();
}


