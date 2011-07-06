/* 
 * File:   main.cpp
 * Author: fancel
 *
 * Created on April 30, 2011, 6:27 AM
 */
#include <QtGui/QApplication>
#include <iostream>

#include "Board.hpp"
#include "Referee.hpp"
#include "Game.hpp"
#include "mainwindow.hpp"

#define TEST_COLOR 0 /* (less -R gere les codes couleurs) */

void cleanBoard(Board &plateau);
void dbgDumpBoard(Board &plateau, int x, int y, int limit);
void testDoubleThree(Board &plateau, Referee &arbitre, int dump_lvl);
void check(Referee &arbitre, Board &plateau, int n, int x, int y, int dump);

#include "Square.hpp"

int main(int ac, char **av) {
    if (ac == 1)
    {
        QApplication a(ac, av);
        MainWindow w;
        w.show();
        return a.exec();
    }
    // Usage: ./Gomoku test [dump | all]
    else if (ac >= 2 && QString(av[1]) == "test") 
    {
      Board plateau;
      Referee arbitre(plateau);

      std::cout << "=== REFEREE TEST ===" << std::endl;
      arbitre.doubleThree(true);
      arbitre.fivePrize(true);

      if (ac == 3 && QString(av[2]) == "dump")
	testDoubleThree(plateau, arbitre, 1);
      else if (ac == 3 && QString(av[2]) == "all")
	testDoubleThree(plateau, arbitre, 2);
      else
	testDoubleThree(plateau, arbitre, 0);
      std::cout << "====================" << std::endl;
    }
    return 1;
}

/* *****  FONCTIONS DE TEST / DEBUG  ***** */

/*
 ** Tests pour verifier le fonctionnement de l'arbitre (Regle #2)
 ** Tout ces tests place une piece a un endroit vide mais non accessible,
 ** si le test FAIL c'est qu'on a reussi a placer la piece (pas normal).
 */
void testDoubleThree(Board &plateau, Referee &arbitre, int dump_lvl)
{
  int toto = PLAYER1;
#if 1
  arbitre.tryPlaceRock(1, 1, toto); /* Cas 1 */
  arbitre.tryPlaceRock(2, 1, toto);
  arbitre.tryPlaceRock(3, 1, toto);
  arbitre.tryPlaceRock(1, 2, toto);
  check(arbitre, plateau, 1, 1, 3, dump_lvl);

  arbitre.tryPlaceRock(3, 1, toto); /* Cas 2 */
  arbitre.tryPlaceRock(1, 2, toto);
  arbitre.tryPlaceRock(3, 2, toto);
  arbitre.tryPlaceRock(1, 3, toto);
  check(arbitre, plateau, 2, 2, 2, dump_lvl);

  arbitre.tryPlaceRock(3, 1, toto);
  arbitre.tryPlaceRock(3, 2, toto);
  arbitre.tryPlaceRock(4, 2, toto);
  arbitre.tryPlaceRock(1, 3, toto);
  check(arbitre, plateau, 3, 2, 2, dump_lvl);

  arbitre.tryPlaceRock(3, 1, toto);
  arbitre.tryPlaceRock(2, 2, toto);
  arbitre.tryPlaceRock(2, 3, toto);
  arbitre.tryPlaceRock(3, 3, toto);
  check(arbitre, plateau, 4, 1, 3, dump_lvl);

  arbitre.tryPlaceRock(4, 1, toto); /* Cas 3 */
  arbitre.tryPlaceRock(3, 2, toto);
  arbitre.tryPlaceRock(2, 4, toto);
  arbitre.tryPlaceRock(3, 4, toto);
  check(arbitre, plateau, 5, 1, 4, dump_lvl);

  arbitre.tryPlaceRock(4, 1, toto);
  arbitre.tryPlaceRock(2, 3, toto);
  arbitre.tryPlaceRock(2, 4, toto);
  arbitre.tryPlaceRock(3, 4, toto);
  check(arbitre, plateau, 6, 1, 4, dump_lvl);

  arbitre.tryPlaceRock(4, 1, toto);
  arbitre.tryPlaceRock(4, 2, toto);
  arbitre.tryPlaceRock(5, 2, toto);
  arbitre.tryPlaceRock(1, 4, toto);
  check(arbitre, plateau, 7, 3, 2, dump_lvl);

  arbitre.tryPlaceRock(4, 1, toto);
  arbitre.tryPlaceRock(2, 2, toto);
  arbitre.tryPlaceRock(4, 2, toto);
  arbitre.tryPlaceRock(1, 4, toto);
  check(arbitre, plateau, 8, 3, 2, dump_lvl);

  arbitre.tryPlaceRock(2, 1, toto); /* Cas 4 */
  arbitre.tryPlaceRock(1, 2, toto);
  arbitre.tryPlaceRock(4, 2, toto);
  arbitre.tryPlaceRock(2, 4, toto);
  check(arbitre, plateau, 9, 2, 2, dump_lvl);

  arbitre.tryPlaceRock(4, 3, toto); /* Cas 5.1 */
  arbitre.tryPlaceRock(5, 3, toto);
  arbitre.tryPlaceRock(1, 1, toto);
  arbitre.tryPlaceRock(2, 2, toto);
  check(arbitre, plateau, 10, 3, 3, dump_lvl);

  arbitre.tryPlaceRock(4, 3, toto);
  arbitre.tryPlaceRock(5, 3, toto);
  arbitre.tryPlaceRock(3, 1, toto);
  arbitre.tryPlaceRock(3, 2, toto);
  check(arbitre, plateau, 11, 3, 3, dump_lvl);

  arbitre.tryPlaceRock(4, 3, toto);
  arbitre.tryPlaceRock(5, 3, toto);
  arbitre.tryPlaceRock(5, 1, toto);
  arbitre.tryPlaceRock(4, 2, toto);
  check(arbitre, plateau, 12, 3, 3, dump_lvl);

  arbitre.tryPlaceRock(2, 1, toto); /* Cas 5.2 */
  arbitre.tryPlaceRock(2, 3, toto);
  arbitre.tryPlaceRock(3, 2, toto);
  arbitre.tryPlaceRock(4, 2, toto);
  check(arbitre, plateau, 13, 2, 2, dump_lvl);

  arbitre.tryPlaceRock(2, 1, toto); /* Cas 5.3 */
  arbitre.tryPlaceRock(2, 2, toto);
  arbitre.tryPlaceRock(1, 3, toto);
  arbitre.tryPlaceRock(3, 3, toto);
  check(arbitre, plateau, 14, 2, 3, dump_lvl);

  arbitre.tryPlaceRock(4, 1, toto);
  arbitre.tryPlaceRock(3, 2, toto);
  arbitre.tryPlaceRock(1, 3, toto);
  arbitre.tryPlaceRock(3, 3, toto);
  check(arbitre, plateau, 15, 2, 3, dump_lvl);

  arbitre.tryPlaceRock(2, 1, toto); /* Cas 5.4 */
  arbitre.tryPlaceRock(2, 3, toto);
  arbitre.tryPlaceRock(1, 2, toto);
  arbitre.tryPlaceRock(3, 2, toto);
  check(arbitre, plateau, 16, 2, 2, dump_lvl);

  arbitre.tryPlaceRock(1, 1, toto);
  arbitre.tryPlaceRock(2, 2, toto);
  arbitre.tryPlaceRock(5, 4, toto);
  arbitre.tryPlaceRock(6, 4, toto);
  check(arbitre, plateau, 17, 4, 4, dump_lvl); /* Cas 6.1 */

  arbitre.tryPlaceRock(4, 1, toto);
  arbitre.tryPlaceRock(4, 2, toto);
  arbitre.tryPlaceRock(5, 4, toto);
  arbitre.tryPlaceRock(6, 4, toto);
  check(arbitre, plateau, 18, 4, 4, dump_lvl);

  arbitre.tryPlaceRock(1, 1, toto);
  arbitre.tryPlaceRock(3, 3, toto);
  arbitre.tryPlaceRock(5, 4, toto);
  arbitre.tryPlaceRock(6, 4, toto);
  check(arbitre, plateau, 19, 4, 4, dump_lvl);

  arbitre.tryPlaceRock(4, 1, toto);
  arbitre.tryPlaceRock(4, 3, toto);
  arbitre.tryPlaceRock(5, 4, toto);
  arbitre.tryPlaceRock(6, 4, toto);
  check(arbitre, plateau, 20, 4, 4, dump_lvl);

  arbitre.tryPlaceRock(2, 1, toto); /* Cas 6.2 */
  arbitre.tryPlaceRock(5, 4, toto);
  arbitre.tryPlaceRock(4, 2, toto);
  arbitre.tryPlaceRock(5, 2, toto);
  check(arbitre, plateau, 21, 3, 2, dump_lvl);

  arbitre.tryPlaceRock(3, 1, toto);
  arbitre.tryPlaceRock(3, 4, toto);
  arbitre.tryPlaceRock(4, 2, toto);
  arbitre.tryPlaceRock(5, 2, toto);
  check(arbitre, plateau, 22, 3, 2, dump_lvl);

  arbitre.tryPlaceRock(2, 1, toto); /* Cas 6.3 */
  arbitre.tryPlaceRock(2, 2, toto);
  arbitre.tryPlaceRock(1, 4, toto);
  arbitre.tryPlaceRock(3, 4, toto);
  check(arbitre, plateau, 23, 2, 4, dump_lvl);

  arbitre.tryPlaceRock(4, 2, toto);
  arbitre.tryPlaceRock(5, 1, toto);
  arbitre.tryPlaceRock(1, 4, toto);
  arbitre.tryPlaceRock(3, 4, toto);
  check(arbitre, plateau, 24, 2, 4, dump_lvl);

  arbitre.tryPlaceRock(2, 1, toto);
  arbitre.tryPlaceRock(2, 3, toto);
  arbitre.tryPlaceRock(1, 4, toto);
  arbitre.tryPlaceRock(3, 4, toto);
  check(arbitre, plateau, 25, 2, 4, dump_lvl);

  arbitre.tryPlaceRock(3, 3, toto);
  arbitre.tryPlaceRock(5, 1, toto);
  arbitre.tryPlaceRock(1, 4, toto);
  arbitre.tryPlaceRock(3, 4, toto);
  check(arbitre, plateau, 26, 2, 4, dump_lvl);

  arbitre.tryPlaceRock(3, 1, toto); /* Cas 6.4 */
  arbitre.tryPlaceRock(3, 4, toto);
  arbitre.tryPlaceRock(2, 2, toto);
  arbitre.tryPlaceRock(4, 2, toto);
  check(arbitre, plateau, 27, 3, 2, dump_lvl);

  arbitre.tryPlaceRock(1, 4, toto);
  arbitre.tryPlaceRock(4, 1, toto);
  arbitre.tryPlaceRock(2, 2, toto);
  arbitre.tryPlaceRock(4, 2, toto);
  check(arbitre, plateau, 28, 3, 2, dump_lvl);

  /* Ces cas sont les meme que 6.3, mais placement de pions pas dans le meme ordre. */
  arbitre.tryPlaceRock(2, 1, toto); /* Cas 6.5 */
  arbitre.tryPlaceRock(2, 4, toto);
  arbitre.tryPlaceRock(1, 4, toto);
  arbitre.tryPlaceRock(3, 4, toto);
  check(arbitre, plateau, 29, 2, 2, dump_lvl);

  arbitre.tryPlaceRock(4, 2, toto);
  arbitre.tryPlaceRock(2, 4, toto);
  arbitre.tryPlaceRock(1, 4, toto);
  arbitre.tryPlaceRock(3, 4, toto);
  check(arbitre, plateau, 30, 5, 1, dump_lvl);

  arbitre.tryPlaceRock(2, 4, toto);
  arbitre.tryPlaceRock(2, 3, toto);
  arbitre.tryPlaceRock(1, 4, toto);
  arbitre.tryPlaceRock(3, 4, toto);
  check(arbitre, plateau, 31, 2, 1, dump_lvl);

  arbitre.tryPlaceRock(2, 4, toto);
  arbitre.tryPlaceRock(5, 1, toto);
  arbitre.tryPlaceRock(1, 4, toto);
  arbitre.tryPlaceRock(3, 4, toto);
  check(arbitre, plateau, 32, 3, 3, dump_lvl);
#endif
  arbitre.tryPlaceRock(2, 1, toto); /* Cas 7.1 */
  arbitre.tryPlaceRock(4, 3, toto);
  arbitre.tryPlaceRock(1, 3, toto);
  arbitre.tryPlaceRock(2, 3, toto);
  check(arbitre, plateau, 33, 5, 4, dump_lvl);

  arbitre.tryPlaceRock(4, 3, toto);
  arbitre.tryPlaceRock(4, 4, toto);
  arbitre.tryPlaceRock(1, 3, toto);
  arbitre.tryPlaceRock(2, 3, toto);
  check(arbitre, plateau, 34, 4, 1, dump_lvl);

  arbitre.tryPlaceRock(6, 1, toto);
  arbitre.tryPlaceRock(3, 4, toto);
  arbitre.tryPlaceRock(4, 3, toto);
  arbitre.tryPlaceRock(2, 3, toto);
  check(arbitre, plateau, 35, 1, 3, dump_lvl);

  arbitre.tryPlaceRock(1, 1, toto); /* Cas 7.1 */
  arbitre.tryPlaceRock(4, 4, toto);
  arbitre.tryPlaceRock(3, 4, toto);
  arbitre.tryPlaceRock(6, 4, toto);
  check(arbitre, plateau, 36, 2, 2, dump_lvl);

  arbitre.tryPlaceRock(4, 4, toto);
  arbitre.tryPlaceRock(4, 2, toto);
  arbitre.tryPlaceRock(3, 4, toto);
  arbitre.tryPlaceRock(6, 4, toto);
  check(arbitre, plateau, 37, 4, 1, dump_lvl);

  arbitre.tryPlaceRock(6, 2, toto);
  arbitre.tryPlaceRock(7, 1, toto);
  arbitre.tryPlaceRock(4, 4, toto);
  arbitre.tryPlaceRock(6, 4, toto);
  check(arbitre, plateau, 38, 3, 4, dump_lvl);

  arbitre.tryPlaceRock(4, 4, toto);
  arbitre.tryPlaceRock(3, 3, toto);
  arbitre.tryPlaceRock(3, 4, toto);
  arbitre.tryPlaceRock(6, 4, toto);
  check(arbitre, plateau, 39, 1, 1, dump_lvl);

  arbitre.tryPlaceRock(4, 1, toto);
  arbitre.tryPlaceRock(4, 3, toto);
  arbitre.tryPlaceRock(4, 4, toto);
  arbitre.tryPlaceRock(6, 4, toto);
  check(arbitre, plateau, 40, 3, 4, dump_lvl);

  arbitre.tryPlaceRock(5, 3, toto);
  arbitre.tryPlaceRock(7, 1, toto);
  arbitre.tryPlaceRock(3, 4, toto);
  arbitre.tryPlaceRock(4, 4, toto);
  check(arbitre, plateau, 41, 6, 4, dump_lvl);

  /*
    arbitre.tryPlaceRock(, , toto);
    check(arbitre, plateau, , , , dump_lvl);
  */
}

void check(Referee &arbitre, Board &plateau, int n, int x, int y, int dump)
{
  int toto = PLAYER1;

  arbitre.tryPlaceRock(x, y, toto);
  std::cout << "  Test ";
  std::cout.width(2);
  std::cout.fill('0');
  std::cout << n;
  std::cout << ": "
	    << ((PLAYER(plateau(x, y).getRawData()) == NOPLAYER) ? "OK" : "FAIL")
	    << std::endl;
  if (dump == 2 || (dump == 1 && (!(PLAYER(plateau(x, y).getRawData()) == NOPLAYER))))
    dbgDumpBoard(plateau, x, y, 10);
  cleanBoard(plateau);
}

void cleanBoard(Board &plateau)
{
  int i, j;

  for (i = 0; i < 19; i++)
    for (j = 0; j < 19; j++)
      plateau(i, j).setRawData(0);
}

void dbgDumpBoard(Board &plateau, int x, int y, int limit = 19) {
    int i, j;
    char c;

    std::cout << "   0  1  2  3  4  5  6  7  8  9"
            << "  10 11 12 13 14 15 16 17 18" << std::endl;
    for (i = 0; i < limit; i++) /* Y */ {
        std::cout.width(2);
        std::cout << i;
        for (j = 0; j < 19; j++) /* X */ {
            switch (GET_PLAYER(plateau(j, i).getRawData())) {
                case NOPLAYER: c = '.';
                    break;
                case PLAYER1: c = 'X';
                    break;
                case PLAYER2: c = 'O';
                    break;
                default: c = '?';
                    break;
            }
            std::cout << " ";
#if TEST_COLOR == 1
	    if (x==j && y==i)
	      std::cout << "\033[31m";
#endif
            std::cout << c;
#if TEST_COLOR == 1
	    if (x==j && y==i)
	      std::cout << "\033[0m";
#endif
            std::cout << " ";
        }
        std::cout << std::endl;
    }
    if (limit != 19)
        std::cout << "   [...]" << std::endl;
}
