#include "tokens.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Token token_table[MAX_TOKENS];
int token_count = 0;

void add_token(const char* type, const char* value, int line) {
    if (token_count >= MAX_TOKENS) return;

    token_table[token_count].type = strdup(type);
    token_table[token_count].value = strdup(value);
    token_table[token_count].line = line;
    token_count++;
}