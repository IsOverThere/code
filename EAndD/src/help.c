#ifdef HELP
#include "debug.h"

#define MAX_STRING 3

char *HelpString[MAX_STRING] = {
       	"Please usage:",
	"-a [hex2txt | txt2hex | cut]",
	"[-i f1 -o f2 [-o size]]"
};

void ShowHelp(void)
{
	int i = 0;
	DEBUG_PRINT_1("sizeof HelpString is %d\n", sizeof(HelpString));
	for(i=0; i<MAX_STRING; i++)
	{	
		printf("%s\n", HelpString[i]);
	}
}
#endif
