/* 
 * File:   HPlayer.h
 * Author: Calimeraw93
 *
 * Created on May 8, 2011, 2:13 PM
 */

#ifndef HPLAYER_H
#define	HPLAYER_H

#include "APlayer.hpp"

class HPlayer : public APlayer {
public:
    HPlayer(unsigned int player);
    virtual ~HPlayer();
private:
    bool doAction(Board & gameboard, Referee & referee, int x, int y);

};

#endif	/* HPLAYER_H */

