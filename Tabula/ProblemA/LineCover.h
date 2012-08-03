/*
 * LineCover.h
 *
 *  Created on: Dec 17, 2011
 *      Author: Rohit Priyadarshi
 */

#ifndef LINECOVER_H_
#define LINECOVER_H_

#include <vector>
#include <algorithm>
#include "Point.h"
#include "Segment.h"

namespace PA {

// Comparison function for sort
inline bool compare (const Point* p1, const Point* p2)
{
	return (p1 && p2) ? *p1 < *p2 : false;
}
////////////////////////////////////////////////////////////////////////////////
// Main class that takes the problem and gives a solution
////////////////////////////////////////////////////////////////////////////////
class LineCover {
public: // Typedefs
	typedef typename std::vector<Point*> Points;

public: // Constructor/destructor
	LineCover(Points& points, size_t l) : m_points(points), m_segment(l, points) {};
	virtual ~LineCover() {};

public: // Accessors
	const Points& getPoints() const { return m_points; }
	const Segment& getSegment() const { return m_segment; }

public: // Helpers
	void solve() { sort(); findMaxPoints(); }
	void print(std::ostream& o) const;

private: // Helpers
	// The sorting algorithm is STL stable_sort. It can be replaced if a more
	// efficient solution is found. We could have chosen counting or radix sort
	// for linear time performance. std::stable_sort was chosen due to easy
	// availability
	void sort() { std::stable_sort (getPoints().begin(), getPoints().end(), compare); }
	void findMaxPoints() { getSegment().findMaxPoints(getPoints()); }

private: // Accessors
	Points& getPoints() { return m_points; }
	Segment& getSegment() { return m_segment; }

private: // data
	Points& m_points;
	Segment m_segment;
};

} /* namespace PA */

inline std::ostream& operator<<(std::ostream& o, const PA::LineCover& lc)
{
	lc.print(o);
	return o;
}

inline std::ostream& operator<<(const PA::LineCover& lc, std::ostream& o)
{
	lc.print(o);
	return o;
}

#endif /* LINECOVER_H_ */
