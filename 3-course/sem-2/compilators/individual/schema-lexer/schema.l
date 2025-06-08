%{
#include <stdio.h>
#include <string.h>
#include "tokens.h"

int line_num = 1;
%}

%option noyywrap
%x STR_ERR

%%
"schema"        { add_token("Keyword", yytext, line_num); }
"type"          { add_token("Keyword", yytext, line_num); }
"record"        { add_token("Keyword", yytext, line_num); }

"int"           { add_token("Type", yytext, line_num); }
"string"        { add_token("Type", yytext, line_num); }
"bool"          { add_token("Type", yytext, line_num); }

[0-9]+          { add_token("IntLiteral", yytext, line_num); }

\"[^\"\n]*\"    { add_token("StringLiteral", yytext, line_num); }

\"[^\"\n]*\n    {
                  fprintf(stderr, "Lexical error: unterminated string at line %d\n", line_num);
                  line_num++;
                }

[0-9]+[a-zA-Z_]+ {
                  fprintf(stderr, "Lexical error: malformed number '%s' at line %d\n", yytext, line_num);
                }

[a-zA-Z_][a-zA-Z0-9_]*  { add_token("Identifier", yytext, line_num); }

"{"             { add_token("LBrace", yytext, line_num); }
"}"             { add_token("RBrace", yytext, line_num); }
":"             { add_token("Colon", yytext, line_num); }
";"             { add_token("Semicolon", yytext, line_num); }
"="             { add_token("Equal", yytext, line_num); }

[ \t\r]+        { /* ігнорувати пробіли */ }
\n              { line_num++; }

.               {
                  fprintf(stderr, "Lexical error: unexpected character '%s' at line %d\n", yytext, line_num);
                }

%%

int main(int argc, char** argv) {
    if (argc > 1) {
        FILE* file = fopen(argv[1], "r");
        if (!file) {
            perror("Cannot open file");
            return 1;
        }
        yyin = file;
    }

    yylex();

    printf("Lexical tokens:\n");
    for (int i = 0; i < token_count; i++) {
        printf("  %-12s %-15s (line %d)\n", token_table[i].type, token_table[i].value, token_table[i].line);
    }

    return 0;
}
