//
// Created by raph on 3/27/21.
//

#ifndef PROJET_BOARDGRAPH_HPP
#define PROJET_BOARDGRAPH_HPP

#include "board.hpp"

#include <unordered_map>
#include <iostream>
#include <vector>

using namespace RR;

struct Play {
    Play(Robot r, Robot::Move m) : robot(r), move(m) {};

    Robot::Move move;
    Robot robot;
};

struct RobotHash {
    std::size_t operator()(const Robot& r) const {
        long long concat = r.location.line;
        concat <<= 8 * sizeof(int);
        concat += r.location.column;
        concat <<= 8 * sizeof(int);
        concat += (int)r.status;

        return std::hash<long long>()(concat);
    }
};

struct RobotComp {
    bool operator()(const Robot& lhs, const Robot& rhs) const {
        return lhs.location == rhs.location and lhs.status == rhs.status;
    }
};

class boardGraph {
public:
    boardGraph(Board& board);
    //path;

private:
    std::unordered_map<Robot, std::vector<Play>, RobotHash, RobotComp> graph;
};


#endif //PROJET_BOARDGRAPH_HPP
