#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VAR_COUNT 100
#define MAX_VAR_NAME_LEN 32

enum operation {
	READ,
	WRITE,
	ADD,
	SUBTRACT,
	ASSIGMENT,
	EQUAL,
	MORE,
	LESS
};

typedef struct {
	char name[MAX_VAR_NAME_LEN];
	int value;
}intv;

intv vars[MAX_VAR_COUNT];//стурктура хранения переменных

char str[100]; //текущая строка для разбора

char whstr[100];//строка для проверки while/if

char script_file[100];//хранит файл скрипта

int check;//0-if, 1-while

FILE *f;//поток из файла скрипта

FILE *wh;//для считывания while

FILE *ff;//для if в while

void make_operation(int op);

void read(char *name, intv *v);

int find_var(char *name);

int make_var(char *name);

void fixEndStr();

int arith(int *a);

void make_if();

int *get_ops();

void make_while(int op);
