#ifndef LIBRARY
#define LIBRARY

#include <stdlib.h>
typedef enum enum_type_token
{
    TOKEN_CALL_VAR,
    TOKEN_TYPE_VAR,
    TOKEN_IDENTIFIER,
    TOKEN_EQUAL,
    TOKEN_NUMBER,
	TOKEN_PLUS,
	TOKEN_MINUS,
    TOKEN_SEMICOLON,
    TOKEN_ERROR
} e_type_token;
typedef struct s_type_token
{
    e_type_token type;
    int          value;
    char         *str_value;
}   type_token;

#endif