# Sorting Algorithms C++ Project

# Table of Contents
- [Sorting Algorithms C++ Project](#sorting-algorithms-c-project)
- [Table of Contents](#table-of-contents)
- [Description](#description)
  - [Installation Tutorial](#installation-tutorial)
    - [Requirements:](#requirements)
    - [Installation:](#installation)
    - [Building the project:](#building-the-project)
      - [Building the project with CMake options:](#building-the-project-with-cmake-options)
  - [Usage:](#usage)
- [TesterLib Documentation](#testerlib-documentation)
  - [About](#about)
    - [Typedefs](#typedefs)
    - [Classes](#classes)
      - [`SortEntityBase`](#sortentitybase)
      - [`SortEntity`](#sortentity)
    - [Functions](#functions)
  - [Example Usage](#example-usage)
      - [Using the TesterLib library to benchmark sorting algorithms in C++.](#using-the-testerlib-library-to-benchmark-sorting-algorithms-in-c)
  - [Notes](#notes)

# Description
    - This project is a collection of sorting algorithms implemented in C++ with 11 algorithms implemented so far. 
    - The algorithms implemented are:  Selection Sort, Insertion Sort, Bubble Sort, Shaker Sort, Shell Sort, Heap Sort, Merge Sort, Quick Sort, Counting Sort, Radix Sort, and Flash Sort.
    - This project to support us to benchmark the performance of these algorithms and compare them with each other.
    - If you want to add more algorithms, you can add them to the project and benchmark them with the other algorithms. You can read documentation about the TesterLib library to know how to add more algorithms to the project.

## Installation Tutorial

### Requirements:
- CMake verison 3.10 or higher
- C++14 compliant compiler

### Installation:
- With Windows:
    - Install CMake: [Download and Install CMake](https://cmake.org/download/).
    - Install Visual Studio: [Download and Install Visual Studio](https://visualstudio.microsoft.com/).
    - Open the project folder in Visual Studio and build the project.

- With Linux:
    - Install CMake: `sudo apt-get install cmake`.
    - Install GCC: `sudo apt-get install gcc`.
    - Install G++: `sudo apt-get install g++`.

### Building the project:
- With Windows:
    - Open terminal in the project folder.
    - Run the following commands:
        - `mkdir build`
        - `cd build`
        - `cmake ..`
        - `cmake --build .`
  
- With Linux:
    - Open terminal in the project folder.
    - Run the following commands:
        - `mkdir build`
        - `cd build`
        - `cmake ..`
          
          ![image](https://github.com/minhdung321/Sorting_Algorithms___Lab_Project__DSA___HCMUS/assets/39442146/ae30e558-ea43-4370-9a3b-c499c5c5cdd7)
        - `make`
      
          ![image](https://github.com/minhdung321/Sorting_Algorithms___Lab_Project__DSA___HCMUS/assets/39442146/48a2f71c-d8f6-4e32-ad3e-ca20de4eb896)
        - Now, there is an executable file in `bin/` folder.   
        
- After successfully building the project, you will find the executable file in the `build/bin/Debug` folder or `build/bin/Release` folder, depending on the build type and platform.
  
#### Building the project with CMake options:
    - To change the build type, use the following command: `cmake -DCMAKE_BUILD_TYPE=Release ..`
    - To disable the -march=native flag, use the following command: `cmake -DUSE_MARCH_NATIVE=OFF ..`
    - If you want to get the best performance, use the following command: `cmake --build . --config Release`

## Usage:
- If you do not know how to use the program, you can run the program without any arguments or with the `-h` or `--help` argument to get the help message.

# TesterLib Documentation

## About
    Namespace: `TesterLib`
    This library is used to benchmark the performance of sorting algorithms in C++. 

### Typedefs
```cpp
using AlgPtr2 = void(*)(int*, int);
using AlgPtr2Size_t = size_t(*)(int*, int);
using AlgPtr3 = void(*)(int*, int, int);
using AlgPtr3Size_t = size_t(*)(int*, int, int);
using AlgPtr4 = void(*)(int*, int, int, int);
using AlgPtr4Size_t = size_t(*)(int*, int, int, int);
using AlgPtr5 = void(*)(int*, int, int, int, int);
using AlgPtr5Size_t = size_t(*)(int*, int, int, int, int);

using SortEntity2 = TesterLib::SortEntity<AlgPtr2, AlgPtr2Size_t>;
using SortEntity3 = TesterLib::SortEntity<AlgPtr3, AlgPtr3Size_t>;
using SortEntity4 = TesterLib::SortEntity<AlgPtr4, AlgPtr4Size_t>;
using SortEntity5 = TesterLib::SortEntity<AlgPtr5, AlgPtr5Size_t>;
```
### Classes

#### `SortEntityBase`
- Base class for the sorting algorithm entity.

#### `SortEntity`
- Structure of the sorting algorithm entity.
  ```cpp
  template <typename T, typename C>
  struct SortEntity : SortEntityBase
  {
    const char* name;
    T sort_algorithm;
    C compare_algorithm;
    SortEntity(const char* name, T sort_algorithm, C compare_algorithm);
    const char* GetName() const override;
    void Run(int* arr, int n) const override;
    double GetRunningTime(int* arr, int n) const override;
    size_t GetComparisons(int* arr, int n) const override;
  };
  ```

### Functions

- `void FreeContainer(std::vector<SortEntityBase *> &container);`
  Frees the memory allocated for sorting entities.
  - **Parameters**
    - `container`: A vector of sorting entities.

- `SortEntityBase *GetSortEntity(const char *name, const std::vector<SortEntityBase *> &container);`
  Gets a sorting entity by name.
  - **Parameters**
    - `name`: The name of the sorting entity.
    - `container`: A vector of sorting entities.
  - **Returns** A pointer to the sorting entity if found, nullptr otherwise.

- `int RunMultiAlgWithSingleTest(const std::vector<SortEntityBase *> &container, int *arr, int n, int order, bool show);`
  Runs a single test for multiple sorting algorithms.
  - **Parameters**
    - `container`: A vector of sorting entities.
    - `arr`: The array to be sorted.
    - `n`: The size of the array.
    - `order`: The initial order of the array.
    - `show`: Whether to show the array before and after sorting.
  - **Returns** 0 on success, -1 on failure.

- `int RunMultiAlgWithMultipleTests(const std::vector<SortEntityBase *> &container, int *arr, int n, int order, int numTests, bool show);`
  Runs multiple tests for multiple sorting algorithms.
  - **Parameters**
    - `container`: A vector of sorting entities.
    - `arr`: The array to be sorted.
    - `n`: The size of the array.
    - `order`: The initial order of the array.
    - `numTests`: The number of tests to run.
    - `show`: Whether to show the array before and after sorting.
  - **Returns** 0 on success, -1 on failure.

- `int RunSingleTest(SortEntityBase *entity, int *arr, int n, int order, bool show);`
  Runs a single test for a single sorting algorithm.
  - **Parameters**
    - `entity`: A sorting entity
    - `arr`: The array to be sorted. (if nullptr, a new array will be generated)
    - `n`: The size of the array.
    - `order`: The initial order of the array.
    - `show`: Whether to show the array before and after sorting.
  - **Returns** 0 on success, -1 on failure.

- `int TimeRunSingleTest(SortEntityBase *entity, int *arr, int n, int order, bool show);`
  Run a single test for a single sorting algorithm with time measurement.
  - **Parameters**
    - `entity`: A sorting entity
    - `arr`: The array to be sorted. (if nullptr, a new array will be generated)
    - `n`: The size of the array.
    - `order`: The initial order of the array.
    - `show`: Whether to show the array before and after sorting.
  - **Returns** 0 on success, -1 on failure.

- `int CompRunSingleTest(SortEntityBase *entity, int *arr, int n, int order, bool show);`
  Run a single test for a single sorting algorithm with comparison measurement.
  - **Parameters**
    - `entity`: A sorting entity
    - `arr`: The array to be sorted. (if nullptr, a new array will be generated)
    - `n`: The size of the array.
    - `order`: The initial order of the array.
    - `show`: Whether to show the array before and after sorting.
  - **Returns** 0 on success, -1 on failure.

- `int RunMultipleTests(SortEntityBase *entity, int *arr, int n, int order, int numTests, bool show, FILE *f);`
  Runs multiple tests for a single sorting algorithm.
  - **Parameters**
    - `entity`: A sorting entity
    - `arr`: The array to be sorted.
    - `n`: The size of the array.
    - `order`: The initial order of the array.
    - `numTests`: The number of tests to run.
    - `show`: Whether to show the array before and after sorting.
    - `f`: File pointer for logging results.
  - **Returns** 0 on success, -1 on failure.

- `int RunMultipleTestsParallel(SortEntityBase *entity, int *arr, int n, int order, int numTests, bool show, FILE *f);`
  Runs multiple tests for a single sorting algorithm in parallel.
  - **Parameters**
    - `entity`: A sorting entity
    - `arr`: The array to be sorted.
    - `n`: The size of the array.
    - `order`: The initial order of the array.
    - `numTests`: The number of tests to run.
    - `show`: Whether to show the array before and after sorting.
    - `f`: File pointer for logging results.
  - **Returns** 0 on success, -1 on failure.

- `int TimeRunMultipleTest(SortEntityBase *entity, int *arr, int n, int order, int numTests, bool show);`
  Run multipl test for a single sorting algorithm with time measurement.
  - **Parameters**
    - `entity`: A sorting entity
    - `arr`: The array to be sorted.
    - `n`: The size of the array.
    - `order`: The initial order of the array.
    - `numTests`: The number of tests to run.
    - `show`: Whether to show the array before and after sorting.
  - **Returns** 0 on success, -1 on failure.

- `int CompRunMultipleTest(SortEntityBase *entity, int *arr, int n, int order, int numTests, bool show);`
  Run multipl test for a single sorting algorithm with comparison measurement.
  - **Parameters**
    - `entity`: A sorting entity
    - `arr`: The array to be sorted.
    - `n`: The size of the array.
    - `order`: The initial order of the array.
    - `numTests`: The number of tests to run.
    - `show`: Whether to show the array before and after sorting.
  - **Returns** 0 on success, -1 on failure.
  
## Example Usage

#### Using the TesterLib library to benchmark sorting algorithms in C++.
```cpp
#include "TesterLib.h"
#include <iostream>

// Example sorting algorithms
void BubbleSort(int* arr, int n);
size_t BubbleSortComp(int* arr, int n);

void SelectionSort(int*, arr, int n);
size_t SelectionSortComp(int* arr, int n);

void InsertionSort(int* arr, int n);
size_t InsertionSortComp(int* arr, int n);

// Function with 3 parameters
void QuickSort(int* arr, int left, int right);
size_t QuickSortComp(int* arr, int left, int right);

int main()
{
    // Initialize sorting entities
    TesterLib::SortEntityBase* selectionEntity = new TesterLib::SortEntity<AlgPtr2, AlgPtr2Size_t>("selection-sort", SelectionSort, SelectionSortComp);
    TesterLib::SortEntityBase* bubbleEntity = new TesterLib::SortEntity<AlgPtr2, AlgPtr2Size_t>("bubble-sort", BubbleSort, BubbleSortComp);
    TesterLib::SortEntityBase* quickEntity = new SortEntity3("quick-sort", QuickSort, QuickSortComp); // You can use typedefs to simplify the code

    // Initialize a container with sorting entities
    std::vector<TesterLib::SortEntityBase*> container = {
        new SortEntity2("insertion-sort", InsertionSort, InsertionSortComp) // You can add more sorting entities here
    };

    // Add more sorting entities to the container
    container.push_back(selectionEntity);
    container.push_back(bubbleEntity);
    container.push_back(quickEntity);

    // Example array
    int arr[] = {5, 2, 9, 1, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Run a single test for multiple sorting algorithms
    TesterLib::RunMultiAlgWithSingleTest(container, arr, n, 0, true);
    TesterLib::RunMultiAlgWithSingleTest(container, nullptr, 10000, 0, true); // Benchmark the algorithms with automatically generated data with 10000 elements

    // Run multiple tests for multiple sorting algorithms 
    TesterLib::RunMultiAlgWithMultipleTests(container, arr, n, 0, 5, true);
    TesterLib::RunMultiAlgWithMultipleTests(container, nullptr, 1000, 0, 5, true); // Benchmark the algorithms with automatically generated data with 1000 elements

    // Run a single test for a single sorting algorithm
    TesterLib::RunSingleTest(&bubbleSortEntity, arr, n, 0, true);
    TesterLib::RunSingleTest(&bubbleSortEntity, nullptr, 10000, 0, true);

    // Run multiple tests for a single sorting algorithm
    TesterLib::RunMultipleTests(&quickSortEntity, arr, n, 0, 5, true);
    TesterLib::RunMultipleTests(&quickSortEntity, nullptr, 1000000, 0, 5, true);

    // Free the container
    TesterLib::FreeContainer(container);

    return 0;
}
```

## Notes
- Make sure to include the necessary headers and libraries in your project.
- Make sure to free the memory allocated for sorting entities using the `FreeContainer` function.
- Namespace 'Utils' is used to store utility functions and classes.
