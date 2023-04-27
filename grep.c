#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grep.h"

int main(int argc, char *argv[])
{
    FILE *fp = NULL;
    if (argc <= 1)
        printf("Bro You Need To Define Path");
    else
    {
        flags_init();
        check_flags(argv, argc);
        for (int i = 3; i < argc; i++)
        {
            int is_multi_files = 0;
            char *line = NULL;
            int len = 0;
            int total_lines_count = 0;
            int matching_lines_count = 0;
            int read = 0;
            if (argc > 4 && !f.h)
                is_multi_files = 1;
            fp = fopen(argv[i], "r");
            if (fp == NULL && !f.s)
            {
                printf("grep: %s: No such file or directory\n", argv[i]);
                // return 0;
                continue;
            }
            while (getline(&line, &len, fp) != -1)
            {
                char *bro = NULL;
                total_lines_count++;
                if (f.i)
                    bro = line_to_lower_case(line, argv[2], len, strlen(argv[2]));
                else
                    bro = strstr(line, argv[2]);
                if (bro != NULL)
                {
                    matching_lines_count++;
                    if(f.v || f.l || f.c) continue;
                    if (is_multi_files)
                        printf("%s:", argv[i]);
                    if (f.n)
                        printf("%d:", total_lines_count);
                    if(f.o) 
                        printf("%s\n", argv[2]);
                    else printf("%s", line);
                }
                else if (bro == NULL && f.v && !f.c && !f.l)
                {
                    if (is_multi_files)
                        printf("%s:", argv[i]);
                    if (f.n)
                        printf("%d:", total_lines_count);
                    printf("%s", line);
                }
            }
            if (f.l && matching_lines_count)
                printf("%s\n", argv[i]);
            else if (f.c && f.v)
            {
                if (is_multi_files)
                    printf("%s:", argv[i]);
                if (f.n)
                    printf("%d:", total_lines_count);
                printf("%d\n", total_lines_count - matching_lines_count);
            }
            else if (f.c && !f.v)
            {
                if (is_multi_files)
                    printf("%s:", argv[i]);
                if (f.n)
                    printf("%d:", total_lines_count);
                printf("%d\n", matching_lines_count);
            }
            free(line);
        }
        fclose(fp);
    }
    return 0;
}
// Hello
void flags_init()
{
    f.e = 0;
    f.i = 0; // Done
    f.v = 0; // Done
    f.c = 0; // Done
    f.l = 0; // Done
    f.n = 0; // Done
    f.h = 0; // Done
    f.s = 0; // Done, but need to add some errors
    f.o = 0; 
}

char *line_to_lower_case(char *str, char *grep_word, int str_len, int grep_word_len)
{
    char *line = (char *)malloc(sizeof(char) * str_len);
    char *gp_word = (char *)malloc(sizeof(char) * grep_word_len);
    strcpy(line, str);
    strcpy(gp_word, grep_word);
    strlwr(line);
    strlwr(gp_word);
    return strstr(line, gp_word);
}

void check_flags(char **argv, int argc)
{
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {

            switch (argv[i][1])
            {
            case 'i':
                f.i = 1;
                break;
            case 'e':
                f.e = 1;
                break;
            case 'v':
                f.v = 1;
                break;
            case 'c':
                f.c = 1;
                break;
            case 'l':
                f.l = 1;
                break;
            case 'n':
                f.n = 1;
                break;
            case 's':
                f.s = 1;
                break;
            case 'o':
                f.o = 1;
                break;
            case 'h':
                f.h = 1;
                break;
            default:
                break;
            }
        }
    }
}