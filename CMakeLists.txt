cmake_minimum_required(VERSION 3.17)
project(Projet)

set(CMAKE_CXX_STANDARD 17)

add_executable(Projet Src/main.cpp
        Src/board.hpp Src/board.cpp
        Src/boardGraph.hpp Src/boardGraph.cpp
        Src/artificialPlayer.hpp Src/artificialPlayer.cpp
        Src/moveDeck.hpp Src/moveDeck.cpp)