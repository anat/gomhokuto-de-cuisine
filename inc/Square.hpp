/* 
 * File:   Square.hpp
 * Author: fancel
 *
 * Created on May 5, 2011, 12:19 PM
 */

#ifndef SQUARE_HPP
#define	SQUARE_HPP

#include "Types.hpp"

#define PLAYER(x)       (0x0000000F & x)
#define IS_TAKABLE(x)   (0x000000F0 & (x << 4))
#define HORZ(x)         (0x00000F00 & (x << 8))
#define VERT(x)         (0x0000F000 & (x << 12))
#define DIAGL(x)        (0x000F0000 & (x << 16))
#define DIAGR(x)        (0x00F00000 & (x << 20))

#define GET_PLAYER(x)      (x & 0x0000000F)
#define GET_TAKABLE(x)     ((x & 0x000000F0) >> 4)
#define GET_HORZ(x)        ((x & 0x00000F00) >> 8)
#define GET_VERT(x)        ((x & 0x0000F000) >> 12)
#define GET_DIAGL(x)       ((x & 0x000F0000) >> 16)
#define GET_DIAGR(x)       ((x & 0x00F00000) >> 20)

class Square {

public:
    struct Data{
        unsigned short player : 4;
        unsigned short is_takable : 4;
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

    void setHorz(unsigned int lineSize);
    void setVert(unsigned int lineSize);
    void setDiagl(unsigned int lineSize);
    void setDiagr(unsigned int lineSize);
    unsigned int getHorz() const;
    unsigned int getVert() const;
    unsigned int getDiagl() const;
    unsigned int getDiagr() const;
    
private:
     int32_t _data;
};

#endif	/* SQUARE_HPP */

