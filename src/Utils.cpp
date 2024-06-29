#define _CRT_SECURE_NO_WARNINGS
#include "Utils.h"

namespace Utils
{
	void ReadFile(const char *fileName, int *&arr, int &n)
	{
		FILE *file = fopen(fileName, "r");
		if (!file)
		{
			printf("Cannot open file %s\n", fileName);
			return;
		}

		fscanf(file, "%d", &n);

		arr = new int[n];

		if (!arr)
		{
			printf("Memory allocation failed\n");
			return;
		}

		for (int i = 0; i < n; i++)
			fscanf(file, "%d", &arr[i]);

		fclose(file);
	}

	void WriteFile(const char *fileName, int *arr, int n)
	{
		FILE *file = fopen(fileName, "w");

		if (!file)
		{
			printf("Cannot open file %s\n", fileName);
			return;
		}

		fprintf(file, "%d\n", n);

		for (int i = 0; i < n; i++)
			fprintf(file, "%d ", arr[i]);

		fclose(file);
	}
}
