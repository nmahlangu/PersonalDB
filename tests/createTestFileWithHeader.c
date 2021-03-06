/*
 *  Just a script that creates a file with the new header format I'm using.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define UNSORTED 1
#define SORTED 2
#define BTREE 3

int main(int argc, char** argv)
{
	// error checking
	// fileSize MUST be a multiple of 4
	if (argc != 3)
	{
		printf("Usage: ./createTestFileWithHeader storageType fileSize\n");
		return 1;
	}
	assert((atoi(argv[1]) == 1) || (atoi(argv[1]) == 2) || (atoi(argv[1]) == 3));
	int storageType = atoi(argv[1]);
	int fileSize = atoi(argv[2]);
	
	// create the file
	FILE* fp = fopen("testFileWithHeader", "wb+");
	
	// write the header
	int zero = 0;
	fwrite(&storageType, sizeof(int), 1, fp);
	fwrite(&zero, sizeof(int), 1, fp);

	// write appropriate number of ints to the file
	srand(time(NULL));
	int i;
	for (i = 0; i < (fileSize / 4); i++)
	{
		int temp = rand() % 10000;
		fwrite(&temp, sizeof(int), 1, fp);
	}

	// update the header information
	printf("Wrote %d integers to the file (%d bytes)\n", i, i * 4);
	fseek(fp, sizeof(int), SEEK_SET);
	int fileSizeActual = i * sizeof(int);
	fwrite(&fileSizeActual, sizeof(int), 1, fp);
}
