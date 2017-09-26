cmake_minimum_required(VERSION 3.8)
project(project)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(SOURCE_FILES main.cpp header.cpp header.h main.h commons.cpp commons.h instruction.h executor.cpp executor.h function.h function.cpp registers.h memory.cpp memory.h argument.h registers.cpp label.cpp label.h instruction.cpp thread_info.cpp thread_info.h)
add_executable(project ${SOURCE_FILES})