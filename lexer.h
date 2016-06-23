/*
BATCH 46
MANAN KHASGIWALE (2013A7PS128P)
ABHINAV AGARWAL (2013A7PS124P)
Contains function prototype declarations of functions in lexer.c
*/

#include"lexerDef.h"

FILE *getStream(FILE *fp, buffer B, buffersize k);
tokenInfo getNextToken(buffer B, FILE *ferr, int line, int *flag, int *pos);
char* substr(char string[], int pos, int len);
