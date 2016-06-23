#include<stdio.h>
#include<string.h>

void foo(char s[20]) {
	strcpy(s,"BOO");
}

int main() {
	char s1[20];
	foo(s1);
	printf("%s", s1);
	return 0;
}

/*
******working for int and real without global declaration*********
void createST(parseTree *p, ST **head, char scope[20], int *flag, ST **temp) {
	if(p==NULL) return;
	printf("*********%s: %d\n", p->token, *flag);
	if(!strcmp(p->token,"TK_FUNID")||!strcmp(p->token,"TK_MAIN")) {
		strcpy(scope, p->lexeme);
	}
	if((!strcmp(p->token,"TK_INT")||!strcmp(p->token,"TK_REAL")) && *flag == 0) {
		*temp = (ST*)malloc(sizeof(ST));
		printf("node created: %s\n", scope);
		strcpy((*temp)->type,p->lexeme);
		strcpy((*temp)->scope,scope);
		//temp->line = p->line;
		*flag = 1;
	}
	if(!strcmp(p->token,"TK_ID") && *flag == 1) {
		strcpy((*temp)->id,p->lexeme);
		printf("%s: here\n", p->token);
		static int offset;
		if(*head==NULL) {
			printf("FUCKYOU\n");
			(*temp)->offset = 0;
			(*temp)->next = NULL;
			*head = *temp;
		} else {
			printf("FUCKYOU2\n");
			ST *curr;
			curr = *head;
			while(curr->next != NULL) {
				curr = curr->next;
			}
			if(!strcmp(curr->scope,scope))
				offset = (!strcmp(curr->type, "int")) ? offset + 2 : offset + 4;
			else
				offset = 0;
			(*temp)->offset = offset;
			(*temp)->next = NULL;
			curr->next = *temp;
		}
		printf("YOLO\n");
		*flag = 0;
	}
	createST(p->child, head, scope, flag, temp);
	
	createST(p->right, head, scope, flag, temp);
}
*/
