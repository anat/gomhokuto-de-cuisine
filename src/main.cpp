/* 
 * File:   main.cpp
 * Author: fancel
 *
 * Created on April 30, 2011, 6:27 AM
 */

#include <iostream>

#include "Board.hpp"
#include "Referee.hpp"
#include "Game.hpp"

/* Proto test/debug */
//void cleanBoard(Board &plateau);
//void dbgDumpBoard(Board &plateau, int limit);
//void testCheck(Board &plateau, Referee &arbitre);
//void check(Referee &arbitre, Board &plateau, int n, int x, int y, int dump);

#include "Square.hpp"

int main(void) {
    //Board plateau;
    //Referee arbitre(plateau);
    
    //plateau.DumpBoard();
    Game game;
    game.doGame();
    //testCheck(plateau, arbitre);
    return 0;
}


/* *****  FONCTIONS DE TEST / DEBUG  ***** */

/*
** Tests pour verifier le fonctionnement de l'arbitre (Regle #2)
** Tout ces tests place une piece a un endroit vide mais non accessible,
** si le test FAIL c'est qu'on a reussi a placer la piece (pas normal).
*/
//void testCheck(Board &plateau, Referee &arbitre)
//{
//  Square::Player toto;
//  toto = Square::PLAYER1;
//
//  arbitre.tryPlaceRock(1, 1, toto); /* Cas 1 */
//  arbitre.tryPlaceRock(2, 1, toto);
//  arbitre.tryPlaceRock(3, 1, toto);
//  arbitre.tryPlaceRock(1, 2, toto);
//  check(arbitre, plateau, 1, 1, 3, 0);
//
//  arbitre.tryPlaceRock(3, 1, toto); /* Cas 2 */
//  arbitre.tryPlaceRock(1, 2, toto);
//  arbitre.tryPlaceRock(3, 2, toto);
//  arbitre.tryPlaceRock(1, 3, toto);
//  check(arbitre, plateau, 2, 2, 2, 0);
//
//  arbitre.tryPlaceRock(3, 1, toto);
//  arbitre.tryPlaceRock(3, 2, toto);
//  arbitre.tryPlaceRock(4, 2, toto);
//  arbitre.tryPlaceRock(1, 3, toto);
//  check(arbitre, plateau, 3, 2, 2, 0);
//
//  arbitre.tryPlaceRock(3, 1, toto);
//  arbitre.tryPlaceRock(2, 2, toto);
//  arbitre.tryPlaceRock(2, 3, toto);
//  arbitre.tryPlaceRock(3, 3, toto);
//  check(arbitre, plateau, 4, 1, 3, 0);
//
//  arbitre.tryPlaceRock(4, 1, toto); /* Cas 3 */
//  arbitre.tryPlaceRock(3, 2, toto);
//  arbitre.tryPlaceRock(2, 4, toto);
//  arbitre.tryPlaceRock(3, 4, toto);
//  check(arbitre, plateau, 5, 1, 4, 0);
//
//  arbitre.tryPlaceRock(4, 1, toto);
//  arbitre.tryPlaceRock(2, 3, toto);
//  arbitre.tryPlaceRock(2, 4, toto);
//  arbitre.tryPlaceRock(3, 4, toto);
//  check(arbitre, plateau, 6, 1, 4, 0);
//
//  arbitre.tryPlaceRock(4, 1, toto);
//  arbitre.tryPlaceRock(4, 2, toto);
//  arbitre.tryPlaceRock(5, 2, toto);
//  arbitre.tryPlaceRock(1, 4, toto);
//  check(arbitre, plateau, 7, 3, 2, 0);
//
//  arbitre.tryPlaceRock(4, 1, toto);
//  arbitre.tryPlaceRock(2, 2, toto);
//  arbitre.tryPlaceRock(4, 2, toto);
//  arbitre.tryPlaceRock(1, 4, toto);
//  check(arbitre, plateau, 8, 3, 2, 0);
//
//  arbitre.tryPlaceRock(2, 1, toto); /* Cas 4 */
//  arbitre.tryPlaceRock(1, 2, toto);
//  arbitre.tryPlaceRock(4, 2, toto);
//  arbitre.tryPlaceRock(2, 4, toto);
//  check(arbitre, plateau, 9, 2, 2, 0);
//}
//
//void check(Referee &arbitre, Board &plateau, int n, int x, int y, int dump)
//{
//  Square::Player toto;
//  toto = Square::PLAYER1;
//
//  arbitre.tryPlaceRock(x, y, toto);
//  std::cout << "Test ";
//  std::cout.width(2);
//  std::cout.fill('0');
//  std::cout << n;
//  std::cout << ": "
//	    << ((plateau(x, y).getPlayer() == Square::NOPLAYER) ? "OK" : "FAIL")
//	    << std::endl;
//  if (dump)
//    dbgDumpBoard(plateau, 10);
//  cleanBoard(plateau);
//}
//
//void cleanBoard(Board &plateau)
//{
//  int i, j;
//
//  for (i = 0; i < 19; i++)
//    for (j = 0; j < 19; j++)
//      {
//	plateau(i, j).setPlayer(Square::NOPLAYER);
//	plateau(i, j)._horz  = 0;
//	plateau(i, j)._vert  = 0;
//	plateau(i, j)._diagl = 0;
//	plateau(i, j)._diagr = 0;
//      }
//}
//
//void dbgDumpBoard(Board &plateau, int limit = 19)
//{
//  int i, j;
//  char c;
//
//  std::cout << "   0  1  2  3  4  5  6  7  8  9"
//	    << "  10 11 12 13 14 15 16 17 18" << std::endl;
//  for (i = 0; i < limit; i++) /* Y */
//    {
//      std::cout.width(2);
//      std::cout << i;
//      for (j = 0; j < 19; j++) /* X */
//	{
//	  switch (plateau(j, i).getPlayer())
//	    {
//	    case Square::NOPLAYER: c = '.'; break;
//	    case Square::PLAYER1:  c = 'X'; break;
//	    case Square::PLAYER2:  c = 'O'; break;
//	    default:               c = '?'; break;
//	    }
//	  std::cout << " ";
//	  std::cout << c;
//	  std::cout << " ";
//	}
//      std::cout << std::endl;
//    }
//  if (limit != 19)
//    std::cout << "   [...]" << std::endl;
//}
