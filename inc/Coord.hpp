#ifndef COORD_HPP
#define COORD_HPP

struct Coord {

    Coord(int x_, int y_) : x(x_), y(y_)
    {
    }

    Coord & operator+(const Coord & value)
    {
        x += value.x;
        y += value.y;
        return (*this);
    }

    bool operator <(const Coord& value)
    {
        return (x + y < value.x + value.y);
    }

    bool operator >(const Coord& value)
    {
        return (x + y > value.x + value.y);
    }

    bool operator=(const Coord& value)
    {
        return (x == value.x && y == value.y);
    }

    int x;
    int y;
};

#endif // COORD_HPP
