cmake_minimum_required(VERSION 3.8)
project(project)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp evm_file_header.cpp evm_file_header.h main.h commons.cpp commons.h)
add_executable(project ${SOURCE_FILES})