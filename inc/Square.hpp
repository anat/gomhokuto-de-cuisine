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
#define GET_HORZ_BLOCK(x) ((x & 0x03000000) >> 24)
#define GET_VERT_BLOCK(x) ((x & 0x0C000000) >> 26)
#define GET_DIAGL_BLOCK(x) ((x & 0x30000000) >> 28)
#define GET_DIAGR_BLOCK(x) ((x & 0xC0000000) >> 30)

class Square {

public:
    struct Data{
        unsigned short player : 4;
        unsigned short is_takable : 4;
        unsigned short horz : 4;
        unsigned short vert : 4;
        unsigned short diagl : 4;
        unsigned short diagr : 4;
        unsigned short horz_block : 2;
        unsigned short vert_block : 2;
        unsigned short diagl_block : 2;
        unsigned short diagr_block : 2;
    };
    
public:
    Square();
    virtual ~Square();

    int32_t             getRawData() const;
    void                setRawData(int32_t mask);
    const Square::Data &      getData() const;
    Square::Data &      getData();
    void                setData(Square::Data & data);
    void                dumpData() const;

    void setHorz(unsigned int lineSize);
    void setVert(unsigned int lineSize);
    void setDiagl(unsigned int lineSize);
    void setDiagr(unsigned int lineSize);
    void setPlayer(unsigned int player);
    void setIsTackable(bool value);
    void setHorzBlock(unsigned int endBlock);
    void setVertBlock(unsigned int endBlock);
    void setDiagrBlock(unsigned int endBlock);
    void setDiaglBlock(unsigned int endBlock);
    unsigned int getHorz() const;
    unsigned int getVert() const;
    unsigned int getDiagl() const;
    unsigned int getDiagr() const;
    unsigned int getHorzBlock() const;
    unsigned int getVertBlock() const;
    unsigned int getDiagrBlock() const;
    unsigned int getDiaglBlock() const;
    unsigned int getPlayer() const;
    
private:
     int32_t _data;
};

#endif	/* SQUARE_HPP */

