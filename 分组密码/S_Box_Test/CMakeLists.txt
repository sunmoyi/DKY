cmake_minimum_required(VERSION 3.15)
project(S_Box_Test)

set(CMAKE_CXX_STANDARD 14)

add_executable(S_Box_Test main.cpp Diff_Unif.cpp Linear_Probability.cpp ANF.cpp)