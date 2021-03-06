#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <malloc.h>


typedef struct list
{
	struct list *prev;
	struct list *next;
	void *data;
} list, *plist;


int initlist(plist list);

int list_length(plist list);

void *get_data(plist list, int i);

int insert_data(plist list, int i, void *ins);

int delete_data(plist list, int i);

void free_node(plist node);

void free_list(plist list);

void *sort_list(plist list);

int cmp_char(const void *a, const void *b);

#endif
