#include "Board.hpp"

#include <iostream>

int main() {
  RR::Board b("../Data/board.txt") ;
  b.save("/tmp/cpy.txt") ;

  return 0 ;
}
