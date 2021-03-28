#include "board.hpp"
#include "boardGraph.hpp"

#include <iostream>

int main() {
    RR::Board b("Data/board.txt") ;
    boardGraph graph(b);

    //b.save("/tmp/cpy.txt") ;

    return 0 ;
}