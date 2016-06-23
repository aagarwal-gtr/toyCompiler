all: stage1exe

stage1exe: driver.c lexer.o parser.o symbolTable.o ast.o typeChecker.o
	gcc -g driver.c parser.o lexer.o symbolTable.o ast.o typeChecker.o -o stage1exe

lexer.o: lexer.c
	gcc -c -g lexer.c

parser.o: parser.c
	gcc -c -g parser.c

symbolTable.o: symbolTable.c
	gcc -c -g symbolTable.c

ast.o: ast.c
	gcc -c -g ast.c

typeChecker.o: typeChecker.c
	gcc -c -g typeChecker.c
clean:
	rm -f *.o stage1exe
