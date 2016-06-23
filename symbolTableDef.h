#ifndef STDEF
#define STDEF

typedef struct symbolTable {
	char id[20];
	char type[30];
	char scope[20];
	char ifRecord[20];
	int add2next;
	int offset;
	int line;
	struct symbolTable* next;
}ST;

typedef struct parameter {
	char type[50];
	char id[20];
	struct parameter *next;
}parameter;

typedef struct functionTable {
	char name[20];
	parameter *input;
	parameter *output;
	struct functionTable *next;
}FT;

typedef struct record {
	char type[20];
	char id[20];
	struct record *next;
	struct record *prev;
}record;

typedef struct recordTable {
	char name[20];
	char ftype[30];
	int offset;
	record *detail;
	struct recordTable *next;
}RT;

#endif
