#include "Utils.h"

namespace Algorithms
{
	// Documentation:
	// 1. https://www.geeksforgeeks.org/bubble-sort/
	// 2. https://www.tutorialspoint.com/data_structures_algorithms/bubble_sort_algorithm.htm

	// Bubble sort algorithm
	void BubbleSort(int *a, int n)
	{
		for (int i = 0; i < n - 1; ++i)
		{
			for (int j = 0; j < n - i - 1; ++j)
			{
				if (a[j] > a[j + 1])
				{
					Utils::Swap(a[j], a[j + 1]);
				}
			}
		}
	}

	// Bubble sort algorithm with comparisons measured
	size_t BubbleSortComp(int *a, int n)
	{
		size_t comparisons = 0;

		for (int i = 0; i < n - 1; ++i)
		{
			for (int j = 0; j < n - i - 1; ++j)
			{
				if (++comparisons && a[j] > a[j + 1])
				{
					Utils::Swap(a[j], a[j + 1]);
				}
			}
		}
		return comparisons;
	}
	// Bubble sort optimized algorithm
	// early termination if the inner loop didn't cause any swap
	void BubbleSortEarlyTermination(int *a, int n)
	{
		bool swapped = false;
		for (int i = 0; i < n - 1; ++i)
		{
			swapped = false;
			for (int j = 0; j < n - i - 1; ++j)
			{
				if (a[j] > a[j + 1])
				{
					Utils::Swap(a[j], a[j + 1]);
					swapped = true;
				}
			}
			if (!swapped)
				break;
		}
	}

	// Recursive bubble sort - not recommended
	// sharker sort/cocktail sort
}