#include <stdio.h>  
#include <getopt.h>
#include <stdbool.h>
#include <stdlib.h>  
#include <string.h>

#define DEBUG(x)  if(bVerbose) printf x
static char inputFileName[256] = {'\0'};
static char outputFileName[256] = {'\0'};
static bool bVerbose = false;

/*16*6=96=0x60*/
#define HEADER_SIZE 0x60
unsigned char header[] = {
    0x74,0x27,0x8d,0xb6,0x00,0x00,0x00,0x00,0x8b,0x44,0x24,0x38,0x89,0x2c,0x24,0x89,
    0x44,0x24,0x08,0x8b,0x44,0x24,0x34,0x89,0x44,0x24,0x04,0xff,0x94,0xbb,0x08,0xff,
    0xff,0xff,0x83,0xc7,0x01,0x39,0xf7,0x75,0xdf,0x83,0xc4,0x1c,0x5b,0x5e,0x5f,0x5d,
    0xc3,0xeb,0x0d,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,
    0xf3,0xc3,0x00,0x00,0x53,0x83,0xec,0x08,0xe8,0x43,0xf2,0xff,0xff,0x81,0xc3,0xf3,
    0x1c,0x00,0x00,0x83,0xc4,0x08,0x5b,0xc3,0x03,0x00,0x00,0x00,0x01,0x00,0x02,0x00,
};

/*16*32=512=0x200*/
#define FOOTER_SIZE 0x200
unsigned char footer[] = {
    0x44,0x24,0x08,0x00,0x00,0x00,0x00,0xc7,0x44,0x24,0x04,0x00,0x00,0x00,0x00,0x89,
    0x04,0x24,0xe8,0x69,0xfb,0xff,0xff,0xa3,0x80,0xb0,0x04,0x08,0x83,0x44,0x24,0x1c,
    0x01,0xeb,0x67,0x8b,0x44,0x24,0x1c,0x8d,0x14,0x85,0x00,0x00,0x00,0x00,0x8b,0x45,
    0x0c,0x01,0xd0,0x8b,0x00,0xc7,0x44,0x24,0x04,0xb8,0x93,0x04,0x08,0x89,0x04,0x24,
    0xe8,0xbb,0xfa,0xff,0xff,0x85,0xc0,0x74,0x26,0x8b,0x44,0x24,0x1c,0x8d,0x14,0x85,
    0x00,0x00,0x00,0x00,0x8b,0x45,0x0c,0x01,0xd0,0x8b,0x00,0xc7,0x44,0x24,0x04,0xbb,
    0x93,0x04,0x08,0x89,0x04,0x24,0xe8,0x95,0xfa,0xff,0xff,0x85,0xc0,0x75,0x1b,0xc7,
    0x04,0x24,0xc2,0x93,0x04,0x08,0xe8,0xe5,0xfa,0xff,0xff,0xe8,0x7e,0x08,0x00,0x00,
    0xb8,0x00,0x00,0x00,0x00,0xe9,0xd1,0x00,0x00,0x00,0x83,0x44,0x24,0x1c,0x01,0x8b,
    0x44,0x24,0x1c,0x3b,0x45,0x08,0x0f,0x8c,0x68,0xfc,0xff,0xff,0xa1,0x64,0xb0,0x04,
    0x08,0x83,0xf8,0x02,0x74,0x3d,0x83,0xf8,0x02,0x7f,0x0a,0x83,0xf8,0x01,0x74,0x14,
    0xe9,0x99,0x00,0x00,0x00,0x83,0xf8,0x03,0x74,0x50,0x83,0xf8,0x04,0x74,0x6d,0xe9,
    0x8a,0x00,0x00,0x00,0xa1,0x80,0xb0,0x04,0x08,0x89,0x44,0x24,0x08,0xc7,0x44,0x24,
    0x04,0xa0,0xb1,0x04,0x08,0xc7,0x04,0x24,0xa0,0xb0,0x04,0x08,0xe8,0x54,0x06,0x00,
    0x00,0xeb,0x78,0xa1,0x68,0xb0,0x04,0x08,0x83,0xf8,0x01,0x75,0x0f,0xc7,0x04,0x24,
    0xc9,0x93,0x04,0x08,0xe8,0x67,0xfa,0xff,0xff,0x90,0xeb,0x5f,0xc7,0x04,0x24,0xdc,
    0x93,0x04,0x08,0xe8,0x58,0xfa,0xff,0xff,0xeb,0x51,0xc7,0x04,0x24,0xee,0x93,0x04,
    0x08,0xe8,0x4a,0xfa,0xff,0xff,0xc7,0x44,0x24,0x04,0xa0,0xb1,0x04,0x08,0xc7,0x04,
    0x24,0xa0,0xb0,0x04,0x08,0xe8,0x7b,0x03,0x00,0x00,0xeb,0x2f,0xc7,0x04,0x24,0x0b,
    0x94,0x04,0x08,0xe8,0x28,0xfa,0xff,0xff,0xc7,0x44,0x24,0x04,0xa0,0xb1,0x04,0x08,
    0xc7,0x04,0x24,0xa0,0xb0,0x04,0x08,0xe8,0x22,0x01,0x00,0x00,0xeb,0x0d,0xc7,0x04,
    0x24,0x28,0x94,0x04,0x08,0xe8,0x06,0xfa,0xff,0xff,0x90,0xc9,0xc3,0x55,0x89,0xe5,
    0x83,0xec,0x04,0x8b,0x45,0x08,0x88,0x45,0xfc,0x80,0x7d,0xfc,0x09,0x77,0x09,0x0f,
    0xb6,0x45,0xfc,0x83,0xc0,0x30,0xeb,0x15,0x80,0x7d,0xfc,0x09,0x76,0x0f,0x80,0x7d,
    0xfc,0x0f,0x77,0x09,0x0f,0xb6,0x45,0xfc,0x83,0xc0,0x57,0xeb,0x00,0xc9,0xc3,0x55,
    0x89,0xe5,0x83,0xec,0x08,0x8b,0x45,0x08,0x88,0x45,0xfc,0x0f,0xb6,0x45,0xfc,0xc0,
    0xe8,0x04,0x0f,0xb6,0xc0,0x89,0x04,0x24,0xe8,0xb0,0xff,0xff,0xff,0x8b,0x55,0x0c,
    0x88,0x02,0x0f,0xb6,0x45,0xfc,0x83,0xe0,0x0f,0x89,0x04,0x24,0xe8,0x9c,0xff,0xff,
    0xff,0x8b,0x55,0x10,0x88,0x02,0xc9,0xc3,0x55,0x89,0xe5,0x83,0xec,0x04,0x8b,0x45,
    0x08,0x88,0x45,0xfc,0x80,0x7d,0xfc,0x40,0x7e,0x0f,0x80,0x7d,0xfc,0x46,0x7f,0x09,
    0x0f,0xb6,0x45,0xfc,0x83,0xe8,0x37,0xeb,0x2a,0x80,0x7d,0xfc,0x60,0x7e,0x0f,0x80,
    0x7d,0xfc,0x66,0x7f,0x09,0x0f,0xb6,0x45,0xfc,0x83,0xe8,0x57,0xeb,0x15,0x80,0x7d,
};

int main(int argc, char **argv)  
{
    unsigned int i=0, size=0;
    unsigned char c;
    int opt;  
    int option_index = 0;  
    char *optstring = "i:o:n:r::vh";
    FILE* inputFileHandle;
    FILE* outputFileHandle;
    static struct option long_options[] = {
        {"input-file",      required_argument,  NULL, 'i'}, 
        {"output-file",     required_argument,  NULL, 'o'}, 
        {"header-size",     required_argument,  NULL, 'n'},
        {"footer-size",     required_argument,  NULL, 'f'},
        {"verbose",         no_argument,        NULL, 'v'},
        {"help",            no_argument,        NULL, 'h'},
        {0, 0, 0, 0}  
    }; 

    if (1 == argc)
    {
        printf("Quit.\n");
        exit(0);
    }

    while ( (opt = getopt_long(argc, argv, optstring, long_options, &option_index)) != -1)  
    {
        switch(opt)
        {
            case 'i':
                strcpy(inputFileName, optarg);
                DEBUG(("inputFileName=<%s>\n", inputFileName));
                break;

            case 'o':
                strcpy(outputFileName, optarg);
                DEBUG(("outputFileName=<%s>\n", outputFileName));
                break;

            case 'v':
                bVerbose = true;
                break;

            case 'h':
                printf("Help.\n");
                exit(0);
                break;

            default:
                printf("Invalid code is returned in getopt_long\n");
                break;
        }
    }

    inputFileHandle = fopen(inputFileName, "rb");
    if (NULL == inputFileHandle)
    {
        printf("Failed when open file %s, return 0x%p\n", inputFileName, inputFileHandle);
        exit(0);
    }
    outputFileHandle = fopen(outputFileName, "w+b");
    if (NULL == outputFileHandle)
    {
        printf("Failed when open file %s, return 0x%p\n", outputFileName, outputFileHandle);
        exit(0);
    }

    /*header*/
    fwrite(header, 1, HEADER_SIZE, outputFileHandle);

    fseek(inputFileHandle, 0, SEEK_END);
    size = ftell(inputFileHandle);
    fseek(inputFileHandle, 0, SEEK_SET);
    
    while (i++ < size)
    {
        fputc(fgetc(inputFileHandle), outputFileHandle);
    }

    /*footer*/
    fwrite(footer, 1, FOOTER_SIZE, outputFileHandle);

    if (NULL != inputFileHandle)
        fclose(inputFileHandle);
    if (NULL != outputFileHandle)
        fclose(outputFileHandle);

}
