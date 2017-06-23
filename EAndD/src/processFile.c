#ifdef PROCESS_FILE
#include <stdio.h>
#include "debug.h"
#include "typedef.h"

int cutFile(char *cInputFileName, char *cOutputFileName, int size)
{
	FILE *fpInputFile, *fpOutputFile;
	char ProcessByte;
	unsigned char ProcessedByte;
	int flag = 0;

	DEBUG_PRINT("Enter cut file...\n");
	ASSERT(0 != size);
	ASSERT(NULL != cInputFileName && NULL != cOutputFileName);
	fpInputFile = fopen(cInputFileName,"rb");
	ASSERT(fpInputFile);
	fpOutputFile = fopen(cOutputFileName,"w+b");
	ASSERT(fpOutputFile);
	while((0 != fread(&ProcessByte, sizeof(unsigned char), 1, fpInputFile))&&(0 != size--))
	{
		fwrite(&ProcessedByte, sizeof(unsigned char), 1, fpOutputFile); 
	}
	if( 0 == size)
	{
		printf("Done!!!\n");	
		printf("Leaves file in: %s", cOutputFileName);
	}
	else
	{
		printf("Cut size is smaller than source file.\n");	
		printf("Leaves file in: %s", cOutputFileName);
	}
	fclose(fpInputFile);
	fclose(fpOutputFile);
	return 1;
}
#endif
