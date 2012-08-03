/*
 * main.cpp
 *
 *  Created on: Sep 5, 2011
 *      Author: rohit
 */
/*
#include <iostream>
inline double calc()
{
	return -1;
}

int main (int argc, char** argv) {
	int month0 = 9, day0 = 7;
	//int month1 = 09, day1 = 07;
	//int car = 1024, auto = 2048;
	int ival = ival;
	//std::cin >> int input_value;
	double wage;
	double salary = wage = 9999.99;
	//double calc = calc();

	std::cout << month0 << std::endl;
	std::cout << ival << std::endl;
	std::cout << salary << std::endl;
	std::cout << wage << std::endl;
	//std::cout << calc << std::endl;
	return 0;
}

*/

#include <iostream>

inline void incr(int a[], int size) {
	bool overflow = true;
	if (a[size-1] == 9) {
		a[size-1] = 0;
		for (int i = size-2; i >= 0; --i) {
			if (a[i] == 9) {
				a[i] = 0;
			} else {
				a[i] += 1;
				overflow = false;
				break;
			}
		}
	} else {
		a[size-1] += 1;
	}

	if (overflow) {
		std::cout << "overflow" << std::endl;
	}
	for(int j = 0; j < size; ++j) {
		std::cout << a[j] << " " << std::endl;
	}
	std::cout << std::endl;
}

int main(int argc, const char** argv) {
	int a[] = {7, 9, 9};
	incr(a, sizeof(a)/sizeof(int));
	return 0;
}
