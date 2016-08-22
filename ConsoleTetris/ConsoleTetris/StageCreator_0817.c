// (IS_NOT)STANDALONE
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <conio.h>

typedef int BOOL;
#ifndef TRUE
#define TRUE	1	
#endif
#ifndef FALSE
#define FALSE	0
#endif
#ifndef NULL
#define NULL	((void*)0)
#endif

#pragma warning(disable:4996)

typedef struct tagStageDataHead{
	int iIndex;
	int iLength;
}StageDataHead, *pStageDataHead;

void main(){
	int i = 0;

	StageDataHead data, read;
	FILE* fp = NULL;
	
	char* cpBlockType = NULL;	// added 08-22
	char* cpBlockRead = NULL;	// added 08-22

	int in_iIndex = 0,
		in_iLength = 0;

	char keyBuffer = 0;

	int quit_index = 0,
		quit_length = 0,
		quit_block_type = 0;

	// Step 0 -- Init
	memset(&data, 0, sizeof(StageDataHead));
	memset(&read, 0, sizeof(StageDataHead));

	printf("\r\n\r\n\tTetris StageCreator.. - 2016.0817\r\n");
	printf("\tData file will be named and saved in TestStage.dat on <this>folder\r\n");
	
	// Step 1 -- Set INDEX
	while (!quit_index)
	{
		printf("\r\nSTEP1-1 > Setting [INDEX NUMBER] -- (integer) : "); scanf("%i", &in_iIndex);

		printf("STEP1-2 > Intended [INDEX NUMBER] is [  %i  ], correct? (y or Y to break)\r\n", in_iIndex);
		fflush(stdin);
		keyBuffer = _getch();

		if (keyBuffer == 'y' || keyBuffer == 'Y')
		{
			data.iIndex = in_iIndex;
			printf("STEP1-3 > Set [INDEX NUMBER] to [  %i  ] (done)\r\n", data.iIndex);
			keyBuffer = 0;
			break;
		}
		else
		{
			printf("\tSYS: CANCELED.\r\n");
			continue;
		}
	}

	// Step 2 -- Set LENGTH
	while (!quit_length)
	{
		printf("\r\nSTEP2-1 > Setting [STAGE LENGTH] -- (integer)\r\n"); 
		printf("\tNOTE: [STAGE LENGTH] should be in range 1 to 10000\t : "); scanf("%i", &in_iLength);

		if (in_iLength == 0)
		{
			printf("\tSYS: ERROR! [STAAGE LENGTH] cannot be set to 0\r\n");
			continue;
		}
		else if (in_iLength > 0 && in_iLength <= 10000)
		{
			printf("STEP2-2 > Intended [STAGE LENGTH] is [  %i  ], correct? (y/Y to break)\r\n", in_iLength);
			fflush(stdin);
			keyBuffer = _getch();

			if (keyBuffer == 'y' || keyBuffer == 'Y'){
				data.iLength = in_iLength;
				printf("STEP2-3 > Set [STAGE LENGTH] to [  %i  ] (done)\r\n", data.iLength);
				keyBuffer = 0;
				break;
			}
			else{
				printf("\tSYS: CANCELED.\r\n");
				continue;
			}
		}
		else
			printf("\tSYS: ERROR! [STAGE LENGTH] is not in the range.\r\n");
	}
	
	// -- TEST -- temporarily Setting variables for testing <Step 4>
	/*data.iIndex = 505;
	data.iLength = 5;
	printf("data.iIndex  : %i\r\n", data.iIndex);
	printf("data.iLength : %i\r\n", data.iLength);*/

	// Step 3 -- Allocating memory on [data.cpBlockType]
	cpBlockType = (char*)malloc(sizeof(char) * (data.iLength +1));			// 2--malloc
	printf("\r\nSTEP3-1 > Allocating memory on [data.cpBlockType]\r\n");
	memset(cpBlockType, 0, sizeof(char) * (data.iLength +1));				// note: +1 for null-ended string.
	printf("STEP3-2 > Set(Initialzation) all [data.cpBlockType] to 0\r\n");
	cpBlockType[data.iLength] = '\0';
	printf("STEP3-3 > Put <EOS-character> on the end\r\n\r\n");

	// Step 4 -- Set Block-sequence.
	for (i = 0; i < data.iLength; ++i)
	{
		printf("STEP4-%i > Setting [  %i  ]st/nd/th Block.\r\n", i, i);
		printf("\tNOTE: [%i]Block should be in range 'a/A' to 'g/G'\r\n");
		while (!quit_block_type){
			fflush(stdin);
			printf("\t[  %i  ]BLOCK : ", i);	scanf("%c", &keyBuffer);

			if (keyBuffer == 'a' || keyBuffer == 'A')
			{
				cpBlockType[i] = 'a';
				keyBuffer = 0;
				quit_block_type = 1;
			}
			else if (keyBuffer == 'b' || keyBuffer == 'B')
			{
				cpBlockType[i] = 'b';
				keyBuffer = 0;
				quit_block_type = 1;
			}
			else if (keyBuffer == 'c' || keyBuffer == 'C')
			{
				cpBlockType[i] = 'c';
				keyBuffer = 0;;
				quit_block_type = 1;
			}
			else if (keyBuffer == 'd' || keyBuffer == 'D')
			{
				cpBlockType[i] = 'd';
				keyBuffer = 0;
				quit_block_type = 1;
			}
			else if (keyBuffer == 'e' || keyBuffer == 'E')
			{
				cpBlockType[i] = 'e';
				keyBuffer = 0;
				quit_block_type = 1;
			}
			else if (keyBuffer == 'f' || keyBuffer == 'F')
			{
				cpBlockType[i] = 'f';
				keyBuffer = 0;
				quit_block_type = 1;
			}
			else if (keyBuffer == 'g' || keyBuffer == 'G')
			{
				cpBlockType[i] = 'g';
				keyBuffer = 0;
				quit_block_type = 1;
			}
			else
			{
				printf("\tSYS> ERROR! Put Appropriate one.\r\n");
				keyBuffer = 0;
				quit_block_type = 0;
			}
		}

		printf("\tSYS: [%i]Block to [   %c   ]\r\n", i, cpBlockType[i]);
		quit_block_type = 0;
	}

	// Step 5 -- writing data(in bin) on file.
	fflush(stdin);
	fp = fopen("TestStage.dat", "wb");	// 1--opening file
	printf("\r\nSTEP5-1 > opening the file in 'write-only' mode.\r\n");
	fwrite(&data, sizeof(int) * 2, 1, fp);	// note: first two member of StageData are int-type. 
	printf("STEP5-2 > writing [INDEX] and [LENGTH] on the file.\r\n");
	fputs(cpBlockType, fp);
	printf("STEP5-3 > writing [BLOCK]s on the file.\r\n");
	fclose(fp);							// 1--closing file
	printf("STEP5-4 > closing the file.\r\n");
	free(cpBlockType);													// 2--free
	printf("STEP5-5 > Freeing memory which was allocated.\r\n");

	// Step 6 -- waiting for signal.
	printf("\r\nSTEP6 > \t Press any key to process.\r\n");
	_getch();

	//
	// --
	system("cls");
	// --
	//

	// Reading Step 1 -- reading file and copying it. (loading?)
	fp = fopen("TestStage.dat", "rb");					// 3--opening file

	fread(&(read.iIndex), sizeof(int), 1, fp);
	printf("READING STEP 1-1 > Reading [INDEX]\r\n");
	// do something.
	// do something.
	printf("READING STEP 1-2 > Checking redundancy .. ");
	if (1)
		printf("[ OKAY ]\r\n");
	// do something.
	// do something.

	// Reading Step 2 -- getting the length and allocating memory base on information.
	fread(&(read.iLength), sizeof(int), 1, fp);
	printf("\r\nREADING STEP 2-1 > Reading [INDEX]\r\n");
	cpBlockRead = (char*)malloc(sizeof(char)*(read.iLength + 1));		// 4--malloc
	printf("READING STEP 2-2 > Allocating memory on [read.cpBlockType], LENGTH : %i\r\n", read.iLength);
	memset(cpBlockRead, 0, sizeof(char)*(read.iLength + 1));
	printf("READING STEP 2-3 > Init allocated memory.\r\n");

	// Reading Step 3 -- getting BlockType(s).
	fgets(cpBlockRead, (read.iLength + 1), fp);	// note: +1 for EOS(EOF)
	printf("\r\nREADING STEP 3-1 > Getting Data of BlockType(s).\r\n");
	fclose(fp);											// 3--closing file
	printf("READING STEP 3-2 > Closing the file.\r\n");
	

	// Reading Step 4 -- waiting for signal.
	printf("\r\nREADING STEP 4 > \t Press any key to see the result.\r\n");
	_getch();

	//
	// --
	system("cls");
	// --
	//

	printf("SYS: Showing Results ...\r\n");
	printf("\tINDEX: %i\r\n", read.iIndex);
	printf("\tLENGTH: %i\r\n", read.iLength);
	for (i = 0; i < read.iLength; ++i)
	{
		if (cpBlockRead[i])
			printf("[%i] : %c\r\n", i, cpBlockRead[i]);
	}
	free(cpBlockRead);
	//free(read.cpBlockType);												// 4--free
	printf("SYS: Freeing memory which was allocated.\r\n");
}