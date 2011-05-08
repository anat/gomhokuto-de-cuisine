/* 
 * File:   HPlayer.h
 * Author: Calimeraw93
 *
 * Created on May 8, 2011, 2:13 PM
 */

#ifndef HPLAYER_H
#define	HPLAYER_H

#include "APlayer.h"

class HPlayer : APlayer {
public:
    HPlayer();
    virtual ~HPlayer();
private:
    void doAction(Board & gameboard, Referee & referee);

};

#endif	/* HPLAYER_H */

