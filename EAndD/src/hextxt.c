#ifdef HEXTXT
#include <stdio.h>
#include "debug.h"
#include "typedef.h"

char Bin2TxtByByte(unsigned char sourceByte)
{
	if(sourceByte>=0x0 && sourceByte<=0x09)
	{
		return (sourceByte+'0');	
	}
	else if(sourceByte>=0x0A && sourceByte<=0x0F)
	{
		return (sourceByte-0x0A+'a');	
	}
}


int Hex2TxtByByte(unsigned char ProcessByte, char *ProcessedByteH, char *ProcessedByteL)
{

	*ProcessedByteH = Bin2TxtByByte((ProcessByte&0xF0)>>4);
	*ProcessedByteL = Bin2TxtByByte(ProcessByte&0x0F);
}

unsigned char Txt2BinByByte(char sourceByte)
{
	if(sourceByte>='A' && sourceByte<='F')
	{
		return (unsigned char)(sourceByte-'A'+10);
	}
	else if (sourceByte>='a' && sourceByte<='f')
	{
		return (unsigned char)(sourceByte-'a'+10);
	}
	else if (sourceByte>='0' && sourceByte<='9')
	{
		return (unsigned char)(sourceByte-'0');
	}
}

int Txt2HexByByte(unsigned char *ProcessedByte, char ProcessByteH, char ProcessByteL)
{
	*ProcessedByte = Txt2BinByByte(ProcessByteH);
	*ProcessedByte <<= 4; 
	*ProcessedByte += Txt2BinByByte(ProcessByteL);
	return 0;
}

int Hex2Txt(char *cInputFileName, char *cOutputFileName)
{

	FILE *fpInputFile, *fpOutputFile;
	char ProcessedByteH, ProcessedByteL;
	unsigned char ProcessByte;
	int count = 0;
	int firstByte = 1;
	int firstLine = 1;

	DEBUG_PRINT("Enter Hex2Txt...\n");
	ASSERT(NULL != cInputFileName && NULL != cOutputFileName);
	fpInputFile = fopen(cInputFileName,"rb");
	ASSERT(fpInputFile);
	fpOutputFile = fopen(cOutputFileName,"w+");
	ASSERT(fpOutputFile);

	while(0 != fread(&ProcessByte, sizeof(unsigned char), 1, fpInputFile))
	{
		Hex2TxtByByte(ProcessByte, &ProcessedByteH, &ProcessedByteL);
		if(firstByte == 1) //To avoid to add the last comma.
		{
			firstByte = 0;
		}
		else
		{
			fputc(',', fpOutputFile);
		}
		if(firstLine == 1)
		{
			if(++count == 17)
			{
				fputc(0xa, fpOutputFile);
				firstLine = 0;
				count = 0;
			}
		}
		else
		{
			if(++count == 16)
			{
				fputc(0xa, fpOutputFile);
				count = 0;
			}
		}
		fputc('0', fpOutputFile);
		fputc('x', fpOutputFile);
		fputc(ProcessedByteH, fpOutputFile);
		fputc(ProcessedByteL, fpOutputFile);
	}
	fclose(fpInputFile);
	fclose(fpOutputFile);
	printf("Done!!!\n");	
	printf("Leaves file in: %s", cOutputFileName);
	DEBUG_PRINT("Exit Hex2Txt...\n");
}

int Txt2Hex(char *cInputFileName, char *cOutputFileName)
{
	FILE *fpInputFile, *fpOutputFile;
	char ProcessByte, ProcessByteH, ProcessByteL;
	unsigned char ProcessedByte;
	int flag = 0;

	DEBUG_PRINT("Enter Txt2Hex...\n");
	ASSERT(NULL != cInputFileName && NULL != cOutputFileName);
	fpInputFile = fopen(cInputFileName,"r");
	ASSERT(fpInputFile);
	fpOutputFile = fopen(cOutputFileName,"w+b");
	ASSERT(fpOutputFile);
	
	while(EOF != (ProcessByte = fgetc(fpInputFile)))
	{
		switch(ProcessByte)
		{
			case '0':
				if(flag == 0)
				{
					flag = 1;
				}
				else if(flag == 2)
				{
					ProcessByteH = ProcessByte;
					flag++;
				}
				else if(flag == 3)
				{
					ProcessByteL = ProcessByte;
					Txt2HexByByte(&ProcessedByte, ProcessByteH, ProcessByteL);
					fwrite(&ProcessedByte, sizeof(unsigned char), 1, fpOutputFile); 
					flag = 0;
				}
				break;	
		
			case 'x':	
				if(flag == 1)
				{
					flag = 2;		
				}
				break;
			case 10:
//				printf("LF");
				break;
			case 13:
//				printf("CR");
				break;
			case 17:
//				printf("DCI");
				break;
			default:
				if((ProcessByte >= '0' && ProcessByte <= '9')
					||(ProcessByte >= 'A' && ProcessByte <= 'F')
					||(ProcessByte >= 'a' && ProcessByte <= 'f'))
				{
					if(flag == 2)
					{
						ProcessByteH = ProcessByte;
						flag++;
					}	
					else if(flag == 3)
					{
						ProcessByteL = ProcessByte;
						Txt2HexByByte(&ProcessedByte, ProcessByteH, ProcessByteL);
						fwrite(&ProcessedByte, sizeof(unsigned char), 1, fpOutputFile); 
						flag = 0;
					}
				
				}
		
		}
	}
	fclose(fpInputFile);
	fclose(fpOutputFile);
	printf("Done!!!\n");	
	printf("Leaves file in: %s", cOutputFileName);
	DEBUG_PRINT("Exit Txt2Hex...\n");
}
#endif
