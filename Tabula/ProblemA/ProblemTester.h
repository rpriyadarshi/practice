/*
 * ProblemTester.h
 *
 *  Created on: Dec 17, 2011
 *      Author: Rohit Priyadarshi
 *
 *      Testing functions
 */

#ifndef PROBLEMTESTER_H_
#define PROBLEMTESTER_H_

namespace PA {
// Simple test for point
void UTestPoints(std::ostream& o);
// Simple test for random point
void UTestRandomPoints(std::ostream& o);
// Setup a representative problem instance filled with random points
void BringUpRandomProblemInstance(size_t size, std::vector<PA::Point*>& v, size_t begin, size_t maxRange);
// Setup increasing points
void BringUpLinearProblemInstance(size_t size, std::vector<PA::Point*>& v);
// Setup problem with known solution in the begining
void BringUpBeginingCustomProblemInstance(std::vector<PA::Point*>& v);
// Setup problem with known solution in the middle
void BringUpMiddleCustomProblemInstance(std::vector<PA::Point*>& v);
// Setup problem with known solution at the end
void BringUpEndingCustomProblemInstance(std::vector<PA::Point*>& v);
// Tear down the problem instance
void TearDownProblemInstance(std::vector<PA::Point*>& v);
} /* namespace PA */


#endif /* PROBLEMTESTER_H_ */
