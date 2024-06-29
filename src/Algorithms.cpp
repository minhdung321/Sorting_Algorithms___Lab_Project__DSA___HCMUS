#include "Algorithms.h"

namespace Algorithms
{
	const char *ALGORITHMS[] = {
		"selection-sort",
		"insertion-sort",
		"bubble-sort",
		"shaker-sort",
		"shell-sort",
		"heap-sort",
		"merge-sort",
		"quick-sort",
		"counting-sort",
		"radix-sort",
		"flash-sort"};

	const int NUM_ALGORITHMS = sizeof(ALGORITHMS) / sizeof(ALGORITHMS[0]);
}