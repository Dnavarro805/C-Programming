// Daniel Navarro
// COMP222 - Computer Architecture & Assembly - Fall 2018
// Programming Assingment: Cache Simulation

// Objective:
// To write a C program that simulates reading and writing to a custom-sized direct-mapped cache, 
// involving a custom-sized main memory.


#include <stdio.h>
#include <stdlib.h>


int numLines, blockSize, cacheSize, mainMemorySize;

// Define main memory as dynamic array of words (int)
int *mainMemory = NULL;

// Define cache as dynamic array of lines (nodes)
struct node 
{
	int tag;      // determined by location of main memory block
	int *block;  // points to a dynamically allocated line-block

} *cache = NULL;

typedef struct node n; // define line as a type of node

void enterParameters() 
{
	int i; 

	// Init globals to zero
	mainMemorySize = 0;
	cacheSize = 0;

	printf("\nEnter main memory size (words): ");
	scanf("%d", &mainMemorySize);

	printf("Enter cache size (words): ");
	scanf("%d", &cacheSize);

	printf("Enter block size (words/blocks): ");
	scanf("%d", &blockSize);
	printf("\n\n");

	// Allocate space for main memory and initialize
	mainMemory = (int*)malloc(mainMemorySize * sizeof(int));

	// Fill main memory with reverse order of natural numbers
	for (i = 0; i < mainMemorySize; i++) 
	{
		mainMemory[i] = mainMemorySize - 1;  
	}

	// Allocate space for cache and initialize
	numLines = cacheSize / blockSize;
	cache = (n*)malloc(numLines * sizeof(n));

	// Initializa cache lines to invalid values
	for (i = 0; i < cacheSize; i++)
	{
		cache[i].block = NULL;
		cache[i].tag = -1;
	}
	return;
}


void accessReadCache()
{
	int mmAddress, writeValue, word, base, set, tag, block;
	writeValue = 0;

	printf("\nEnter main memory address to read from: ");
	scanf("%d", &mmAddress);

	/*calculate tag, line of cache, and word associated w/ MM address*/
	tag = mmAddress / cacheSize;

	block = 1;

	set = (mmAddress % cacheSize) / blockSize;

	word = mmAddress % blockSize;

	base = (mmAddress / blockSize) * blockSize;

	//CASE 1: MISS DUE TO UNALLOCATED BLOCK
	if (cache[block].block == NULL)
	{
		cache[block].block = (int*)malloc(blockSize * sizeof(int));
	}

	//CASE 2: MISS DUE TO NON MATCHING TAGS
	if (cache[block].tag != tag)
	{
		cache[block].tag = tag;

		//replace block in the cache
		int i;

		for (i = 0; i < blockSize; i++)
		{
			cache[block].block[i] = mainMemory[base + 1];
		}
		
		printf("\nRead Miss - First load block from memory \n");
		printf("Word %d of cache line %d with tag %d contains the value %d \n\n\n", word, block, tag, writeValue);
		return;
	}

	//CASE 3: HIT IN THE CACHE, TAGS MATCH
	else if (cache[block].tag == tag)
	{
		printf("\nCache Hit \n");
		writeValue = cache[block].block[word];
	}
	printf("Word %d of cache line %d with tag %d contains the value %d \n\n\n", word, tag, tag, writeValue);
}


void accessWriteCache()
{
	int mmAddress, writeValue, word, base, set, tag, block;

	printf("\nEnter main memory address to write to: ");
	scanf("%d", &mmAddress);

	printf("Enter value to write: ");
	scanf("%d", &writeValue);
	
	/*calculate tag, line of cache, and word associated w/ MM address*/
	tag = mmAddress / cacheSize;

	block = 1;

	set = (mmAddress % cacheSize) / blockSize;

	word = mmAddress % blockSize;

	base = (mmAddress / blockSize) * blockSize;

	/*3 cases for hit/miss*/

	//CASE 1: MISS DUE TO UNALLOCATED BLOCK
	if (cache[block].block == NULL)
	{
		cache[block].block = (int*)malloc(blockSize * sizeof(int));
	}

	//CASE 2: MISS DUE TO NON MATCHING TAGS
	if (cache[block].tag != tag)
	{
		cache[block].tag = tag;

		//replace block in the cache
		int i;

		for (i = 0; i < blockSize; i++)
		{
			cache[block].block[i] = mainMemory[base + 1];
		}
		printf("\n\nWrite Miss - First load block from memory \n");
		mainMemory[mmAddress] = writeValue;
	}

	//CASE 3: HIT IN THE CACHE, TAGS MATCH
	else if (cache[block].tag == tag)
	{
		printf("Cache Hit! \n");
		cache[block].block[word] = writeValue;
		mainMemory[mmAddress] = writeValue;
	}
	printf("Word %d of cache line %d with tag %d contains the value %d \n\n\n", word, tag, tag, writeValue);
}

void freeMemory()
{
	int i;

	for (i = 0; i < numLines; i++)
	{
		if (cache[i].block != NULL) 
		{
			free(cache[i].block);
		}
		if (cache != NULL) 
		{
			free(cache);
		}
	}
	printf("Memory Freed up");
}

void isPowerOfTwo()
{
	if (((cacheSize % 2) == 0) && cacheSize > 1)
	cacheSize = cacheSize;
	else
		printf("Error - Cache Size is not a power of 2! \n\n");
}

int main()
{
	int selection;

	printf("Program Written by Daniel Navarro \n");
	printf("Program  Assingment: Cache Simulation \n");
	printf("Comp222 - Fall 2018 \n\n\n");

	while (1)
	{
		printf("Daniel Navarro \n\n");
		printf("Main Memory to Cache Memory Mapping: \n");
		printf("------------------------------------\n");
		printf("1) Enter Configuration Parameters \n");
		printf("2) Read from Cache \n");
		printf("3) Write to Cache \n");
		printf("4) Quit Program \n\n");
		
		printf("Enter Selection: ");
		scanf("%d", &selection);

		switch (selection) 
		{
		case 1:
			enterParameters();
			isPowerOfTwo();
			break;

		case 2:
			accessReadCache();
			break;

		case 3:
			accessWriteCache();
			break;

		case 4:
			freeMemory();
			exit(0);
			break;

		default:
			printf("\n\n\nYou Have Entered a Invalid Choice! \n\n\n");
			break;

		}
	}
	return 0;
}