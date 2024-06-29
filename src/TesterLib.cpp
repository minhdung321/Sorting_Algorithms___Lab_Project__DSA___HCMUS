#include "TesterLib.h"
#include "DataGenerator.h"
#include "Utils.h"
#include "omp.h"

#include <iostream>
#include <vector>
#include <cstring>

using namespace TesterLib;

static bool IsSorted(int *a, int n)
{
	for (int i = 0; i < n - 1; ++i)
	{
		if (a[i] > a[i + 1])
		{
			std::cout << "Array is not sorted!" << std::endl;
			return false;
		}
	}

	return true;
}

static const char *GetOrder(int order)
{
	switch (order)
	{
	case 0:
		return "Random";
	case 1:
		return "Ascending";
	case 2:
		return "Descending";
	case 3:
		return "Nearly sorted";
	default:
		return "Unknown";
	}
}

static void SetupTest(const char *message, int *&testArray, int *originalData, int n, int order, bool show)
{
	std::cout << message << std::endl;

	// If the test array is not initialized, generate data
	if (testArray == nullptr)
	{
		testArray = new int[n];

		if (testArray == nullptr)
		{
			std::cout << "Memory allocation failed!" << std::endl;
			return;
		}

		GenerateData(testArray, n, order);
	}

	if (show)
	{
		std::cout << "Original data: ";
		Utils::PrintArray(testArray, n);
	}

	// Copy the original data
	if (originalData != nullptr)
	{
		for (int i = 0; i < n; ++i)
			originalData[i] = testArray[i];
	}
}

static void PrintResultSingleTest(const char *message, int *testArray, int n, int order, double runTime, bool isSorted, size_t comp, bool show)
{
	std::cout << message << std::endl;
	std::cout << "Data size: " << n << std::endl;
	std::cout << "Order: " << GetOrder(order) << std::endl;
	std::cout << "Is sorted: " << (isSorted ? "Yes" : "No") << std::endl;
	std::cout << "Run time: " << runTime << " ms" << " (" << runTime / 1000.0f << " s)" << std::endl;
	std::cout << "Comparisons: " << comp << std::endl;

	if (show)
	{
		std::cout << std::endl;
		std::cout << "Modified data: ";
		Utils::PrintArray(testArray, n);
	}
}

static void PrintResultEachTest(int id, int n, int order, bool isSorted, double runTime, size_t comp)
{
	std::cout << "Test " << id + 1 << " Result: " << std::endl;
	std::cout << "Data size: " << n << std::endl;
	std::cout << "Order: " << GetOrder(order) << std::endl;
	std::cout << "Is sorted: " << (isSorted ? "Yes" : "No") << std::endl;
	std::cout << "Run time: " << runTime << " ms" << " (" << runTime / 1000.0f << " s)" << std::endl;
	std::cout << "Comparisons: " << comp << std::endl
			  << std::endl;
	;
}

static void PrintResultMultipleTests(const char *message, int n, int order, double avgTime, size_t avgComp)
{
	std::cout << message << std::endl;
	std::cout << "Data size: " << n << std::endl;
	std::cout << "Order: " << GetOrder(order) << std::endl;
	std::cout << "Average running time: " << avgTime << " (ms)" << " (" << avgTime / 1000.0f << " s)" << std::endl;
	std::cout << "Average of comparisons: " << avgComp << std::endl;
	std::cout << "---------------------------------" << std::endl;
}

void TesterLib::FreeContainer(std::vector<SortEntityBase *> &container)
{
	for (auto &entity : container)
		delete entity;
	container.clear();
}

SortEntityBase *TesterLib::GetSortEntity(const char *name, const std::vector<SortEntityBase *> &container)
{
	for (const auto &entity : container)
	{
		if (strcmp(entity->GetName(), name) == 0)
			return entity;
	}

	return nullptr;
}

int TesterLib::RunMultiAlgWithSingleTest(
	const std::vector<SortEntityBase *> &container,
	int *arr, int n, int order, bool show)
{
	int *testArray = arr; // Use the input array

	int *originalData = new int[n];

	SetupTest("[Multiple Algorithms with Single Test] is running...", testArray, originalData, n, order, show);

	double runTime = 0.0f;
	size_t comp = 0;
	bool isSorted = false;

	if (container.empty())
	{
		std::cout << "No algorithm is set!" << std::endl;
		std::cout << "Please check the input parameters!" << std::endl;
		return -1;
	}

	for (int i = 0; i < container.size(); ++i)
	{
		runTime = container[i]->GetRunningTime(testArray, n);
		isSorted = IsSorted(testArray, n);

		// Restore the original data
		for (int i = 0; i < n; ++i)
			testArray[i] = originalData[i];

		comp = container[i]->GetComparisons(testArray, n);

		if (show)
			PrintResultSingleTest(container[i]->GetName(), testArray, n, order, runTime, isSorted, comp, show);

		// Restore the original data
		for (int i = 0; i < n; ++i)
			testArray[i] = originalData[i];
	}

	delete[] testArray;

	delete[] originalData;

	return 0;
}

int TesterLib::RunMultiAlgWithMultipleTests(
	const std::vector<SortEntityBase *> &container,
	int *arr, int n, int order, int numTests, bool show)
{
	int *testArray = arr; // Use the input array

	int *originalData = new int[n];

	SetupTest("[Multiple Algorithms with Multiple Tests] is running...", testArray, originalData, n, order, show);

	std::cout << "Number of tests: " << numTests << std::endl;

	double runTime = 0.0;
	double avgTime = 0.0;
	size_t comp = 0;
	bool isSorted = false;

	// Run multiple tests
	if (container.empty())
	{
		std::cout << "No algorithm is set!" << std::endl;
		std::cout << "Please check the input parameters!" << std::endl;
		return -1;
	}

	for (int i = 0; i < container.size(); ++i)
	{
		avgTime = 0.0;

		std::cout << "Name: " << container[i]->GetName() << std::endl;
		std::cout << "---------------------------------" << std::endl;

		bool isMeasuredComp = false;

		for (int j = 0; j < numTests; ++j)
		{
			runTime = container[i]->GetRunningTime(testArray, n);
			avgTime += runTime;
			isSorted = IsSorted(testArray, n);

			// Restore the original data
			for (int i = 0; i < n; ++i)
				testArray[i] = originalData[i];

			if (!isMeasuredComp)
			{
				comp = container[i]->GetComparisons(testArray, n);
				isMeasuredComp = true;
			}

			if (show)
				PrintResultEachTest(j, n, order, isSorted, runTime, comp);

			// Restore the original data
			for (int i = 0; i < n; ++i)
				testArray[i] = originalData[i];
		}

		avgTime /= numTests;

		PrintResultMultipleTests(container[i]->GetName(), n, order, avgTime, comp);
	}

	delete[] testArray;

	delete[] originalData;

	return 0;
}

int TesterLib::RunSingleTest(SortEntityBase *entity, int *arr, int n, int order, bool show)
{
	int *testArray = arr; // Use the input array

	int *originalData = new int[n];

	SetupTest("[Single Test] is running...", testArray, originalData, n, order, show);

	if (entity == NULL)
	{
		std::cout << "No algorithm is set!" << std::endl;
		std::cout << "Please check the input parameters!" << std::endl;
		return -1;
	}

	double runTime = entity->GetRunningTime(testArray, n);

	bool isSorted = IsSorted(testArray, n);

	// Restore the original data
	for (int i = 0; i < n; ++i)
		testArray[i] = originalData[i];

	size_t comp = entity->GetComparisons(testArray, n);

	std::cout << "Name: " << entity->GetName() << std::endl;
	std::cout << "---------------------------------" << std::endl;

	PrintResultSingleTest("[Single Test] Result: ", testArray, n, order, runTime, isSorted, comp, show);

	delete[] testArray;

	return 0;
}

int TesterLib::TimeRunSingleTest(SortEntityBase *entity, int *arr, int n, int order, bool show)
{
	int *testArray = arr; // Use the input array

	int *originalData = new int[n];

	SetupTest("[Single Test] is running...", testArray, originalData, n, order, show);

	if (entity == NULL)
	{
		std::cout << "No algorithm is set!" << std::endl;
		std::cout << "Please check the input parameters!" << std::endl;
		return -1;
	}

	double runTime = entity->GetRunningTime(testArray, n);
	bool isSorted = IsSorted(testArray, n);

	std::cout << "Name: " << entity->GetName() << std::endl;
	std::cout << "---------------------------------" << std::endl;

	PrintResultSingleTest("[Single Test] Result: ", testArray, n, order, runTime, isSorted, 0, show);

	delete[] testArray;

	delete[] originalData;

	return 0;
}

int TesterLib::CompRunSingleTest(SortEntityBase *entity, int *arr, int n, int order, bool show)
{
	int *testArray = arr; // Use the input array

	int *originalData = new int[n];

	SetupTest("[Single Test] is running...", testArray, originalData, n, order, show);

	if (entity == NULL)
	{
		std::cout << "No algorithm is set!" << std::endl;
		std::cout << "Please check the input parameters!" << std::endl;
		return -1;
	}

	size_t comp = entity->GetComparisons(testArray, n);
	bool isSorted = IsSorted(testArray, n);

	std::cout << "Name: " << entity->GetName() << std::endl;
	std::cout << "---------------------------------" << std::endl;

	PrintResultSingleTest("[Single Test] Result: ", testArray, n, order, -1.0f, isSorted, comp, show);

	delete[] testArray;

	delete[] originalData;

	return 0;
}

int TesterLib::RunMultipleTests(SortEntityBase *entity, int *arr, int n, int order, int numTests, bool show, FILE *f)
{
	int *testArray = arr; // Use the input array
	int *originalData = new int[n];

	SetupTest("[Multiple Tests] is running...", testArray, originalData, n, order, show);

	if (entity == NULL)
	{
		std::cout << "No algorithm is set!" << std::endl;
		std::cout << "Please check the input parameters!" << std::endl;
		return -1;
	}

	std::cout << "Name: " << std::uppercase << entity->GetName() << std::endl;
	std::cout << "Number of tests: " << numTests << std::endl;
	std::cout << "---------------------------------" << std::endl;

	double avgTime = 0.0;
	size_t avgComp = 0;

	for (int i = 0; i < numTests; ++i)
	{
		double runTime = entity->GetRunningTime(testArray, n);
		avgTime += runTime;
		bool isSorted = IsSorted(testArray, n);

		// Restore the original data
		memcpy(testArray, originalData, n * sizeof(int));

		size_t comp = entity->GetComparisons(testArray, n);
		avgComp += comp;

		if (f)
			fprintf(f, "%s, %s, %d, %s, %llf, %zu\n", entity->GetName(), GetOrder(order), n, isSorted ? "Yes" : "No", runTime, comp);

		if (show)
		{
			PrintResultEachTest(i, n, order, isSorted, runTime, comp);
		}

		// Restore the original data
		memcpy(testArray, originalData, n * sizeof(int));
	}

	avgTime /= numTests;
	avgComp /= numTests;

	PrintResultMultipleTests("[Multiple Tests] Result: ", n, order, avgTime, avgComp);

	if (f)
		fprintf(f, "%s, %s, %d, %s, %llf, %zu\n", entity->GetName(), GetOrder(order), n, "Average", avgTime, avgComp);

	delete[] testArray;
	delete[] originalData;

	return 0;
}

int TesterLib::RunMultipleTestsParallel(SortEntityBase *entity, int *arr, int n, int order, int numTests, bool show, FILE *f)
{
	int *originalData = new int[n];
	SetupTest("[Multiple Tests] is running...", arr, originalData, n, order, show);

	if (entity == NULL)
	{
		std::cout << "No algorithm is set!" << std::endl;
		std::cout << "Please check the input parameters!" << std::endl;
		delete[] originalData;
		return -1;
	}

	std::cout << "Name: " << std::uppercase << entity->GetName() << std::endl;
	std::cout << "Number of tests: " << numTests << std::endl;
	std::cout << "---------------------------------" << std::endl;

	double avgTime = 0.0;
	size_t avgComp = 0;

#pragma omp parallel for reduction(+ : avgTime, avgComp) num_threads(12)
	for (int i = 0; i < numTests; ++i)
	{
		int *testArray = new int[n];
		memcpy(testArray, originalData, n * sizeof(int));

		double runTime = entity->GetRunningTime(testArray, n);
		bool isSorted = IsSorted(testArray, n);
		avgTime += runTime;

		size_t comp = entity->GetComparisons(testArray, n);
		avgComp += comp;

#pragma omp critical
		{
			fprintf(f, "%s, %s, %d, %s, %llf, %zu\n", entity->GetName(), GetOrder(order), n, isSorted ? "Yes" : "No", runTime, comp);
		}

		if (show)
		{
#pragma omp critical
			{
				PrintResultEachTest(i, n, order, true, runTime, comp); // "true" vì biến isSorted đã bỏ
			}
		}

		delete[] testArray;
	}

	avgTime /= numTests;
	avgComp /= numTests;

	PrintResultMultipleTests("[Multiple Tests] Result: ", n, order, avgTime, avgComp);

	fprintf(f, "Average, %s, %d, %s, %llf, %zu\n", entity->GetName(), n, "N/A", avgTime, avgComp);

	delete[] arr;
	delete[] originalData;

	return 0;
}

int TesterLib::TimeRunMultipleTest(SortEntityBase *entity, int *arr, int n, int order, int numTests, bool show)
{
	int *testArray = arr; // Use the input array

	int *originalData = new int[n];

	SetupTest("[Multiple Tests] is running...", testArray, originalData, n, order, show);

	double runTime = 0.0;
	double avgTime = 0.0;
	bool isSorted = false;

	if (entity == NULL)
	{
		std::cout << "No algorithm is set!" << std::endl;
		std::cout << "Please check the input parameters!" << std::endl;
		return -1;
	}

	std::cout << "Number of tests: " << numTests << std::endl;
	std::cout << "Name: " << entity->GetName() << std::endl;
	std::cout << "---------------------------------" << std::endl;

	for (int i = 0; i < numTests; ++i)
	{
		runTime = entity->GetRunningTime(testArray, n);
		avgTime += runTime;
		isSorted = IsSorted(testArray, n);

		if (show)
			PrintResultEachTest(i, n, order, isSorted, runTime, 0);

		// Restore the original data
		for (int i = 0; i < n; ++i)
			testArray[i] = originalData[i];
	}

	avgTime /= numTests;

	PrintResultMultipleTests("[Multiple Tests] Result: ", n, order, avgTime, 0);

	delete[] testArray;

	delete[] originalData;

	return 0;
}

int TesterLib::CompRunMultipleTest(SortEntityBase *entity, int *arr, int n, int order, int numTests, bool show)
{
	int *testArray = arr; // Use the input array

	int *originalData = new int[n];

	SetupTest("[Multiple Tests] is running...", testArray, originalData, n, order, show);

	size_t comp = 0;
	size_t avgComp = 0;
	bool isSorted = false;

	if (entity == NULL)
	{
		std::cout << "No algorithm is set!" << std::endl;
		std::cout << "Please check the input parameters!" << std::endl;
		return -1;
	}

	std::cout << "Number of tests: " << numTests << std::endl;
	std::cout << "Name: " << entity->GetName() << std::endl;
	std::cout << "---------------------------------" << std::endl;

	for (int i = 0; i < numTests; ++i)
	{
		comp = entity->GetComparisons(testArray, n);
		avgComp += comp;
		isSorted = IsSorted(testArray, n);

		if (show)
			PrintResultEachTest(i, n, order, isSorted, -1.0f, comp);

		// Restore the original data
		for (int i = 0; i < n; ++i)
			testArray[i] = originalData[i];
	}

	avgComp /= numTests;

	PrintResultMultipleTests("[Multiple Tests] Result: ", n, order, -1.0f, avgComp);

	delete[] testArray;

	delete[] originalData;

	return 0;
}
