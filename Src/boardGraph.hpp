//
// Created by raph on 3/27/21.
//

#ifndef PROJET_BOARDGRAPH_HPP
#define PROJET_BOARDGRAPH_HPP

#include "board.hpp"

#include <unordered_map>
#include <algorithm>
#include <vector>
#include <queue>

using namespace RR;

// Structure contenant un robot et un mouvement (correspond à un coup)
struct Play {
    Play() : robot(), move() {};
    Play(Robot r, Robot::Move m) : robot(r), move(m) {};

    Robot::Move move;
    Robot robot;
};

// Foncteur de hashage du robot
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

// Foncteur de comparaison d'égalité du robot
struct RobotEqual {
    bool operator()(const Robot& lhs, const Robot& rhs) const {
        return lhs.location == rhs.location and lhs.status == rhs.status;
    }
};

class boardGraph {

public:
    // Constructeur de la classe, prend un plateau en paramètre et construit le graph
    explicit boardGraph(Board& board);

    // Algorithme du plus court chemin entre deux points (implémentation de Dijkstraa)
    std::vector<Play> path(Robot origin, Robot destination);
    std::vector<Play> path(Robot origin, Location destination);

private:
    std::unordered_map<Robot, std::vector<Play>, RobotHash, RobotEqual> mGraph;

    // Variables réutilisées :
    const std::vector<Robot::Status> statuses = {
            Robot::Status::EAST,
            Robot::Status::NORTH,
            Robot::Status::WEST,
            Robot::Status::SOUTH,
    };
};


#endif //PROJET_BOARDGRAPH_HPP
