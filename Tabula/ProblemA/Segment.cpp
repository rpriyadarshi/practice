/*
 * Segment.cpp
 *
 *  Created on: Dec 17, 2011
 *      Author: Rohit Priyadarshi
 */

#include "Segment.h"
#include "Point.h"

namespace PA {
// Main algorithm to calculate the best points. This should run in linear time.
void
Segment::findMaxPoints(const Points& points)
{
	size_t length = getLength();
	size_t minIndex = 0;
	size_t bestMinIndex = 0;
	size_t bestMaxIndex = 0;
	size_t cRun = 0;

	for (size_t maxIndex = 0; maxIndex < points.size(); ++maxIndex)
	{
		cRun = maxIndex - minIndex;

		size_t dRun = calcDistance(minIndex, maxIndex, points);
		while (dRun > length && minIndex < maxIndex)
		{
			++minIndex;
			dRun = calcDistance(minIndex, maxIndex, points);
			cRun = maxIndex - minIndex;
		}

		size_t cBest = bestMaxIndex - bestMinIndex;
		if (cBest < cRun)
		{
			bestMinIndex = minIndex;
			bestMaxIndex = maxIndex;
		}
	}
	setBestMinIndex(bestMinIndex);
	setBestMaxIndex(bestMaxIndex);
}

// Calculate distance between two points picked from the collection
size_t
Segment::calcDistance(size_t min, size_t max, const Points& points) const
{
	size_t size = 0;
	if (min < points.size() && max < points.size())
	{
		const Point* pMin = points[min];
		const Point* pMax = points[max];
		size = pMin->distance(*pMax);
	}
	return size;
}

void
Segment::print(std::ostream& o) const
{
	o << "Requested length: " << getLength() << std::endl;
	o << "Best minimun index: " << getBestMinIndex() << std::endl;
	o << "Best maximum index: " << getBestMaxIndex() << std::endl;
}

} /* namespace PA */
