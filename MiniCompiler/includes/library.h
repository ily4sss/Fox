#ifndef LIBRARY
#define LIBRARY
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
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
//-----------------------Parser-----------------
typedef enum  en_node_ast
{
    AST_VAR,
    AST_NUMBER,
    AST_ADD,
    AST_MULT,
    AST_DIV,
    AST_MINUS,
    AST_GREATER,
    AST_LESS,
    AST_GREATER_EQUAL,
    AST_LESS_EQUAL,
    AST_EQUAL_EQUAL,
    AST_NOT_EQUAL
}  e_node_ast;

typedef struct a_node_ast
{
    e_node_ast type;
    int number;
    struct a_node_ast *left;
    struct a_node_ast *right;
} node_ast;

typedef struct a_var_ast
{
    struct a_node_ast *var_node;
    char *identifier;
    char *var_type;
} var_ast;

typedef struct s_display_ast
{
	char *string;
}	display_ast;

typedef enum e_stat_type
{
	STMT_VAR,
	STMT_DISPLAY,
	STMT_IF
}	stat_type;

typedef struct s_stat
{
	stat_type		type;
	void				*data;
}	stat;

typedef struct f_if_ast
{
    node_ast *if_node;
    stat      *body_stat;
} if_ast;

node_ast *cr_num(int value);
node_ast *cr_add(node_ast *left, node_ast *right);
node_ast *cr_minus(node_ast *left, node_ast *right);
node_ast *cr_mult(node_ast *left, node_ast *right);
node_ast *cr_div(node_ast *left, node_ast *right);
node_ast *parse_num(type_token *token, int *i);
node_ast *parse_term(type_token *token, int *i);
node_ast *parse_expr(type_token *token, int *i);
node_ast *parse_condition(type_token *token, int *i);
//----------------------------------------------

#endif