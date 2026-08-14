#include "../includes/library.h"


stat *parse_program(type_token *token)
{
    stat *first = NULL;
    stat *last = NULL;
    for (int i = 0; token[i].type != TOKEN_TEND;)
    {
        stat *program_stat = malloc(sizeof(stat));
        if (program_stat == NULL)
	        return NULL;
        if(token[i].type == TOKEN_CALL_VAR)
        {
            program_stat->type = STMT_VAR;
            program_stat->data = parse_var(token , &i);
            if(program_stat->data == NULL)
            {
                free(program_stat);
                return NULL;
            }
        }
        else if(token[i].type == TOKEN_DISPLAY)
        {
            program_stat->type = STMT_DISPLAY;
            program_stat->data = parse_display(token , &i);
            if(program_stat->data == NULL)
            {
                free(program_stat);
                return NULL;
            }
        }
        else if(token[i].type == TOKEN_CHECK_IF)
        {
            program_stat->type = STMT_IF;
            program_stat->data = parse_if(token , &i);
            if(program_stat->data == NULL)
            {
                free(program_stat);
                return NULL;
            }
        }
        else if(token[i].type == TOKEN_CHECK_ELSE)
        {
            if (last == NULL || last->type != STMT_IF)
                return NULL;
            program_stat->type = STMT_ELSE;
            program_stat->data = parse_else(token , &i);
            if(program_stat->data == NULL)
            {
                free(program_stat);
                return NULL;
            }
        }
        else
        {
            free(program_stat);
            return NULL;
        }
        program_stat->next = NULL;
        if (first == NULL)
        {
            first = program_stat;
            last = program_stat;
        }
        else
        {
            last->next = program_stat;
	        last = program_stat;
        }
    }
    return first;
}