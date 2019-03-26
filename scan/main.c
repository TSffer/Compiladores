#include <stdio.h>
#include <stdlib.h>
#include "Calculator_scanner.c"

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Usage: %s file\n",argv[0]);
        exit(1);
    }
    scan_file(argv[1]);
}