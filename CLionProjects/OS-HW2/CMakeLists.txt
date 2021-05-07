cmake_minimum_required(VERSION 3.19)
project(OS-HW2 C)

set(CMAKE_C_STANDARD 99)

add_executable(OS-HW2
        concurrent_list.c
        concurrent_list.h
        main.c)