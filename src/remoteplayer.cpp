#include "remoteplayer.hpp"
#include <iostream>
RemotePlayer::RemotePlayer(unsigned int player) : APlayer(player) {
}

RemotePlayer::~RemotePlayer() {
}


bool RemotePlayer::doAction(Board&, Referee& referee, int x, int y)
{
    int res = 0;
    if (x < 0 && y < 0)
    {
        std::cout << "test" << std::endl;
    }
    else
    {
        res = referee.tryPlaceRock(x, y, this->getPlayerNum());
        if (res == -1)
            return false;
    }
    return true;
}
