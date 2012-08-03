/*
 * main.cpp
 *
 *  Created on: Dec 17, 2011
 *      Author: Rohit Priyadarshi
 *
 *      Problem Statement: The input is a collection of N arbitrary points on a line and a length L.
 *      Please provide an algorithm, coded in C++, that finds an interval of length L that covers as
 *      many of the points as possible, where a point p is covered by an interval [x,x+L] if x<=p<=x+L.
 *
 *      Assumptions about the problem:
 *      1. L < 2^64
 *      2. N < 2^64
 *      3. The line is parallel to x-axis or solution applies to projection of line and points on x-axis
 *      4. x >= 0, no negative points are considered. Negative numbers may be handled by shifting the
 *      problem instance to positive domain.
 *		5. No explicit memory management other than system default.
 *
 *      Algorithm:
 *      1. Sort the input vector of points in increasing order
 *      2. scan through the vectors and keep track of the minimum and
 *      maximum distance between the points
 */

#include <iostream>
#include <vector>
#include "LineCover.h"
#include "ProblemTester.h"

// A variety of testcases that would help test robustness
void Test1()
{
	std::vector<PA::Point*> v;
	//PA::BringUpRandomProblemInstance(1000000, v, 0, 20000000);
	PA::BringUpRandomProblemInstance(100, v, 0, 200);

	PA::LineCover lc(v, 9);
	lc.solve();
	std::cout << lc;

	PA::TearDownProblemInstance(v);
}

void Test2()
{
	std::vector<PA::Point*> v;
	PA::BringUpLinearProblemInstance(100, v);

	PA::LineCover lc(v, 9);
	lc.solve();
	std::cout << lc;

	PA::TearDownProblemInstance(v);
}

void Test3()
{
	std::vector<PA::Point*> v;
	PA::BringUpBeginingCustomProblemInstance(v);

	PA::LineCover lc(v, 9);
	lc.solve();
	std::cout << lc;

	PA::TearDownProblemInstance(v);
}

void Test4()
{
	std::vector<PA::Point*> v;
	PA::BringUpMiddleCustomProblemInstance(v);

	PA::LineCover lc(v, 9);
	lc.solve();
	std::cout << lc;

	PA::TearDownProblemInstance(v);
}

void Test5()
{
	std::vector<PA::Point*> v;
	PA::BringUpEndingCustomProblemInstance(v);

	PA::LineCover lc(v, 9);
	lc.solve();
	std::cout << lc;

	PA::TearDownProblemInstance(v);
}

int main (int argc, char** argv)
{
	srand(time(0));
	PA::UTestPoints(std::cout);
	PA::UTestRandomPoints(std::cout);
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();

	return 0;
}
