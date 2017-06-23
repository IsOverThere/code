#include <stdio.h>
#include "debug.h"

#ifdef HEXTXT
extern int Hex2Char(unsigned char *cInputFileName, unsigned char *cOutputFileName);
extern int Char2Hex(unsigned char *cInputFileName, unsigned char *cOutputFileName);
#endif

#ifdef PROCESS_FILE
extern int cutFile(char *cInputFileName, char *cOutputFileName, int size);
#endif

#ifdef HELP
extern void ShowHelp(void);
#endif

