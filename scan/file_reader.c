#include <stdio.h>
#include "utils.h"

char read_character(char **str)
{
    char c = **str;
    (*str)++;
    return c;
}

void unread_character(char **str)
{
    (*str)--;
}

int get_current_line_length(FILE *fp)
{
    int len = 0;
    char c;
    while((c = fgetc(fp)) && c != '\n' && c != EOF)
    {
        len++;
    }

    if(c == EOF)
    {
        fseek(fp, -len, SEEK_CUR);
    }
    else
    {
        fseek(fp,-len-1,SEEK_CUR);
    }
    
    return len + 1;
}

int read_line(FILE *fp, char *buf)
{
    int i = 0;
    while(1)
    {
        char c = fgetc(fp);
        if(c == '\n' || c == EOF)
        {
            buf[i] = '\0';
            return c == 'n';
        }
        buf[i++] = c;
    }
    
    WTF;
    return 0;
}