/*	Radix Sort
 *	Created by Doug Wagner
 */

#include<iostream>
#include<cstdlib>
#include<ctime>
#include<queue>
#include<Windows.h>

#define ARRSIZE 10000	// Array size constant. Determines size of randomly generated array of integers.
#define NUMTESTS 1000	// Number of times for the algorithm to run in the test function.
#define MAXRAND 10000	// Maximum integer value for random number generator.

void radix(int*, int);
int findMax(int*, int);
void printarray(int*, int);
void runtest();
LARGE_INTEGER radixtest();

int main()
{
	srand(time(NULL));
	runtest();
	system("pause");
}

void runtest()
{
	/* INITIALIZE ARRAY OF RESULTS FROM TIMER */
	LARGE_INTEGER *values = new LARGE_INTEGER[NUMTESTS];
	int percent = 0, prevpercent = -1;
	for (int i = 0; i < NUMTESTS; i++)
	{
		percent = (int)(((float)i / (float)NUMTESTS) * 100);
		if (percent != prevpercent)
		{
			CONSOLE_SCREEN_BUFFER_INFO csbi;
			GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
			COORD pos = { 0, csbi.dwCursorPosition.Y };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			std::cout << percent << "%";
		}
		values[i] = radixtest();	// test results stored here
		prevpercent = percent;
	}
	
	/* CALCULATE MINIMUM, MAXIMUM, TOTAL, AND AVERAGE TIMES */
	LARGE_INTEGER min, max, total, average;
	total.QuadPart = 0;
	max.QuadPart = 0;
	min.QuadPart = 9223372036854775807;
	for (int i = 0; i < NUMTESTS; i++)
	{
		total.QuadPart += values[i].QuadPart;
		if (max.QuadPart < values[i].QuadPart)
			max.QuadPart = values[i].QuadPart;
		if (min.QuadPart > values[i].QuadPart)
			min.QuadPart = values[i].QuadPart;
	}
	average.QuadPart = total.QuadPart / NUMTESTS;

	/* DISPLAY RESULTS */
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	COORD pos = { 0, csbi.dwCursorPosition.Y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	std::cout << "Radix Sort ran " << NUMTESTS << " times." << std::endl;
	std::cout << "Array Size: " << ARRSIZE << " elements." << std::endl;
	std::cout << "Maximum integer size: " << MAXRAND << std::endl;
	std::cout << "Shortest runtime: " << min.QuadPart << " microseconds." << std::endl;
	std::cout << "Longest runtime: " << max.QuadPart << " microseconds." << std::endl;
	std::cout << "Average runtime: " << average.QuadPart << " microseconds." << std::endl;
	delete values;
}

LARGE_INTEGER radixtest()
{
	/* INITIALIZE ARRAY OF RANDOM INTEGERS */
	int *nums;
	nums = new int[ARRSIZE];
	for (int i = 0; i < ARRSIZE; i++)
	{
		nums[i] = rand() % MAXRAND;
	}
//	printarray(nums, ARRSIZE);

	/* TIMER */
	LARGE_INTEGER starttime, endtime, elapsed;
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
//	std::cout << "BEGIN TEST" << std::endl;
	QueryPerformanceCounter(&starttime);
	radix(nums, ARRSIZE);
	QueryPerformanceCounter(&endtime);
//	std::cout << "END TEST" << std::endl;

	/* RESULTS */
	elapsed.QuadPart = endtime.QuadPart - starttime.QuadPart;
	elapsed.QuadPart *= 1000000;
	elapsed.QuadPart /= frequency.QuadPart;
//	printarray(nums, ARRSIZE);
//	std::cout << elapsed.QuadPart << " microseconds" << std::endl;
	delete nums;
	return elapsed;
}

void radix(int *arr, int size)
{
	int max = findMax(arr, size);
	std::queue<int> bucket[10];
	for (int n = 1; n <= max; n *= 10)
	{
		for (int i = 0; i < size; i++)
			bucket[(arr[i] / n) % 10].push(arr[i]);
		int k = 0;
		for (int j = 0; j < 10; j++)
		{
			while (!bucket[j].empty())
			{
				arr[k++] = bucket[j].front();
				bucket[j].pop();
			}
		}
	}
}

int findMax(int *arr, int size)
{
	int max = arr[0];
	for (int i = 1; i < size; i++)
		max = (arr[i] > max) ? arr[i] : max;
	return max;
}

void printarray(int *arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << arr[i] << ", ";
	}
	std::cout << std::endl;
}
