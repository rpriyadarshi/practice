/*
 * main.cpp
 *
 *  Created on: Sep 16, 2011
 *      Author: rohit
 */

#include <iostream>
#include <stdlib.h>
#include <time.h>

void printArray(const int *beg, const int *end)
{
	if (beg == 0 || end == 0 || beg > end)
	{
		return;
	}
	for(const int *iter = beg; iter != end; ++iter)
	{
		std::cout << *iter << " ";
	}
	std::cout << std::endl;
}

void swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

int partition(int *a, int n, int p, int r)
{
	if (p > n || r > n || r-p < 0 || r-p > n)
	{
		return -1;
	}
	int i = p;
	int x = *(a+r);
	for(int j = p; j < r; ++j)
	{
		if (*(a+j) <= x)
		{
			swap(&a[j], &a[i]);
			++i;
		}
	}
	swap(&a[i], &a[r]);
	return i;
}

int rpartition(int *a, int n, int p, int r)
{
	int i = rand() % (r-p);
	std::cout << i << std::endl;
	swap(&a[i], &a[i]);
	return partition(a, n, p, r);
}

void quick_sort(int *a, int n, int p, int r)
{
	if (p < r)
	{
		int q = partition(a, n, p, r);
		quick_sort(a, n, p, q-1);
		quick_sort(a, n, q+1, r);
	}
}

void rquick_sort(int *a, int n, int p, int r)
{
	if (p < r)
	{
		int q = rpartition(a, n, p, r);
		rquick_sort(a, n, p, q-1);
		rquick_sort(a, n, q+1, r);
	}
}

void run_test(int *a, int n)
{
	int r = n-1;
	printArray(a, a+n);
	rquick_sort(a, n, 0, r);
	printArray(a, a+n);
}

int main(int argc, const char** argv)
{
	srand(time(0));
	int a[] = {2, 8, 7, 1, 3, 5, 6, 4};
	run_test(a, sizeof(a)/sizeof(int));
	int b[] = {13, 19, 9, 5, 12, 8, 7, 4, 21, 2, 6, 11, 12, 45,34, 56, 6, 234, 2, 1, 23, 3, 4, 45, 5};
	run_test(b, sizeof(b)/sizeof(int));
	return 0;
}
