cmake_minimum_required(VERSION 3.19)
project(OS-HW2 C)

set(CMAKE_C_STANDARD 99)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

set(THREADS_PREFER_PTHREAD_FLAG ON)

add_executable(OS-HW2
        concurrent_list.c
        concurrent_list.h
        test.c)

find_package(Threads REQUIRED)
target_link_libraries(OS-HW2 Threads::Threads)