/* 
 * File:   Square.hpp
 * Author: fancel
 *
 * Created on May 5, 2011, 12:19 PM
 */

#ifndef SQUARE_HPP
#define	SQUARE_HPP

class Square {

public:
    enum Player {
        NOPLAYER,
        PLAYER1,
        PLAYER2
    };
    
    enum LINK_TYPE {
        TWO,
        THREE,
        FOUR,
        FIVE,
        END
    };
    
private:
    Player _player;
    char   _status_link[4][4];

public :
    Square();
    Player getPalyer();
    bool   isEndLink();
    void   setPlayer(Player player);
    void   setStatusLink(int type, char value);
    char * getLinkType(int type);
};

#endif	/* SQUARE_HPP */

