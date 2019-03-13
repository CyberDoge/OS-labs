cmake_minimum_required(VERSION 3.13)
project(Lab1)

set(CMAKE_CXX_STANDARD 11)

add_executable(Lab1 main.cpp function/Function.h function/Sin.cpp function/Sin.h function/Cos.cpp function/Cos.h function/Exp.cpp function/Exp.h)