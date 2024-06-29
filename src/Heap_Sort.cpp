#include "Utils.h"

namespace Algorithms
{
	static void heapify(int *a, int n, int i)
	{
		int largest = i;
		int l = 2 * i + 1;
		int r = 2 * i + 2;

		if (l < n && a[l] > a[largest])
		{
			largest = l;
		}

		if (r < n && a[r] > a[largest])
		{
			largest = r;
		}

		if (largest != i)
		{
			Utils::Swap(a[largest], a[i]);
			heapify(a, n, largest);
		}
	}

	static void heapifyComp(int *a, int n, int i, size_t &comparisons)
	{
		int largest = i;
		int l = 2 * i + 1;
		int r = 2 * i + 2;

		if (l < n)
		{
			if (++comparisons && a[l] > a[largest])
			{
				largest = l;
			}
		}

		if (r < n)
		{
			if (++comparisons && a[r] > a[largest])
			{
				largest = r;
			}
		}

		if (largest != i)
		{
			Utils::Swap(a[largest], a[i]);
			heapifyComp(a, n, largest, comparisons);
		}
	}

	void HeapSort(int *a, int n)
	{
		// Build MAX_HEAP
		for (int i = (n - 1) / 2; i >= 0; i--)
		{
			heapify(a, n, i);
		}

		for (int i = n - 1; i > 0; i--)
		{
			Utils::Swap(a[i], a[0]);
			heapify(a, i, 0);
		}
	}

	size_t HeapSortComp(int *a, int n)
	{
		size_t comparisons = 0;
		// Build MAX_HEAP
		for (int i = (n - 1) / 2; i >= 0; i--)
		{
			heapifyComp(a, n, i, comparisons);
		}

		for (int i = n - 1; i > 0; i--)
		{
			Utils::Swap(a[i], a[0]);
			heapifyComp(a, i, 0, comparisons);
		}

		return comparisons;
	}
}