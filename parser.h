/*
BATCH 46
MANAN KHASGIWALE (2013A7PS128P)
ABHINAV AGARWAL (2013A7PS124P)
Contains function prototype declarations of functions in parser.c
*/

#include"parserDef.h"

void init();
int search(char* str, int flag);
void convertGrammar();
int push(int i);
int pop();
int isEmpty();
void display();
parseTree *parseInputSourceCode(FILE *fp, FILE *ferr);
void printParseTree(parseTree *p, FILE *out);
