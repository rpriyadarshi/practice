/*
 * Segment.h
 *
 *  Created on: Dec 17, 2011
 *      Author: Rohit Priyadarshi
 */

#ifndef SEGMENT_H_
#define SEGMENT_H_

#include <iostream>
#include <vector>

namespace PA {
class Point;

////////////////////////////////////////////////////////////////////////////////
// Algorithms class that does final calculations
////////////////////////////////////////////////////////////////////////////////
class Segment {
public: // Typedefs
	typedef typename std::vector<Point*> Points;

public: // Constructor/destructor
	Segment(size_t l, const Points& points)
		: m_length(l), m_bestMinIndex(0), m_bestMaxIndex(points.size()) {};
	virtual ~Segment() {};

public: // Accessors
	size_t getLength() const { return m_length; }
	size_t getBestMinIndex() const { return m_bestMinIndex; }
	size_t getBestMaxIndex() const { return m_bestMaxIndex; }

private: // Accessors
	size_t getLength() { return m_length; }
	size_t getBestMinIndex() { return m_bestMinIndex; }
	size_t getBestMaxIndex() { return m_bestMaxIndex; }
	void setLength(size_t v) { m_length = v; }
	void setBestMinIndex(size_t v) { m_bestMinIndex = v; }
	void setBestMaxIndex(size_t v) { m_bestMaxIndex = v; }

public: // Helpers
	// Main algorithm to find best points
	void findMaxPoints(const Points& points);
	size_t getDistance(const Points& points) const { return calcDistance(getBestMinIndex(), getBestMaxIndex(), points); }
	void print(std::ostream& o) const;

private:
	// Calculate distance between two points picked from the collection
	size_t calcDistance(size_t min, size_t max, const Points& points) const;

public: // Data
	size_t m_length;
	size_t m_bestMinIndex;
	size_t m_bestMaxIndex;
};

} /* namespace PA */

inline std::ostream& operator<<(std::ostream& o, const PA::Segment& s)
{
	s.print(o);
	return o;
}

inline std::ostream& operator<<(const PA::Segment& s, std::ostream& o)
{
	s.print(o);
	return o;
}

#endif /* SEGMENT_H_ */
