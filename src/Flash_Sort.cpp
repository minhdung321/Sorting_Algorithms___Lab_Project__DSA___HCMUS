#include "Utils.h"
#include <algorithm>

namespace Algorithms
{
	// Documentation: https://en.wikipedia.org/wiki/Flashsort
	// 1. https://codelearn.io/sharing/flash-sort-thuat-toan-sap-xep-than-thanh
	// 2. https://www.w3resource.com/javascript-exercises/searching-and-sorting-algorithm/searching-and-sorting-algorithm-exercise-12.php
	// 3. https://www.educative.io/answers/what-is-flash-sort

	// Works well with nearly uniformly distributed data
	void FlashSort(int *a, int n)
	{
		int m = static_cast<int>(0.45f * n); // Convert to integer
		int *l = new int[m]{0};

		int min = a[0], max = 0; // Find the minimum element

		for (int i = 1; i < n; ++i)
		{
			if (a[i] < min)
				min = a[i];
			if (a[i] > a[max])
				max = i;
		}

		if (min == a[max])
		{
			delete[] l;
			return; // All elements are the same
		}

		double c1 = static_cast<double>(m - 1) / (a[max] - min);

		for (int i = 0; i < n; ++i)
		{
			int k = static_cast<int>(c1 * (a[i] - min));
			++l[k];
		}

		for (int p = 1; p < m; ++p)
			l[p] += l[p - 1];

		Utils::Swap(a[0], a[max]);

		// Permutation
		int move = 0, j = 0, k = m - 1;
		while (move < (n - 1))
		{
			while (j > (l[k] - 1))
			{
				j++;
				k = static_cast<int>(c1 * (a[j] - min)); // Find the class
			}

			int flash = a[j]; // Element to be inserted

			while (j != l[k]) // While not the last element of the class
			{
				k = static_cast<int>(c1 * (flash - min));
				int hold = a[--l[k]];
				a[l[k]] = flash;
				flash = hold;
				++move;
			}
		}

		// Insertion sort
		for (int j = 1; j < n; ++j)
		{
			int key = a[j];
			int i = j - 1;
			while (i >= 0 && a[i] > key)
			{
				a[i + 1] = a[i];
				i--;
			}
			a[i + 1] = key;
		}

		delete[] l;
	}

	size_t FlashSortComp(int *a, int n)
	{
		size_t comparisions = 0;

		int m = static_cast<int>(0.45f * n);
		int *l = new int[m]{0};

		int min = a[0], max = 0; // Find the minimum element

		for (int i = 1; i < n; ++i)
		{
			if (++comparisions && a[i] < min)
				min = a[i];
			if (++comparisions && a[i] > a[max])
				max = i;
		}

		// All elements are the same
		if (++comparisions && min == a[max])
		{
			delete[] l;
			return comparisions;
		}

		double c1 = static_cast<double>(m - 1) / (a[max] - min);

		// Find the class
		for (int i = 0; i < n; ++i)
		{
			int k = static_cast<int>(c1 * (a[i] - min));
			++l[k];
		}

		// Cumulative distribution
		for (int p = 1; p < m; ++p)
			l[p] += l[p - 1];

		Utils::Swap(a[0], a[max]);

		// Permutation
		int move = 0, j = 0, k = m - 1;
		while (move < (n - 1))
		{
			while (++comparisions && j > (l[k] - 1))
			{
				j++;
				k = static_cast<int>(c1 * (a[j] - min)); // Find the class
			}

			int flash = a[j]; // Element to be inserted

			while (++comparisions && j != l[k]) // While not the last element of the class
			{
				k = static_cast<int>(c1 * (flash - min));
				int hold = a[--l[k]];
				a[l[k]] = flash;
				flash = hold;
				++move;
			}
		}

		// Insertion sort
		for (int j = 1; j < n; ++j)
		{
			int key = a[j];
			int i = j - 1;
			while (i >= 0 && ++comparisions && a[i] > key)
			{
				a[i + 1] = a[i];
				i--;
			}
			a[i + 1] = key;
		}

		delete[] l;

		return comparisions;
	}

	// Flash sort kết hợp với Quick sort
	// Cải thiện hơn với trường hợp dữ liệu phân phối không đều
	// Nhưng hoàn toàn không hiệu quả hơn với phiên bản gốc đối với dữ liệu phân phối đều hoặc gần đều
	void FlashSortWithQuickSort(int *a, int n)
	{
		int m = static_cast<int>(0.45f * n);
		int *l = new int[m]{0};

		int min = a[0], max = 0; // Find the minimum element

		for (int i = 1; i < n; ++i)
		{
			if (a[i] < min)
				min = a[i];
			if (a[i] > a[max])
				max = i;
		}

		if (min == a[max])
		{
			delete[] l;
			return; // All elements are the same
		}

		double c1 = static_cast<double>(m - 1) / (a[max] - min);

		for (int i = 0; i < n; ++i)
		{
			int k = static_cast<int>(c1 * (a[i] - min));
			++l[k];
		}

		for (int p = 1; p < m; ++p)
			l[p] += l[p - 1];

		Utils::Swap(a[0], a[max]);

		// Permutation
		int move = 0, j = 0, k = m - 1;
		while (move < (n - 1))
		{
			while (j > (l[k] - 1))
			{
				j++;
				k = static_cast<int>(c1 * (a[j] - min)); // Find the class
			}

			int flash = a[j]; // Element to be inserted

			while (j != l[k]) // While not the last element of the class
			{
				k = static_cast<int>(c1 * (flash - min));
				int hold = a[--l[k]];
				a[l[k]] = flash;
				flash = hold;
				++move;
			}
		}

		// Quick sort with STL
		for (int i = 0; i < m - 1; ++i)
		{
			int left = l[i];
			int right = l[i + 1] - 1;
			if (left < right)
				std::sort(a + left, a + right + 1);
		}

		delete[] l;
	}
}