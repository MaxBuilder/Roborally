//
// Created by raph on 3/27/21.
//

#include "boardGraph.hpp"

boardGraph::boardGraph(Board &board) { // Choix d'un parcours exhaustif de toutes les cases
    const std::vector<Robot::Move> moves = {
        Robot::Move::FORWARD_1,
        Robot::Move::FORWARD_2,
        Robot::Move::FORWARD_3,
        Robot::Move::BACKWARD_1,
        Robot::Move::TURN_LEFT,
        Robot::Move::TURN_RIGHT,
        Robot::Move::U_TURN
    };

    for(const auto& [location, tile] : board.tiles) {
        for(auto status : statuses) {
            const Robot origin(location, status); // On teste les destinations à partir de l'origine pour chaque déplacement
            std::vector<Play> transitions;

            for(auto move : moves) { // Pour tous les coups
                Robot temp = origin;
                board.play(temp, move);

                if(temp.status != Robot::Status::DEAD)
                    transitions.emplace_back(temp, move);
            }

            mGraph.insert(std::make_pair(origin, transitions));
        }
    }
}

// Obligé d'utiliser une template et un foncteur pour la comparaison (le compilateur n'acceptais pas une lambda)
template<typename T, typename C>
struct comp {
    bool operator () (const std::pair<T, C>& lhs, const std::pair<T, C>& rhs) {return lhs.second > rhs.second; }
};

std::vector<Play> boardGraph::path(const Robot origin, const Robot destination) {
    // Variables de l'algorithme de Dijkstra :
    std::unordered_map<Robot, int, RobotHash, RobotEqual> d; // Distance
    std::unordered_map<Robot, Play, RobotHash, RobotEqual> p; // Predecesseur

    // Utilisation de paires (sommet + distance) pour éviter de créer un nouveau type)
    std::priority_queue<std::pair<Robot, int>, std::vector<std::pair<Robot, int>>, comp<Robot, int>> s; // File à priorité (basse)

    // Initialisation des distances au max
    for(const auto& vertex : mGraph)
        d[vertex.first] = std::numeric_limits<int>::max();

    // On place l'origine dans la file avec une distance de 0
    s.push(std::make_pair(origin, 0));
    d[origin] = 0;

    // Traitement des sommets :
    while(not s.empty()) {
        Robot u = s.top().first;
        s.pop();

        // Exploration de toutes les transitions du sommet
        for(Play t : mGraph[u]) {
            Robot v = t.robot;
            if(d[v] > d[u] + 1) { // Un chemin plus court est trouvé
                d[v] = d[u] + 1; // Mise à jour de la distance
                p[v] = Play(u, t.move); // Mise à jour du prédecesseur
                s.push(std::make_pair(v, d[v]));
            }
        }
    }

    // Construction du résultat :
    Robot temp = destination;
    std::vector<Play> res;

    if(d[origin] == std::numeric_limits<int>::max()) // Cas d'un chemin impossible
        return res;

    while(temp != origin) {
        Play play = p[temp];
        res.push_back(play);
        temp = play.robot;
    }

    std::reverse(res.begin(), res.end()); // Inversion du tableau
    return res;
}

std::vector<Play> boardGraph::path(const Robot origin, const Location destination) {
    // Variables de l'algorithme de Dijkstra :
    std::unordered_map<Robot, int, RobotHash, RobotEqual> d; // Distance
    std::unordered_map<Robot, Play, RobotHash, RobotEqual> p; // Predecesseur

    // Utilisation de paires (sommet + distance) pour éviter de créer un nouveau type)
    std::priority_queue<std::pair<Robot, int>, std::vector<std::pair<Robot, int>>, comp<Robot, int>> s; // File à priorité (basse)

    // Initialisation des distances au max
    for(const auto& vertex : mGraph)
        d[vertex.first] = std::numeric_limits<int>::max();

    // On place l'origine dans la file avec une distance de 0
    s.push(std::make_pair(origin, 0));
    d[origin] = 0;

    // Traitement des sommets :
    while(not s.empty()) {
        Robot u = s.top().first;
        s.pop();

        // Exploration de toutes les transitions du sommet
        for(Play t : mGraph[u]) {
            Robot v = t.robot;
            if(d[v] > d[u] + 1) { // Un chemin plus court est trouvé
                d[v] = d[u] + 1; // Mise à jour de la distance
                p[v] = Play(u, t.move); // Mise à jour du prédecesseur
                s.push(std::make_pair(v, d[v]));
            }
        }
    }

    // Selection de la meilleure orientation :
    Robot::Status best;
    int bestDistance = std::numeric_limits<int>::max();
    std::vector<Play> res;
    for(auto status : statuses) {
        Robot trial(destination, status);
        if(d[trial] < bestDistance) {
            best = status;
            bestDistance = d[trial];
        }
    }

    if(bestDistance == std::numeric_limits<int>::max()) // Cas d'un chemin impossible
        return res;

    // Construction de la solution
    Robot temp(destination, best);
    while(temp != origin) {
        Play play = p[temp];
        res.push_back(play);
        temp = play.robot;
    }

    std::reverse(res.begin(), res.end()); // Inversion du tableau
    return res;
}