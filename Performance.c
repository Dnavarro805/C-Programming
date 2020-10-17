// Daniel Navarro
// COMP222 - Computer Architecture & Assembly
// Department of Computer Science
// Fall 2018

// Objective:
// To write a C program that calculates the average CPI, total processing time(T),
// and MIPS of a sequence of instructions, given the number of instruction classes, 
// the CPI and total count of each instruction type, and the clock rate (frequency) of the machine. 


#include <stdlib.h>
#include <stdio.h>
#include <math.h> 


int numOfInsType, *totalInsCountOfEachInst; 
float *cpiOfEachInst, clockRate;


float averageCPI()
{
	float cycles, avgCPI;
	cycles = 0;

	int insType, instCount;
	instCount = 0;

	for (insType = 0; insType < numOfInsType; insType++)
	{
		cycles = cycles + cpiOfEachInst[insType] * (float)totalInsCountOfEachInst[insType];
		instCount = instCount + totalInsCountOfEachInst[insType];
	}
	avgCPI = cycles / instCount;
	return avgCPI;
}

float time()
{
	float timeInMS;
	int insType, totalInstCount;
	totalInstCount = 0;

	for (insType = 0; insType < numOfInsType; insType++)
	{
		totalInstCount = totalInstCount + totalInsCountOfEachInst[insType];
	}
	timeInMS = (totalInstCount * averageCPI() * (1 / clockRate)) * pow(10, 3);
	return timeInMS;
}

float MIPS()
{
	float mips;
	mips = (clockRate * pow(10, 6)) / (averageCPI() * pow(10, 6));
	return mips;
}

void parameters() 
{
	int insType;

	printf("\n\nEnter the number of instruction classes: ");
	scanf("%d", &numOfInsType);
	printf("\n\nEnter the frequency of the machine (MHz): ");
	scanf("%f", &clockRate);

	cpiOfEachInst = (float*)
		malloc(numOfInsType * sizeof(float));   
	totalInsCountOfEachInst = (int*)
		malloc(numOfInsType * sizeof(float));

	for (insType = 0; insType < numOfInsType; insType++)
	{
		printf("\n\nEnter CPI of class ");
		printf("%d: ", insType + 1);
		scanf("%f", &cpiOfEachInst[insType]);

		printf("\nEnter instruction count of class ");
		printf("%d (millions): ", insType + 1);
		scanf("%d", &totalInsCountOfEachInst[insType]);
		printf("\n\n");
	}
}

void instructionDistribution()
{
	int insType;
	
	printf("\n\n\n\nFREQUENCY (MHz): %d\n\n\n\n", (int)clockRate);
	printf("INSTRUCION DISTRIBUTION\n\n\n\n");
	printf("CLASS  CPI  COUNT");
	for (insType = 0; insType < numOfInsType; insType++)
	{
		printf("\n\n%d     %d     %d", (insType + 1), (int)cpiOfEachInst[insType], totalInsCountOfEachInst[insType]);
	}
}

void performanceValues() 
{
	printf("\n\n\n\nPerformance Values ");
	printf("\n\n\n\nAverage CPI %.2f ", averageCPI());
	printf("\n\nTime (ms) %.2f ", time());
	printf("\n\nMIPS       %.2f \n\n\n\n", MIPS());
}

int main()
{
	int selection;

	while (1)
	{
		printf("\n\nDaniel Navarro\n\n");
		printf("Performance Assesment:\n\n\n\n");

		printf("1) Enter Parameters\n\n");
		printf("2) Print Results\n\n");
		printf("3) Quit\n\n\n\n");

		printf("Enter Selection: ");
		scanf("%d", &selection);

		switch (selection)
		{
		case 1: 
			parameters();
			break;

		case 2: 
			instructionDistribution();
			performanceValues();
			break;

		case 3: 
			exit(0);

		default: 
			printf("\n\n\n\nYou Have Entered a Invalid Choice!\n\n\n\n");

		}
	}
	return 0;
}