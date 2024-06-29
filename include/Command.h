#ifndef COMMAND_H
#define COMMAND_H

#include "Algorithms.h"

// Command line 1: Sorting.exe -a [Algorithm] [Input file] [Output param]
// Command line 2: Sorting.exe -a [Algorithm] [Input size] [Input order] [Output param]
// Command line 3: Sorting.exe -a [Algorithm] [Input size] [Output param]
// Command line 4: Sorting.exe -c [Algorithm 1] [Algorithm 2] [Given input file]
// Command line 5: Sorting.exe -c [Algorithm 1] [Algorithm 2] [Input size] [Input order]
// Mode:
// -a: Algorithm mode
// -c: Comparision mode
// Input order:
// -rand: Random order
// -nsorted: Nearly sorted order
// -sorted: Sorted order
// -rev: Reverse order
// Given input file: Path to thse input file
// Input size: Number of elements in the input array, range from 1 to 10^6
// Output param: Path to the output file
// -time: Measure the time of execution
// -comp: Measure the number of comparisons
// -both: Measure both time and comparisons

namespace CommandLib
{
	enum Mode
	{
		INVALID_MODE = -1,
		Alogrithm,
		Comparision
	};

	enum InputOrder
	{
		INVALID_IN_ORDER = -1,
		RANDOM,
		SORTED,
		REVERSE,
		NSORTED // Nearly sorted
	};

	enum OutputMode
	{
		INVALID_OUT_MODE = -1,
		TIME,
		COMP,
		BOTH
	};

	// A struct to store the command line arguments
	struct Command
	{
		Mode mode = Mode::INVALID_MODE;						  // -1: No mode
		int algorithm_1 = -1;								  // -1: No algorithm
		int algorithm_2 = -1;								  // -1: No algorithm
		int inputSize = -1;									  // -1: No input size
		InputOrder inputOrder = InputOrder::INVALID_IN_ORDER; // -1: No input order
		const char *inputFileName = nullptr;				  // Default input file name
		OutputMode outputMode = OutputMode::INVALID_OUT_MODE; // -1: No output mode
		int typeCommand = -1;								  // Command line 1, 2, 3, 4, 5
	};

	// Parses the command line arguments and populates the Command struct
	int parseCommandLineArguments(int argc, char **argv, Command &command);

	// Print formatted message to the console
	void printConsoleMessage(const Command &command, const Algorithms::Benchmark &benchmark_1, const Algorithms::Benchmark &benchmark_2);

	// Output the result to the output file
	void outputBenchmarkResults(const Command &command, const Algorithms::Benchmark &benchmark_1, const Algorithms::Benchmark &benchmark_2);
}

#endif // !COMMAND_H
