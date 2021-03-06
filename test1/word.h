#ifndef WORD_H
#define WORD_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define MAXLENGTH 50

typedef struct struct_word {
	char word[MAXLENGTH];
	int freq;
} str_word, *str_pword;

void sys_init(void);

char read_word(FILE *fp, char *str);

int list_binsrch(plist list, char *data);

void add_to_list(FILE *fp);

void sort_byfreq(void);

void printf_word(int percent, char **str);

#endif
