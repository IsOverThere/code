#include "psi_si.h" 
#include <stdio.h>

FILE *fpStream

int parse_pmt(char * cInputFileName, unsigned short usPmtPid, unsigned char ucStreamType)
{
	if(NULL == cInputFileName)
	{
		printf("Bad file name\n");	
	}

	*fpStream = fopen(cInputFileName,"rb");
	if(!fpStream)
	{
		printf("Can't Open the file\n");
		return 0;
	}


	//Begin to Parse PMT	
	
	fclose(fpStream);
}
