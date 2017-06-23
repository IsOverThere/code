#ifndef DEBUG_H
#define DEBUG_H
#endif
#ifdef DEBUG_H

#ifdef DEBUG
#define PREFIX	printf("[DBG][%s][%d] ",__FILE__,__LINE__)
#define DEBUG_PRINT(x)		PREFIX;printf(x)
#define DEBUG_PRINT_1(x,y)	PREFIX;printf(x,y)
#else
#define DEBUG_PRINT(x)
#define DEBUG_PRINT_1(x,y)
#endif

#endif//DEBUG_H
