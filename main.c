#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define TEST(__name)\
	clock_t t = 0;\
	fprintf(stdout, "%s", "\n> " #__name "\n");\
	TEST_CASE(Random, __name(array, ARRAY_SIZE))\
	TEST_CASE(Asc, __name(array, ARRAY_SIZE))\
	TEST_CASE(Desc, __name(array, ARRAY_SIZE))\
	TEST_CASE(Tricky, __name(array, ARRAY_SIZE))

#ifdef DBG
#	define ARRAY_SIZE 16 // 2^4
#	define TEST_CASE(__type, __expr)\
		CopyArray ## __type(array, sampleArray, ARRAY_SIZE);\
		t = GetTime();\
		__expr;\
		fprintf(stdout, " %*s | %.5fs | ", 6, #__type, GetElapsedSeconds(t));\
		PrintArray(array, ARRAY_SIZE);
#else
#	define ARRAY_SIZE 16384 // 2^14
#	define TEST_CASE(__type, __expr)\
		CopyArray ## __type(array, sampleArray, ARRAY_SIZE);\
		t = GetTime();\
		__expr;\
		fprintf(stdout, " %*s | %.5fs\n", 6, #__type, GetElapsedSeconds(t));
#endif

void PrintArray(int const* array, size_t size)
{
	for (size_t i = 0; i < size; ++i)
	{
		fprintf(stdout, "%i ", array[i]);
	}
	
	putc('\n', stdout);
}

void RandFill(int* array, size_t size)
{
	srand(time(NULL));
	
	for (size_t i = 0; i < size; ++i)
	{
		array[i] = rand() % 100;
	}
}

clock_t GetTime()
{
	return clock();
}

double GetElapsedSeconds(clock_t t)
{
	return (double)(GetTime() - t) / CLOCKS_PER_SEC;
}

int Less(void const* lhs, void const* rhs)
{
    int const a = *(int const*)lhs;
    int const b = *(int const*)rhs;
	
    if (a < b)
		return -1;
    else if(a > b)
		return 1;
    else
		return 0;
}

int Greater(void const* lhs, void const* rhs)
{
    int const a = *(int const*)lhs;
    int const b = *(int const*)rhs;
	
    if (a < b)
		return 1;
    else if(a > b)
		return -1;
    else
		return 0;
}

void Swap(int* lhs, int* rhs)
{
	int const tmp = *lhs;
	*lhs = *rhs;
	*rhs = tmp;
}

void CopyArrayRandom(int* dst, int const* src, size_t size)
{
	while (size--) dst[size] = src[size];
}

void CopyArrayAsc(int* dst, int const* src, size_t size)
{
	CopyArrayRandom(dst, src, size);
	
	qsort(dst, size, sizeof(int), &Less);
}

void CopyArrayDesc(int* dst, int const* src, size_t size)
{
	CopyArrayRandom(dst, src, size);
	
	qsort(dst, size, sizeof(int), &Greater);
}

void CopyArrayTricky(int* dst, int const* src, size_t size)
{
	CopyArrayAsc(dst, src, size);
	
	if (size > 0)
	{
		Swap(dst + 0, dst + size - 1);
	}
}

void QuickSortImpl(int* array, int first, int last)
{
	if (first < last)
	{
		int const back = array[last];
		int curr = first - 1;
		
		for (int i = first; i < last; ++i)
		{
			if (array[i] > back) continue;
			
			++curr;
			Swap(array + curr, array + i);
		}
		
		++curr;
		Swap(array + curr, array + last);
		
		QuickSortImpl(array, first, curr - 1);
		QuickSortImpl(array, curr + 1, last);
	}
}

void QuickSort(int* array, int size)
{
	QuickSortImpl(array, 0, size - 1);
}

void MaxHeapify(int* array, int heapSize, int index)
{
	int const left  = (index * 2) + 1;
	int const right = (index * 2) + 2;
	int curr  = -1;
	
	if (left <= heapSize && array[left] > array[index])
	{
		curr = left;
	}
	else
	{
		curr = index;
	}
	
	if (right <= heapSize && array[right] > array[curr])
	{
		curr = right;
	}
	
	if (curr != index)
	{
		Swap(array + curr, array + index);
		
		MaxHeapify(array, heapSize, curr);
	}
}

void BuildMaxHeap(int* array, int size)
{
	int const heapSize = size - 1;
	int index = size / 2;
	
	while (index--)
	{
		MaxHeapify(array, heapSize, index);
	}
}

void HeapSort(int* array, int size)
{
	BuildMaxHeap(array, size);
	
	for (int i = size - 1; i >= 1; --i)
	{
		Swap(array + i, array + 0);
		
		BuildMaxHeap(array, i);	
	}
}

void BubbleSort(int* array, int size)
{
	int changed;
	
	while (size--)
	{
		changed = 0;
		
		for (int i = 0; i < size; ++i)
		{
			if (array[i] > array[i + 1])
			{
				Swap(array + i, array + i + 1);
				
				changed = 1;
			}
		}
		
		if (changed == 0) break;
	};
}

int main(void)
{
	int* sampleArray = malloc(sizeof(int) * ARRAY_SIZE);
	int* array       = malloc(sizeof(int) * ARRAY_SIZE);
	
	RandFill(sampleArray, ARRAY_SIZE);
	
	{ TEST(QuickSort) }
	
	{ TEST(HeapSort) }
	
	{ TEST(BubbleSort) }
	
	
	free(sampleArray);
	free(array);
	
	return 0;
}