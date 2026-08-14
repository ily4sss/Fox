#include "includes/library.h"

int	main(int ac, char **av)
{
    if (ac != 2)
        return 1;
    FILE *src_file = fopen(av[1], "r");
    if (src_file == NULL)
    {
        perror("Error while opening the file...");
        return 1;
    }
    long size = FileSize(src_file);
    char *src = malloc(size + 1);
    if (src == NULL)
    {
        fclose(src_file);
        return 1;
    }
    size_t bytes_r = fread(src, 1, size, src_file);
    src[bytes_r] = '\0';
    type_token *token = Tokenize(src, bytes_r);
    if (token == NULL)
    {
        free(src);
        fclose(src_file);
        return 1;
    }
    stat *program;
    program = parse_program(token);
    if (program == NULL)
    {
        printf("Parser error\n");
        return (1);
    }
    int j = 0;
    print_program(program);
    free(src);
    fclose(src_file);
    return 0;
}
