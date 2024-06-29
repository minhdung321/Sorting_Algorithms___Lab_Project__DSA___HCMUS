#include "Utils.h"

namespace Algorithms
{
	// Documentation: Slide from co Hai Minh
	// https://www.geeksforgeeks.org/make-mergesort-perform-comparisons-best-case/?ref=lbp
	// https://www.geeksforgeeks.org/in-place-merge-sort/?ref=lbp

	static void merge(int *a, int left, int mid, int right)
	{
		int subArrayOne = mid - left + 1;
		int subArrayTwo = right - mid;

		int *leftArray = new int[subArrayOne],
			*rightArray = new int[subArrayTwo];

		for (int i = 0; i < subArrayOne; i++)
			leftArray[i] = a[left + i];
		for (int j = 0; j < subArrayTwo; j++)
			rightArray[j] = a[mid + 1 + j];

		int indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
		int indexOfMergedArray = left;

		while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo)
		{
			if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo])
			{
				a[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
				indexOfSubArrayOne++;
			}
			else
			{
				a[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
				indexOfSubArrayTwo++;
			}
			indexOfMergedArray++;
		}

		while (indexOfSubArrayOne < subArrayOne)
		{
			a[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
			indexOfMergedArray++;
		}

		while (indexOfSubArrayTwo < subArrayTwo)
		{
			a[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
			indexOfMergedArray++;
		}
		delete[] leftArray;
		delete[] rightArray;
	}

	static size_t mergeComp(int *a, int left, int mid, int right, size_t &comparisions)
	{
		int subArrayOne = mid - left + 1;
		int subArrayTwo = right - mid;

		int *leftArray = new int[subArrayOne],
			*rightArray = new int[subArrayTwo];

		for (int i = 0; i < subArrayOne; i++)
			leftArray[i] = a[left + i];
		for (int j = 0; j < subArrayTwo; j++)
			rightArray[j] = a[mid + 1 + j];

		int indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
		int indexOfMergedArray = left;

		while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo)
		{
			if (++comparisions && leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo])
			{
				a[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
				indexOfSubArrayOne++;
			}
			else
			{
				a[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
				indexOfSubArrayTwo++;
			}
			indexOfMergedArray++;
		}

		while (indexOfSubArrayOne < subArrayOne)
		{
			a[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
			indexOfMergedArray++;
		}

		while (indexOfSubArrayTwo < subArrayTwo)
		{
			a[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
			indexOfMergedArray++;
		}

		delete[] leftArray;
		delete[] rightArray;
		return comparisions;
	}

	void MergeSort(int *a, int n, int begin, int end)
	{
		if (begin >= end)
			return;

		int mid = begin + (end - begin) / 2;
		MergeSort(a, n, begin, mid);
		MergeSort(a, n, mid + 1, end);
		merge(a, begin, mid, end);
	}

	static size_t MergeSortAlgoComp(int *a, int n, int begin, int end, size_t &comparisions)
	{
		if (begin >= end)
			return 0;

		int mid = begin + (end - begin) / 2;
		MergeSortAlgoComp(a, n, begin, mid, comparisions);
		MergeSortAlgoComp(a, n, mid + 1, end, comparisions);
		mergeComp(a, begin, mid, end, comparisions);

		return comparisions;
	}

	size_t MergeSortComp(int *a, int n, int begin, int end)
	{
		size_t comparisions = 0;
		MergeSortAlgoComp(a, n, begin, end, comparisions);
		return comparisions;
	}

	// Merge sort works in O(n) time in best case.
	void MergeSortImprove(int *a, int n, int first, int last)
	{
		if (first < last)
		{
			int mid = (first + last) / 2;
			MergeSortImprove(a, n, first, mid);
			MergeSortImprove(a, n, mid + 1, last);
			if (a[mid] > a[mid + 1])
				merge(a, first, mid, last);
		}
	}

	// In-place Merge Sort with Time Complexity:
	// Worst Case: O(n^2 log n),  Average: O(n (log n)^2), Best: O(log n)
#define __INSERT_THRESH 7
	static void mergeInPlace(int *a, size_t an, size_t bn)
	{
		int *b = a + an, *e = b + bn, *s;

		// Return right now if we're done
		if (an == 0 || bn == 0 || !(*b < *(b - 1)))
			return;

		// Do insertion sort to merge if size of sub-arrays are
		// small enough
		if (an < __INSERT_THRESH && an <= bn)
		{
			for (int *p = b, *v; p > a; p--) // Insert Sort A into B
				for (v = p, s = p - 1; v < e && *v < *s; s = v, v++)
					Utils::Swap(s, v);
			return;
		}

		if (bn < __INSERT_THRESH)
		{
			for (int *p = b, *v; p < e; p++) // Insert Sort B into A
				for (s = p, v = p - 1; s > a && *s < *v; s = v, v--)
					Utils::Swap(s, v);
			return;
		}

		// Find the pivot points.  Basically this is just
		// finding the point in 'a' where we can swap in the
		// first part of 'b' such that after the swap the last
		// element in 'a' will be less than or equal to the
		// least element in 'b'
		int *pa = a, *pb = b;

		for (s = a; s < b && pb < e; s++)
		{
			if (*pb < *pa)
				pb++;
			else
				pa++;
		}
		pa += b - s;

		// Swap first part of b with last part of a
		for (int *la = pa, *fb = b; la < b; la++, fb++)
			Utils::Swap(la, fb);

		// Now merge the two sub-array pairings
		mergeInPlace(a, pa - a, pb - b);
		mergeInPlace(b, pb - b, e - pb);
	} // merge_array_inplace

#undef __INSERT_THRESH

	// Merge Sort Implementation
	void MergeSortInPlace(int *a, size_t n)
	{
		size_t m = (n + 1) / 2;

		// Sort first and second halves
		if (m > 1)
			MergeSortInPlace(a, m);

		if (n - m > 1)
			MergeSortInPlace(a + m, n - m);

		// Now merge the two sorted sub-arrays together
		mergeInPlace(a, m, n - m);
	}
}