#include "../includes/library.h"

node_ast *cr_num(int value)
{
    node_ast *node = malloc(sizeof(node_ast));
    if (node == NULL)
        return NULL;
    node->type = AST_NUMBER;
    node->number = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}
node_ast *cr_add(node_ast *left, node_ast *right)
{
    node_ast *node = malloc(sizeof(node_ast));
    if (node == NULL)
        return NULL;
    node->type = AST_ADD;
    node->left = left;
    node->right = right;
    return node;
}
node_ast *cr_minus(node_ast *left, node_ast *right)
{
    node_ast *node = malloc(sizeof(node_ast));
    if (node == NULL)
        return NULL;
    node->type = AST_MINUS;
    node->left = left;
    node->right = right;
    return node;
}
node_ast *cr_mult(node_ast *left, node_ast *right)
{
    node_ast *node = malloc(sizeof(node_ast));
    if (node == NULL)
        return NULL;
    node->type = AST_MULT;
    node->left = left;
    node->right = right ;
    return node;
}
node_ast *cr_div(node_ast *left, node_ast *right)
{
    node_ast *node = malloc(sizeof(node_ast));
    if (node == NULL)
        return NULL;
    node->type = AST_DIV;
    node->left = left;
    node->right = right ;
    return node;
}
node_ast *cr_grea(node_ast *left, node_ast *right)
{
    node_ast *node = malloc(sizeof(node_ast));
    if (node == NULL)
        return NULL;
    node->type = AST_GREATER;
    node->left = left;
    node->right = right ;
    return node;
}
node_ast *cr_less(node_ast *left, node_ast *right)
{
    node_ast *node = malloc(sizeof(node_ast));
    if (node == NULL)
        return NULL;
    node->type = AST_LESS;
    node->left = left;
    node->right = right ;
    return node;
}
node_ast *cr_grea_eq(node_ast *left, node_ast *right)
{
    node_ast *node = malloc(sizeof(node_ast));
    if (node == NULL)
        return NULL;
    node->type = AST_GREATER_EQUAL;
    node->left = left;
    node->right = right ;
    return node;
}
node_ast *cr_less_eq(node_ast *left, node_ast *right)
{
    node_ast *node = malloc(sizeof(node_ast));
    if (node == NULL)
        return NULL;
    node->type = AST_LESS_EQUAL;
    node->left = left;
    node->right = right ;
    return node;
}
node_ast *cr_eq_eq(node_ast *left, node_ast *right)
{
    node_ast *node = malloc(sizeof(node_ast));
    if (node == NULL)
        return NULL;
    node->type = AST_EQUAL_EQUAL;
    node->left = left;
    node->right = right ;
    return node;
}
node_ast *cr_not_eq(node_ast *left, node_ast *right)
{
    node_ast *node = malloc(sizeof(node_ast));
    if (node == NULL)
        return NULL;
    node->type = AST_NOT_EQUAL;
    node->left = left;
    node->right = right ;
    return node;
}
node_ast *parse_num(type_token *token, int *i)
{
    if (token[*i].type != TOKEN_NUMBER)
        return NULL;
    node_ast *node = cr_num(token[*i].value);
    if (node == NULL)
        return NULL;
    (*i)++;
    return node;
}

node_ast *parse_term(type_token *token, int *i)
{
    node_ast *left;
    node_ast *right;
    node_ast *node;
    left = parse_num(token, i);
    if (left == NULL)
        return NULL;
    while ((token[*i].type == TOKEN_MULTIPLE)
    || (token[*i].type == TOKEN_DIVISION))
    {
        if (token[*i].type == TOKEN_MULTIPLE)
        {
            (*i)++;
            right = parse_num(token, i);
            if (right == NULL)
                return NULL;
            node = cr_mult(left, right);
            if (node == NULL)
	            return (NULL);
            left = node;
        }
        else if(token[*i].type == TOKEN_DIVISION)
        {
            (*i)++;
            right = parse_num(token, i);
            if (right == NULL)
                return NULL;
            node = cr_div(left, right);
            if (node == NULL)
	            return (NULL);
            left = node;
        }
    }
    return left;
}
node_ast *parse_condition(type_token *token, int *i)
{
    node_ast *left;
    node_ast *right;
    node_ast *node;
    left = parse_expr(token, i);
    if (left == NULL)
        return NULL;
    if (token[*i].type == TOKEN_GREATER)
    {
        (*i)++;
        right = parse_expr(token, i);
        if (right == NULL)
            return NULL;
        node = cr_grea(left, right);
        if (node == NULL)
	        return (NULL);
        left = node;
    }
    else if(token[*i].type == TOKEN_LESS)
    {
        (*i)++;
        right = parse_expr(token, i);
        if (right == NULL)
            return NULL;
        node = cr_less(left, right);
        if (node == NULL)
	        return (NULL);
        left = node;
    }
    else if(token[*i].type == TOKEN_GREATER_EQUAL)
    {
        (*i)++;
        right = parse_expr(token, i);
        if (right == NULL)
            return NULL;
        node = cr_grea_eq(left, right);
        if (node == NULL)
	        return (NULL);
        left = node;
    }
    else if(token[*i].type == TOKEN_LESS_EQUAL)
    {
        (*i)++;
        right = parse_expr(token, i);
        if (right == NULL)
            return NULL;
        node = cr_less_eq(left, right);
        if (node == NULL)
	        return (NULL);
        left = node;
    }
    else if(token[*i].type == TOKEN_EQUAL_EQUAL)
    {
        (*i)++;
        right = parse_expr(token, i);
        if (right == NULL)
            return NULL;
        node = cr_eq_eq(left, right);
        if (node == NULL)
	        return (NULL);
        left = node;
    }
    else if(token[*i].type == TOKEN_NOT_EQUAL)
    {
        (*i)++;
        right = parse_expr(token, i);
        if (right == NULL)
            return NULL;
        node = cr_not_eq(left, right);
        if (node == NULL)
	        return (NULL);
        left = node;
    }
    return left;
}
node_ast *parse_expr(type_token *token, int *i)
{
    node_ast *left;
    node_ast *right;
    node_ast *node;
    left = parse_term(token, i);
    if (left == NULL)
        return NULL;
    while ((token[*i].type == TOKEN_PLUS)
    || (token[*i].type == TOKEN_MINUS))
    {
        if (token[*i].type == TOKEN_PLUS)
        {
            (*i)++;
            right = parse_term(token, i);
            if (right == NULL)
                return NULL;
            node = cr_add(left, right);
            if (node == NULL)
	            return (NULL);
            left = node;
        }
        else if (token[*i].type == TOKEN_MINUS)
        {
            (*i)++;
            right = parse_term(token, i);
            if (right == NULL)
                return NULL;
            node = cr_minus(left, right);
            if (node == NULL)
	            return (NULL);
            left = node;
        }
    }
    return left;
}