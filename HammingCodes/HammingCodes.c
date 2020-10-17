// Daniel Navarro
// COMP222 - Computer Architecture & Assembly - Fall 2018
// Programming Assingment: Error Detection & Correction
// Department of Computer Science CSUN

// Objective:
// To write a program which checks a Hamming Code for a single-bit error,
// and to report and correct the error (if any).


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>


int maxLengthHamCode;
int parity;
int binary;
char *hamCode = NULL;


void enterParameters(FILE *fp) 
{
	printf("\n\nEnter the maximum length: ");
	fscanf(fp,"%d", &maxLengthHamCode);

	printf("\n\nEnter the parity ( 0 = even, 1 = odd): ");
	fscanf(fp,"%d", &parity);

	/* allocate memory for hamming string based on maximum length and size of a character element */
	hamCode = (char *)malloc(sizeof(char)*maxLengthHamCode);
}

void checkHammingCode(FILE * fp)
{
	int hamLength;
	int error = 0;
	int pBit;

	/* prompt for hamming code as a "string" */
	printf("\n\nEnter the Hamming code: ");
	fscanf(fp,"%s", hamCode);    
	hamLength = strlen(hamCode);

	if (hamLength > maxLengthHamCode) 
	{
		printf("\n\n*** Incorrect Hamming Code: %s", hamCode);
		printf( "\n*** Invalid Entry - Exceeds Maximum Code Length of %d", maxLengthHamCode);
	}
	else
	{
		/* Checking Hamming code for errors */
		int a, b, c, count = 0;
		/* Check for each parity bit */
		for (a = 1; a < hamLength; a = a * 2) 
		{
			pBit = parity;
			for (b = a; b <= hamLength; b = c + a) 
			{
				for (c = b; count != a && c <= hamLength; c++)
				{
					pBit = pBit ^ (hamCode[hamLength - c] - '0');
					count++;
				} 
				count = 0;
			} 
			error += (pBit * a);
		} 

		if (error == 0)
		{
			printf("\n\n*** Hamming Code Correct.");
			printf("\n*** Correct Hamming Code: %s\n", hamCode); 
		}
		else
		{
			printf("\n\n*** Incorrect Hamming Code: %s", hamCode);
			printf("\n*** Error in bit: %d", error);

			hamCode[hamLength - error] = (hamCode[hamLength - error] == '0' ? '1' : '0');
			printf("\n*** Correct Hamming code is: %s\n", hamCode);
		}
	}
}

int main(int argc, char * argv[])
{
	//char * fn = "hc_data_2018.txt";
	FILE *fp = fopen(argv[1],"r");
	
	if (!fp)
	{
		printf("Error - File not found!", argv[1]);
	}

	int selection;
	
	printf("\n\nDaniel Navarro\n");
	printf("Hamming Codes\n");
	printf("Comp 222 - Fall 2018\n");

	while (1)
	{
		printf("\n\nDaniel Navarro\n");
		printf("---------------------\n");
		printf("1) Enter Parameters\n");
		printf("2) Check Hamming Code\n");
		printf("3) Quit\n");

		printf("\n\nEnter Selection: ");
		fscanf(fp, "%d", &selection);

		switch (selection)
		{
		case 1:
			enterParameters(fp);
			break;

		case 2:
			checkHammingCode(fp);
			break;

		case 3:
			free(hamCode); // Free Up Memory
			exit(0);
			return 0;

		default:
			printf("\n\n\nYou Have Entered a Invalid Choice!\n\n\n");
		}
	} 
	fclose(fp);
	return 0;
} 