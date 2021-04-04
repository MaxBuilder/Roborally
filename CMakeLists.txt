cmake_minimum_required(VERSION 3.17)
project(Projet)

set(CMAKE_CXX_STANDARD 17)

add_executable(Projet Src/main.cpp
        Src/Board.hpp Src/Board.cpp
        Src/BoardGraph.hpp Src/BoardGraph.cpp
        Src/ArtificialPlayer.hpp Src/ArtificialPlayer.cpp
        Src/MoveDeck.hpp Src/MoveDeck.cpp)