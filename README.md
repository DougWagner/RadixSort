# RadixSort
Radix sort algorithm.

This is a benchmark of the radix sort algorithm in C++ for sorting an array of integers. Time complexity of radix sort: O(kn) where k is the number of digits of the largest number in the array.

The time benchmark is done with the Windows API, and computes the time in microseconds. 
The constant ARRSIZE determines the number of elements of randomly generated integers in the array that is sorted with radix sort. The constant NUMTESTS determines the number of times the program runs the radix sort algorithm on new arrays of randomly generated integers. The constant MAXRAND determines the maximum integer value for the random number generator to create; the actual value of the maximum value will be MAXRAND - 1.

This program was compiled and tested on MSVC 2013.
