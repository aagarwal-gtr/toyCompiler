/*
BATCH 46
MANAN KHASGIWALE (2013A7PS128P)
ABHINAV AGARWAL (2013A7PS124P)
Contains all data definitions used in lexer.c
*/

#ifndef LEXERDEF
#define LEXERDEF

typedef char* buffer;
typedef int buffersize;

typedef struct tokenInfo
{
    char lexeme[100];
    char token[30];  //symbols like ID, string, MATRIX, RNUM, NUM etc.
    int line;
}tokenInfo;


//extern int flag, line, pos;

#endif
