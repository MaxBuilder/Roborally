cmake_minimum_required(VERSION 3.17)
project(Projet)

set(CMAKE_CXX_STANDARD 17)

add_executable(Projet Src/main.cpp Src/board.cpp Src/board.hpp Src/boardGraph.hpp Src/boardGraph.cpp)