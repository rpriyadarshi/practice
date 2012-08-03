/*
 * Point.h
 *
 *  Created on: Dec 17, 2011
 *      Author: Rohit Priyadarshi
 *
 *      Purpose: Hold the coordinates of a point
 */

#ifndef POINT_H_
#define POINT_H_

#include <iostream>
#include <cstdlib>

namespace PA {
// This variable is used to format the printing
const size_t PRINT_MAX_POINTS = 10;
// Calculates distance between to points
inline size_t distance(size_t l1, size_t l2) {  return l1 < l2 ? l2 - l1 : l1 - l2; }

////////////////////////////////////////////////////////////////////////////////
// Holds x coordinate of the point
// Can be extended to y coordinate as well, to handle lines with arbitrary
// slope. It adds to complexity a bit more as well as handling of negative
// numbers (negative slope)
//
// The existing solution models projection of coordinates on x-axis, while
// ignoring y-axis. It did not seem that it was even required in the problem
// specification.
////////////////////////////////////////////////////////////////////////////////
class Point {
public: // Constructors/destructors
	Point() : m_x(0) {};
	explicit Point(size_t x) : m_x(x) {}
	virtual ~Point() {};

public: // Public accessors
	size_t getX() { return m_x; }
	const size_t getX() const { return m_x; }

public: // Helpers
	// Calculate distance between points
	size_t distance(const Point& p) const {  return distance(p.getX()); }
	size_t distance(size_t l) const {  return PA::distance(getX(), l); }
	// Fill the x value as specified
	void fill(size_t v) { setX(v); }
	// Fill the x value with a randomly generated value
	void randomFill(size_t begin, size_t maxRange) { setX(std::rand() % maxRange + begin); }
	void print(std::ostream& o) const;

private: // Private accessors
	void setX(size_t x) { m_x = x; }

private: // Data
	size_t m_x;
};

} /* namespace PA */

// Comparison operators. Not all of them are used
inline bool operator==(const PA::Point& p1, const PA::Point& p2)
{
	return p1.getX() == p2.getX();
}

inline bool operator!=(const PA::Point& p1, const PA::Point& p2)
{
	return p1.getX() != p2.getX();
}

inline bool operator<(const PA::Point& p1, const PA::Point& p2)
{
	return p1.getX() < p2.getX();
}

inline bool operator>(const PA::Point& p1, const PA::Point& p2)
{
	return p1.getX() > p2.getX();
}

// Output streaming operators
inline std::ostream& operator<<(std::ostream& o, const PA::Point& p)
{
	p.print(o);
	return o;
}

inline std::ostream& operator<<(const PA::Point& p, std::ostream& o)
{
	p.print(o);
	return o;
}

#endif /* POINT_H_ */
