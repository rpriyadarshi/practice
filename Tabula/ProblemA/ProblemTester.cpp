/*
 * ProblemTester.cpp
 *
 *  Created on: Dec 17, 2011
 *      Author: Rohit Priyadarshi
 */

#include "Point.h"
#include "LineCover.h"

namespace PA {
// Simple test for point
void UTestPoints(std::ostream& o)
{
	PA::Point p0;
	PA::Point p1(101);
	PA::Point p2(1209387498423);

	o << "Testing some points: ";
	o << p0 << " " << p1 << " " << p2 << std::endl;
}

// Simple test for random point
void UTestRandomPoints(std::ostream& o)
{
	o << "Testing random points:" << std::endl;
	PA::Point p;
	for (int i = 0; i < 100; ++i)
	{
		p.randomFill(101, 200);
		o << " " << p;
		if (i % PA::PRINT_MAX_POINTS == 0)
		{
			o << std::endl;
		}
	}
	o << std::endl;
}

// Setup a representative problem instance filled with random points
void BringUpRandomProblemInstance(size_t size, std::vector<PA::Point*>& v, size_t begin, size_t maxRange)
{
	for (size_t i = 0; i < size; ++i)
	{
		PA::Point* p = new PA::Point();
		p->randomFill(begin, maxRange);
		v.push_back(p);
	}
}

// Setup increasing points
void BringUpLinearProblemInstance(size_t size, std::vector<PA::Point*>& v)
{
	for (size_t i = 0; i < size; ++i)
	{
		PA::Point* p = new PA::Point();
		p->fill(i);
		v.push_back(p);
	}
}

// Setup problem with known solution in the begining
void BringUpBeginingCustomProblemInstance(std::vector<PA::Point*>& v)
{
	v.push_back(new PA::Point(0));
	v.push_back(new PA::Point(10));
	v.push_back(new PA::Point(20));
	v.push_back(new PA::Point(30));
	// Cluster 1
	v.push_back(new PA::Point(40));
	v.push_back(new PA::Point(41));
	v.push_back(new PA::Point(42));
	v.push_back(new PA::Point(43));
	v.push_back(new PA::Point(44));
	v.push_back(new PA::Point(45));
	v.push_back(new PA::Point(46));
	v.push_back(new PA::Point(47));

	v.push_back(new PA::Point(50));
	v.push_back(new PA::Point(60));
	v.push_back(new PA::Point(70));
	// CLuster 2
	v.push_back(new PA::Point(80));
	v.push_back(new PA::Point(81));
	v.push_back(new PA::Point(82));
	v.push_back(new PA::Point(83));
	v.push_back(new PA::Point(84));
	v.push_back(new PA::Point(85));

	v.push_back(new PA::Point(90));
	v.push_back(new PA::Point(100));
	v.push_back(new PA::Point(110));
	v.push_back(new PA::Point(120));
	// Cluster 3
	v.push_back(new PA::Point(130));
	v.push_back(new PA::Point(131));
	v.push_back(new PA::Point(132));

	v.push_back(new PA::Point(140));
	v.push_back(new PA::Point(150));
}

// Setup problem with known solution in the middle
void BringUpMiddleCustomProblemInstance(std::vector<PA::Point*>& v)
{
	v.push_back(new PA::Point(0));
	v.push_back(new PA::Point(10));
	v.push_back(new PA::Point(20));
	v.push_back(new PA::Point(30));
	// Cluster 1
	v.push_back(new PA::Point(40));
	v.push_back(new PA::Point(41));
	v.push_back(new PA::Point(42));

	v.push_back(new PA::Point(50));
	v.push_back(new PA::Point(60));
	v.push_back(new PA::Point(70));
	// CLuster 2
	v.push_back(new PA::Point(80));
	v.push_back(new PA::Point(81));
	v.push_back(new PA::Point(82));
	v.push_back(new PA::Point(83));
	v.push_back(new PA::Point(84));
	v.push_back(new PA::Point(85));
	v.push_back(new PA::Point(86));
	v.push_back(new PA::Point(87));

	v.push_back(new PA::Point(90));
	v.push_back(new PA::Point(100));
	v.push_back(new PA::Point(110));
	v.push_back(new PA::Point(120));
	// Cluster 3
	v.push_back(new PA::Point(130));
	v.push_back(new PA::Point(131));
	v.push_back(new PA::Point(132));

	v.push_back(new PA::Point(140));
	v.push_back(new PA::Point(150));
}

// Setup problem with known solution at the end
void BringUpEndingCustomProblemInstance(std::vector<PA::Point*>& v)
{
	v.push_back(new PA::Point(0));
	v.push_back(new PA::Point(10));
	v.push_back(new PA::Point(20));
	v.push_back(new PA::Point(30));
	// Cluster 1
	v.push_back(new PA::Point(40));
	v.push_back(new PA::Point(41));
	v.push_back(new PA::Point(42));

	v.push_back(new PA::Point(50));
	v.push_back(new PA::Point(60));
	v.push_back(new PA::Point(70));
	// CLuster 2
	v.push_back(new PA::Point(80));
	v.push_back(new PA::Point(81));
	v.push_back(new PA::Point(82));
	v.push_back(new PA::Point(83));
	v.push_back(new PA::Point(84));
	v.push_back(new PA::Point(85));

	v.push_back(new PA::Point(90));
	v.push_back(new PA::Point(100));
	v.push_back(new PA::Point(110));
	v.push_back(new PA::Point(120));
	// Cluster 3
	v.push_back(new PA::Point(130));
	v.push_back(new PA::Point(131));
	v.push_back(new PA::Point(132));
	v.push_back(new PA::Point(133));
	v.push_back(new PA::Point(134));
	v.push_back(new PA::Point(135));
	v.push_back(new PA::Point(136));
	v.push_back(new PA::Point(137));

	v.push_back(new PA::Point(140));
	v.push_back(new PA::Point(150));
}

// Tear down the problem instance
void TearDownProblemInstance(std::vector<PA::Point*>& v)
{
	std::vector<PA::Point*>::iterator iter;
	for (iter = v.begin(); iter != v.end(); ++iter)
	{
		PA::Point* p = (*iter);
		delete p;
	}
}
} /* namespace PA */
