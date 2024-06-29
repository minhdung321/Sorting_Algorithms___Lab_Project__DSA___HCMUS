#include "Utils.h"
#include <iostream>

namespace Algorithms
{
	// Documentation: https://www.geeksforgeeks.org/radix-sort/
	// https://github.com/KirillLykov/int-sort-bmk

	static void countingSort(int *a, int n, int exp)
	{
		int *output = new int[n];

		if (output == nullptr)
		{
			std::cerr << "[Radix Sort] Memory allocation failed\n";
			return;
		}

		int i, count[10] = {0};

		for (i = 0; i < n; i++)
			count[(a[i] / exp) % 10]++;

		for (i = 1; i < 10; i++)
			count[i] += count[i - 1];

		for (i = n - 1; i >= 0; i--)
		{
			output[count[(a[i] / exp) % 10] - 1] = a[i];
			count[(a[i] / exp) % 10]--;
		}

		for (i = 0; i < n; i++)
		{
			a[i] = output[i];
		}

		delete[] output;
	}

	static void countingSortComp(int *a, int n, int exp, size_t &comparisions)
	{
		int *output = new int[n];

		if (output == nullptr)
		{
			std::cerr << "[Radix Sort] Memory allocation failed\n";
			return;
		}

		int i, count[10] = {0};

		for (i = 0; i < n; i++)
			count[(a[i] / exp) % 10]++;

		for (i = 1; i < 10; i++)
			count[i] += count[i - 1];

		for (i = n - 1; i >= 0; i--)
		{
			output[count[(a[i] / exp) % 10] - 1] = a[i];
			count[(a[i] / exp) % 10]--;
		}

		for (i = 0; i < n; i++)
		{
			a[i] = output[i];
		}

		delete[] output;
	}

	void RadixSort(int *a, int n)
	{
		int m = Utils::MaxElement(a, n);

		for (int exp = 1; m / exp > 0; exp *= 10)
		{
			countingSort(a, n, exp);
		}
	}

	static int findMaxComp(int *a, int n, size_t &comparisions)
	{
		int max = a[0];

		for (int i = 1; i < n; i++)
		{
			if (++comparisions && a[i] > max)
				max = a[i];
		}

		return max;
	}

	size_t RadixSortComp(int *a, int n)
	{
		size_t comparisions = 0;

		int m = findMaxComp(a, n, comparisions);

		for (int exp = 1; ++comparisions && m / exp > 0; exp *= 10)
		{
			countingSortComp(a, n, exp, comparisions);
		}

		return comparisions;
	}
}