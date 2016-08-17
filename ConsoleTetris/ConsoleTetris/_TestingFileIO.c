#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <conio.h>

#pragma warning(disable:4996)

typedef struct tagStageData{
	int iIndex;
	int iLength;

	char* cpBlockType;
}StageData, *pStageData;

void main()
{
	StageData	test;
	StageData	read;
	
	FILE* fp;
	int i = 0;

	memset(&test, 0, sizeof(StageData));
	test.iIndex = 2070;
	test.iLength = 2590;
	test.cpBlockType = (char*)malloc(sizeof(char) * 5 +1);	// +1 for null-ended string.

	//for (i = 0; i < 5; ++i)
	//	test.cpBlockType[i] = (5 - i);

	//for (i = 0; i < 5; ++i)
	//	printf("%i ", test.cpBlockType[i]);

	test.cpBlockType[0] = 'a';
	test.cpBlockType[1] = 'b';
	test.cpBlockType[2] = 'c';
	test.cpBlockType[3] = 'd';
	test.cpBlockType[4] = 'e';

	// Step 5 -- writing data(in bin) on file.
	fp = fopen("test.dat", "wb");
	fwrite(&test, sizeof(int)*2, 1, fp);
	fputs(test.cpBlockType, fp);
	fclose(fp);

/*
	int temp = 0;
	printf("%i\r\n", temp);
	fread(&temp, sizeof(int), 1, fp);
	printf("%i\r\n", temp);
	fread(&temp, sizeof(int), 1, fp);
	printf("%i\r\n", temp);
*/
	fp = fopen("test.dat", "rb");
	
	// Reading Step 1 -- Checking redundancy.
	fread(&(read.iIndex), sizeof(int), 1, fp);
	printf("Reading <test.dat> ..\r\n");
	printf("\tINDEX: %i\r\n", read.iIndex);
	//
	// do something ...
	//

	// Reading Step 2 -- Getting iLength and Allocating memory based on 'length'.
	fread(&(read.iLength), sizeof(int), 1, fp);
	printf("\tLENGTH: %i\r\n", read.iLength);
	read.cpBlockType = (char*)malloc(sizeof(char)*read.iLength);
	memset(read.cpBlockType, 0, sizeof(char)*read.iLength);

	fgets(read.cpBlockType, 5 +1, fp);	// +1 for null-ended string.
	// Reading Step 3 -- Getting BlockType(s).
	//for (i = 0; i < read.iLength; ++i)
	for (i = 0; i < 5; ++i){
		if (read.cpBlockType[i])
			printf("[%i] : %c\r\n", i, read.cpBlockType[i]);
	}//printf("");

	fclose(fp);
	free(read.cpBlockType);
}

//
//void main(){
//	int i = 0;
//
//	StageData data;
//	//FILE* fp = NULL;
//	
//	int in_iIndex = 0,
//		in_iLength = 0;
//
//	char keyBuffer = 0;
//
//	int quit_index = 0,
//		quit_length = 0;
//	//fopen("TestStage.dat", "wb");	// 1--opening file
//	//fflush(stdin);
//	memset(&data, 0, sizeof(StageData));
//
//	//// Step 1 -- Set INDEX
//	//while (!quit_index){
//	//	printf("STEP1-1 > Inserting [INDEX NUMBER] -- (integer) : "); scanf("%i", &in_iIndex);
//
//	//	printf("STEP1-2 > Intended [INDEX NUMBER] is [  %i  ], correct? (y or Y to break)\r\n", in_iIndex);
//	//	fflush(stdin);
//	//	keyBuffer = _getch();
//
//	//	if (keyBuffer == 'y' || keyBuffer == 'Y'){
//	//		data.iIndex = in_iIndex;
//	//		printf("STEP1-3 > Set [INDEX NUMBER] to [  %i  ] (done)\r\n", data.iIndex);
//	//		keyBuffer = 0;
//	//		break;
//	//	}
//	//	else{
//	//		printf("\tSYS: CANCELED.\r\n");
//	//		continue;
//	//	}
//	//}
//
//	//// Step 2 -- Set Length
//	//while (!quit_length){
//	//	printf("STEP2-1 > Inserting [STAGE LENGTH] -- (integer)\r\n"); 
//	//	printf("\tNOTE: [STAGE LENGTH] should be in range 1 to 10000\t : "); scanf("%i", &in_iLength);
//
//	//	if (in_iLength == 0){
//	//		printf("\tSYS: ERROR! [STAAGE LENGTH] cannot be set to 0\r\n");
//	//		continue;
//	//	}
//	//	else if (in_iLength > 0 && in_iLength <= 10000){
//	//		printf("STEP2-2 > Intended [STAGE LENGTH] is [  %i  ], correct? (y/Y to break)\r\n", in_iLength);
//	//		fflush(stdin);
//	//		keyBuffer = _getch();
//
//	//		if (keyBuffer == 'y' || keyBuffer == 'Y'){
//	//			data.iLength = in_iLength;
//	//			printf("STEP2-3 > Set [STAGE LENGTH] to [  %i  ] (done)\r\n", data.iLength);
//	//			keyBuffer = 0;
//	//			break;
//	//		}
//	//		else{
//	//			printf("\tSYS: CANCELED.\r\n");
//	//			continue;
//	//		}
//	//	}
//	//	else
//	//		printf("\tSYS: ERROR! [STAGE LENGTH] is not in the range.\r\n");
//	//}
//	
//
//	// temporarily Setting variables for testing <Step 4>
//	data.iIndex = 505;
//	data.iLength = 5;
//	printf("data.iIndex  : %i\r\n", data.iIndex);
//	printf("data.iLength : %i\r\n", data.iLength);
//
//	// Step 3 -- Allocating memory on [data.cpBlockType]
//	data.cpBlockType = (char*)malloc(sizeof(char) * data.iLength);			// 2--malloc
//	printf("STEP3-1 > Allocating memory on [data.cpBlockType]\r\n");
//	memset(data.cpBlockType, 0, sizeof(char) * data.iLength);
//	printf("STEP3-2 > Initialze all [data.cpBlockType] to 0\r\n");
//
//	//char a;
//
//	// Step 4 -- Set Block-sequence.
//	for (i = 0; i < data.iLength; ++i){
//		printf("[%i]BLOCK : ", i);
//		scanf("%c", &(data.cpBlockType[i]));
//		printf("\tSYS: [%i]Block to [   %c   ]\r\n", data.cpBlockType[i]);
//	}
//	//fclose(fp);						// 1--closing file
//
//	free(data.cpBlockType);													// 2--free
//}