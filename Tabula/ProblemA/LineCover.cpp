/*
 * LineCover.cpp
 *
 *  Created on: Dec 17, 2011
 *      Author: Rohit Priyadarshi
 */

#include "LineCover.h"

namespace PA {

void
LineCover::print(std::ostream& o) const
{
	o << "Printing data points:" << std::endl;
	size_t i = 0;
	for (Points::const_iterator citer = getPoints().begin();
			citer != getPoints().end(); ++citer)
	{
		const Point* p = (*citer);
		o << " " << *p;
		++i;
		if (i % PA::PRINT_MAX_POINTS == 0)
		{
			o << std::endl;
		}
	}
	o << std::endl;
	o << getSegment();
	o << "Best length: " << getSegment().getDistance(getPoints()) << std::endl;
	o << "Best minimum point: " << *getPoints()[getSegment().getBestMinIndex()] << std::endl;
	o << "Best maximum point: " << *getPoints()[getSegment().getBestMaxIndex()] << std::endl;
	o << std::endl;
}

} /* namespace PA */
