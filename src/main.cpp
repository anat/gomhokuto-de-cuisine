/* 
 * File:   main.cpp
 * Author: fancel
 *
 * Created on April 30, 2011, 6:27 AM
 */

#include <iostream>

#include "Board.hpp"
#include "Referee.hpp"

void dbgDumpBoard(Board &plateau, int limit = 19)
{
  int i, j;
  char c;

  std::cout << "   0  1  2  3  4  5  6  7  8  9"
	    << "  10 11 12 13 14 15 16 17 18" << std::endl;
  for (i = 0; i < limit; i++) /* Y */
    {
      std::cout.width(2);
      std::cout << i;
      for (j = 0; j < 19; j++) /* X */
	{
	  switch (plateau(j, i).getPlayer())
	    {
	    case Square::NOPLAYER: c = '.'; break;
	    case Square::PLAYER1:  c = 'X'; break;
	    case Square::PLAYER2:  c = 'O'; break;
	    default:               c = '?'; break;
	    }
	  std::cout << " ";
	  std::cout << c;
	  std::cout << " ";
	}
      std::cout << std::endl;
    }
  if (limit != 19)
    std::cout << "   [...]" << std::endl;
}

int main(void) {
    Board plateau;
    Referee arbitre(plateau);

    if (plateau(1, 2).getPlayer() == Square::NOPLAYER)
        std::cout << "caca" << std::endl;

    /* Propagation test (A commenter si ca vous gene) */
    Square::Player toto;
    toto = Square::PLAYER1;

    arbitre.tryPlaceRock(1, 2, toto);
    arbitre.tryPlaceRock(4, 2, toto);
    arbitre.tryPlaceRock(5, 2, toto);
    arbitre.tryPlaceRock(2, 3, toto);
    arbitre.tryPlaceRock(3, 3, toto);
    arbitre.tryPlaceRock(2, 5, toto);
    arbitre.tryPlaceRock(3, 5, toto);

    arbitre.tryPlaceRock(3, 4, toto);
    arbitre.propagation_inverse(3, 4, Square::PLAYER1);

    dbgDumpBoard(plateau, 10);
    /* !Propagation test */
    return 0;
}

