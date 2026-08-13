#ifndef LIBRARY
#define LIBRARY
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//-----------------Lexer--------------------
typedef enum enum_type_token
{
    TOKEN_CALL_VAR,
    TOKEN_TYPE_VAR,
    TOKEN_IDENTIFIER,
    TOKEN_EQUAL,
    TOKEN_EQUAL_EQUAL,
    TOKEN_NUMBER,
	TOKEN_PLUS,
	TOKEN_MINUS,
    TOKEN_MULTIPLE,
    TOKEN_DIVISION,
    TOKEN_GREATER,
    TOKEN_LESS,
    TOKEN_GREATER_EQUAL,
    TOKEN_LESS_EQUAL,
    TOKEN_NOT_EQUAL,
    TOKEN_SEMICOLON,
    TOKEN_ERROR,
    TOKEN_DISPLAY,
    TOKEN_OUTPUT,
    TOKEN_STRING,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_LBRACKET,
    TOKEN_RBRACKET,
    TOKEN_CHECK_IF,
    TOKEN_CHECK_ELSE,
    TOKEN_TEND,
    TOKEN_COMMA
} e_type_token;
typedef struct s_type_token
{
    e_type_token type;
    int          value;
    char         *str_value;
}   type_token;

type_token *Tokenize(char *src, long size);
type_token Tokenize_word(char *str, int *i);
void Skip_Space(char *str, int *i);
long FileSize (FILE *file);
char *Tokenize_num(char *str, int *i);
type_token Tokenize_str_num(char *str, int *i);
//----------------------------------------------
#endif
