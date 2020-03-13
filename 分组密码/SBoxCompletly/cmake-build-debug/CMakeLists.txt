cmake_minimum_required(VERSION 3.15)
project(S_Boxes)

set(CMAKE_CXX_STANDARD 14)

add_executable(main.c  boolean_only.c  properties.c representations.c helper_functions.c   basic_info.c header.h)

