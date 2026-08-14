#include "../includes/library.h"
type_token Tokenize_word(char *str, int *i)
{
    type_token id_token;
    int j = 0;
    int start = *i;
    while (isalnum(str[start])
	|| str[start] == '_')
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
    while (isalnum(str[*i])
	|| str[*i] == '_')
    {
	    id_str[j++] = str[*i];
	    (*i)++;
    }
    id_str[j] = '\0';
    id_token.str_value = id_str;
	if (strcmp(id_str, "var") == 0)
		id_token.type = TOKEN_CALL_VAR;
	else if (strcmp(id_str, "display") == 0)
		id_token.type = TOKEN_DISPLAY;
	else if (strcmp(id_str, "int") == 0)
		id_token.type = TOKEN_TYPE_VAR;
    else if (strcmp(id_str, "check_if") == 0)
		id_token.type = TOKEN_CHECK_IF;
    else if (strcmp(id_str, "check_else") == 0)
		id_token.type = TOKEN_CHECK_ELSE;
	else
		id_token.type = TOKEN_IDENTIFIER;
    return id_token;
}

type_token Tokenize_str_num(char *str, int *i)
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
    token.str_value = NULL;
    free(tokenStr);
    return (token);
}
type_token	Tokenize_op(char *str, int *i)
{
	type_token	token;
	int	len = 1;
	if ((str[*i] == '=' && str[*i + 1] == '=')
		|| (str[*i] == '>' && str[*i + 1] == '=')
		|| (str[*i] == '<' && str[*i + 1] == '=')
		|| (str[*i] == '!' && str[*i + 1] == '='))
		len = 2;
	char *opr = malloc(len + 1);
	if (opr == NULL)
	{
		token.type = TOKEN_ERROR;
		token.str_value = NULL;
		return (token);
	}
	opr[0] = str[*i];
	if (len == 2)
		opr[1] = str[*i + 1];
	opr[len] = '\0';
	*i += len;
	if (strcmp(opr, "=") == 0)
		token.type = TOKEN_EQUAL;
	else if (strcmp(opr, "==") == 0)
		token.type = TOKEN_EQUAL_EQUAL;
	else if (strcmp(opr, "+") == 0)
		token.type = TOKEN_PLUS;
	else if (strcmp(opr, "-") == 0)
		token.type = TOKEN_MINUS;
	else if (strcmp(opr, "*") == 0)
		token.type = TOKEN_MULTIPLE;
	else if (strcmp(opr, "/") == 0)
		token.type = TOKEN_DIVISION;
	else if (strcmp(opr, ">") == 0)
		token.type = TOKEN_GREATER;
	else if (strcmp(opr, ">=") == 0)
		token.type = TOKEN_GREATER_EQUAL;
	else if (strcmp(opr, "<") == 0)
		token.type = TOKEN_LESS;
	else if (strcmp(opr, "<=") == 0)
		token.type = TOKEN_LESS_EQUAL;
	else if (strcmp(opr, "!=") == 0)
		token.type = TOKEN_NOT_EQUAL;
	else if (strcmp(opr, ",") == 0)
		token.type = TOKEN_COMMA;
	else if (strcmp(opr, ";") == 0)
		token.type = TOKEN_SEMICOLON;
	else if (strcmp(opr, "(") == 0)
		token.type = TOKEN_LPAREN;
	else if (strcmp(opr, ")") == 0)
		token.type = TOKEN_RPAREN;
	else if (strcmp(opr, "{") == 0)
		token.type = TOKEN_LBRACE;
	else if (strcmp(opr, "}") == 0)
		token.type = TOKEN_RBRACE;
	else if (strcmp(opr, "[") == 0)
		token.type = TOKEN_LBRACKET;
	else if (strcmp(opr, "]") == 0)
		token.type = TOKEN_RBRACKET;
	else
		token.type = TOKEN_ERROR;
	token.str_value = opr;
	return (token);
}

type_token Tokenize_str(char *str, int *i)
{
    type_token token;
    int j = 0;
    (*i)++;
    int end= *i;
    while (str[end] != '"' && str[end])
        end++;
    if (str[end] != '"')
    {
        token.type = TOKEN_ERROR;
        token.str_value = NULL;
        return token;
    }
    int size = end - *i;
    char *phrase = malloc(size +1);
    if (phrase == NULL)
    {
        token.type = TOKEN_ERROR;
        token.str_value = NULL;
        return token;
    }
    while (*i < end)
    {
        phrase[j++] = str[*i];
        (*i)++;
    }
    phrase[j] = '\0';
    (*i)++;
    token.type = TOKEN_STRING;
    token.str_value = phrase;
    return token;
}

type_token *Tokenize(char *str, long size)
{
    int t = 0;
    int i = 0;
    int line = 0;
    int column = 0;
    type_token	*tokens;
    tokens = malloc(sizeof(type_token) * (size + 1));
    if (tokens == NULL)
        return NULL;
    while (str[i])
    {
        if (str[i] == '\n')
        {
            line++;
            column = 1;
            i++;
        }
        else if (isspace(str[i]))
            Skip_Space(str, &i);
        else if (isdigit(str[i]))
            tokens[t++] = Tokenize_str_num(str, &i);
        else if (isalpha(str[i]) || str[i] == '_')
		    tokens[t++] = Tokenize_word(str, &i);
        else if(str[i] == '=' || str[i] == '+'
	    || str[i] == '-' || str[i] == '*'
	    || str[i] == '/' || str[i] == '>'
	    || str[i] == '<' || str[i] == '!'
	    || str[i] == ',' || str[i] == ';'
	    || str[i] == '(' || str[i] == ')'
	    || str[i] == '{' || str[i] == '}'
	    || str[i] == '[' || str[i] == ']')
		    tokens[t++] = Tokenize_op(str, &i);
        else if(str[i] == '"')
            tokens[t++] = Tokenize_str(str, &i); 
        else
        {
            tokens[t].type = TOKEN_ERROR;
            tokens[t].str_value = NULL;
            t++;
            i++;
        }
    }
    tokens[t].type = TOKEN_TEND;
    tokens[t].str_value = NULL;
    return tokens;
}
