#include "../includes/library.h"

long FileSize (FILE *file)
{
    fseek(file, 0 , SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}

char *Tokenize_num(char *str, int *i)
{
    int size = *i;
    int j = 0;
    while (str[size] >= '0' && str[size] <= '9')
        size++;
    j = size - *i;
    char *token = malloc(j + 1);
    if (token == NULL)
        return NULL;
    j = 0;
    while (str[*i] >= '0' && str[*i] <= '9')
    {
        token[j++] = str[*i];
        (*i)++;
    }
    token[j] = '\0';
    return token;
}

void Skip_Space(char *str, int *i)
{
        while (str[*i] == ' '
        || str[*i] == '\t')
	    (*i)++;
}

