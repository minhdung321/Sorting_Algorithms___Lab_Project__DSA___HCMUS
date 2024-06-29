#include "Utils.h"

namespace Algorithms
{
	// Documentation: https://en.wikipedia.org/wiki/Insertion_sort
	// 1. https://www.geeksforgeeks.org/insertion-sort/
	// 2. https://www.tutorialspoint.com/data_structures_algorithms/insertion_sort_algorithm.htm

	void InsertionSort(int *a, int n)
	{
		for (int i = 1; i < n; ++i)
		{
			int key = a[i];
			int j = i - 1;
			while (j >= 0 && a[j] > key)
			{
				a[j + 1] = a[j];
				--j;
			}
			a[j + 1] = key;
		}
	}

	size_t InsertionSortComp(int *a, int n)
	{
		size_t comparisons = 0;
		for (int i = 1; i < n; ++i)
		{
			int key = a[i];
			int j = i - 1;
			while (j >= 0 && ++comparisons && a[j] > key)
			{
				a[j + 1] = a[j];
				--j;
			}
			a[j + 1] = key;
		}
		return comparisons;
	}

	// Insertion sort algorithm with binary search
	void InsertionSortBinarySearch(int *a, int n)
	{
		for (int i = 1; i < n; ++i)
		{
			int key = a[i];
			int j = i - 1;
			int index = -1;
			int low = 0;
			int high = j;
			while (low <= high)
			{
				int mid = low + (high - low) / 2;
				if (a[mid] > key)
				{
					index = mid;
					high = mid - 1;
				}
				else
				{
					low = mid + 1;
				}
			}
			if (index != -1)
			{
				for (int k = j; k >= index; --k)
				{
					a[k + 1] = a[k];
				}
				a[index] = key;
			}
		}
	}
	// Shell sort
	// Insertion sort with recursive - not recommended
}