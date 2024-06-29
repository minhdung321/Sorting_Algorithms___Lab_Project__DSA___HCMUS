#include "Utils.h"

namespace Algorithms
{
	// Documentation: https://en.wikipedia.org/wiki/Selection_sort
	// 1. https://www.geeksforgeeks.org/selection-sort/
	// 2. https://www.tutorialspoint.com/data_structures_algorithms/selection_sort_algorithm.htm

	// Selection sort algorithm - https://en.wikipedia.org/wiki/Selection_sort
	void SelectionSort(int *a, int n)
	{
		for (int i = 0; i < n - 1; ++i)
		{
			int minIndex = i;
			for (int j = i + 1; j < n; ++j)
			{
				if (a[j] < a[minIndex])
				{
					minIndex = j;
				}
			}
			Utils::Swap(a[i], a[minIndex]);
		}
	}

	// Selection sort algorithm with comparisons measured
	size_t SelectionSortComp(int *a, int n)
	{
		size_t comparisons = 0;

		for (int i = 0; i < n - 1; ++i)
		{
			int minIndex = i;
			for (int j = i + 1; j < n; ++j)
			{
				if (++comparisons && a[j] < a[minIndex])
				{
					minIndex = j;
				}
			}
			Utils::Swap(a[i], a[minIndex]);
		}
		return comparisons;
	}

	// Selection sort with recursive - not recommended
	// Selection sort with early termination
	void SelectionSortEarlyTermination(int *a, int n)
	{
		for (int i = 0; i < n - 1; ++i)
		{
			int minIndex = i;
			bool swapped = false;
			for (int j = i + 1; j < n; ++j)
			{
				if (a[j] < a[minIndex])
				{
					minIndex = j;
					swapped = true;
				}
			}
			if (swapped)
				Utils::Swap(a[i], a[minIndex]);
		}
	}

	// Stable selection sort
	void StableSelectionSort(int *a, int n)
	{
		for (int i = 0; i < n - 1; ++i)
		{
			int minIndex = i;
			for (int j = i + 1; j < n; ++j)
			{
				if (a[j] < a[minIndex])
				{
					minIndex = j;
				}
			}
			int key = a[minIndex];
			while (minIndex > i)
			{
				a[minIndex] = a[minIndex - 1];
				--minIndex;
			}
			a[i] = key;
		}
	}
}