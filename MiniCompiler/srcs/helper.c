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

void	print_ast(node_ast *node, int depth)
{
	int	i;

	if (node == NULL)
		return;
	i = 0;
	while (i++ < depth)
		printf("  ");
	if (node->type == AST_NUMBER)
		printf("NUMBER: %d\n", node->number);
	else if (node->type == AST_ADD)
		printf("ADD\n");
	else if (node->type == AST_MINUS)
		printf("MINUS\n");
	else if (node->type == AST_MULT)
		printf("MULT\n");
	else if (node->type == AST_DIV)
		printf("DIV\n");
	else if (node->type == AST_GREATER)
		printf("GREATER\n");
	else if (node->type == AST_LESS)
		printf("LESS\n");
	else if (node->type == AST_GREATER_EQUAL)
		printf("GREATER_EQUAL\n");
	else if (node->type == AST_LESS_EQUAL)
		printf("LESS_EQUAL\n");
	else if (node->type == AST_EQUAL_EQUAL)
		printf("EQUAL_EQUAL\n");
	else if (node->type == AST_NOT_EQUAL)
		printf("NOT_EQUAL\n");
	print_ast(node->left, depth + 1);
	print_ast(node->right, depth + 1);
}
void	print_program(stat *program)
{
	var_ast		*var;
	display_ast	*display;
	if_ast		*if_data;
	stat		*body;

	while (program)
	{
		if (program->type == STMT_VAR)
		{
			var = (var_ast *)program->data;
			printf("STMT_VAR\n");
			printf("  type: %s\n", var->var_type);
			printf("  identifier: %s\n", var->identifier);
			printf("  expression:\n");
			print_ast(var->var_node, 2);
		}
		else if (program->type == STMT_DISPLAY)
		{
			display = (display_ast *)program->data;
			printf("STMT_DISPLAY\n");
			printf("  string: %s\n", display->string);
		}
		else if (program->type == STMT_IF)
		{
			if_data = (if_ast *)program->data;
			printf("STMT_IF\n");
			printf("  condition:\n");
			print_ast(if_data->if_node, 2);
			printf("  body:\n");
			body = if_data->body_stat;
			while (body)
			{
				if (body->type == STMT_DISPLAY)
					printf("    STMT_DISPLAY\n");
				else if (body->type == STMT_VAR)
					printf("    STMT_VAR\n");
				else if (body->type == STMT_IF)
					printf("    STMT_IF\n");
				body = body->next;
			}
		}
		else if (program->type == STMT_ELSE)
		{
			printf("STMT_ELSE\n");
		}
		program = program->next;
	}
}