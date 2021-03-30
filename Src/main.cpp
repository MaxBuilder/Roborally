#include "board.hpp"
#include "boardGraph.hpp"

#include <iostream>

int main() {
    RR::Board b("Data/board.txt") ;
    boardGraph graph(b);
    Robot start = Robot({0, 1}, Robot::Status::EAST);
    Robot end = Robot({3, 4}, Robot::Status::EAST);
    Location endLoc = Location(3, 4);
    auto res = graph.path(start, endLoc);

    std::cout << "Plus court chemin : " << std::endl;
    for(auto& r : res) {
        std::cout << r.robot.location.line << " " << r.robot.location.column << " , move : " << (int)r.move << std::endl;
    }

    std::cout << std::endl << "Comparaison :" << std::endl;
    Robot test = start;
    for(auto& r : res) {
        std::cout << r.robot.location.line << " " << r.robot.location.column << std::endl;
        b.play(test, r.move);
    }
    std::cout << test.location.line << " " << test.location.column << " " << (int)test.status << std::endl;

    return 0 ;
}
/*
    FORWARD_1 -> 0
    FORWARD_2 -> 1
    FORWARD_3 -> 2
    BACKWARD_1 -> 3
    TURN_LEFT -> 4
    TURN_RIGHT -> 5
    U_TURN -> 6

    EAST -> 0
    NORTH -> 1
    WEST -> 2
    SOUTH -> 3
 */