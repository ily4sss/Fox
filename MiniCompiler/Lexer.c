#include "library.h"
type_token Tokenize_var_call(char *str, int *i)
{
    type_token var_token;
    char *base = "var";
    char *var = malloc(4);
    if (var == NULL)
    {
        var_token.type = TOKEN_ERROR;
        var_token.str_value = NULL;
        return var_token;
    }
    int j = 0;
    while(*i < 3)
    {
        if (str[*i] == base[j]) 
            var[j++] = str[*i];
        else
        {
            var_token.type = TOKEN_ERROR;
            var_token.str_value = NULL;
            free(var);
            return var_token;
        }
        (*i)++;
    }
    var_token.type = TOKEN_CALL_VAR;
    var[j] = '\0';
    var_token.str_value = var;
    return var_token;
}

type_token Tokenize_var_type(char *str, int *i)
{
    type_token type_token;
    int start = *i;
    int j = 0;
    while (str[start] >= 'a' && str[start] <= 'z')
        start++;
    j = start - *i;
    char *type = malloc(j + 1);
    if (type == NULL)
    {
        type_token.type = TOKEN_ERROR;
        type_token.str_value = NULL;
        return type_token;
    }
    j = 0;
    while (str[*i] != ' ' && str[*i])
    {
        if (str[*i] >= 'a' && str[*i] <= 'z')
            type[j++] = str[*i];
        else
        {
            type_token.type = TOKEN_ERROR;
            type_token.str_value = NULL;
            free(type);
            return type_token; 
        }
        (*i)++;
    }
    type[j] = '\0';
    type_token.type = TOKEN_TYPE_VAR;
    type_token.str_value = type;
    return type_token;
}

type_token Tokenize_id(char *str, int *i)
{
    type_token id_token;
    int j = 0;
    int start = *i;
    while ((str[start] >= 'a' && str[start] <= 'z') || (str[start] >= 'A' && str[start] <= 'Z')
    || str[start] == '_' || (str[start] >= '0' && str[start] <= '9'))
        start++;
    j = start - *i;
    char *id_str = malloc(j + 1);
    if (id_str == NULL)
    {
        id_token.type = TOKEN_ERROR;
        id_token.str_value = NULL;
        return id_token;
    }
    j = 0;
    while (str[*i] != ' ' && str[*i])
    {
        if((str[*i] >= 'a' && str[*i] <= 'z') || (str[*i] >= 'A' && str[*i] <= 'Z')
        || str[*i] == '_' || (str[*i] >= '0' && str[*i] <= '9'))
            id_str[j++] = str[*i];
        else
        {
            id_token.type = TOKEN_ERROR;
            id_token.str_value = NULL;
            free(id_str);
            return id_token;
        }
        (*i)++;
    }
    id_str[j] = '\0';
    id_token.type = TOKEN_IDENTIFIER;
    id_token.str_value = id_str;
    return id_token;
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
void Skip_Space(char *str, int *i)
{
        while (str[*i] == ' ')
	    (*i)++;
}
type_token *Tokenize(char *str)
{
    int t = 0;
    int i = 0;
    type_token	*tokens;
    tokens = malloc (sizeof(type_token) * 100);
    if (tokens == NULL)
        return NULL;
    tokens[t] = Tokenize_var_call(str, &i);
    t++;
    Skip_Space(str, &i);
    tokens[t] = Tokenize_var_type(str, &i);
    t++;
    Skip_Space(str, &i);
    tokens[t] = Tokenize_id(str, &i);
    t++;
    Skip_Space(str, &i);
    if(str[i] == '=')
    {
        tokens[t].type = TOKEN_EQUAL;
        tokens[t].str_value = "=";
        t++;
        i++;
    }
    Skip_Space(str, &i);
    tokens[t] = Str_To_Num(str, &i);
    t++;
    Skip_Space(str, &i);
    if(str[i] == '+')
    {
        tokens[t].type = TOKEN_PLUS;
        tokens[t].str_value = "+";
        t++;
        i++;
    } 
    else if(str[i] == '-')
    {
        tokens[t].type = TOKEN_MINUS;
        tokens[t].str_value = "-";
        t++; 
        i++;
    }
    Skip_Space(str, &i);
    tokens[t] = Str_To_Num(str, &i);
    t++;
    if(str[i] == ';')
    {
        tokens[t].type = TOKEN_SEMICOLON;
        tokens[t].str_value = ";";
        t++;
        i++;
    }
    return tokens;
}

int main ()
{
    char* Text = "var int x = 1 + 5;";
    type_token *tokens;
    tokens = Tokenize(Text);
    return 0;
}
