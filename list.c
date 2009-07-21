/************  list.c  **************/

#include "list.h"

//链表初始化
int initlist(plist list)
{
	list->prev = list;
	list->next = list;
}

//计算链表节点总数
int list_length(plist list)
{
	int i = 1;
	plist p;

	p = list;
	
	while(p && p->next && p->next != list)
	{
		p = p->next;
		i++;
	}
	
	return i;
}


/****************************************
在列表中查找第i个节点的数据
*****************************************/
void *get_data(plist list, int i)
{
	plist p;
	int j;
	p = list;

	/************
	j = list_length(list);
	if(i > j)
	{
		printf("error i.Can't big than "
		       "the length of list.\n");
		return 0;
	}
	**************/
	j = 1;
	while(p && j < i)
        {
		//  printf("%d\t%s\n", j, p->data);
		p = p->next;
		j++;
	}
	/********
	if(!p || j > i)
	{
		printf("error read data\n");
	}
	***********/

	return p->data;
}


/*********************************************
在第i个结点之后插入一个节点
*********************************************/
int insert_data(plist list, int i, void *ins)
{
  
	plist s;
	plist p = list;
	int j;

	/*************
	j = list_length(list);
	if(i > j)
	{
		printf("error i.Can't big than "
		       "the length of list.\n");
		return 0;
	}
	*******************/
	
	j = 1;
	while (p && j < i)
	{
		p = p->next;
		j++;
	}

	if (!p || j < i)
	{
		printf("error");
		return 0;
	}

	s = (plist) malloc(sizeof(list));
	
	s->data = ins;
	s->next = p->next;
	s->prev = p;
	p->next->prev = s;
	p->next = s;

	//	printf("insert_data_is_ok\n");

	return 1;
  
}

/**************************************
删除一个结点,删除后该节点仍然存在可以访问
**************************************/
int delete_data(plist list, int i)
{
	plist p = list;
	int j;

	j = list_length(list);
	if(i > j)
	{
		printf("error i.Can't big than "
		       "the length of list");
		return 0;
	}
	
	j = 1;
	if(i == 1)
		printf("please be carefule when delete head node, "
		       "it may cause the index lost of list\n");

	while(p->next && j < i)
        {
		p = p->next;
		j++;
	}

	if(!(p->next) || j > i)
        {
		printf("error");
		return 0;
	}

	p->prev->next = p->next;
	p->next->prev = p->prev;
	p->next = NULL;            //避免计算已删除结点
	p->prev = NULL;            //长度时出现无穷大
	
	printf("delete success\n");

	return 1;
}

//释放删除节点的内存
void free_node(plist node)
{
	free(node->data);
	free(node);
}

//删除整个链表并释放链表内存
void free_list(plist list)
{
	plist p = list;

	p = p->next;
	while(p != list)
	{
		p = p->next;
		free_node(p->prev);
	}
}


/************************************

************************************/
void *sort_list(plist list)
{
	plist p = list;
	char **p_data;
	char *temp;
	int i,j;

	printf("仅对字符串进行排序， "
	       "数字转化成字符串排序"
	       "链表中若包含其他类型如结构体会导致出错\n");

	for(i = 0; i < list_length(list); i++)
        {
	        *p_data = get_data(list,i + 1);
		printf("sort %s\n", *p_data);
		p_data++;
	
	}
	
	p_data = p_data - i;
	//list->data = *(p_data + 1);
	//list->next->data = *(p_data + 3);
	/***********
	for(i = 0; i < list_length(list) - 1; i++)
	{
		for(j = 0; j <= list_length(list) - 2;j++)
		{
			if(strcmp(*(p_data + j), 
				  *(p_data + j + 1)))
				{
					*temp = (p_data+j);
				        *(p_data +j+1) = *(p_data+j);
					*(p_data+j) = temp;
				}
	      	}
	}

	****************/
	{
		*temp = *(p_data+1);
		*(p_data + 2) = *(p_data + 1);
		*(p_data + 1) = *temp;
		
	}

	/*********	
	p = list;
	for(i = 0; i < list_length(list); i++)
        {
	        p->data = *(p_data + i);
		p = p->next;
		p_data++;
	}
	************/
	
}
