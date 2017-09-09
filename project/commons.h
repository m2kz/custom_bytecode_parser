//
// Created by michal on 09.09.17.
//

#ifndef PROJECT_COMMONS_H
#define PROJECT_COMMONS_H

#include <string>
#include <vector>

int is_file(std::string& file_path);
int read_file_to_buffer(std::string& file_path, std::vector<char>& buffer);

#endif //PROJECT_COMMONS_H
