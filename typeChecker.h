char *extractType(ST *symT, char* id);
char *extractTypeRecord(ST *symT, RT *recT, char* id, char* recid);
int isRel(char *lexeme);
int isLog(char *lexeme);
void typeCheck(parseTree *p, ST *symT, RT *recT, char typeRHS[30], int *flag);
