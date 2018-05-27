#include "func.h"
#include "lex.h"

void make_operation(int op)
{
	switch (op) {
		case READ: {
			fixEndStr();
			char *vtok;
			vtok = strtok(str, " ");
			int i = find_var(vtok);
			if (i == -1)
				i = make_var(vtok);
			read(vtok, &vars[i]);
			break; 
		}
		case WRITE: {
			fixEndStr();
			char *vtok;
			vtok = strtok(str, " ");
			int i = find_var(vtok);
			printf("%s: %d\n", &vars[i].name[0], vars[i].value);
			break; 
		}
		case ADD: {
			fixEndStr();
			int *a, i;
			a = (int*)malloc(2 * sizeof(int));
			i = arith(a);
			vars[i].value = a[0] + a[1];
			free(a);
			break;			
		}
		case SUBTRACT: {
			fixEndStr();
			int *a, i;
			a = (int*)malloc(2 * sizeof(int));
			i = arith(a);
			vars[i].value = a[0] - a[1];
			free(a);
			break;			
		}
		case ASSIGMENT: {
			fixEndStr();
			char *vtok;
			vtok = strtok(str, " ");
			int i = find_var(vtok);
			if (i == -1)
				i = make_var(vtok);
			vtok = strtok(NULL, " ");
			int a;
			if((a = atoi(vtok)) == 0) {
				int j = find_var(vtok);
				a = vars[j].value;
			}
			vars[i].value = a;
			break; 
		}
		case EQUAL: {
			if(wh != NULL)
				ff = wh;
			else
				ff = f;
			strcpy(whstr, str);
			int *a = NULL;
			a = get_ops();
			if (a[0] == a[1]) {
				switch (check) {
					case 0: {
						make_if();
						while(strstr(str, "fi") == NULL)
							fgets(str, 100, ff);
						break;
					}
					case 1: {
						make_while(EQUAL);
						break;
					}	
				}
			}else {
				while(1) {
					fgets(str, 100, ff);
					if (strstr(str, "else") != NULL) {
						make_if();
						break;
					}
					if (strstr(str, "fi") != NULL)
						break;
					if (strstr(str, "done") != NULL)
						break;
				}
			}
			free(a);
			break; 
		}
		case MORE: {
			if(wh != NULL)
				ff = wh;
			else
				ff = f;
			strcpy(whstr, str);
			int *a = NULL;
			a = get_ops();
			if (a[0] > a[1]) {
				switch (check) {
					case 0: {
						make_if();
						while(strstr(str, "fi") == NULL)
							fgets(str, 100, ff);
						break;
					}
					case 1: {
						make_while(MORE);
						break;
					}
				}
			}else {
				while(1) {
					fgets(str, 100, ff);
					if (strstr(str, "else") != NULL) {
						make_if();
						break;
					}
					if (strstr(str, "fi") != NULL)
						break;
					if (strstr(str, "done") != NULL)
						break;
				}
			}	
			free(a);
			break;
		}
		case LESS: {
			if(wh != NULL)
				ff = wh;
			else
				ff = f;
			strcpy(whstr, str);
			int *a = NULL;
			a = get_ops();
			if (a[0] < a[1]) {
				switch (check) {
					case 0: {
						make_if();
						while(strstr(str, "fi") == NULL)
							fgets(str, 100, ff);
						break;
					}
					case 1: {
						make_while(LESS);
						break;
					}
				}
			}else {
				while(1) {
					fgets(str, 100, ff);
					if (strstr(str, "else") != NULL) {
						make_if();
						break;
					}
					if (strstr(str, "fi") != NULL)
						break;
					if (strstr(str, "done") != NULL)
						break;
				}
			}
			free(a);	
			break; 
		}
	}
}

void read(char *name, intv *v)
{
	scanf("%d", &v->value);
	strcpy(v->name, name);
	return;
}

int find_var(char *name)
{
	for(int index = 0; index < MAX_VAR_COUNT; index++) {
		if(strcmp(vars[index].name, name) == 0)
			return index;
	}
	return -1;
}

int make_var(char *name)
{
	int index = 0;
	while(vars[index].name[0] != '\0')
		index++;
	strcpy(&vars[index].name[0], name);;
	return index;
}

void fixEndStr()
{
	if(strcmp(&str[strlen(str)-1], "\n") == 0)
		strcpy(&str[strlen(str)-1],"\0");
}

int arith(int *a)
{
	char *vtok;
	vtok = strtok(str, " ");
	int i = find_var(vtok);
	if (i == -1)
		i = make_var(vtok);
	int k = 0;
	while(k < 2) {//вычисление левого и правого операндов, хранящихся в массиве a
		vtok = strtok(NULL, " ");
		if((a[k] = atoi(vtok)) == 0) {
			int j = find_var(vtok);
			a[k] = vars[j].value;
		}
		k++;
	}
	return i;//i - индекс переменной, которой присваивается значение
}

void make_if()
{
	while(1) {
		fgets(str, 100, ff);
		if (strstr(str, "else") != NULL)
			break;
		if (strstr(str, "fi") != NULL)
			break;
		lex();
	}
	return;
}

int *get_ops()
{
	strcpy(str, whstr);
	int *arr;
	arr = (int*)malloc(2 * sizeof(int));
	char *vtok;
	vtok = strtok(str, " ");
	if((arr[0] = atoi(vtok)) == 0) {
		int j = find_var(vtok);
		arr[0] = vars[j].value;
	}
	vtok = strtok(NULL, " ");
	if((arr[1] = atoi(vtok)) == 0) {
		int j = find_var(vtok);
		arr[1] = vars[j].value;
	}
	return arr;
}

void make_while(int op)
{
	int k = 0;
	while(k != 1) {
		wh = fopen(script_file, "r");
		while(strstr(fgets(str, 100, wh), "while") == NULL)
			continue;
		char *tok;
		if ((tok = strstr(str, "while")) != NULL) {
			removeOperation(tok, 6);
			if((tok = strstr(str, " do")) != NULL) {
				removeOperation(tok, 3);
				if((tok = strstr(str, "==")) != NULL) {
					removeOperation(tok, 3);
				}
				if((tok = strstr(str, ">")) != NULL) {
					removeOperation(tok, 2);
				}
				if((tok = strstr(str, "<")) != NULL) {
					removeOperation(tok, 2);
				}
			}
		}
		int *a = NULL;
		a = get_ops();
		switch(op) {
			case EQUAL: {
				if(!(a[0] == a[1]))
					k = 1;
				break;
			}
			case MORE: {
				if(!(a[0] > a[1]))
					k = 1;
				break;
			}
			case LESS: {
				if(!(a[0] < a[1]))
					k = 1;
				break;
			}
		}
		while(k != 1) {
			fgets(str, 100, wh);
			if (strstr(str, "done") != NULL) {
				break;
			}
			lex();
		}
		fclose(wh);
	}
	while(1) {
		fgets(str, 100, f);
		if (strstr(str, "done") != NULL)
			break;
	}
	return;
}
