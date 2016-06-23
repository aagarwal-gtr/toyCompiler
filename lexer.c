/*
BATCH 46
MANAN KHASGIWALE (2013A7PS128P)
ABHINAV AGARWAL (2013A7PS124P)
*/
#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lexerDef.h"

char* substr(char string[], int lpos, int len) {
   int i = 0;
   char *sub = malloc(len*sizeof(char));
   while(i < len) {
      sub[i] = string[lpos+i];
      i++;
   }
   sub[i] = '\0';
   return sub;
}

FILE *getStream(FILE *fp, buffer B, buffersize k) {
	fgets(B, 1000, fp);
	return fp;
}

tokenInfo getNextToken(buffer B, FILE *ferr, int line, int *flag, int *pos) {
	int i, j, len;
	tokenInfo toko;
	len = strlen(B);
	while(1) {
		for(i = *pos; i < len; i++) {
			switch(B[i]) {
				case '%':
					strcpy(toko.lexeme, substr(B, i+1, len-(i+2)));
					strcpy(toko.token, "TK_COMMENT");
					toko.line = line;
					*flag = 1;
					i = -1;
					break;
				case '[':
					strcpy(toko.lexeme, "[");
					strcpy(toko.token, "TK_SQL");
					toko.line = line;
					break;
				case ']':
					strcpy(toko.lexeme, "]");
					strcpy(toko.token, "TK_SQR");
					toko.line = line;
					break;
				case ';':
					strcpy(toko.lexeme, ";");
					strcpy(toko.token, "TK_SEM");
					toko.line = line;
					break;
				case ',':
					strcpy(toko.lexeme, ",");
					strcpy(toko.token, "TK_COMMA");
					toko.line = line;
					break;
				case ':':
					strcpy(toko.lexeme, ":");
					strcpy(toko.token, "TK_COLON");
					toko.line = line;
					break;
				case '.':
					strcpy(toko.lexeme, ".");
					strcpy(toko.token, "TK_DOT");
					toko.line = line;
					break;
				case '(':
					strcpy(toko.lexeme, "(");
					strcpy(toko.token, "TK_OP");
					toko.line = line;
					break;
				case ')':
					strcpy(toko.lexeme, ")");
					strcpy(toko.token, "TK_CL");
					toko.line = line;
					break;
				case '+':
					strcpy(toko.lexeme, "+");
					strcpy(toko.token, "TK_PLUS");
					toko.line = line;
					break;
				case '-':
					strcpy(toko.lexeme, "-");
					strcpy(toko.token, "TK_MINUS");
					toko.line = line;
					break;
				case '*':
					strcpy(toko.lexeme, "*");
					strcpy(toko.token, "TK_MUL");
					toko.line = line;
					break;
				case '/':
					strcpy(toko.lexeme, "/");
					strcpy(toko.token, "TK_DIV");
					toko.line = line;
					break;
				case '~':
					strcpy(toko.lexeme, "~");
					strcpy(toko.token, "TK_NOT");
					toko.line = line;
					break;
				case '<':
					if(B[i+1] == '=') {
						strcpy(toko.lexeme, "<=");
						strcpy(toko.token, "TK_LE");
						toko.line = line;
						i++;
						break;
					}
					if(!strcmp(substr(B, i+1, 3), "---")){
						strcpy(toko.lexeme, "<---");
						strcpy(toko.token, "TK_ASSIGNOP");
						toko.line = line;
						i+=3;
						break;
					} else if(!strcmp(substr(B, i+1, 2), "--")){
						strcpy(toko.lexeme, "<--");
						strcpy(toko.token, "error");
						toko.line = line;
						fprintf(ferr,"ERROR_3:  Unknown pattern <%s> at line <%d>\n", toko.lexeme, line);
						i+=2;
						break;
					} else if(!strcmp(substr(B, i+1, 1), "-")){
						strcpy(toko.lexeme, "<-");
						strcpy(toko.token, "error");
						toko.line = line;
						fprintf(ferr,"ERROR_3:  Unknown pattern <%s> at line <%d>\n", toko.lexeme, line);
						i+=1;
						break;
					}
					strcpy(toko.lexeme, "<");
					strcpy(toko.token, "TK_LT");
					toko.line = line;
					break;
				case '>':
					if(B[i+1] == '=') {
						strcpy(toko.lexeme, ">=");
						strcpy(toko.token, "TK_GE");
						toko.line = line;
						i++;
						break;
					}
					strcpy(toko.lexeme, ">");
					strcpy(toko.token, "TK_GT");
					toko.line = line;
					break;
				case '=':
					if(B[i+1] == '=') {
						strcpy(toko.lexeme, "==");
						strcpy(toko.token, "TK_EQ");
						toko.line = line;
						i++;
						break;
					}
					strcpy(toko.lexeme, "=");
					strcpy(toko.token, "error");
					fprintf(ferr,"ERROR_3:  Unknown pattern <%s> at line <%d>\n", toko.lexeme, line);
					break;
				case '!':
					if(B[i+1] == '=') {
						strcpy(toko.lexeme, "!=");
						strcpy(toko.token, "TK_NE");
						toko.line = line;
						i++;
						break;
					}
					strcpy(toko.lexeme, "!");
					fprintf(ferr, "ERROR_3:  Unknown pattern <%s> at line <%d>\n", toko.lexeme, line);
					strcpy(toko.token, "error");
					toko.line = line;
					break;
				case '@':
					if(!strcmp(substr(B, i+1, 2), "@@")) {
						strcpy(toko.lexeme, "@@@");
						strcpy(toko.token, "TK_OR");
						toko.line = line;
						i+=2;
						break;
					}else if(!strcmp(substr(B, i+1, 1), "@")) {
						strcpy(toko.lexeme, "@@");
						strcpy(toko.token, "error");
						toko.line = line;
						fprintf(ferr, "ERROR_3:  Unknown pattern <%s> at line <%d>\n", toko.lexeme, line);
						i+=1;
						break;
					}
					strcpy(toko.lexeme, "@");
					fprintf(ferr, "ERROR_3:  Unknown pattern <%s> at line <%d>\n", toko.lexeme, line);
					strcpy(toko.token, "error");
					toko.line = line;
					break;
				case '&':
					if(!strcmp(substr(B, i+1, 2), "&&")) {
						strcpy(toko.lexeme, "&&&");
						strcpy(toko.token, "TK_AND");
						toko.line = line;
						i+=2;
						break;
					}else if(!strcmp(substr(B, i+1, 1), "&")) {
						strcpy(toko.lexeme, "&&");
						strcpy(toko.token, "error");
						toko.line = line;
						fprintf(ferr, "ERROR_3:  Unknown pattern <%s> at line <%d>\n", toko.lexeme, line);
						i+=1;
						break;
					}
					strcpy(toko.lexeme, "&");
					fprintf(ferr, "ERROR_3:  Unknown pattern <%s> at line <%d>\n", toko.lexeme, line);
					strcpy(toko.token, "error");
					toko.line = line;
					break;
				case '_':
					if(!strcmp(substr(B, i+1, 4), "main") && (B[i+5] == ' ' || B[i+5] == '\n' || B[i+5] == '\r')) {
						strcpy(toko.lexeme, "_main");
						strcpy(toko.token, "TK_MAIN");
						toko.line = line;
						i+=4;
						break;
					}
					toko.lexeme[0] = '_';
					toko.lexeme[1] = '\0';
					j=i+1;
					if((B[j] >= 'A' && B[j] <= 'Z') || (B[j] >= 'a' && B[j] <= 'z')) {
						toko.lexeme[j-i] = B[j];
						toko.lexeme[j-i+1] = '\0';
						j++;
					} else {
						fprintf(ferr, "ERROR_3:  Unknown pattern <%s> at line <%d>\n", toko.lexeme, line);
						strcpy(toko.token, "error");
						break;
					}
					while((B[j] >= 'A' && B[j] <= 'Z') || (B[j] >= 'a' && B[j] <= 'z') || (B[j] >= '0' && B[j] <= '9')) {
						toko.lexeme[j-i] = B[j];
						toko.lexeme[j-i+1] = '\0';
						j++;
					}
					if(strlen(toko.lexeme) > 30)
						fprintf(ferr, "ERROR_1: Identifier at line <%d> is longer than the prescribed length of 20 characters\n", line);
					toko.lexeme[j-i] = '\0';
					strcpy(toko.token, "TK_FUNID");
					toko.line = line;
					i = j - 1;
					break;
				case '#':
					toko.lexeme[0] = '#';
					toko.lexeme[1] = '\0';
					j = i + 1;
					if(B[j] >= 'a' && B[j] <= 'z') {
						toko.lexeme[j-i] = B[j];
						toko.lexeme[j-i+1] = '\0';
						j++;
					} else {
						fprintf(ferr, "ERROR_3:  Unknown pattern <%s> at line <%d>\n", toko.lexeme, line);
						strcpy(toko.token, "error");
						break;
					}
					while(B[j] >= 'a' && B[j] <= 'z') {
						toko.lexeme[j-i] = B[j];
						toko.lexeme[j-i+1] = '\0';
						j++;
					}
					if(strlen(toko.lexeme) > 20)
						fprintf(ferr, "ERROR_1: Identifier at line <%d> is longer than the prescribed length of 20 characters\n", line);
					strcpy(toko.token, "TK_RECORDID");
					toko.line = line;
					i = j - 1;
					break;

				case 'b':
				case 'c':
					if(!strcmp(substr(B, i, 4), "call")) {
						strcpy(toko.lexeme, "call");
						strcpy(toko.token, "TK_CALL");
						toko.line = line;
						i = i + 3;
						break;
					}
				case 'd':
					toko.lexeme[0] = B[i];
					j = i+1;
					if(B[j] >= '2' && B[j] <= '7') {
						toko.lexeme[j-i] = B[j];
						toko.lexeme[j-i+1] = '\0';
						j++;
					} else if (B[j] >= 'a'&& B[j] <= 'z'){
						while(B[j] >= 'a'&& B[j] <= 'z') {
							toko.lexeme[j-i] = B[j];
							toko.lexeme[j-i+1] = '\0';
							j++;
						}
                        strcpy(toko.token, "TK_FIELDID");
						toko.line = line;
						i = j - 1;
						break;
					} else {
						toko.lexeme[j-i] = B[j];
						toko.lexeme[j-i+1] = '\0';
						fprintf(ferr, "ERROR_3:  Unknown pattern <%s> at line <%d>\n", toko.lexeme, line);
						strcpy(toko.token, "error");
						i = j;
						break;
					}
					while(B[j] >= 'b' && B[j] <= 'd') {
						toko.lexeme[j-i] = B[j];
						toko.lexeme[j-i+1] = '\0';
						j++;
					}
					while(B[j] >= '2' && B[j] <= '7') {
						toko.lexeme[j-i] = B[j];
						toko.lexeme[j-i+1] = '\0';
						j++;
					}
					if(strlen(toko.lexeme) > 20)
						fprintf(ferr, "ERROR_1: Identifier at line <%d> is longer than the prescribed length of 20 characters\n", line);
					strcpy(toko.token, "TK_ID");
					toko.line = line;
					i = j - 1;
					break;

				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					toko.lexeme[0] = B[i];
					toko.lexeme[1] = '\0';
					j = i + 1;
					strcpy(toko.token, "TK_NUM");
					while((B[j] >= '0' && B[j] <= '9') || B[j] == '.') {
						if(B[j] == '.' && (B[j+1] >= '0' && B[j+1] <= '9') && (B[j+2] >= '0' && B[j+2] <= '9')) {
							strcpy(toko.token, "TK_RNUM");
							toko.lexeme[j-i] = B[j];
							toko.lexeme[j-i+1] = B[j+1];
							toko.lexeme[j-i+2] = B[j+2];
							toko.lexeme[j-i+3] = '\0';
							j+=3;
							break;
						} else if(B[j] == '.') {
							strcpy(toko.token, "error");
							toko.lexeme[j-i] = B[j];
							while(B[j+1] >= '0' && B[j+1] <= '9') {
								j++;
								toko.lexeme[j-i] = B[j];
							}
							j++;				
							toko.lexeme[j-i] = '\0';
							fprintf(ferr, "ERROR_3:  Unknown pattern <%s> at line <%d>\n", toko.lexeme, line);
							break;
						}
						toko.lexeme[j-i] = B[j];
						toko.lexeme[j-i+1] = '\0';
						j++;
					}
					toko.line = line;
					i = j - 1;
					break;

				case 'q':
				case 'w':
				case 'e':
				case 'r':
				case 't':
				case 'y':
				case 'u':
				case 'i':
				case 'o':
				case 'p':
				case 'a':
				case 's':
				//case 'd':
				case 'f':
				case 'g':
				case 'h':
				case 'j':
				case 'k':
				case 'l':
				case 'z':
				case 'x':
				//case 'c':
				case 'v':
				//case 'b':
				case 'n':
				case 'm':
					j = i;
					if(!strcmp(substr(B, j, 4), "with")) {
						strcpy(toko.lexeme, "with");
						strcpy(toko.token, "TK_WITH");
						toko.line = line;
						i = j + 3;
					} else if(!strcmp(substr(B, j, 10), "parameters")) {
						strcpy(toko.lexeme, "parameters");
						strcpy(toko.token, "TK_PARAMETERS");
						toko.line = line;
						i = j + 9;
					} else if(!strcmp(substr(B, j, 3), "int")) {
						strcpy(toko.lexeme, "int");
						strcpy(toko.token, "TK_INT");
						toko.line = line;
						i = j + 3;
					} else if(!strcmp(substr(B, j, 4), "real")) {
						strcpy(toko.lexeme, "real");
						strcpy(toko.token, "TK_REAL");
						toko.line = line;
						i = j + 3;
					} else if(!strcmp(substr(B, j, 4), "type")) {
						strcpy(toko.lexeme, "type");
						strcpy(toko.token, "TK_TYPE");
						toko.line = line;
						i = j + 3;
					} else if(!strcmp(substr(B, j, 6), "global")) {
						strcpy(toko.lexeme, "global");
						strcpy(toko.token, "TK_GLOBAL");
						toko.line = line;
						i = j + 5;
					} else if(!strcmp(substr(B, j, 9), "parameter")) {
						strcpy(toko.lexeme, "parameter");
						strcpy(toko.token, "TK_PARAMETER");
						toko.line = line;
						i = j + 8;
					} else if(!strcmp(substr(B, j, 4), "list")) {
						strcpy(toko.lexeme, "list");
						strcpy(toko.token, "TK_LIST");
						toko.line = line;
						i = j + 3;
					} else if(!strcmp(substr(B, j, 5), "input")) {
						strcpy(toko.lexeme, "input");
						strcpy(toko.token, "TK_INPUT");
						toko.line = line;
						i = j + 4;
					} else if(!strcmp(substr(B, j, 6), "output")) {
						strcpy(toko.lexeme, "output");
						strcpy(toko.token, "TK_OUTPUT");
						toko.line = line;
						i = j + 5;
					} else if(!strcmp(substr(B, j, 8), "endwhile")) {
						strcpy(toko.lexeme, "endwhile");
						strcpy(toko.token, "TK_ENDWHILE");
						toko.line = line;
						i = j + 7;
					} else if(!strcmp(substr(B, j, 9), "endrecord")) {
						strcpy(toko.lexeme, "endrecord");
						strcpy(toko.token, "TK_ENDRECORD");
						toko.line = line;
						i=j + 8;
					} else if(!strcmp(substr(B, j, 5), "endif")) {
						strcpy(toko.lexeme, "endif");
						strcpy(toko.token, "TK_ENDIF");
						toko.line = line;
						i = j + 4;
					} else if(!strcmp(substr(B, j, 3), "end")) {
						strcpy(toko.lexeme, "end");
						strcpy(toko.token, "TK_END");
						toko.line = line;
						i = j + 2;
					} else if(!strcmp(substr(B, j, 5), "while")) {
						strcpy(toko.lexeme, "while");
						strcpy(toko.token, "TK_WHILE");
						toko.line = line;
						i = j + 4;
					} else if(!strcmp(substr(B, j, 2), "if")) {
						strcpy(toko.lexeme, "if");
						strcpy(toko.token, "TK_IF");
						toko.line = line;
						i = j + 1;
					} else if(!strcmp(substr(B, j, 4), "then")) {
						strcpy(toko.lexeme, "then");
						strcpy(toko.token, "TK_THEN");
						toko.line = line;
						i = j + 3;
					} else if(!strcmp(substr(B, j, 4), "read")) {
						strcpy(toko.lexeme, "read");
						strcpy(toko.token, "TK_READ");
						toko.line = line;
						i = j + 3;
					} else if(!strcmp(substr(B, j, 5), "write")) {
						strcpy(toko.lexeme, "write");
						strcpy(toko.token, "TK_WRITE");
						toko.line = line;
						i = j + 4;
					} else if(!strcmp(substr(B, j, 6), "return")) {
						strcpy(toko.lexeme, "return");
						strcpy(toko.token, "TK_RETURN");
						toko.line = line;
						i = j + 5;
					} else if(!strcmp(substr(B, j, 6), "record")) {
						strcpy(toko.lexeme, "record");
						strcpy(toko.token, "TK_RECORD");
						toko.line = line;
						i = j + 5;
					} else if(!strcmp(substr(B, j, 4), "else")) {
						strcpy(toko.lexeme, "else");
						strcpy(toko.token, "TK_ELSE");
						toko.line = line;
						i=j + 3;
					} else {
						while(B[j] >= 'a' && B[j] <= 'z') {
							toko.lexeme[j-i] = B[j];
							toko.lexeme[j-i+1] = '\0';
							j++;
						}
                        strcpy(toko.token, "TK_FIELDID");
						toko.line = line;
						i = j - 1;
					}
					if(strlen(toko.lexeme) > 20)
						fprintf(ferr, "ERROR_1: Identifier at line <%d> is longer than the prescribed length of 20 characters\n", line);
				break;

				case '\0':
				case '\n':
				case '\r':
					*flag = 1;
					i = -1;
				case ' ':
				case '\t':
					strcpy(toko.lexeme, "EMPTY");
					strcpy(toko.token, "EMPTY");
					toko.line = -1;
					break;
				default:
					fprintf(ferr, "ERROR_2: Unknown Symbol <%c> at line <%d>\n", B[i], line);
					strcpy(toko.lexeme, "q");
					strcpy(toko.token, "q");
					toko.line = -1;
					break;
			}//endswitch
			*pos = i + 1;
			return toko;
		}//endfor
	}//endwhile
}
