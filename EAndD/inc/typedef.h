#ifndef TYPEDEF_H
#define TYPEDEF_H
#endif

#ifdef TYPEDEF_H
typedef unsigned int 	U32;
typedef signed int	S32;
typedef unsigned short	U16;
typedef signed short	S16;
typedef unsigned char	U8;
typedef signed char	S8;

#define ASSERT(x) 	if(!(x))\
			{\
			       	printf("[#ASSERT ERROR][%s][%s][%d]\n", __FILE__, __FUNCTION__, __LINE__);\
			       	return 0;\
			}

#endif
