#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <cstring>

#include "Command.h"
#include "Algorithms.h"
#include "TesterLib.h"
#include "DataGenerator.h"

// Testing algorithms area for devs
static void TestingMode()
{
	std::vector<TesterLib::SortEntityBase *> container = {
		new SortEntity2("selection-sort", Algorithms::SelectionSort, Algorithms::SelectionSortComp),
		new SortEntity2("insertion-sort", Algorithms::InsertionSort, Algorithms::InsertionSortComp),
		new SortEntity2("bubble-sort", Algorithms::BubbleSort, Algorithms::BubbleSortComp),
		new SortEntity2("shaker-sort", Algorithms::ShakerSort, Algorithms::ShakerSortComp),
		new SortEntity2("shell-sort", Algorithms::ShellSort, Algorithms::ShellSortComp),
		new SortEntity2("heap-sort", Algorithms::HeapSort, Algorithms::HeapSortComp),
		new SortEntity4("merge-sort", Algorithms::MergeSort, Algorithms::MergeSortComp),
		new SortEntity4("quick-sort", Algorithms::QuickSort, Algorithms::QuickSortComp),
		new SortEntity2("counting-sort", Algorithms::CountingSort, Algorithms::CountingSortComp),
		new SortEntity2("radix-sort", Algorithms::RadixSort, Algorithms::RadixSortComp),
		new SortEntity2("flash-sort", Algorithms::FlashSort, Algorithms::FlashSortComp),
	};

	std::vector<int> sizeTestcases = {10000, 30000, 50000, 100000, 300000, 500000};

	FILE *f = fopen("benchmark.csv", "w");

	if (f == nullptr)
	{
		printf("Cannot open file\n");
		return;
	}

	// Write the header
	fprintf(f, "Algorithm, Order, Size, Is Sorted, Time (ms), Comparisons\n");

	int *arr;

	// Run multiple tests
	for (int order = 0; order < 4; ++order) // 0: Random, 1: Nearly sorted, 2: Sorted, 3: Reverse
	{
		for (size_t sizeIdx = 0; sizeIdx < sizeTestcases.size(); ++sizeIdx) // Test with multiple sizes
		{
			for (const auto &sortEntity : container) // Test with multiple sorting algorithms
			{
				int size = sizeTestcases[sizeIdx];
				arr = new int[size];
				GenerateData(arr, size, order);

				// Run a single test for a single sorting algorithm
				// TesterLib::RunMultipleTests(sortEntity, arr, size, order, 10, true, f);
				TesterLib::RunMultipleTestsParallel(sortEntity, arr, size, order, 10, true, f);
			}
		}
	}

	fclose(f);

	// free memory
	TesterLib::FreeContainer(container);
}

int main(int argc, char **argv)
{
	// TestingMode();
	// return 0;

	CommandLib::Command command;
	if (!CommandLib::parseCommandLineArguments(argc, argv, command))
		return 1;

	std::vector<TesterLib::SortEntityBase *> container = {
		new SortEntity2("selection-sort", Algorithms::SelectionSort, Algorithms::SelectionSortComp),
		new SortEntity2("insertion-sort", Algorithms::InsertionSort, Algorithms::InsertionSortComp),
		new SortEntity2("bubble-sort", Algorithms::BubbleSort, Algorithms::BubbleSortComp),
		new SortEntity2("shaker-sort", Algorithms::ShakerSort, Algorithms::ShakerSortComp),
		new SortEntity2("shell-sort", Algorithms::ShellSort, Algorithms::ShellSortComp),
		new SortEntity2("heap-sort", Algorithms::HeapSort, Algorithms::HeapSortComp),
		new SortEntity4("merge-sort", Algorithms::MergeSort, Algorithms::MergeSortComp),
		new SortEntity4("quick-sort", Algorithms::QuickSort, Algorithms::QuickSortComp),
		new SortEntity2("counting-sort", Algorithms::CountingSort, Algorithms::CountingSortComp),
		new SortEntity2("radix-sort", Algorithms::RadixSort, Algorithms::RadixSortComp),
		new SortEntity2("flash-sort", Algorithms::FlashSort, Algorithms::FlashSortComp),
	};

	Algorithms::Benchmark benchmark{};
	Algorithms::Benchmark benchmark_2{};

	switch (command.typeCommand)
	{
	case 1:
	{
		int *arr = new int[command.inputSize];

		if (arr == nullptr)
		{
			std::cerr << "Memory allocation failed\n";
			return 1;
		}

		Utils::ReadFile(command.inputFileName, arr, command.inputSize);

		benchmark.Random.sizeArr = command.inputSize;
		benchmark.Random.SetOriginalArray(arr, command.inputSize);

		if (command.outputMode == CommandLib::OutputMode::BOTH)
		{
			benchmark.Random.time = container[command.algorithm_1]->GetRunningTime(arr, command.inputSize);
			memcpy(arr, benchmark.Random.originalArr, command.inputSize * sizeof(int));
			benchmark.Random.comparisons = container[command.algorithm_1]->GetComparisons(arr, command.inputSize);
		}
		else if (command.outputMode == CommandLib::OutputMode::COMP)
		{
			benchmark.Random.comparisons = container[command.algorithm_1]->GetComparisons(arr, command.inputSize);
		}
		else
		{
			benchmark.Random.time = container[command.algorithm_1]->GetRunningTime(arr, command.inputSize);
		}

		benchmark.Random.SetSortedArray(arr, command.inputSize);

		break;
	}
	case 2:
	{
		int *arr = new int[command.inputSize];

		if (arr == nullptr)
		{
			std::cerr << "Memory allocation failed\n";
			return 1;
		}

		GenerateData(arr, command.inputSize, command.inputOrder);

		switch (command.inputOrder)
		{
		case CommandLib::InputOrder::RANDOM:
		{
			benchmark.Random.sizeArr = command.inputSize;
			benchmark.Random.SetOriginalArray(arr, command.inputSize);

			if (command.outputMode == CommandLib::OutputMode::BOTH)
			{
				benchmark.Random.time = container[command.algorithm_1]->GetRunningTime(arr, command.inputSize);
				memcpy(arr, benchmark.Random.originalArr, command.inputSize * sizeof(int));
				benchmark.Random.comparisons = container[command.algorithm_1]->GetComparisons(arr, command.inputSize);
			}
			else if (command.outputMode == CommandLib::OutputMode::COMP)
			{
				benchmark.Random.comparisons = container[command.algorithm_1]->GetComparisons(arr, command.inputSize);
			}
			else
			{
				benchmark.Random.time = container[command.algorithm_1]->GetRunningTime(arr, command.inputSize);
			}

			benchmark.Random.SetSortedArray(arr, command.inputSize);
			break;
		}
		case CommandLib::InputOrder::SORTED:
		{
			benchmark.Sorted.sizeArr = command.inputSize;
			benchmark.Sorted.SetOriginalArray(arr, command.inputSize);

			if (command.outputMode == CommandLib::OutputMode::BOTH)
			{
				benchmark.Sorted.time = container[command.algorithm_1]->GetRunningTime(arr, command.inputSize);
				memcpy(arr, benchmark.Sorted.originalArr, command.inputSize * sizeof(int));
				benchmark.Sorted.comparisons = container[command.algorithm_1]->GetComparisons(arr, command.inputSize);
			}
			else if (command.outputMode == CommandLib::OutputMode::COMP)
			{
				benchmark.Sorted.comparisons = container[command.algorithm_1]->GetComparisons(arr, command.inputSize);
			}
			else
			{
				benchmark.Sorted.time = container[command.algorithm_1]->GetRunningTime(arr, command.inputSize);
			}

			benchmark.Sorted.SetSortedArray(arr, command.inputSize);
			break;
		}
		case CommandLib::InputOrder::REVERSE:
		{
			benchmark.Reverse.sizeArr = command.inputSize;
			benchmark.Reverse.SetOriginalArray(arr, command.inputSize);

			if (command.outputMode == CommandLib::OutputMode::BOTH)
			{
				benchmark.Reverse.time = container[command.algorithm_1]->GetRunningTime(arr, command.inputSize);
				memcpy(arr, benchmark.Reverse.originalArr, command.inputSize * sizeof(int));
				benchmark.Reverse.comparisons = container[command.algorithm_1]->GetComparisons(arr, command.inputSize);
			}
			else if (command.outputMode == CommandLib::OutputMode::COMP)
			{
				benchmark.Reverse.comparisons = container[command.algorithm_1]->GetComparisons(arr, command.inputSize);
			}
			else
			{
				benchmark.Reverse.time = container[command.algorithm_1]->GetRunningTime(arr, command.inputSize);
			}

			benchmark.Reverse.SetSortedArray(arr, command.inputSize);
			break;
		}
		case CommandLib::InputOrder::NSORTED:
		{
			benchmark.NearlySorted.sizeArr = command.inputSize;
			benchmark.NearlySorted.SetOriginalArray(arr, command.inputSize);

			if (command.outputMode == CommandLib::OutputMode::BOTH)
			{
				benchmark.NearlySorted.time = container[command.algorithm_1]->GetRunningTime(arr, command.inputSize);
				memcpy(arr, benchmark.NearlySorted.originalArr, command.inputSize * sizeof(int));
				benchmark.NearlySorted.comparisons = container[command.algorithm_1]->GetComparisons(arr, command.inputSize);
			}
			else if (command.outputMode == CommandLib::OutputMode::COMP)
			{
				benchmark.NearlySorted.comparisons = container[command.algorithm_1]->GetComparisons(arr, command.inputSize);
			}
			else
			{
				benchmark.NearlySorted.time = container[command.algorithm_1]->GetRunningTime(arr, command.inputSize);
			}

			benchmark.NearlySorted.SetSortedArray(arr, command.inputSize);
			break;
		}
		default:
			break;
		}

		break;
	}
	case 3:
	{
		int *arr_1 = new int[command.inputSize];
		int *arr_2 = new int[command.inputSize];
		int *arr_3 = new int[command.inputSize];
		int *arr_4 = new int[command.inputSize];

		if (arr_1 == nullptr || arr_2 == nullptr || arr_3 == nullptr || arr_4 == nullptr)
		{
			std::cerr << "Memory allocation failed\n";
			return 1;
		}

		GenerateData(arr_1, command.inputSize, CommandLib::InputOrder::RANDOM);
		GenerateData(arr_2, command.inputSize, CommandLib::InputOrder::SORTED);
		GenerateData(arr_3, command.inputSize, CommandLib::InputOrder::REVERSE);
		GenerateData(arr_4, command.inputSize, CommandLib::InputOrder::NSORTED);

		benchmark.Random.sizeArr = command.inputSize;
		benchmark.Random.SetOriginalArray(arr_1, command.inputSize);
		benchmark.Sorted.sizeArr = command.inputSize;
		benchmark.Sorted.SetOriginalArray(arr_2, command.inputSize);
		benchmark.Reverse.sizeArr = command.inputSize;
		benchmark.Reverse.SetOriginalArray(arr_3, command.inputSize);
		benchmark.NearlySorted.sizeArr = command.inputSize;
		benchmark.NearlySorted.SetOriginalArray(arr_4, command.inputSize);

		if (command.outputMode == CommandLib::OutputMode::BOTH)
		{
			benchmark.Random.time = container[command.algorithm_1]->GetRunningTime(arr_1, command.inputSize);
			benchmark.Sorted.time = container[command.algorithm_1]->GetRunningTime(arr_2, command.inputSize);
			benchmark.Reverse.time = container[command.algorithm_1]->GetRunningTime(arr_3, command.inputSize);
			benchmark.NearlySorted.time = container[command.algorithm_1]->GetRunningTime(arr_4, command.inputSize);

			memcpy(arr_1, benchmark.Random.originalArr, command.inputSize * sizeof(int));
			memcpy(arr_2, benchmark.Sorted.originalArr, command.inputSize * sizeof(int));
			memcpy(arr_3, benchmark.Reverse.originalArr, command.inputSize * sizeof(int));
			memcpy(arr_4, benchmark.NearlySorted.originalArr, command.inputSize * sizeof(int));

			benchmark.Random.comparisons = container[command.algorithm_1]->GetComparisons(arr_1, command.inputSize);
			benchmark.Sorted.comparisons = container[command.algorithm_1]->GetComparisons(arr_2, command.inputSize);
			benchmark.Reverse.comparisons = container[command.algorithm_1]->GetComparisons(arr_3, command.inputSize);
			benchmark.NearlySorted.comparisons = container[command.algorithm_1]->GetComparisons(arr_4, command.inputSize);
		}
		else if (command.outputMode == CommandLib::OutputMode::COMP)
		{
			benchmark.Random.comparisons = container[command.algorithm_1]->GetComparisons(arr_1, command.inputSize);
			benchmark.Sorted.comparisons = container[command.algorithm_1]->GetComparisons(arr_2, command.inputSize);
			benchmark.Reverse.comparisons = container[command.algorithm_1]->GetComparisons(arr_3, command.inputSize);
			benchmark.NearlySorted.comparisons = container[command.algorithm_1]->GetComparisons(arr_4, command.inputSize);
		}
		else
		{
			benchmark.Random.time = container[command.algorithm_1]->GetRunningTime(arr_1, command.inputSize);
			benchmark.Sorted.time = container[command.algorithm_1]->GetRunningTime(arr_2, command.inputSize);
			benchmark.Reverse.time = container[command.algorithm_1]->GetRunningTime(arr_3, command.inputSize);
			benchmark.NearlySorted.time = container[command.algorithm_1]->GetRunningTime(arr_4, command.inputSize);
		}

		benchmark.Random.SetSortedArray(arr_1, command.inputSize);
		benchmark.Sorted.SetSortedArray(arr_2, command.inputSize);
		benchmark.Reverse.SetSortedArray(arr_3, command.inputSize);
		benchmark.NearlySorted.SetSortedArray(arr_4, command.inputSize);

		break;
	}
	case 4:
	{
		int *arr = new int[command.inputSize];
		int *arr_2 = new int[command.inputSize];

		if (arr == nullptr || arr_2 == nullptr)
		{
			std::cerr << "Memory allocation failed\n";
			return 1;
		}

		Utils::ReadFile(command.inputFileName, arr, command.inputSize);
		memcpy(arr_2, arr, command.inputSize * sizeof(int));

		benchmark.Random.sizeArr = command.inputSize;
		benchmark.Random.SetOriginalArray(arr, command.inputSize);

		benchmark_2.Random.sizeArr = command.inputSize;
		benchmark_2.Random.SetOriginalArray(arr_2, command.inputSize);

		benchmark.Random.time = container[command.algorithm_1]->GetRunningTime(arr, command.inputSize);
		benchmark_2.Random.time = container[command.algorithm_2]->GetRunningTime(arr_2, command.inputSize);

		memcpy(arr, benchmark.Random.originalArr, command.inputSize * sizeof(int));
		memcpy(arr_2, benchmark_2.Random.originalArr, command.inputSize * sizeof(int));

		benchmark.Random.comparisons = container[command.algorithm_1]->GetComparisons(arr, command.inputSize);
		benchmark_2.Random.comparisons = container[command.algorithm_2]->GetComparisons(arr_2, command.inputSize);

		benchmark.Random.SetSortedArray(arr, command.inputSize);
		benchmark_2.Random.SetSortedArray(arr_2, command.inputSize);

		break;
	}
	case 5:
	{
		int *arr = new int[command.inputSize];
		int *arr_2 = new int[command.inputSize];

		if (arr == nullptr || arr_2 == nullptr)
		{
			std::cerr << "Memory allocation failed\n";
			return 1;
		}

		GenerateData(arr, command.inputSize, command.inputOrder);
		memcpy(arr_2, arr, command.inputSize * sizeof(int));

		benchmark.Random.sizeArr = command.inputSize;
		benchmark.Random.SetOriginalArray(arr, command.inputSize);

		benchmark_2.Random.sizeArr = command.inputSize;
		benchmark_2.Random.SetOriginalArray(arr_2, command.inputSize);

		benchmark.Random.time = container[command.algorithm_1]->GetRunningTime(arr, command.inputSize);
		benchmark_2.Random.time = container[command.algorithm_2]->GetRunningTime(arr_2, command.inputSize);

		memcpy(arr, benchmark.Random.originalArr, command.inputSize * sizeof(int));
		memcpy(arr_2, benchmark_2.Random.originalArr, command.inputSize * sizeof(int));

		benchmark.Random.comparisons = container[command.algorithm_1]->GetComparisons(arr, command.inputSize);
		benchmark_2.Random.comparisons = container[command.algorithm_2]->GetComparisons(arr_2, command.inputSize);

		benchmark.Random.SetSortedArray(arr, command.inputSize);
		benchmark_2.Random.SetSortedArray(arr_2, command.inputSize);

		break;
	}
	default:
		std::cerr << "Invalid command type\n";
		break;
	}

	// Print the results
	CommandLib::printConsoleMessage(command, benchmark, benchmark_2);

	CommandLib::outputBenchmarkResults(command, benchmark, benchmark_2);

	// free memory
	TesterLib::FreeContainer(container);

	return 0;
}