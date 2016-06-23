#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

int noOfChildren(parseTree *p) {
	int noc = 0;
	parseTree *temp;
	temp =  p;
	if(temp -> child != NULL)  {
		noc++;
		temp = temp -> child;
		while(temp -> right != NULL) {
			temp = temp -> right;
			noc++;
		}
	}
	return noc;
}

int isTerminal(parseTree *p) {
	if(p -> token[0] == 'T' || p->token[0] == 'E') return 1;
	else return 0;
}
/*
int isUseful(char* token) {
    if(!strcmp(token, "TK_MAIN") || !strcmp(token, "TK_END") || !strcmp(token, "TK_SEM") || !strcmp(token, "TK_INPUT") || !strcmp(token, "TK_PARAMETER") || !strcmp(token, "TK_LIST") || !strcmp(token, "TK_SQL") || !strcmp(token, "TK_SQR") || !strcmp(token, "TK_OUTPUT") || !strcmp(token, "TK_COMMA") || !strcmp(token, "TK_COLON") || !strcmp(token, "TK_DOT") || !strcmp(token, "TK_CALL") || !strcmp(token, "TK_WITH") || !strcmp(token, "TK_PARAMETERS") || !strcmp(token, "TK_ASSIGNOP") || !strcmp(token, "TK_WHILE") || !strcmp(token, "TK_ENDWHILE") || !strcmp(token, "TK_IF") || !strcmp(token, "TK_ENDIF") || !strcmp(token, "TK_OP") || !strcmp(token, "TK_CL") || !strcmp(token, "TK_RETURN"))
    	return 0;
    else
    	return 1;
}*/

int isNotUseful(char *token) {
	if(!strcmp(token, "(") || !strcmp(token, ")") || !strcmp(token, ":") || !strcmp(token, "[") || !strcmp(token, ";") || !strcmp(token, "parameter") || !strcmp(token, "list") || !strcmp(token, "end") || !strcmp(token, "type") || !strcmp(token, ".") || !strcmp(token, "with") || !strcmp(token, "parameters")) return 1;
	else return 0;
}

void createAST(parseTree **p) {
	if((*p)==NULL) return;
	//printf("%s: %d\n",(*p)->token, (*p)->line);
	if(isTerminal(*p)) {}
	else {
		while((*p)->child->right!=NULL) {
			if(isNotUseful((*p)->child->lexeme)) {
				if((*p)->child->left == NULL && (*p)->child->right!= NULL) {
					(*p)->child = (*p)->child->right;
					(*p)->child->left = NULL;
				}
				else if((*p)->child->left != NULL && (*p)->child->right== NULL) {
					(*p)->child = (*p)->child->left;
					(*p)->child->right = NULL;
				}
				else if((*p)->child->left == NULL && (*p)->child->right== NULL) {
					(*p)->child->right = (*p)->child->parent->right;
					(*p)->child->left = (*p)->child->parent->left;
					if((*p)->left==NULL){
						(*p)->parent->child = (*p)->child;
					}
					else (*p)->left->right = (*p)->child;
					if((*p)->right!=NULL) (*p)->right->left = (*p)->child;
					(*p)->child->parent = (*p)->parent;
					(*p)->child->parent->child = NULL;
					(*p) = (*p)->child;
				}
				else {
					//(*p)->child->parent->child = (*p)->child->right;
					//free((*p)->child->right);
					(*p)->child->left->right = (*p)->child->right;
					(*p)->child->right->left = (*p)->child->left;
					(*p)->child = (*p)->child->right;
				}
			} else (*p)->child = (*p)->child->right;
		}
			if(isNotUseful((*p)->child->lexeme)) {
				if((*p)->child->left == NULL && (*p)->child->right!= NULL) {
					(*p)->child = (*p)->child->right;
					(*p)->child->left = NULL;
				}
				else if((*p)->child->left != NULL && (*p)->child->right== NULL) {
					(*p)->child = (*p)->child->left;
					(*p)->child->right = NULL;
				}
				else if((*p)->child->left == NULL && (*p)->child->right== NULL) {
					(*p)->child = (*p)->child->parent;
					free((*p)->child->parent->child);
					(*p)->child->parent->child = NULL;(*p)->child->right = (*p)->child->parent->right;
					(*p)->child->left = (*p)->child->parent->left;
					if((*p)->left==NULL){
						(*p)->parent->child = (*p)->child;
					}
					else (*p)->left->right = (*p)->child;
					if((*p)->right!=NULL) (*p)->right->left = (*p)->child;
					(*p)->child->parent = (*p)->parent;
					(*p)->child->parent->child = NULL;
					(*p) = (*p)->child;
				}
				else {
					//(*p)->child->parent->child = (*p)->child->right;
					//free((*p)->child->right);
					(*p)->child->left->right = (*p)->child->right;
					(*p)->child->right->left = (*p)->child->left;
					(*p)->child = (*p)->child->right;
				}
			}
		while((*p)->child->left!=NULL) (*p)->child = (*p)->child->left; 
		if((*p)->left==NULL && (*p)->right==NULL) {
			
		}
	}
	createAST(&((*p)->child));
	createAST(&((*p)->right));
}
