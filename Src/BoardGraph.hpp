#ifndef PROJET_BOARDGRAPH_HPP
#define PROJET_BOARDGRAPH_HPP

#include "Board.hpp"

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
    std::size_t operator () (const Robot& r) const {
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
    bool operator () (const Robot& lhs, const Robot& rhs) const {
        return lhs.location == rhs.location and lhs.status == rhs.status;
    }
};

class BoardGraph {

public:
    // Construit le graph en fonction du plateau passé en paramètre
    explicit BoardGraph(Board& board);

    // Chemin avec orientation finale exacte
    std::vector<Robot::Move> path(Robot origin, Robot destination);

    // Chemin avec orientation finale quelquonque
    std::vector<Robot::Move> path(Robot origin, Location destination);

    // Interface avec le graph
    std::vector<Play> getTransitions(const Robot& robot);

private:
    // Boucle principale de l'aglorithme de Dijkstra
    void shortestPath(const Robot& origin, std::unordered_map<Robot, int, RobotHash, RobotEqual>& d, std::unordered_map<Robot, Play, RobotHash, RobotEqual>& p);

    // Structure contenant le graph
    std::unordered_map<Robot, std::vector<Play>, RobotHash, RobotEqual> mGraph;

    // Orientations possibles du robot :
    const std::vector<Robot::Status> statuses = {
            Robot::Status::EAST,
            Robot::Status::NORTH,
            Robot::Status::WEST,
            Robot::Status::SOUTH,
    };
};


#endif //PROJET_BOARDGRAPH_HPP
