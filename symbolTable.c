#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "symbolTable.h"
//function table
void createFT(parseTree *p, FT **head, char scope[30], int *flag, FT **temp, RT *recordT) {
	if(p==NULL) return;
	if(!strcmp(p->token,"TK_FUNID") && (p->right->child != NULL) && *flag == 0) {
		*temp = (FT*)malloc(sizeof(FT));
		strcpy((*temp)->name,p->right->lexeme);
		(*temp)->next = NULL;
		*flag = 1;
	}
	if(!strcmp(p->token,"TK_INPUT") && *flag == 1) {
		(*temp)->input = (parameter*)malloc(sizeof(parameter));
		*flag = 2;
	}
	if(!strcmp(p->token,"TK_ID") && *flag == 2) {
		strcpy((*temp)->input->id,p->lexeme);
		(*temp)->input->next = NULL;
		if(!strcmp(p->left->child->token,"TK_INT")||!strcmp(p->left->child->token,"TK_REAL"))
			strcpy((*temp)->input->type,p->left->child->lexeme);
		else if(!strcmp(p->left->child->token,"TK_RECORD")) {
			RT *currRT = recordT;
			while(currRT!=NULL) {
				if(!strcmp(p->left->child->right->lexeme,currRT->name)) {
					strcpy((*temp)->input->type,currRT->ftype);
					break;
				}
				currRT=currRT->next;
			}
		}
	}
	if(!strcmp(p->token,"TK_OUTPUT") && *flag == 2) {
		(*temp)->output = (parameter*)malloc(sizeof(parameter));
		*flag = 3;
	}
	if(!strcmp(p->token,"TK_ID") && *flag == 3) {
		strcpy((*temp)->output->id,p->lexeme);
		(*temp)->output->next = NULL;
		if(!strcmp(p->left->child->token,"TK_INT")||!strcmp(p->left->child->token,"TK_REAL"))
			strcpy((*temp)->output->type,p->left->child->lexeme);
		else if(!strcmp(p->left->child->token,"TK_RECORD")) {
			RT *currRT = recordT;
			while(currRT!=NULL) {
				if(!strcmp(p->left->child->right->lexeme,currRT->name)) {
					strcpy((*temp)->output->type,currRT->ftype);
					break;
				}
				currRT=currRT->next;
			}
		}
		*flag = 3;
	}
	createFT(p->child, head, scope, flag, temp, recordT);
	createFT(p->right, head, scope, flag, temp, recordT);
}

//record table
void createRT(parseTree *p, RT **head, char scope[30], int *flag, RT **temp, record **tmp) {
	if(p==NULL) return;
	if(!strcmp(p->token,"TK_RECORD") && (p->right->right != NULL) && *flag == 0) {
		*temp = (RT*)malloc(sizeof(RT));
		strcpy((*temp)->name,p->right->lexeme);
		(*temp)->offset = 0;
		(*temp)->next = NULL;
		*flag = 1;
	}
	if((!strcmp(p->token,"TK_INT")||!strcmp(p->token,"TK_REAL")) && *flag == 1) {
		*tmp = (record*)malloc(sizeof(record));
		strcpy((*tmp)->type,p->lexeme);
		strcpy((*tmp)->id,p->parent->right->right->lexeme);
		//printf("@@@@@%s\n", (*tmp)->id);
		(*tmp)->next = NULL;
		(*tmp)->prev = NULL;
		if((*temp)->detail==NULL) {
			(*temp)->detail = *tmp;
		} else {
			record *curr;
			curr = (*temp)->detail;
			while(curr->next != NULL) {
				curr = curr->next;
			}
			curr->next = *tmp;
			(*tmp)->prev = curr;
		}
	}
	if(!strcmp(p->token,"TK_ENDRECORD") && *flag == 1) {
		RT *currr;
		currr = *temp;
		strcpy(currr->ftype,"");
		while(currr->detail->next!=NULL) {
			//printf("++++++++%s\n", currr->detail->id);
			strcat(currr->ftype,"*");
			currr->offset = (!strcmp(currr->detail->type, "int")) ? currr->offset + 2 : currr->offset + 4;
			strcat(currr->ftype,currr->detail->type);
			currr->detail = currr->detail->next;
		}
		//printf("++++++++%s\n", currr->detail->id);
		strcat(currr->ftype,"*");
		currr->offset = (!strcmp(currr->detail->type, "int")) ? currr->offset + 2 : currr->offset + 4;
		strcat(currr->ftype,currr->detail->type);
		while(currr->detail->prev != NULL) {
			//printf("1\n");
			currr->detail = currr->detail->prev;
			//printf("1\n");
		}
		if(*head==NULL) {
			*head = *temp;
		} else {
			RT *currrr;
			currrr = *head;
			while(currrr->next != NULL) {
				currrr = currrr->next;
			}
			currrr->next = *temp;
		}
		*flag = 0;
	}
	createRT(p->child, head, scope, flag, temp, tmp);
	createRT(p->right, head, scope, flag, temp, tmp);
}
void printRT(RT *head) {
	printf("Printing Record Table\n");
	if(head == NULL) {
		printf(": Error.\n");
		return;
	}
	RT* curr = head;
	while(curr != NULL) {
		printf("%s: %s: %d\n", curr->name, curr->ftype, curr->offset);
		//printf("&&&&&\n");
		while(curr->detail!=NULL) {
			printf("Records: %s: %s\n", curr->detail->id, curr->detail->type);
			curr->detail = curr->detail->next;
		}
		curr = curr->next;
	}
}

//symbol table
void createST(parseTree *p, ST **head, char scope[30], int *flag, ST **temp, RT *recordT) {
	if(p==NULL) return;
	if(!strcmp(p->token,"TK_FUNID")||!strcmp(p->token,"TK_MAIN")) {
		strcpy(scope, p->lexeme);
	}
	//for record
	if(!strcmp(p->token,"TK_RECORD") && *flag == 0 && p->right->right == NULL) {
		*temp = (ST*)malloc(sizeof(ST));
		strcpy((*temp)->scope,scope);
		(*temp)->line = p->line;
		*flag = 1;
	}
	if(!strcmp(p->token,"TK_RECORDID") && *flag==1) {
		RT *currRT = recordT;
		//printf("RRRRRRRRR: %s\n", p->lexeme);
		strcpy((*temp)->ifRecord, p->lexeme);
		while(currRT!=NULL) {
			if(!strcmp(p->lexeme,currRT->name)) {
				strcpy((*temp)->type,currRT->ftype);
				(*temp)->add2next = currRT->offset;
				break;
			}
			currRT=currRT->next;
		}
		*flag = 3;
	}
	if(!strcmp(p->token,"TK_ENDRECORD")) *flag = 0;
	//for int and real with global
	if((!strcmp(p->token,"TK_INT")||!strcmp(p->token,"TK_REAL")) && *flag == 0) {
		*temp = (ST*)malloc(sizeof(ST));
		strcpy((*temp)->type,p->lexeme);
		strcpy((*temp)->scope,scope);
		strcpy((*temp)->ifRecord, " ");
		(*temp)->add2next = (!strcmp(p->token,"TK_INT")) ? 2 : 4;
		(*temp)->line = p->line;
		*flag = 3;
	}
	//real int record id
	if(!strcmp(p->token,"TK_ID") && *flag == 3) {
		strcpy((*temp)->id,p->lexeme);
		static int offset, curr_off;
		if(*head==NULL) {
			(*temp)->offset = 0;
			*head = *temp;
			//printf("IN HEAD: %20s %20s %20s %3d %2d\n", (*temp)->id, (*temp)->type, (*temp)->scope, (*temp)->offset, (*temp)->add2next);
		} else {
			ST *curr;
			curr = *head;
			//offset
			while(curr->next != NULL) {
				if(!strcmp(curr->scope,scope))
					curr_off = curr->offset + curr->add2next;
				else if(!strcmp(curr->scope,"global"));
				else
					curr_off = 0;
				curr = curr->next;
			}
			if(!strcmp(curr->scope,scope))
				curr_off = curr->offset + curr->add2next;
			else if(!strcmp(curr->scope,"global"));
			else
				curr_off = 0;
			//endof_offset
			//check for global ********* change if change in parse tree
			if(strcmp(p->right->child->token,"EPSILON") && !strcmp(p->right->child->right->token,"TK_GLOBAL")) {
				offset = -1;
				strcpy((*temp)->scope,"global");
			} else {
				offset = curr_off;
			}
			(*temp)->offset = offset;
			(*temp)->next = NULL;
			//check for duplicates
			ST *dup = *head;
			static int f;
			f = 0;
			while(dup!=NULL) {
				if(!strcmp(dup->id,(*temp)->id)) {
					f = 1;
					printf("ERROR(redeclared): %10s %10s %10s %3d %2d\n", (*temp)->id, (*temp)->type, (*temp)->scope, (*temp)->offset, (*temp)->add2next);
				}
				dup = dup->next;
			}
			if(f==0) {
				curr->next = *temp;
				//printf("IN ELSE: %20s %20s %20s %3d %2d\n", (*temp)->id, (*temp)->type, (*temp)->scope, (*temp)->offset, (*temp)->add2next);
			} else curr->next = NULL;
		}
		*flag = 0;
	}
	createST(p->child, head, scope, flag, temp, recordT);
	
	createST(p->right, head, scope, flag, temp, recordT);
}
void printST(ST *head) {
	printf("Printing Symbol Table\n");
	if(head == NULL) {
		printf(" :Error.\n");
		return;
	}
	ST *curr = head;
	printf("%20s %20s %20s %s\n", "LEXEME", "TYPE", "SCOPE", "offset");
	while(curr!=NULL) {
		printf("%20s %20s %20s %3d\n", curr->id, curr->type, curr->scope, curr->offset);
		curr = curr->next;
	}
}
