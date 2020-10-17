// Daniel Navarro
// COMP222 - Computer Architecture & Assembly - Fall 2018
// Department of Computer Science CSUN
// Programming Assingment: Virtual Memory 

// Objective:
// To translate a virtual address to a physical address, 
// involving a custom-sized fully associative page table. 


#include <stdio.h>
#include <stdlib.h>


int sizeOfMainMemory;
int sizeOfPage;
int replacementPolicy;
int numPages;
int selection;

struct pageTable
{
	int pageFrame;
	int virtualPage;
} *memory;

void enterParameters(FILE *fp)
{
	//printf("\n\nEnter main memory size (words):");
	fscanf(fp, "%d", &sizeOfMainMemory);

	//printf("\nEnter page size (words/page):");
	fscanf(fp, "%d", &sizeOfPage);

	//printf("\nEnter replacement policy (0=LRU, 1=FIFO): ");
	fscanf(fp, "%d", &replacementPolicy);

	numPages = sizeOfMainMemory / sizeOfPage;

	memory = (struct pageTable *)malloc(numPages * sizeof(struct pageTable));

	int i;
	for (i = 0; i < numPages; i++)
	{
		//Flag each member of structure's index as -1
		memory[i].pageFrame = -1;
		memory[i].virtualPage = -1;
	}
}

void mapVA(FILE *fp)
{
	int VMAddress;
	int realAddress;
	int virtualPage;
	int offset;

	//printf("\n\nEnter virtual memory address to access: ");
	fscanf(fp, "%d", &VMAddress);

	//Calculate offset and virtual page
	offset = VMAddress % sizeOfPage;
	virtualPage = VMAddress / sizeOfPage;

	int i;
	for (i = 0; i < numPages; i++)
	{
		//if there is a hit (page in memory)
		if (memory[i].virtualPage == virtualPage)
		{
			realAddress = (memory[i].pageFrame * sizeOfPage) + offset;
			//LRU Replacement Policy
			if (replacementPolicy == 0)
			{
				int pfHolder;//placeholder for pageframe
				int vpHolder;//placeholder for virtualpage
				
				int g;
				for (g = i; g < numPages - 1; g++)
				{
					//Shift page table at index of hit
					pfHolder = memory[g].pageFrame;
					vpHolder = memory[g].virtualPage;
					memory[g] = memory[g + 1];
					memory[g + 1].pageFrame = pfHolder;
					memory[g + 1].virtualPage = vpHolder;
				}
			}
			printf("\n\n*** Virtual Address %d maps to physical address %d", VMAddress, realAddress);
			i = numPages - 1;
		}
		//if theres a blank space
		else if (memory[i].virtualPage == -1)
		{
			//map virtual page to generated virtual page
			memory[i].virtualPage = virtualPage; 
			//map pageframe to current index
			memory[i].pageFrame = i;
			printf("\n\n*** Page fault! ");
			//set index to last element
			realAddress = (memory[i].pageFrame * sizeOfPage) + offset;
			printf("\n*** Virtual Address %d maps to physical address %d", VMAddress, realAddress);
			i = numPages - 1;
		}
		else if (i == numPages - 1)
		{
			//condition for last element
			memory[0].virtualPage = virtualPage;
			int pfHolder;//placeholder for pageframe
			int vpHolder;//placeholder for virtualpage
			int h;
			for (h = 0; h < numPages - 1; h++)
			{
				//shift page table from beginning
				pfHolder = memory[h].pageFrame;
				vpHolder = memory[h].virtualPage;
				memory[h] = memory[h + 1];
				memory[h + 1].pageFrame = pfHolder;
				memory[h + 1].virtualPage = vpHolder;
			}
			printf("\n\n*** Page Fault! ");
			realAddress = (memory[h].pageFrame * sizeOfPage) + offset;
			printf("\n*** Virtual Address %d maps to physical address %d", VMAddress, realAddress);
		}
	}

	for (i = 0; i < numPages; i++)
	{
		if (memory[i].pageFrame != -1 && memory[i].virtualPage != -1)
		{
			printf("\n*** VP %d -->", memory[i].virtualPage);
			printf(" PF %d", memory[i].pageFrame);
		}
	}
}


int main(int argc, char * argv[]) 
{
	FILE *fp = fopen(argv[1], "r");
	
	if (!fp)
	{
		printf("*** Error - File not found!", argv[1]);
	}

	printf("\n\nDaniel Navarro\n");
	printf("Assingment - Virtual Address Mapping\n");
	printf("Comp 222 - Fall 2018\n");

	while (1)
	{
		fscanf(fp, "%d", &selection);

		switch (selection)
		{
		case 1:
			enterParameters(fp);
			break;

		case 2:
			mapVA(fp);
			break;

		case 3:
			return 0;

		default:
			printf("\n\n\nYou Have Entered a Invalid Choice!\n\n\n");
		}
	}
	fclose(fp);
}