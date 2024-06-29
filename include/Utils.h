#ifndef UTILS_H
#define UTILS_H
#include <chrono>
#include <cstdio>
#include <utility>
#include <cstdlib>

namespace Utils
{
	// Swap two elements
	template <typename T>
	inline void Swap(T &a, T &b)
	{
		T temp = a;
		a = b;
		b = temp;
	}

	// Generate a random value in the range [min, max]
	template <typename T>
	inline T GetRandValue(T min, T max)
	{
		return min + rand() % (max - min + 1);
	}

	// Print an array
	template <typename T>
	void PrintArray(T *arr, int n, int numberBreak = 100)
	{
		for (int i = 0; i < n; ++i)
		{
			printf("%d ", arr[i]);
			if (numberBreak == -1)
				continue; // No break
			if ((i + 1) % numberBreak == 0)
			{
				printf("...\n");
				break;
			}
		}
		printf("\n");
	}

	void ReadFile(const char *fileName, int *&arr, int &n);

	void WriteFile(const char *fileName, int *arr, int n);

	// Find the maximun element in an array
	template <typename T>
	T MaxElement(T *arr, int n)
	{
		T max = arr[0];
		for (int i = 0; i < n; ++i)
			if (arr[i] > max)
				max = arr[i];
		return max;
	}

	// Find the minimum element in an array
	template <typename T>
	T MinElement(T *arr, int n)
	{
		T min = arr[0];
		for (int i = 0; i < n; ++i)
			if (arr[i] < min)
				min = arr[i];
		return min;
	}

	// Measure time of execution of a function
	template <typename T, typename... Args>
	double MeasureTime(T func, Args &&...args)
	{
		auto start = std::chrono::steady_clock::now();
		func(std::forward<Args>(args)...);
		auto end = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::milli> duration = end - start;
		return duration.count();
	}
}
#endif // !UTILS_H
