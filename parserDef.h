/*
BATCH 46
MANAN KHASGIWALE (2013A7PS128P)
ABHINAV AGARWAL (2013A7PS124P)
Contains all definitions for data types such as grammar, table, parseTree etc. used in parser.c
*/

#ifndef PARSERDEF
#define PARSERDEF

#define MAX 1000

typedef struct var {
	int id;
	char name[100];
} var;

var nonterm[100], term[100];


union valueIfNumber {
	int i;
	float f;
};

typedef struct parseTree {
	//tokenInfo token; // lexeme, token, line
	char lexeme[50];
	char token[30];  //symbols like ID, string, MATRIX, RNUM, NUM etc.
	int line;
	union valueIfNumber value;
	struct parseTree* parent;
	struct parseTree* child;
	struct parseTree* right;
	struct parseTree* left;
	int isLeafNode;//(yes/no)
	char nodeSymbol[30];
} parseTree; 

typedef struct STACK {
	int symbols[MAX];
	int top;
}stack;

#endif
