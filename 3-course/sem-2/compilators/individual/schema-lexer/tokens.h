#pragma once

#define MAX_TOKENS 1000

typedef struct {
    char* type;
    char* value;
    int line;
} Token;

extern Token token_table[MAX_TOKENS];
extern int token_count;

void add_token(const char* type, const char* value, int line);