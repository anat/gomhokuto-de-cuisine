#ifndef REMOTEPLAYER_H
#define REMOTEPLAYER_H


#include "APlayer.hpp"

class RemotePlayer : public APlayer
{
public:
    RemotePlayer(unsigned int player);
    virtual ~RemotePlayer();
private:
    bool doAction(Board & gameboard, Referee & referee, int x, int y);
};

#endif // REMOTEPLAYER_H
