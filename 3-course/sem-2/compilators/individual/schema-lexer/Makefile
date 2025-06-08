lexer: schema.l token_table.c
	flex schema.l
	gcc -o lexer lex.yy.c token_table.c \
	    -I/opt/homebrew/opt/flex/include \
	    -L/opt/homebrew/opt/flex/lib -lfl

clean:
	rm -f lexer lex.yy.c
