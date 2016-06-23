#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "symbolTable.h"
#include "typeChecker.h"

char *extractType(ST *symT, char* id) {
	char *type = (char*)malloc(30*sizeof(char));
	ST *temp = symT;
	while(temp!=NULL) {
		if(!strcmp(temp->id,id)) {
			strcpy(type, temp->type);
			return type;
		}
		temp = temp->next;
	}
	return "no_type";
}

char *extractTypeRecord(ST *symT, RT *recT, char* id, char* recid) {
	char *type = (char*)malloc(30*sizeof(char));
	ST *temp = symT;
	RT *curr = recT;
	//record *rcd;
	while(temp!=NULL) {
		//curr = recT;
		if(!strcmp(temp->id,id)) {
			while(curr!=NULL) {
				if(!strcmp(curr->name, temp->ifRecord)) {\
					//rcd = curr->detail;
					//printf("#########%s\n",curr->name);
					while(curr->detail!=NULL) {
						//printf("$$$$$$%s: %s\n", recid, curr->detail->id);
						if(!strcmp(recid, curr->detail->id)) {
							strcpy(type, curr->detail->type);
							return type;
						}
						curr->detail = curr->detail->next;
					}
				}
				curr = curr->next;
			}
		}
		temp = temp->next;
	}
	return "no_type";
}

int isRel(char *lexeme) {
	if(!strcmp(lexeme,"<=") || !strcmp(lexeme,"<") || !strcmp(lexeme,">") || !strcmp(lexeme,">=") || !strcmp(lexeme,"==") || !strcmp(lexeme,"") || !strcmp(lexeme,"!=")) return 1;
	else return 0;
}

int isLog(char *lexeme) {
	if(!strcmp(lexeme,"&&&") || !strcmp(lexeme,"@@@")) return 1;
	else return 0;
}
void typeCheck(parseTree *p, ST *symT, RT *recT, char typeLHS[30], int *flag) {
	if(p==NULL) return;
	//printf("here reached: %10s: %d: %d\n",p->token, *flag, p->line);
	//boolean
	if(isRel(p->lexeme) && *flag == 0) {
		if(!strcmp(p->parent->left->child->token,"TK_ID"))
			strcpy(typeLHS, extractType(symT, p->parent->left->child->lexeme));
		else if(!strcmp(p->parent->left->child->token,"TK_NUM"))
			strcpy(typeLHS, "int");
		else if(!strcmp(p->parent->left->child->token,"TK_RNUM"))
			strcpy(typeLHS, "real");
		else {}
		if(!strcmp(p->parent->right->child->token,"TK_ID")) {
			if(strcmp(typeLHS, extractType(symT, p->parent->right->child->lexeme))) printf("Line: %d: Lexeme: %s should be of type %s\n", p->parent->right->child->line, p->parent->right->child->lexeme, typeLHS);
		}
		else if(!strcmp(p->right->child->token,"TK_NUM")) {
			if(strcmp(typeLHS, "int")) printf("Line: %d: Lexeme: %s should be of type %s\n", p->parent->right->child->line, p->parent->right->child->lexeme, typeLHS);
		}
		else if(!strcmp(p->parent->right->child->token,"TK_RNUM")) {
			if(strcmp(typeLHS, "real")) printf("Line: %d: Lexeme: %s should be of type %s\n", p->parent->right->child->line, p->parent->right->child->lexeme, typeLHS);
		}
		else{}
	}
	//arithmetic
	if(!strcmp(p->token,"TK_ASSIGNOP") && p->right != NULL && *flag == 0) {
		//if int or real
		if(p->left->child->right->child->right==NULL) {
			strcpy(typeLHS, extractType(symT, p->left->child->lexeme));
		}
		else {
			strcpy(typeLHS, extractTypeRecord(symT, recT, p->left->child->lexeme, p->left->child->right->child->right->lexeme));
		//printf("here record: %s: %s: %s\n", typeLHS, p->left->child->lexeme,  p->left->child->right->child->right->lexeme);
		}
		*flag = 1;
	}
	if(!strcmp(p->token,"TK_ID") && *flag == 1) {
		//printf("here reached\n");
		if(!strcmp(typeLHS, extractType(symT, p->lexeme)) && p->right->child->right == NULL){}
		else if(p->right->child->right != NULL && !strcmp(typeLHS, extractTypeRecord(symT, recT, p->lexeme, p->right->child->right->lexeme))){}
		else printf("Line: %d: Lexeme: %s should be of type %s\n", p->line, p->lexeme, typeLHS);
		//printf("here reached\n");
		*flag = 0;
	}
	if(!strcmp(p->token,"TK_NUM") && *flag == 1) {
		if(!strcmp(typeLHS, "int")){}
		else printf("Line: %d: Lexeme: %s should be of type %s\n", p->line, p->lexeme, typeLHS);
		*flag = 0;
	}
	if(!strcmp(p->token,"TK_RNUM") && *flag == 1) {
		if(!strcmp(typeLHS, "real")){}
		else printf("Line: %d: Lexeme: %s should be of type %s\n", p->line, p->lexeme, typeLHS);
		*flag = 0;
	}
	if(!strcmp(p->token,"TK_PLUS") && !strcmp(p->token,"TK_MINUS") && !strcmp(p->token,"TK_MUL") && !strcmp(p->token,"TK_DIV")) *flag = 1;
	typeCheck(p->child, symT, recT, typeLHS, flag);
	typeCheck(p->right, symT, recT, typeLHS, flag);
}
