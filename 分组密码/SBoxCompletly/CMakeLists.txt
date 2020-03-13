cmake_minimum_required(VERSION 3.15)
project(SBoxCompletly)

set(CMAKE_CXX_STANDARD 14)

add_executable(SBoxCompletly   main.c boolean_only.c  properties.c representations.c helper_functions.c   basic_info.c header.h)