
#include "Square.hpp"

Square::Square() :  _value(), _player(NOPLAYER), _horz(0), _vert(0), _diagl(0), _diagr(0) {
    _value.resize(VEC_SIZE);
    for (int i = 0; i < VEC_SIZE; ++i)
        _value[i].resize(BYTE_SIZE);
}

Square::Player Square::getPlayer()
{
    return (_player);
}

void Square::setPlayer(Player player)
{
    _player = player;
}

void   Square::modifValue(Player player, int num_case, bool increment)
{
    if (increment)
        this->increment(player, num_case);
    else
        this->decrement(player, num_case);
}

void   Square::increment(Player player, int num_case)
{
    _value[(int) player][num_case]++;
}

void   Square::decrement(Player player, int num_case)
{
    _value[(int) player][num_case]--;    
}

std::vector<char> const & Square::getValues(Player player) const
{
    return (_value.at((int)player));
}
