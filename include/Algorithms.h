#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "Utils.h"
#include <iostream>

namespace Algorithms
{
	struct BenchmarkData
	{
		const char *name;			// Name of the algorithm
		double time = 0.0f;			// Time of execution
		size_t comparisons = 0;		// Number of comparisons
		int *originalArr = nullptr; // Original array
		int *sortedArr = nullptr;	// Sorted array
		int sizeArr = 0;			// Size of the array

		// THỬ NGHIỆM
		BenchmarkData() = default; // Default constructor

		// Set name
		void SetName(const char *name)
		{
			this->name = name;
		}

		// Set original array
		void SetOriginalArray(int *arr, int n)
		{
			originalArr = new int[n];
			sizeArr = n;
			for (int i = 0; i < n; ++i)
				originalArr[i] = arr[i];
		}

		// Set sorted array
		void SetSortedArray(int *arr, int n)
		{
			if (n != sizeArr)
				throw std::invalid_argument("The size of the array is not correct");

			sortedArr = new int[n];
			for (int i = 0; i < n; ++i)
				sortedArr[i] = arr[i];
		}

		void Print()
		{
			std::cout << "Name of Benchmark: " << name << "\n";
			std::cout << "Time: " << time << "s\n";
			std::cout << "Comparisons: " << comparisons << "\n";
			std::cout << "Size of array: " << sizeArr << "\n";
			std::cout << "Original array: ";
			Utils::PrintArray(originalArr, sizeArr);
			std::cout << "Sorted array: ";
			Utils::PrintArray(sortedArr, sizeArr);
		}

		// Copy constructor
		void operator=(const BenchmarkData &data)
		{
			time = data.time;
			comparisons = data.comparisons;
			sizeArr = data.sizeArr;

			if (originalArr)
				delete[] originalArr;
			if (sortedArr)
				delete[] sortedArr;

			originalArr = new int[sizeArr];
			sortedArr = new int[sizeArr];

			for (int i = 0; i < sizeArr; ++i)
			{
				originalArr[i] = data.originalArr[i];
				sortedArr[i] = data.sortedArr[i];
			}
		}

		bool operator==(const BenchmarkData &data)
		{
			if (time != data.time)
				return false;
			if (comparisons != data.comparisons)
				return false;
			if (sizeArr != data.sizeArr)
				return false;

			for (int i = 0; i < sizeArr; ++i)
			{
				if (originalArr[i] != data.originalArr[i])
					return false;
				if (sortedArr[i] != data.sortedArr[i])
					return false;
			}

			return true;
		}

		bool operator!=(const BenchmarkData &data)
		{
			return !(*this == data);
		}

		~BenchmarkData()
		{
			if (originalArr)
				delete[] originalArr;
			if (sortedArr)
				delete[] sortedArr;
		}
	};

	struct Benchmark
	{
		BenchmarkData Random = BenchmarkData();
		BenchmarkData Sorted = BenchmarkData();
		BenchmarkData Reverse = BenchmarkData();
		BenchmarkData NearlySorted = BenchmarkData();
	};

	extern const char *ALGORITHMS[]; // Array of algorithm name
	extern const int NUM_ALGORITHMS; // Number of algorithms

	// Section to declare sorting algorithms

	// SELECTION SORT
	void SelectionSort(int *, int);
	size_t SelectionSortComp(int *, int);
	void SelectionSortEarlyTermination(int *, int);
	void StableSelectionSort(int *, int);

	// BUBBLE SORT
	void BubbleSort(int *, int);
	size_t BubbleSortComp(int *, int);
	void BubbleSortEarlyTermination(int *, int);

	// INSERTION SORT
	void InsertionSort(int *, int);
	size_t InsertionSortComp(int *, int);
	void InsertionSortBinarySearch(int *, int);

	// SHAKER SORT
	void ShakerSort(int *, int);
	size_t ShakerSortComp(int *, int);

	// SHELL SORT
	void ShellSort(int *, int);
	size_t ShellSortComp(int *, int);
	void ShellSortKnuth(int *, int);
	void ShellSortSedgewick(int *, int);

	// HEAP SORT
	void HeapSort(int *, int);
	size_t HeapSortComp(int *, int);

	// MERGE SORT
	void MergeSort(int *, int, int, int);
	size_t MergeSortComp(int *, int, int, int);
	void MergeSortImprove(int *, int, int, int);
	void MergeSortInPlace(int *, size_t);

	// QUICK SORT
	void QuickSort(int *, int, int, int);
	size_t QuickSortComp(int *, int, int, int);
	void DualPivotQuickSort(int *, int, int, int);
	void QuickSortThreeWay(int *, int, int, int);

	// COUNTING SORT
	void CountingSort(int *, int);
	size_t CountingSortComp(int *, int);

	// RADIX SORT
	void RadixSort(int *, int);
	size_t RadixSortComp(int *, int);

	// FLASH SORT
	void FlashSort(int *, int);
	size_t FlashSortComp(int *, int);
	void FlashSortWithQuickSort(int *, int);
}

#endif // !ALGORITHMS_H
