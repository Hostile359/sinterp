#include "lex.h"
#include "func.h"

void lex()
{
	char *tok;
	if ((tok = strstr(str, "if")) != NULL) {
		removeOperation(tok, 3);
		if((tok = strstr(str, " then")) != NULL) {
			removeOperation(tok, 5);
			if((tok = strstr(str, "==")) != NULL) {
				removeOperation(tok, 3);
				check = 0;
				make_operation(EQUAL);
			}
			if((tok = strstr(str, ">")) != NULL) {
				removeOperation(tok, 2);
				check = 0;
				make_operation(MORE);
			}
			if((tok = strstr(str, "<")) != NULL) {
				removeOperation(tok, 2);
				check = 0;
				make_operation(LESS);
			}
		}
		return;
	}
	if ((tok = strstr(str, "while")) != NULL) {
		removeOperation(tok, 6);
		if((tok = strstr(str, " do")) != NULL) {
			removeOperation(tok, 3);
			if((tok = strstr(str, "==")) != NULL) {
				removeOperation(tok, 3);
				check = 1;
				make_operation(EQUAL);
			}
			if((tok = strstr(str, ">")) != NULL) {
				removeOperation(tok, 2);
				check = 1;
				make_operation(MORE);
			}
			if((tok = strstr(str, "<")) != NULL) {
				removeOperation(tok, 2);
				check = 1;
				make_operation(LESS);
			}
		}
		return;
	}
	if ((tok = strstr(str, "read")) != NULL) {
		removeOperation(tok, 4);
		make_operation(READ);
		return;
	}
	if ((tok = strstr(str, "write")) != NULL) {
		removeOperation(tok, 5);
		make_operation(WRITE);
		return;
	}
	if ((tok = strstr(str, "+")) != NULL) {
		removeOperation(tok, 2);
		tok = strstr(str, "=");
		removeOperation(tok, 2);
		make_operation(ADD);
		return;
	}
	if ((tok = strstr(str, "-")) != NULL) {
		removeOperation(tok, 2);
		tok = strstr(str, "=");
		removeOperation(tok, 2);
		make_operation(SUBTRACT);
		return;
	}
	if ((tok = strstr(str, "=")) != NULL) {
		removeOperation(tok, 2);
		make_operation(ASSIGMENT);
		return;
	}
}

void removeOperation(char *p, int lenght)
{
	for(int i = 0; i < lenght; i++)
	{
		p[i] = ' ';
	}
}
