cmake_minimum_required(VERSION 3.17)
project(CPU)

set(CMAKE_CXX_STANDARD 20)

add_executable(CPU Assembler.cpp main.cpp Enum.h CPU.cpp File.cpp File.h stack_1.h)