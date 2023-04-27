#include <stdlib.h>

struct flags {
    int e;
    int i;
    int v;
    int c;
    int l;
    int n;
    int h;
    int s;
    int o;
} f;


void flags_init();
void check_flags(char **argv, int argc);
char *line_to_lower_case(char *str, char *grep_word, int str_len, int grep_word_len);