#ifndef TESTERLIB_H
#define TESTERLIB_H

// Documentation
// https://www.vietjack.com/cplusplus/interface_trong_cplusplus.jsp - Interface in C++
// https://www.geeksforgeeks.org/pure-virtual-functions-and-abstract-classes/ - Pure virtual functions and abstract classes
// https://www.ibm.com/docs/en/zos/2.4.0?topic=only-abstract-classes-c - Abstract classes in C++
// https://en.cppreference.com/w/cpp/language/virtual - Virtual functions

#include <vector>
#include <cstdio>
#include "Utils.h"

// Define function pointer types for sorting algorithms
using AlgPtr2 = void (*)(int *, int);						 // For algorithms that take an array and its size
using AlgPtr2Size_t = size_t (*)(int *, int);				 // For algorithms that take an array and its size and return the number of comparisons
using AlgPtr3 = void (*)(int *, int, int);					 // For algorithms that take an array, its size, and one index
using AlgPtr3Size_t = size_t (*)(int *, int, int);			 // For algorithms that take an array, its size, and one index and return the number of comparisons
using AlgPtr4 = void (*)(int *, int, int, int);				 // For algorithms that take an array, its size, and two indices
using AlgPtr4Size_t = size_t (*)(int *, int, int, int);		 // For algorithms that take an array, its size, and two indices and return the number of comparisons
using AlgPtr5 = void (*)(int *, int, int, int, int);		 // For algorithms that take an array, its size, and three indices
using AlgPtr5Size_t = size_t (*)(int *, int, int, int, int); // For algorithms that take an array, its size, and three indices and return the number of comparisons

// A namespace containing functions to test sorting algorithms
namespace TesterLib
{
	// Base class for sorting entities
	struct SortEntityBase
	{
		virtual ~SortEntityBase() = default;
		virtual const char *GetName() const = 0;
		virtual void Run(int *arr, int n) const = 0;
		virtual double GetRunningTime(int *arr, int n) const = 0;
		virtual size_t GetComparisons(int *arr, int n) const = 0;
	};

	// A struct to hold 2 types of sorting algorithms and their names
	template <typename T, typename C>
	struct SortEntity : SortEntityBase
	{
		const char *name;
		T sort_algorithm;
		C compare_algorithm;

		SortEntity(const char *name, T sort_algorithm, C compare_algorithm)
			: name(name), sort_algorithm(sort_algorithm), compare_algorithm(compare_algorithm) {}

		const char *GetName() const override { return this->name; }

		void Run(int *arr, int n) const override
		{
			if (this->sort_algorithm)
				this->sort_algorithm(arr, n);
			else
				printf("Error: No sorting algorithm is set\n");
		}

		double GetRunningTime(int *arr, int n) const override
		{
			if (this->sort_algorithm)
				return Utils::MeasureTime(this->sort_algorithm, arr, n);
			else
				printf("Error: No sorting algorithm is set\n");
			return -1.0;
		}

		size_t GetComparisons(int *arr, int n) const override
		{
			if (this->compare_algorithm)
				return this->compare_algorithm(arr, n);
			return 0;
		}
	};

	template <>
	struct SortEntity<AlgPtr3, AlgPtr3Size_t> : SortEntityBase
	{
		const char *name;
		AlgPtr3 sort_algorithm;
		AlgPtr3Size_t compare_algorithm = nullptr;

		SortEntity(const char *name, AlgPtr3 sort_algorithm, AlgPtr3Size_t compare_algorithm)
			: name(name), sort_algorithm(sort_algorithm), compare_algorithm(compare_algorithm){};

		const char *GetName() const override { return this->name; }

		void Run(int *arr, int n) const override
		{
			if (this->sort_algorithm)
				this->sort_algorithm(arr, n, 0);
			else
				printf("Error: No sorting algorithm is set\n");
		}

		double GetRunningTime(int *arr, int n) const override
		{
			if (this->sort_algorithm)
				return Utils::MeasureTime(this->sort_algorithm, arr, 0, n - 1);
			else
				printf("Error: No sorting algorithm is set\n");
			return -1.0;
		}

		size_t GetComparisons(int *arr, int n) const override
		{
			if (this->compare_algorithm)
				return this->compare_algorithm(arr, 0, n - 1);
			return 0;
		}
	};

	template <>
	struct SortEntity<AlgPtr4, AlgPtr4Size_t> : SortEntityBase
	{
		const char *name;
		AlgPtr4 sort_algorithm;
		AlgPtr4Size_t compare_algorithm;

		SortEntity(const char *name, AlgPtr4 sort_algorithm, AlgPtr4Size_t compare_algorithm)
			: name(name), sort_algorithm(sort_algorithm), compare_algorithm(compare_algorithm) {}

		const char *GetName() const override { return this->name; }

		void Run(int *arr, int n) const override
		{
			if (this->sort_algorithm)
				this->sort_algorithm(arr, n, 0, n - 1);
			else
				printf("Error: No sorting algorithm is set\n");
		}

		double GetRunningTime(int *arr, int n) const override
		{
			if (this->sort_algorithm)
				return Utils::MeasureTime(this->sort_algorithm, arr, n, 0, n - 1);
			else
				printf("Error: No sorting algorithm is set\n");
			return -1.0;
		}

		size_t GetComparisons(int *arr, int n) const override
		{
			if (this->compare_algorithm)
				return this->compare_algorithm(arr, n, 0, n - 1);
			return 0;
		}
	};

	/**
	 * Frees the memory allocated for sorting entities.
	 * @param container: A vector of sorting entities.
	 */
	void FreeContainer(std::vector<SortEntityBase *> &container);

	/**
	 * Gets a sorting entity by name.
	 * @param name: The name of the sorting entity.
	 * @param container: A vector of sorting entities.
	 * @return A pointer to the sorting entity if found, nullptr otherwise.
	 */
	SortEntityBase *GetSortEntity(const char *name, const std::vector<SortEntityBase *> &container);

	/**
	 * Runs a single test for multiple sorting algorithms.
	 * @param container: A vector of sorting entities.
	 * @param arr: The array to be sorted.
	 * @param n: The size of the array.
	 * @param order: The initial order of the array.
	 * @param show: Whether to show the array before and after sorting.
	 * @return 0 on success, -1 on failure.
	 */
	int RunMultiAlgWithSingleTest(
		const std::vector<SortEntityBase *> &container,
		int *arr, int n, int order, bool show);

	/**
	 * Runs multiple tests for multiple sorting algorithms.
	 * @param container: A vector of sorting entities.
	 * @param arr: The array to be sorted.
	 * @param n: The size of the array.
	 * @param order: The initial order of the array.
	 * @param numTests: The number of tests to run.
	 * @param show: Whether to show the array before and after sorting.
	 * @return 0 on success, -1 on failure.
	 */
	int RunMultiAlgWithMultipleTests(
		const std::vector<SortEntityBase *> &container,
		int *arr, int n, int order, int numTests, bool show);

	/**
	 * Runs a single test for a single sorting algorithm.
	 * @param entity: A sorting entity
	 * @param arr: The array to be sorted. (if nullptr, a new array will be generated)
	 * @param n: The size of the array.
	 * @param order: The initial order of the array.
	 * @param show: Whether to show the array before and after sorting.
	 * @return 0 on success, -1 on failure.
	 */
	int RunSingleTest(SortEntityBase *entity, int *arr, int n, int order, bool show);

	/**
	 * Run a single test for a single sorting algorithm with time measurement.
	 * @param entity: A sorting entity
	 * @param arr: The array to be sorted. (if nullptr, a new array will be generated)
	 * @param n: The size of the array.
	 * @param order: The initial order of the array.
	 * @param show: Whether to show the array before and after sorting.
	 * @return 0 on success, -1 on failure.
	 */
	int TimeRunSingleTest(SortEntityBase *entity, int *arr, int n, int order, bool show);

	/**
	 * Run a single test for a single sorting algorithm with comparison measurement.
	 * @param entity: A sorting entity
	 * @param arr: The array to be sorted. (if nullptr, a new array will be generated)
	 * @param n: The size of the array.
	 * @param order: The initial order of the array.
	 * @param show: Whether to show the array before and after sorting.
	 * @return 0 on success, -1 on failure.
	 */
	int CompRunSingleTest(SortEntityBase *entity, int *arr, int n, int order, bool show);

	/**
	 * Runs multiple tests for a single sorting algorithm.
	 * @param entity: A sorting entity
	 * @param arr: The array to be sorted.
	 * @param n: The size of the array.
	 * @param order: The initial order of the array.
	 * @param numTests: The number of tests to run.
	 * @param show: Whether to show the array before and after sorting.
	 * @return 0 on success, -1 on failure.
	 */
	int RunMultipleTests(SortEntityBase *entity, int *arr, int n, int order, int numTests, bool show, FILE *f);

	/**
	 * Runs multiple tests for a single sorting algorithm in parallel.
	 * @param entity: A sorting entity
	 * @param arr: The array to be sorted.
	 * @param n: The size of the array.
	 * @param order: The initial order of the array.
	 * @param numTests: The number of tests to run.
	 * @param show: Whether to show the array before and after sorting.
	 * @return 0 on success, -1 on failure.
	 */
	int RunMultipleTestsParallel(SortEntityBase *entity, int *arr, int n, int order, int numTests, bool show, FILE *f);

	/**
	 * Run multipl test for a single sorting algorithm with time measurement.
	 * @param entity: A sorting entity
	 * @param arr: The array to be sorted.
	 * @param n: The size of the array.
	 * @param order: The initial order of the array.
	 * @param numTests: The number of tests to run.
	 * @param show: Whether to show the array before and after sorting.
	 * @return 0 on success, -1 on failure.

	*/
	int TimeRunMultipleTest(SortEntityBase *entity, int *arr, int n, int order, int numTests, bool show);

	/**
	 * Run multipl test for a single sorting algorithm with comparison measurement.
	 * @param entity: A sorting entity
	 * @param arr: The array to be sorted.
	 * @param n: The size of the array.
	 * @param order: The initial order of the array.
	 * @param numTests: The number of tests to run.
	 * @param show: Whether to show the array before and after sorting.
	 * @return 0 on success, -1 on failure.
	 */
	int CompRunMultipleTest(SortEntityBase *entity, int *arr, int n, int order, int numTests, bool show);
}

// Define sorting entities
using SortEntity2 = TesterLib::SortEntity<AlgPtr2, AlgPtr2Size_t>;
using SortEntity3 = TesterLib::SortEntity<AlgPtr3, AlgPtr3Size_t>;
using SortEntity4 = TesterLib::SortEntity<AlgPtr4, AlgPtr4Size_t>;
using SortEntity5 = TesterLib::SortEntity<AlgPtr5, AlgPtr5Size_t>;

#endif // !TESTERLIB_H
