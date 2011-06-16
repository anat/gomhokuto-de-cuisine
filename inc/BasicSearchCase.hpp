/* 
 * File:   BasicSearchCase.hpp
 * Author: fancel
 *
 * Created on June 16, 2011, 10:50 AM
 */

#ifndef BASICSEARCHCASE_HPP
#define	BASICSEARCHCASE_HPP

#include <vector>

#include "ISearchFile.hpp"
#include "Coord.hpp"

class BasicSearchCase : public ISearchCase< std::vector<Coord> >
{
public:
    void operator()(Board& game, CoordContainer& possibleCase);
};

#endif	/* BASICSEARCHCASE_HPP */

