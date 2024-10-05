cmake_minimum_required(VERSION 3.25)
project(DynamicCollection C)

set(CMAKE_C_STANDARD 11)

add_executable(DynamicCollection main.c
        dynamicarray.c
        map.c
        string.c
        linkedlist.c
        testarray.c)
