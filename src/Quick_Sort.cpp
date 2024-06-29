#include "Utils.h"

namespace Algorithms
{
	// Documentation: Slide co Hai Minh
	// https://en.wikipedia.org/wiki/Quicksort
	// https://en.wikipedia.org/wiki/Quickselect: consider for selection sort class
	// https://algs4.cs.princeton.edu/lectures/23DemoPartitioning.pdf
	// https://www.geeksforgeeks.org/dual-pivot-quicksort/?ref=lbp
	// https://www.geeksforgeeks.org/3-way-quicksort-dutch-national-flag/?ref=lbp

	static int partition(int *a, int l, int r)
	{
		int random = Utils::GetRandValue(l, r);
		Utils::Swap(a[random], a[r]);
		int pivot = a[r];
		int i = l - 1;

		for (int j = l; j < r; j++)
		{
			if (a[j] < pivot)
			{
				i++;
				Utils::Swap(a[i], a[j]);
			}
		}
		Utils::Swap(a[i + 1], a[r]);
		return i + 1;
	}

	static int partitionComp(int *a, int l, int r, size_t &comparisions)
	{
		int random = Utils::GetRandValue(l, r);
		Utils::Swap(a[random], a[r]);
		int pivot = a[r];
		int i = l - 1;

		for (int j = l; j < r; j++)
		{
			if (++comparisions && a[j] < pivot)
			{
				i++;
				Utils::Swap(a[i], a[j]);
			}
		}
		Utils::Swap(a[i + 1], a[r]);
		return i + 1;
	}

	void QuickSort(int *a, int n, int l, int r)
	{
		if (l < r)
		{
			int p = partition(a, l, r);
			QuickSort(a, n, l, p - 1);
			QuickSort(a, n, p + 1, r);
		}
	}

	static size_t QuickSortAlgoComp(int *a, int l, int r, size_t &comparisions)
	{
		if (++comparisions && l < r)
		{
			int p = partitionComp(a, l, r, comparisions);
			QuickSortAlgoComp(a, l, p - 1, comparisions); // Left partition
			QuickSortAlgoComp(a, p + 1, r, comparisions); // Right partition
		}

		return comparisions;
	}

	size_t QuickSortComp(int *a, int n, int l, int r)
	{
		size_t totalComparisons = 0;
		QuickSortAlgoComp(a, 0, n - 1, totalComparisons);
		return totalComparisons;
	}

	// Dual Pivot Quick sort
	static int partitionDualPivot(int *a, int low, int high, int *lp)
	{
		if (a[low] > a[high])
			Utils::Swap(a[low], a[high]);

		// p is the left pivot, and q is the right pivot.
		int j = low + 1;
		int g = high - 1, k = low + 1, p = a[low], q = a[high];
		while (k <= g)
		{
			// if elements are less than the left pivot
			if (a[k] < p)
			{
				Utils::Swap(a[k], a[j]);
				j++;
			}

			// if elements are greater than or equal
			// to the right pivot
			else if (a[k] >= q)
			{
				while (a[g] > q && k < g)
					g--;
				Utils::Swap(a[k], a[g]);
				g--;
				if (a[k] < p)
				{
					Utils::Swap(a[k], a[j]);
					j++;
				}
			}
			k++;
		}
		j--;
		g++;

		// bring pivots to their appropriate positions.
		Utils::Swap(a[low], a[j]);
		Utils::Swap(a[high], a[g]);

		// returning the indices of the pivots.
		*lp = j; // because we cannot return two elements
		// from a function.

		return g;
	}

	void DualPivotQuickSort(int *a, int n, int low, int high)
	{
		if (low < high)
		{
			// lp means left pivot, and rp means right pivot.
			int lp, rp;
			rp = partitionDualPivot(a, low, high, &lp);
			DualPivotQuickSort(a, n, low, lp - 1);
			DualPivotQuickSort(a, n, lp + 1, rp - 1);
			DualPivotQuickSort(a, n, rp + 1, high);
		}
	}

	// 3-Way QuickSort (Dutch National Flag)
	static void partitionThreeWay(int *a, int l, int r, int &i, int &j)
	{
		i = l - 1, j = r;
		int p = l - 1, q = r;
		int v = a[r];

		while (true)
		{
			// From left, find the first element greater than
			// or equal to v. This loop will definitely
			// terminate as v is last element
			while (a[++i] < v)
				;

			// From right, find the first element smaller than
			// or equal to v
			while (v < a[--j])
				if (j == l)
					break;

			// If i and j cross, then we are done
			if (i >= j)
				break;

			// Swap, so that smaller goes on left greater goes
			// on right
			Utils::Swap(a[i], a[j]);

			// Move all same left occurrence of pivot to
			// beginning of array and keep count using p
			if (a[i] == v)
			{
				p++;
				Utils::Swap(a[p], a[i]);
			}

			// Move all same right occurrence of pivot to end of
			// array and keep count using q
			if (a[j] == v)
			{
				q--;
				Utils::Swap(a[j], a[q]);
			}
		}

		// Move pivot element to its correct index
		Utils::Swap(a[i], a[r]);

		// Move all left same occurrences from beginning
		// to adjacent to arr[i]
		j = i - 1;
		for (int k = l; k < p; k++, j--)
			Utils::Swap(a[k], a[j]);

		// Move all right same occurrences from end
		// to adjacent to arr[i]
		i = i + 1;
		for (int k = r - 1; k > q; k--, i++)
			Utils::Swap(a[i], a[k]);
	}

	// 3-way partition based quick sort
	void QuickSortThreeWay(int *a, int n, int l, int r)
	{
		if (r <= l)
			return;

		int i, j;

		// Note that i and j are passed as reference
		partitionThreeWay(a, l, r, i, j);

		// Recur
		QuickSortThreeWay(a, n, l, j);
		QuickSortThreeWay(a, n, i, r);
	}
}