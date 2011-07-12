/* 
 * File:   ISearchFile.hpp
 * Author: fancel
 *
 * Created on June 16, 2011, 10:43 AM
 */

#ifndef ISEARCHFILE_HPP
#define	ISEARCHFILE_HPP

#include "Board.hpp"

template <typename T>
class ISearchCase {
public:
    typedef T CoordContainer;
    
    virtual ~ISearchCase() {}
    virtual void operator()(const Board& game, CoordContainer& possibleCase) = 0;
};

#endif	/* ISEARCHFILE_HPP */

