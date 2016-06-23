#include"symbolTableDef.h"

void createRT(parseTree *p, RT **head, char scope[30], int *flag, RT **temp, record **tmp);
void printRT(RT *head);
void createST(parseTree *p, ST **head, char scope[30], int *flag, ST **temp, RT *recordT);
void printST(ST *head);
