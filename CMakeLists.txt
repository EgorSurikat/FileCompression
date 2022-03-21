cmake_minimum_required(VERSION 3.20)
project(FileCompression C)

set(CMAKE_C_STANDARD 23)

add_executable(FileCompression files/main.c files/coding.h files/coding.c files/decoding.c files/decoding.h)
