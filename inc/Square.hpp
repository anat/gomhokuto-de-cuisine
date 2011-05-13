/* 
 * File:   Square.hpp
 * Author: fancel
 *
 * Created on May 5, 2011, 12:19 PM
 */

#ifndef SQUARE_HPP
#define	SQUARE_HPP

#include "Types.hpp"

class Square {

public:
    struct Data{
        unsigned short player : 2;
        unsigned short is_takable : 1;
        unsigned short horz : 4;
        unsigned short vert : 4;
        unsigned short diagl : 4;
        unsigned short diagr : 4;
    };
    
public:
    Square();
    virtual ~Square();

    int32_t             getRawData() const;
    void                setRawData(int32_t mask);
    Square::Data &      getData();
    void                setData(Square::Data & data);
    void                dumpData();
    
private:
     int32_t _data;

};

#endif	/* SQUARE_HPP */

