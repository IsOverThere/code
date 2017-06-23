#include "main.h"

#define PARAM_ACTION		"-a"
#define PARAM_FILE		"-f"
#define PARAM_TABLE		"-t"

#define STR_ACTION_CUT		"cut"
#define STR_ACTION_PARSE	"parse"
#define STR_ACTION_CHAR2HEX	"char2hex"
#define STR_ACTION_HEX2CHAR	"hex2char"

#define STR_TABLE_PMT		"pmt"

#define ACTION_NULL		0
#define ACTION_CUT		1
#define ACTION_PARSE		2
#define ACTION_CHAR2HEX		3
#define ACTION_HEX2CHAR		4

#define TABLE_NULL		0
#define TABLE_PMT		1

char	gInputFileName[256];
int	gAction = ACTION_NULL;
int	gTable = TABLE_NULL;

int main(int argc, char *argv[])
{
	int i;

	if(argc == 1)
	{
		printf("Please input parameters!!!\n");
	}
	else
	{
		for(i=0; i<argc; i++)
		{
			if(0 == strcmp((const char *)argv[i], PARAM_ACTION))
			{
				if(i + 1 >= argc) {printf("Missing action\n"); return 1;}
				if(0 == strcmp((const char *)argv[i+1], STR_ACTION_CUT))
				{
					gAction = ACTION_CUT;	
				}
				else if(0 == strcmp((const char *)argv[i+1], STR_ACTION_PARSE))
				{
					gAction = ACTION_PARSE;	
				}
				i++;
			}
			else if(0 == strcmp((const char *)argv[i], PARAM_FILE))
			{
				if(i + 1 >= argc) {printf("Missing filename\n"); return 1;}
				strcpy(gInputFileName, argv[i+1]);
				i++;
			}
			else if(0 == strcmp((const char *)argv[i], PARAM_TABLE))
			{
				if(i + 1 >= argc) {printf("Missing which table\n"); return 1;}
				if(0 == strcmp((const char *)argv[i+1], STR_ACTION_CUT))
				{
					gTable = TABLE_PMT;	
				}
			}
		}
	}

	switch(gAction)
	{
		case ACTION_CUT:
			//cut
			break;

		case ACTION_PARSE:
			switch(gTable)
			{
				case TABLE_PMT:
					printf("Begin to parse pmt\n");
					//parse pmt
					break;
				default:
					printf("Bad -p parameters\n");
			}
			break;
		default:
			printf("Bad -a parameters\n");
			break;
	}
}
