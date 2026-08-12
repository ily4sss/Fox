#include <stdlib.h>
typedef enum enum_type_token
{
    TOKEN_NUMBER,
	TOKEN_PLUS,
	TOKEN_MINUS,
    TOKEN_ERROR
} e_type_token;
typedef struct s_type_token
{
    e_type_token type;
    int          value;
}   type_token;
char *Tokenize_num(char *str, int *i)
{
    int size = 0;
    int j = 0;
    while (str[size] >= '0' && str[size] <= '9')
        size++;
    size = size - *i;
    char *token = malloc(size + 1);
    if (token == NULL)
        return NULL;
    while (str[*i] == ' ')
        (*i)++;
    while (str[*i] >= '0' && str[*i] <= '9')
    {
        token[j++] = str[*i];
        (*i)++;
    }
    token[j] = '\0';
    return token;
}
type_token Str_To_Num(char *str, int *i)
{
    int number = 0;
    int n = 0;
    int length = 0;
    type_token token;
    char *tokenStr = Tokenize_num(str, i);
    if (tokenStr == NULL)
    {
        token.type = TOKEN_ERROR;
        token.value = 0;
        return token;
    }
    token.type = TOKEN_NUMBER;
    while (tokenStr[length])
        length++;
    while (n < length)
        number = (number * 10) + tokenStr[n++] - '0';
    token.value = number;
    free(tokenStr);
    return (token);
}
type_token Tokenize(char *str)
{
    int t = 0;
    int i = 0;
    type_token	tokens[100];
    tokens[t] = Str_To_Num(str, &i);
    t++;
    while (str[i] == ' ')
	i++;
    if(str[t] == '+')
    {
        tokens[t].type = TOKEN_PLUS;
        t++;
        i++;
    } 
    else if(str[t] == '-')
    {
        tokens[t].type = TOKEN_MINUS;
        t++; 
        i++;
    }
    tokens[t] = Str_To_Num(str, &i);
    t++;
    return tokens[100];
}
int main ()
{
    char* Text = "15 + 1";
    type_token	tokens[100];
    tokens[100] = Tokenize(Text);
    return 0;
}
