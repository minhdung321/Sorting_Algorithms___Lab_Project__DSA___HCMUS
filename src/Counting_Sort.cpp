#include <iostream>

namespace Algorithms
{
	void CountingSort(int *a, int n)
	{
		int k = a[0];
		for (int i = 0; i < n; i++)
		{
			if (a[i] > k)
				k = a[i];
		}

		int *c = new int[k + 1]{0};

		if (c == nullptr)
		{
			std::cerr << "[Counting Sort] Memory allocation failed\n";
			return;
		}

		for (int i = 0; i < n; i++)
			c[a[i]]++;

		for (int i = 1; i <= k; i++)
			c[i] += c[i - 1];

		int *s = new int[n];

		if (s == nullptr)
		{
			std::cerr << "[Counting Sort] Memory allocation failed\n";
			delete[] c;
			return;
		}

		for (int i = n - 1; i >= 0; i--)
		{

			s[c[a[i]] - 1] = a[i];
			--c[a[i]];
		}

		for (int i = 0; i < n; i++)
			a[i] = s[i];

		delete[] s;
		delete[] c;
	}

	size_t CountingSortComp(int *a, int n)
	{
		size_t comparisons = 0;

		// Find max element in array
		int k = a[0];

		for (int i = 0; i < n; i++)
		{
			if (++comparisons && a[i] > k)
				k = a[i];
		}

		int *c = new int[k + 1]{0};

		if (c == nullptr)
		{
			std::cerr << "[Counting Sort] Memory allocation failed\n";
			return 0;
		}

		for (int i = 0; i < n; i++)
			c[a[i]]++;

		for (int i = 1; i <= k; i++)
			c[i] += c[i - 1];

		int *s = new int[n];

		if (s == nullptr)
		{
			std::cerr << "[Counting Sort] Memory allocation failed\n";
			delete[] c;
			return 0;
		}

		for (int i = n - 1; i >= 0; i--)
		{

			s[c[a[i]] - 1] = a[i];
			--c[a[i]];
		}

		for (int i = 0; i < n; i++)
			a[i] = s[i];

		delete[] c;
		delete[] s;

		return comparisons;
	}
}