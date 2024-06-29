#include "Utils.h"

namespace Algorithms
{
	// Documentation: https://www.geeksforgeeks.org/cocktail-sort/
	// https://en.wikipedia.org/wiki/Cocktail_shaker_sort

	void ShakerSort(int *a, int n)
	{
		bool swapped = true;
		int start = 0;
		int end = n - 1;

		while (swapped)
		{
			swapped = false;

			for (int i = start; i < end; ++i)
			{
				if (a[i] > a[i + 1])
				{
					Utils::Swap(a[i], a[i + 1]);
					swapped = true;
				}
			}

			if (!swapped)
				break;

			swapped = false;

			--end;

			for (int i = end - 1; i >= start; --i)
			{
				if (a[i] > a[i + 1])
				{
					Utils::Swap(a[i], a[i + 1]);
					swapped = true;
				}
			}

			++start;
		}
	}

	size_t ShakerSortComp(int *a, int n)
	{
		size_t comparisions = 0;

		bool swapped = true;
		int start = 0;
		int end = n - 1;

		while (swapped)
		{
			swapped = false;

			for (int i = start; i < end; ++i)
			{
				if (++comparisions && a[i] > a[i + 1])
				{
					Utils::Swap(a[i], a[i + 1]);
					swapped = true;
				}
			}

			if (!swapped)
				break;

			swapped = false;

			--end;

			for (int i = end - 1; i >= start; --i)
			{
				if (++comparisions && a[i] > a[i + 1])
				{
					Utils::Swap(a[i], a[i + 1]);
					swapped = true;
				}
			}

			++start;
		}

		return comparisions;
	}
}