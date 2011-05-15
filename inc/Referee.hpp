/* 
 * File:   Referee.hpp
 * Author: fancel
 *
 * Created on May 5, 2011, 1:14 PM
 */

#ifndef REFEREE_HPP
#define	REFEREE_HPP

#include "Board.hpp"

#define DIR_UP    0x1
#define DIR_DOWN  0x2
#define DIR_LEFT  0x4
#define DIR_RIGHT 0x8

/*
 * L'arbitre
 */
struct Coord {
	Coord(int x_, int y_) : x(x_), y(y_) {}
	Coord& operator+(const Coord& value) {
		x += value.x;
		y += value.y;
          return (*this);
        }
	int x;
	int y;
};

class Referee {
public:
    Referee(Board& board);
    Referee(const Referee& orig);
    virtual ~Referee();

    int tryPlaceRock(unsigned int x, unsigned int y, unsigned int square); //Test et si ok place
    bool testPosition(unsigned int x, unsigned int y, unsigned int player); //Test tout cours
    unsigned int checkWin() const;
    void propagation_inverse(unsigned int x, unsigned int y, const unsigned int player);
    bool doubleThree() const;
    bool fivePrize() const;
    bool doubleThree(bool value);
    bool fivePrize(bool value);
    void reset(); 
 
private:
	enum Vector {
		RIGHT,
		UP_RIGHT,
		UP,
		UP_LEFT,
		LEFT,
		DOWN_LEFT,
		DOWN,
		DOWN_RIGHT
	};

    Board& _board;
    unsigned int _winner;
    bool _fivePrize;
    bool _doubleThree;
	std::vector<Coord> _directionIncrement;

    inline unsigned int opponant(const unsigned int pla) {
        unsigned int result = 0;
        if (pla == 1)
            result = 2;
        else if (pla == 2)
            result = 1;
        return result;
    }

    inline bool checkPosition(unsigned int x, unsigned int y) {
        return (x < _board.getSize() && y < _board.getSize());
    }

    inline unsigned int abs(int value) {
        if (value < 0)
            return value * -1;
        return value;
    }

	inline Vector invert(Vector dir) {
		switch (dir) {
			case UP: return DOWN;
			case DOWN: return UP;
			case LEFT: return RIGHT;
			case RIGHT: return LEFT;
			case UP_LEFT: return DOWN_RIGHT;
			case DOWN_RIGHT: return UP_LEFT;
			case UP_RIGHT: return DOWN_LEFT;
			case DOWN_LEFT: return UP_RIGHT;
			default: return UP;
		}
		return UP;
	}

	void InitDirection();
	bool goTo(unsigned int& x, unsigned int& y, Vector dir);
	unsigned int getDirAlign(const Square& value, Vector dir);
	bool ispartOfAlign(const Square& value, int size);

	/*
	* Fonction de check pour les double alignement de trois
	*/
    bool checkDoubleThree(unsigned int x, unsigned int y, unsigned int player);
	bool isPartOfFree3Align(unsigned int x, unsigned int y, Vector dir, unsigned int player);
	bool classicFree3Align(unsigned int x, unsigned int y, Vector dir, unsigned int player);
	bool unClassicFree3Align(unsigned int x, unsigned int y, Vector dir, unsigned int player);

	/*
	* Fonction pour la victoire par alignement de 5
	*/ 
	void checkWin(unsigned int x, unsigned int y, unsigned int player);
    bool checkfiveWin(unsigned int x, unsigned int y);
	bool checkFivePrize(unsigned int x, unsigned int y, unsigned int player);
	unsigned int checkFivePrize(unsigned int x, unsigned int y, Vector dir, unsigned int player);

	 /*
	* Fonction pour la prise de pierre
	*/
	unsigned int checkPrize(unsigned int x, unsigned int y, const unsigned int player);
    bool checkPrize(unsigned int x, unsigned int y, Vector dir, unsigned int player);
    bool checkIsTakable(unsigned x, unsigned int y, Vector dir, unsigned int player);
	void cleanRock(unsigned int x, unsigned int y, Vector dir, unsigned int player);

	/*
	* Fonction pour la propagation
	*/

	void propagation(unsigned int x, unsigned int y, const unsigned int player);
    void propagation(unsigned int x, unsigned int y, const unsigned int player,
            unsigned int dir, unsigned int usize);

    int lineSize(unsigned int x, unsigned int y, const unsigned int player, int dir);
};

#endif	/* REFEREE_HPP */

