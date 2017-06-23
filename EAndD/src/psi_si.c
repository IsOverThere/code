#include <sdtio.h>
#include "psi_si.h"
#include "debug.h"
#include "typedef.h"

int parse_psi_si(
	const unsigned char* pStreamBuffer,
	const unsigned char* filter, 
	const unsigned char* mask,
	unsigned int uiLenght,
	unsigned char* pBuffer,
	unsigned int uiBufferSize)
{

}
/* filter[0] is PID Hight
 * filter[1] is PID Low
 * filter[2] is TableID
 * ... ...
 *
 *
 *
 */
int parse_psi_si_in_file(
	FILE* fpStream,
	const unsigned short* PID,
	const unsigned char* filter, 
	const unsigned char* mask,
	unsigned int uiLenght,
	unsigned char* pBuffer,
	unsigned int uiBufferSize)
{
	unsigned char 	ucCurrentChar;
	int	  	iCurrentChar;
	unsigned char	ucParsePID_H;
	unsigned char	ucParsePID_L;
	unsigned char	ucStreamPID_H;
	unsigned char	ucStreamPID_L;
	unsigned char	ucOnePacket[PSI_SI_PACKET_SIZE];

	if(!fpStream)
	{
		printf("Can't Open the file\n");
		return 0;
	}

	//Here we go! 
	//Step 1. Find out the header of the packet.
	iCurrentChar = fgetc(fpStream);
	while(EOF != ucCurrentChar)
	{

	}
	
	//Step 2. Search the packet one by one
	while(EOF != fread(unOnePacket, sizeof(unsigned char), PSI_SI_PACKET_SIZE, fpStream))
	{

	}
}
