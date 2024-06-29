#define _CRT_SECURE_NO_WARNINGS
#include "Command.h"
#include "Utils.h"
#include <cstring>
#include <iomanip>

namespace CommandLib
{
	static void helpCommand()
	{
		std::cout << "Usage:" << std::endl;
		std::cout << "Command line 1: [Exection file] -a [Algorithms] [Input file] [Output param(s)]" << std::endl;
		std::cout << "Command line 2: [Exection file] -a [Algorithms] [Input size] [Input order] [Output param(s)]" << std::endl;
		std::cout << "Command line 3: [Exection file] -a [Algorithms] [Input size] [Output param(s)]" << std::endl;
		std::cout << "Command line 4: [Exection file] -c [Algorithms 1] [Algorithms 2] [Given input file]" << std::endl;
		std::cout << "Command line 5: [Exection file] -c [Algorithms 1] [Algorithms 2] [Input size] [Input order]" << std::endl
				  << std::endl;

		std::cout << "Algorithms: ";
		for (int i = 0; i < Algorithms::NUM_ALGORITHMS; ++i)
		{
			if (i != Algorithms::NUM_ALGORITHMS - 1)
				std::cout << Algorithms::ALGORITHMS[i] << ", ";
			else
				std::cout << Algorithms::ALGORITHMS[i] << std::endl;
		}

		// Show information about input order and output param
		std::cout << "Input order: -rand, -sorted, -rev, -nsorted" << std::endl;
		std::cout << "Output param(s): -time, -comp, -both" << std::endl;
		std::cout << "Given input file: Path to the input file" << std::endl;
		std::cout << "Input size: Number of elements in the input array, range from 1 to 10^6" << std::endl;
		std::cout << "Output file will be saved in the same directory automatically" << std::endl
				  << std::endl;

		// Show information about the command line
		std::cout << "Command line 1 and 2: Write down the sorted array to the \"output.txt\"" << std::endl;
		std::cout << "Command line 2 and 5: Write down the generated input to the \"input.txt\"" << std::endl;
		std::cout << "Command line 3: Write down all four generated input:" << std::endl;
		std::cout << "  - Random order to the \"input_1.txt\"" << std::endl;
		std::cout << "  - Nearly Sorted order to the \"input_2.txt\"" << std::endl;
		std::cout << "  - Sorted order to the \"input_3.txt\"" << std::endl;
		std::cout << "  - Reverse order to the \"input_4.txt\"" << std::endl
				  << std::endl;

		// Show information about developers
		std::cout << "--------------------------------------------------" << std::endl;
		std::cout << "Developed by: " << std::endl;
		std::cout << "  - Dang Lu Kieu My - 23127230" << std::endl;
		std::cout << "  - Nguyen Pham Minh Thu - MSSV" << std::endl;
		std::cout << "  - Nguyen Dang Khoa - 23127393" << std::endl;
		std::cout << "  - Ho Minh Dung - 23127174" << std::endl;
		std::cout << "Thank you for using our program!" << std::endl;
	}

	static int findAlgorithm(const char *algorithm)
	{
		for (int i = 0; i < Algorithms::NUM_ALGORITHMS; i++)
		{
			if (strcmp(algorithm, Algorithms::ALGORITHMS[i]) == 0)
				return i;
		}

		return -1;
	}

	static bool isValidInputFile(const char *inputFileName, int &size)
	{
		FILE *file = fopen(inputFileName, "r");

		if (!file) // File does not exist
			return false;

		if (fscanf(file, "%d", &size) != 1) // Read the size of the array
		{
			fclose(file);
			return false;
		}

		fclose(file);

		return true;
	}

	static InputOrder findInputOrder(const char *inputOrder)
	{
		if (strcmp(inputOrder, "-rand") == 0)
			return InputOrder::RANDOM;
		else if (strcmp(inputOrder, "-sorted") == 0)
			return InputOrder::SORTED;
		else if (strcmp(inputOrder, "-rev") == 0)
			return InputOrder::REVERSE;
		else if (strcmp(inputOrder, "-nsorted") == 0)
			return InputOrder::NSORTED;

		return InputOrder::INVALID_IN_ORDER;
	}

	static OutputMode findOutputMode(const char *outputMode)
	{
		if (strcmp(outputMode, "-time") == 0)
			return OutputMode::TIME;
		else if (strcmp(outputMode, "-comp") == 0)
			return OutputMode::COMP;
		else if (strcmp(outputMode, "-both") == 0)
			return OutputMode::BOTH;

		return OutputMode::INVALID_OUT_MODE;
	}

	static bool isValidInputSize(int inputSize)
	{
		return (inputSize > 0 && inputSize <= 1000000);
	}

	static const char *getInputOrderString(InputOrder inputOrder)
	{
		switch (inputOrder)
		{
		case InputOrder::RANDOM:
			return "Random";
		case InputOrder::SORTED:
			return "Sorted";
		case InputOrder::REVERSE:
			return "Reverse";
		case InputOrder::NSORTED:
			return "Nearly sorted";
		default:
			return "Invalid input order";
		}
	}

	static const char *getOutputModeString(OutputMode outputMode)
	{
		switch (outputMode)
		{
		case OutputMode::TIME:
			return "Time";
		case OutputMode::COMP:
			return "Comparisions";
		case OutputMode::BOTH:
			return "Both";
		default:
			return "Invalid output mode";
		}
	}

	int parseCommandLineArguments(int argc, char **argv, Command &command)
	{
		// Check the number of arguments
		if (argc < 5)
		{
			// Check if the user wants to see the help
			if ((argc == 2 && ((strcmp(argv[1], "-h") == 0) || strcmp(argv[1], "--help") == 0)) || (argc == 1))
			{
				helpCommand();
				return 0;
			}

			std::cerr << "Invalid command line arguments" << std::endl;
			return 0;
		}

		// Parse mode
		if (strcmp(argv[1], "-a") == 0)
		{
			command.mode = Mode::Alogrithm;
		}
		else if (strcmp(argv[1], "-c") == 0)
		{
			command.mode = Mode::Comparision;
		}
		else
		{
			std::cerr << "Invalid mode" << std::endl;
			return 0;
		}

		// Parse arguments in mode Algorithms
		if (command.mode == Mode::Alogrithm)
		{
			// Find the algorithm in the list
			command.algorithm_1 = findAlgorithm(argv[2]);

			// Invalid algorithm
			if (command.algorithm_1 == -1)
			{
				std::cerr << "[Mode Algorithms] Invalid algorithm" << std::endl;
				return 0;
			}

			// Check if the file exists
			if (isValidInputFile(argv[3], command.inputSize))
			{
				command.typeCommand = 1;
				command.inputFileName = argv[3];
			}
			// If the file does not exist, then argv[3] is a number
			else
			{
				// Check if argv[3] is a number
				int inputSize = atoi(argv[3]);

				if (isValidInputSize(inputSize))
				{
					if (argc == 5)
						command.typeCommand = 3;
					else if (argc == 6)
						command.typeCommand = 2;
					else
					{
						std::cerr << "[Mode Algorithms] Invalid command line arguments" << std::endl;
						return 0;
					}

					command.inputSize = inputSize;
				}
				else
				{
					std::cerr << "[Mode Algorithms] Invalid input size" << std::endl;
					return 0;
				}
			}

			// If the command line is 1 or 3
			if (command.typeCommand == 1 || command.typeCommand == 3)
			{
				// Parse output param
				command.outputMode = findOutputMode(argv[4]);

				if (command.outputMode == OutputMode::INVALID_OUT_MODE)
				{
					std::cerr << "[Mode Algorithms] Invalid output param" << std::endl;
					return 0;
				}

				return 1; // Finish parsing the command line
			}

			// If the command line is 2
			if (command.typeCommand == 2)
			{
				// Parse input order
				command.inputOrder = findInputOrder(argv[4]);

				if (command.inputOrder == InputOrder::INVALID_IN_ORDER)
				{
					std::cerr << "[Mode Algorithms] Invalid input order" << std::endl;
					return 0;
				}

				// Parse output param
				command.outputMode = findOutputMode(argv[5]);

				if (command.outputMode == OutputMode::INVALID_OUT_MODE)
				{
					std::cerr << "[Mode Algorithms] Invalid output param" << std::endl;
					return 0;
				}

				return 1; // Finish parsing the command line
			}
		} // end of if (command.mode == Mode::Alogrithm)
		// Parse arguments in mode Comparision
		else if (command.mode == Mode::Comparision)
		{
			// Find the first algorithm in the list
			command.algorithm_1 = findAlgorithm(argv[2]);

			// Invalid algorithm
			if (command.algorithm_1 == -1)
			{
				std::cerr << "[Mode Comparision] Invalid algorithm 1" << std::endl;
				return 0;
			}

			// Find the second algorithm in the list
			command.algorithm_2 = findAlgorithm(argv[3]);

			// Invalid algorithm
			if (command.algorithm_2 == -1)
			{
				std::cerr << "[Mode Comparision] Invalid algorithm 2" << std::endl;
				return 0;
			}

			// Check if the file exists
			if (isValidInputFile(argv[4], command.inputSize))
			{
				command.typeCommand = 4;
				command.inputFileName = argv[4];

				return 1; // Finish parsing the command line
			}
			// If the file does not exist, then argv[4] may be a number
			else
			{
				// Check if argv[4] is a number
				int inputSize = atoi(argv[4]);

				if (isValidInputSize(inputSize))
				{
					if (argc == 6)
						command.typeCommand = 5;
					else
					{
						std::cerr << "[Mode Comparision] Invalid command line arguments" << std::endl;
						return 0;
					}

					command.inputSize = inputSize;
				}
				else
				{
					std::cerr << "[Mode Comparision] Invalid input size" << std::endl;
					return 0;
				}

				// Parse input order
				command.inputOrder = findInputOrder(argv[5]);

				if (command.inputOrder == InputOrder::INVALID_IN_ORDER)
				{
					std::cerr << "[Mode Comparision] Invalid input order" << std::endl;
					return 0;
				}

				return 1; // Finish parsing the command line
			}
		} // end of if (command.mode == Mode::Comparision)

		return 0; // Invalid command
	} // end of parseCommand

	// Print the output of the command line
	// type: 0 - Time, 1 - Comparisions, 2 - Both
	static void printCommandOutput(int type, const Algorithms::Benchmark &benchmark, int order = 0) // Default order is 0 - Random order
	{
		if (type != OutputMode::INVALID_OUT_MODE)
		{
			std::cout << "--------------" << std::endl;
			if (type == OutputMode::TIME)
			{
				switch (order)
				{
				case 0: // Random order
					std::cout << "Running time: " << benchmark.Random.time << " (ms)" << std::endl;
					break;
				case 1: // Sorted order
					std::cout << "Running time: " << benchmark.Sorted.time << " (ms)" << std::endl;
					break;
				case 2: // Reverse order
					std::cout << "Running time: " << benchmark.Reverse.time << " (ms)" << std::endl;
					break;
				case 3: // Nearly sorted order
					std::cout << "Running time: " << benchmark.NearlySorted.time << " (ms)" << std::endl;
					break;
				default:
					break;
				}
			}
			else if (type == OutputMode::COMP)
			{
				switch (order)
				{
				case 0: // Random order
					std::cout << "Comparisions: " << benchmark.Random.comparisons << std::endl;
					break;
				case 1: // Sorted order
					std::cout << "Comparisions: " << benchmark.Sorted.comparisons << std::endl;
					break;
				case 2: // Reverse order
					std::cout << "Comparisions: " << benchmark.Reverse.comparisons << std::endl;
					break;
				case 3: // Nearly sorted order
					std::cout << "Comparisions: " << benchmark.NearlySorted.comparisons << std::endl;
					break;
				default:
					break;
				}
			}
			else if (type == OutputMode::BOTH)
			{
				switch (order)
				{
				case 0: // Random order
					std::cout << "Running time: " << benchmark.Random.time << " (ms)" << std::endl;
					std::cout << "Comparisions: " << benchmark.Random.comparisons << std::endl;
					break;
				case 1: // Sorted order
					std::cout << "Running time: " << benchmark.Sorted.time << " (ms)" << std::endl;
					std::cout << "Comparisions: " << benchmark.Sorted.comparisons << std::endl;
					break;
				case 2: // Reverse order
					std::cout << "Running time: " << benchmark.Reverse.time << " (ms)" << std::endl;
					std::cout << "Comparisions: " << benchmark.Reverse.comparisons << std::endl;
					break;
				case 3: // Nearly sorted order
					std::cout << "Running time: " << benchmark.NearlySorted.time << " (ms)" << std::endl;
					std::cout << "Comparisions: " << benchmark.NearlySorted.comparisons << std::endl;
					break;
				default:
					break;
				}
			}
		}
	} // end of printCommandOutput

	void printConsoleMessage(const Command &command, const Algorithms::Benchmark &benchmark_1, const Algorithms::Benchmark &benchmark_2)
	{
		switch (command.typeCommand)
		{
		case 1:
		{
			std::cout << "ALGORITHM MODE" << std::endl;
			std::cout << "Algorithm: " << Algorithms::ALGORITHMS[command.algorithm_1] << std::endl;
			std::cout << "Input file: " << command.inputFileName << std::endl;
			std::cout << "Input size: " << command.inputSize << std::endl;

			printCommandOutput(command.outputMode, benchmark_1);

			break;
		}
		case 2:
		{
			std::cout << "ALGORITHM MODE" << std::endl;
			std::cout << "Algorithm: " << Algorithms::ALGORITHMS[command.algorithm_1] << std::endl;
			std::cout << "Input size: " << command.inputSize << std::endl;
			std::cout << "Input order: " << getInputOrderString(command.inputOrder) << std::endl;

			printCommandOutput(command.outputMode, benchmark_1, command.inputOrder);

			break;
		}
		case 3:
		{
			std::cout << "ALGORITHM MODE" << std::endl;
			std::cout << "Algorithm: " << Algorithms::ALGORITHMS[command.algorithm_1] << std::endl;
			std::cout << "Input size: " << command.inputSize << std::endl;

			std::cout << "Input order: Randomize" << std::endl;
			printCommandOutput(command.outputMode, benchmark_1, 0);
			std::cout << std::endl;

			std::cout << "Input order: Nearly sorted" << std::endl;
			printCommandOutput(command.outputMode, benchmark_1, 3);
			std::cout << std::endl;

			std::cout << "Input order: Sorted" << std::endl;
			printCommandOutput(command.outputMode, benchmark_1, 1);
			std::cout << std::endl;

			std::cout << "Input order: Reverse" << std::endl;
			printCommandOutput(command.outputMode, benchmark_1, 2);

			break;
		}
		case 4:
		{
			std::cout << "COMPARE MODE" << std::endl;
			std::cout << "Algorithm: " << Algorithms::ALGORITHMS[command.algorithm_1] << " | " << Algorithms::ALGORITHMS[command.algorithm_2] << std::endl;
			std::cout << "Input file: " << command.inputFileName << std::endl;
			std::cout << "Input size: " << command.inputSize << std::endl;

			std::cout << "---------------------------" << std::endl;
			std::cout << "Running time: " << benchmark_1.Random.time << " (ms) | " << benchmark_2.Random.time << " (ms)" << std::endl;
			std::cout << "Comparisions: " << benchmark_1.Random.comparisons << " | " << benchmark_2.Random.comparisons << std::endl;

			break;
		}
		case 5:
		{
			std::cout << "COMPARE MODE" << std::endl;
			std::cout << "Algorithm: " << Algorithms::ALGORITHMS[command.algorithm_1] << " | " << Algorithms::ALGORITHMS[command.algorithm_2] << std::endl;
			std::cout << "Input size: " << command.inputSize << std::endl;
			std::cout << "Input order: " << getInputOrderString(command.inputOrder) << std::endl;

			std::cout << "---------------------------" << std::endl;
			std::cout << "Running time: " << benchmark_1.Random.time << " (ms) | " << benchmark_2.Random.time << " (ms)" << std::endl;
			std::cout << "Comparisions: " << benchmark_1.Random.comparisons << " | " << benchmark_2.Random.comparisons << std::endl;

			break;
		}
		default:
			break;
		}
	}

	void outputBenchmarkResults(const Command &command, const Algorithms::Benchmark &benchmark_1, const Algorithms::Benchmark &benchmark_2)
	{
		switch (command.typeCommand)
		{
		case 1: // print sorted array
		{
			Utils::WriteFile("output.txt", benchmark_1.Random.sortedArr, benchmark_1.Random.sizeArr);

			break;
		}
		case 2:
		{
			switch (command.inputOrder)
			{
			case InputOrder::RANDOM:
			{
				Utils::WriteFile("input.txt", benchmark_1.Random.originalArr, benchmark_1.Random.sizeArr);

				Utils::WriteFile("output.txt", benchmark_1.Random.sortedArr, benchmark_1.Random.sizeArr);
				break;
			}
			case InputOrder::SORTED:
			{
				Utils::WriteFile("input.txt", benchmark_1.Sorted.originalArr, benchmark_1.Sorted.sizeArr);

				Utils::WriteFile("output.txt", benchmark_1.Sorted.sortedArr, benchmark_1.Sorted.sizeArr);
				break;
			}
			case InputOrder::REVERSE:
			{
				Utils::WriteFile("input.txt", benchmark_1.Reverse.originalArr, benchmark_1.Reverse.sizeArr);

				Utils::WriteFile("output.txt", benchmark_1.Reverse.sortedArr, benchmark_1.Reverse.sizeArr);
				break;
			}
			case InputOrder::NSORTED:
			{
				Utils::WriteFile("input.txt", benchmark_1.NearlySorted.originalArr, benchmark_1.NearlySorted.sizeArr);

				Utils::WriteFile("output.txt", benchmark_1.NearlySorted.sortedArr, benchmark_1.NearlySorted.sizeArr);
				break;
			}
			default:
				break;
			}
			break;
		}
		case 3:
		{
			Utils::WriteFile("input_1.txt", benchmark_1.Random.originalArr, benchmark_1.Random.sizeArr);

			Utils::WriteFile("input_2.txt", benchmark_1.NearlySorted.originalArr, benchmark_1.NearlySorted.sizeArr);

			Utils::WriteFile("input_3.txt", benchmark_1.Sorted.originalArr, benchmark_1.Sorted.sizeArr);

			Utils::WriteFile("input_4.txt", benchmark_1.Reverse.originalArr, benchmark_1.Reverse.sizeArr);

			break;
		}
		case 5:
		{
			Utils::WriteFile("input.txt", benchmark_1.Random.originalArr, benchmark_1.Random.sizeArr);

			break;
		}
		default:
			break;
		}
	}
} // end of namespace Command