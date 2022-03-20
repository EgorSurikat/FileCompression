cmake_minimum_required(VERSION 3.21)
project(FileCompression C)

set(CMAKE_C_STANDARD 23)

add_executable(FileCompression files/main.c files/basic_var_and_struct.h files/basic_var_and_struct.c)
