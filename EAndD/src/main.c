#include "main.h"
#include "typedef.h"

#define PARAM_ACTION		"-a"
#define PARAM_INPUT_FILE	"-i"
#define PARAM_OUTPUT_FILE	"-o"
#define PARAM_TABLE		"-t"
#define PARAM_MORE		"-m"
#define PARAM_HELP_1		"-h"
#define PARAM_HELP_2		"--help"

#define STR_ACTION_CUT		"cut"
#define STR_ACTION_PARSE	"parse"
#define STR_ACTION_TXT2HEX	"txt2hex"
#define STR_ACTION_HEX2TXT	"hex2txt"

#define STR_TABLE_PMT		"pmt"

#define ACTION_NULL		0
#define ACTION_CUT		1
#define ACTION_PARSE		2
#define ACTION_TXT2HEX		3
#define ACTION_HEX2TXT		4

#define TABLE_NULL		0
#define TABLE_PMT		1

#define MORE_NULL		0
#define MORE_SIZE		1

char	gInputFileName[256];
char	gOutputFileName[256];
int	gAction = ACTION_NULL;
int	gTable = TABLE_NULL;
int	gMoreParam;
#ifdef TEST	
extern void just_test(void);
#endif
int main(int argc, char *argv[])
{
	int i;
#ifdef TEST	
	just_test();
#endif
	DEBUG_PRINT("Enter Main\n");

	if(argc == 1)
	{
		printf("Please input parameters!!!\n");
		ShowHelp();
		return 0;
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
				else if(0 == strcmp((const char *)argv[i+1], STR_ACTION_TXT2HEX))
				{
					gAction = ACTION_TXT2HEX;	
				}
				else if(0 == strcmp((const char *)argv[i+1], STR_ACTION_HEX2TXT))
				{
					gAction = ACTION_HEX2TXT;	
				}
				i++;
			}
			else if(0 == strcmp((const char *)argv[i], PARAM_INPUT_FILE))
			{
				if(i + 1 >= argc) {printf("Missing filename\n"); return 1;}
				strcpy(gInputFileName, argv[i+1]);
				i++;
			}
			else if(0 == strcmp((const char *)argv[i], PARAM_OUTPUT_FILE))
			{
				if(i + 1 >= argc) {printf("Missing filename\n"); return 1;}
				strcpy(gOutputFileName, argv[i+1]);
				i++;
			}
			else if(0 == strcmp((const char *)argv[i], PARAM_TABLE))
			{
				if(i + 1 >= argc) {printf("Missing which table\n"); return 1;}
				if(0 == strcmp((const char *)argv[i+1], STR_TABLE_PMT))
				{
					gTable = TABLE_PMT;	
				}
				i++;
			}
			else if(0 == strcmp((const char *)argv[i], PARAM_MORE))
			{
				if(i + 1 >= argc) {printf("Missing the more parameters\n"); return 1;}
				gMoreParam = (unsigned int)strtoul((const char *)argv[i+1], NULL, 0);
				i++;
			}
			else if((0 == strcmp((const char *)argv[i], PARAM_HELP_1)) || (0 == strcmp((const char *)argv[i], PARAM_HELP_2)))
			{
				printf("help:)\n");
#if HELP
				ShowHelp();
				return 0;
#endif
			}
		}
	}

	switch(gAction)
	{
		case ACTION_CUT:
#ifdef PROCESS_FILE
			cutFile(gInputFileName, gOutputFileName, gMoreParam);
#endif
			break;

		case ACTION_PARSE:
			switch(gTable)
			{
				case TABLE_PMT:
					printf("Begin to parse pmt\n");
					//parse pmt
					break;
				default:
					printf("Bad -t parameters\n");
			}
			break;
		case ACTION_TXT2HEX:
			printf("Begin to convert text 2 hex.\n");
#ifdef HEXTXT
			Txt2Hex(gInputFileName, gOutputFileName);
#endif
			break;
		case ACTION_HEX2TXT:
			printf("Begin to convert hex 2 text.\n");
#ifdef HEXTXT
			Hex2Txt(gInputFileName, gOutputFileName);
#endif
			break;
		default:
			printf("Bad -a parameters\n");
			break;
	}
}
