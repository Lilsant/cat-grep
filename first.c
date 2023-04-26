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
        char *line = NULL;
        int len = 0;
        int total_lines_count = 0;
        int matching_lines_count = 0;
        int read = 0;
        fp = fopen(argv[2], "r");
        if (fp == NULL)
            return 0;
        flags_init();
        check_flags(argv, argc);
        while (getline(&line, &len, fp) != -1)
        {
            char *bro = NULL;
            total_lines_count++;
            if(f.i) bro = line_to_lower_case(line, argv[1], len, strlen(argv[1]));
            else bro = strstr(line, argv[1]);
            if (bro != 0)
            {
                matching_lines_count++;
                if(!f.c && !f.l && f.n) printf("%d:%s", total_lines_count, line); 
                else if(!f.c && !f.l) printf("%s", line);
            }
            else {
                if(f.v && f.n) printf("");
            }
        }
        if(f.l && matching_lines_count) printf("%s", argv[2]);
        if(f.c) printf("%d", matching_lines_count);
        fclose(fp);
        free(line);
    }
    return 0;
}

void flags_init()
{
    f.e = 0;
    f.i = 0; // Done
    f.v = 0;
    f.c = 0; // Done
    f.l = 0; // Done, but only for one file
    f.n = 0; // Done
}

char *line_to_lower_case(char *str, char *grep_word, int str_len, int grep_word_len) {
    char *line = (char*) malloc(sizeof(char) * str_len);
    char *gp_word = (char*) malloc(sizeof(char) * grep_word_len);
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
            default:
                break;
            }
        }
    }
}