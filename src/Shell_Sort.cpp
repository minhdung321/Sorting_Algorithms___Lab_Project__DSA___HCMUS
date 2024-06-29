#include <vector>
#include <algorithm>

#include "Utils.h"

namespace Algorithms
{
	// Documentation: https://en.wikipedia.org/wiki/Shellsort
	// 1. https://www.scholarhat.com/tutorial/datastructures/shell-sort-in-data-structures
	// 2. https://www.geeksforgeeks.org/shellsort/
	// 3. https://www.tutorialspoint.com/data_structures_algorithms/shell_sort_algorithm.htm
	// 4. https://www.programiz.com/dsa/shell-sort
	// 5. Analysis of Shellsort and Related Algorithms - Robert Sedgewick - Princeton University

	// Shell sort algorithm - https://en.wikipedia.org/wiki/Shellsort
	void ShellSort(int *a, int n)
	{
		for (int gap = n / 2; gap > 0; gap /= 2)
		{
			for (int i = gap; i < n; ++i)
			{
				int temp = a[i];
				int j;
				for (j = i; j >= gap && a[j - gap] > temp; j -= gap)
				{
					a[j] = a[j - gap];
				}

				a[j] = temp;
			}
		}
	}

	// Shell sort algorithm with comparisons measured
	size_t ShellSortComp(int *a, int n)
	{
		size_t comparisons = 0;

		for (int gap = n / 2; gap > 0; gap /= 2)
		{
			for (int i = gap; i < n; ++i)
			{
				int temp = a[i];
				int j;
				for (j = i; j >= gap; j -= gap)
				{
					if (++comparisons && a[j - gap] <= temp)
						break;
					a[j] = a[j - gap];
				}
				a[j] = temp;
			}
		}
		return comparisons;
	}

	// Shell sort algorithm with Knuth's sequence
	void ShellSortKnuth(int *a, int n)
	{
		int interval = 1;
		while (interval < n / 3)
			interval = interval * 3 + 1;

		// Keep reducing the gap until it becomes 1
		while (interval > 0)
		{
			for (int i = interval; i < n; ++i)
			{
				int valueToInsert = a[i];

				int j = i;

				while (j > interval - 1 && a[j - interval] > valueToInsert)
				{
					a[j] = a[j - interval];
					j -= interval;
				}

				a[j] = valueToInsert; // Insert the value
			}

			interval = (interval - 1) / 3; // Reduce the gap
		}
	}

	// Shell sort algorithm with Sedgewick's sequence
	void ShellSortSedgewick(int *a, int n)
	{
		std::vector<int> sedgewickSeq; // Sedgewick's sequence
		int k = 0;

		// Generate Sedgewick's sequence
		while (true)
		{
			int gap_1 = 4 * (1 << k) - 3 * (1 << (k / 2)) + 1;
			int gap_2 = 9 * (1 << k) - 9 * (1 << (k / 2)) + 1;

			if (gap_1 < n)
				sedgewickSeq.emplace_back(gap_1);
			if (gap_2 < n)
				sedgewickSeq.emplace_back(gap_2);
			if (gap_1 >= n && gap_2 >= n)
				break;

			k++;
		}

		// Reverse the sequence
		for (int i = 0; i < sedgewickSeq.size() / 2; ++i)
		{
			Utils::Swap(sedgewickSeq[i], sedgewickSeq[sedgewickSeq.size() - i - 1]);
		}

		// Start sorting
		for (int gap : sedgewickSeq)
		{
			for (int i = gap; i < n; ++i)
			{
				int valueToInsert = a[i];
				int j = i;
				while (j >= gap && a[j - gap] > valueToInsert)
				{
					a[j] = a[j - gap];
					j -= gap;
				}

				a[j] = valueToInsert;
			}
		}
	}
}