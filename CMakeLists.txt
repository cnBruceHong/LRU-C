cmake_minimum_required(VERSION 3.8)
project(algorithm)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c lru.c entry.c hash.c hash.h)
add_executable(lru ${SOURCE_FILES})