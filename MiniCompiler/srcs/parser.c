#include "../includes/library.h"

var_ast *parse_var(type_token *token, int *i)
{
    var_ast *var = malloc (sizeof(var_ast));
    if(var == NULL)
        return NULL;
    if (token[*i].type != TOKEN_CALL_VAR)
    {
        free(var);
        return NULL;
    }
    (*i)++;
    if (token[*i].type != TOKEN_TYPE_VAR)
    {
        free(var);
        return NULL;
    }
    var->var_type = token[*i].str_value; 
    (*i)++;
    if (token[*i].type != TOKEN_IDENTIFIER)
    {
        free(var);
        return NULL;
    }
    var->identifier = token[*i].str_value;
    (*i)++;
    if (token[*i].type != TOKEN_EQUAL)
    {
        free(var);
        return NULL;
    }
    (*i)++;
    var->var_node = parse_expr(token, i);
    if (var->var_node == NULL)
    {
        free(var);
        return NULL;
    };
    return var;
}

display_ast *parse_display(type_token *token, int *i)
{
    display_ast *display = malloc (sizeof(display_ast));
    if(display == NULL)
        return NULL;
    if (token[*i].type != TOKEN_DISPLAY)
    {
        free(display);
        return NULL;
    }
    (*i)++;
    if(token[*i].type != TOKEN_GREATER)
    {
        free(display);
        return NULL;
    }
    (*i)++;
    if(token[*i].type != TOKEN_STRING)
    {
        free(display);
        return NULL;
    }
    display->string = token[*i].str_value;
    if (display->string == NULL)
    {
	    free(display);
	    return (NULL);
    }
    (*i)++;
    return display;
}

if_ast *parse_if(type_token *token, int *i)
{
    if_ast *if_stat = malloc(sizeof(if_ast));
    if (if_stat == NULL)
        return NULL;
    if_stat->if_node = NULL;
    if_stat->body_stat = NULL;
    if (token[*i].type != TOKEN_CHECK_IF)
    {
        free(if_stat);
        return NULL;
    }
    (*i)++;
    if (token[*i].type != TOKEN_LPAREN)
    {
        free(if_stat);
        return NULL;
    }
    (*i)++;
    if_stat->if_node = parse_condition(token, i);
    if (if_stat->if_node == NULL)
    {
        free(if_stat);
        return (NULL);
    }
    if (token[*i].type != TOKEN_RPAREN)
    {
        free(if_stat);
        return NULL;
    }
    (*i)++;
    if (token[*i].type != TOKEN_LBRACE)
    {
        free(if_stat);
        return NULL;
    }
    (*i)++;
    stat *first = NULL;
    stat *last = NULL;
    while (token[*i].type != TOKEN_RBRACE
    && token[*i].type != TOKEN_TEND
    && token[*i].type != TOKEN_ERROR)
    {        
        stat *new_stat = malloc(sizeof(stat));
        if (new_stat == NULL)
        {
            free(if_stat);
	        return NULL;
        }
        if (token[*i].type == TOKEN_CHECK_IF)
        {
            new_stat->type = STMT_IF;
            new_stat->data = parse_if(token, i);
            if (new_stat->data == NULL)
            {
                free(new_stat);
                free(if_stat);
                return (NULL);
            }
        }
        else if(token[*i].type == TOKEN_CHECK_ELSE)
        {
            new_stat->type = STMT_ELSE;
            new_stat->data = parse_else(token, i);
            if (new_stat->data == NULL)
            {
                free(new_stat);
                free(if_stat);
                return (NULL);
            }
        }
        else if (token[*i].type == TOKEN_DISPLAY)
        {
            new_stat->type = STMT_DISPLAY;
            new_stat->data = parse_display(token, i);
            if (new_stat->data == NULL)
            {
                free(new_stat);
                free(if_stat);
                return (NULL);
            }
        }
        else if(token[*i].type == TOKEN_CALL_VAR)
        {
            new_stat->type = STMT_VAR;
            new_stat->data = parse_var(token,i);
            if (new_stat->data == NULL)
            {
                free(new_stat);
                free(if_stat);
                return (NULL);
            }
        }
        else
        {
            free(if_stat);
            free(new_stat);
            return NULL;
        }
        new_stat->next = NULL;
        if (first == NULL)
        {
            first = new_stat;
            last = new_stat;
        }
        else
        {
            last->next = new_stat;
	        last = new_stat;
        }
    }
    if_stat->body_stat = first;
    if (token[*i].type != TOKEN_RBRACE)
    {
        free(if_stat);
        return (NULL);
    }
    (*i)++;
    return if_stat;
}
if_ast *parse_else(type_token *token, int *i)
{
    if_ast *else_stat = malloc(sizeof(if_ast));
    if (else_stat == NULL)
        return NULL;
    else_stat->if_node = NULL;
    else_stat->body_stat = NULL;
    if (token[*i].type != TOKEN_CHECK_ELSE)
    {
        free(else_stat);
        return NULL;
    }
    (*i)++;
    if (token[*i].type != TOKEN_LBRACE)
    {
        free(else_stat);
        return NULL;
    }
    (*i)++;
    stat *first = NULL;
    stat *last = NULL;
    while (token[*i].type != TOKEN_RBRACE
    && token[*i].type != TOKEN_TEND
    && token[*i].type != TOKEN_ERROR)
    {
        stat *new_stat = malloc(sizeof(*new_stat));
        if (new_stat == NULL)
        {
            free(else_stat);
	        return (NULL);
        }
        if (token[*i].type == TOKEN_CHECK_IF)
        {
            new_stat->type = STMT_IF;
            new_stat->data = parse_if(token, i);
            if (new_stat->data == NULL)
            {
                free(new_stat);
                free(else_stat);
                return (NULL);
            }
        }
        else if(token[*i].type == TOKEN_CHECK_ELSE)
        {
            new_stat->type = STMT_ELSE;
            new_stat->data = parse_else(token, i);
            if (new_stat->data == NULL)
            {
                free(new_stat);
                free(else_stat);
                return (NULL);
            }
        }
        else if (token[*i].type == TOKEN_DISPLAY)
        {
            new_stat->type = STMT_DISPLAY;
            new_stat->data = parse_display(token, i);
            if (new_stat->data == NULL)
            {
                free(new_stat);
                free(else_stat);
                return (NULL);
            }
        }
        else if(token[*i].type == TOKEN_CALL_VAR)
        {
            new_stat->type = STMT_VAR;
            new_stat->data = parse_var(token,i);
            if (new_stat->data == NULL)
            {
                free(new_stat);
                free(else_stat);
                return (NULL);
            }
        }
        else
        {
            free(else_stat);
            free(new_stat);
            return NULL;
        }
        new_stat->next = NULL;
        if (first == NULL)
        {
            first = new_stat;
            last = new_stat;
        }
        else
        {
            last->next = new_stat;
	        last = new_stat;
        }
    }
    else_stat->body_stat = first;
    if (token[*i].type != TOKEN_RBRACE)
    {
        free(else_stat);
        return (NULL);
    }
    (*i)++;
    return else_stat;
}
