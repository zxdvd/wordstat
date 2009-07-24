#include "word.h"

list word_list[2];
plist current_list;
plist index_list[27];
int flag_rep = 0;
int case_flag;

void sys_init(void)

{
	int i;
	str_pword pword;

	initlist(&word_list[0]);
	word_list[0].data = 0;
	current_list = (plist) malloc(sizeof(list));

	index_list[0] = (plist) malloc(sizeof(list));
	pword=(str_pword)malloc(sizeof(str_word));
	pword->freq = 0;
	pword->word[0] = 'a' + i;
	pword->word[1] = '\0';
	insert_data(&word_list[0], i + 1,pword);
	index_list[0] = &word_list[0];
	index_list[0] = index_list[0]->next;

	for(i = 1; i < 27;i++){
		index_list[i] = (plist) malloc(sizeof(list));
		pword=(str_pword)malloc(sizeof(str_word));
		pword->freq = 0;
		pword->word[0] = 'a' + i;
		pword->word[1] = '\0';
		insert_data(&word_list[0], i + 1,pword);
		index_list[i] = index_list[i - 1]->next;
		//pword = index_list[i]->data;
		//printf("%d\n", pword->freq);
	}
}

char read_word(FILE *fp, char str[])
{
	int i;
	char ch;
	char temp[MAXLENGTH] = "a\0";

	i = 0;
	while(1){
		if(fp == NULL) {
			ch = getchar();
		} else {
			ch = fgetc(fp);
		}
		if(ch == -1)
			return '#';
		else if (i > MAXLENGTH - 2) {
			break;
		}
		else if(ch >= 'a' && ch <= 'z') {
			temp[i] = ch;
			i++;
			continue;
		} else if (ch >= 'A' && ch <= 'Z') {
			ch += 32;
			temp[i] = ch;
			i++;
			continue;
		} else if (ch == 0x0A){
			if (temp[i-1] == '-'){
				i--;
				continue;
			} else 
				break;
		} else if (i == 0) {
			continue;
		} else {
			break;
		}
		
	}

	strcpy(str,temp);
	return temp[0];
}
	


	/********************only available for char list
int list_binsrch(plist list, char *data)
{
	int low, mid, high;
	int temp;
	str_pword p;

	low = 2;
	high = list_length(list);

	while(low <= high){
		mid = (low + high) / 2;
		p = get_data(list,mid);
		temp = strcmp(data,p->word);
		if (temp == 0){
			flag_rep = 1;
			return mid;
		} else if (temp < 0)
			high = mid - 1;
		else 
			low = mid + 1;
	}
	p = get_data(list,mid);
	temp = strcmp(data,p->word);
	if(temp < 0)
		mid--;

	return mid;
}
	**********************/


int list_search(plist list, char *data)
{
	plist p;
	int i;
	int temp;
	str_pword pp;

	p = list->next;
	i = 1;
	//	printf("aaaaaaaa\n");
	while(p != list){
		//	printf("ok\n");
		pp = p->data;
		temp = strcmp(pp->word, data);
		//	printf("%d\n",temp);

		if (temp == 0) {
			i++;
			flag_rep = 1;
			break;
		} else if(temp > 0)
			break;
		else {
			p = p->next;
			i++;
		}
	}
	p = p->prev;
	current_list = p;
	return i;
}


void add_to_list(FILE *fp)
{
	int index;
	int length;
	char prefix;
	char str[MAXLENGTH];
	str_pword pword,p;
	char except_word[3][10] = {"you", "to", "and"};


	length = list_length(&word_list[0]);
	printf("length is %d \n",length);
	while (1) {
		prefix = read_word(fp,str);
		if (prefix == '#')
			break;
		if ((pword=(str_pword)malloc(sizeof(str_word)))==NULL){
			printf("no enough memory to allocte bufer.\n");
			exit(1);
		}
		
		strcpy(pword->word,str);
		pword->freq = 1;

		index = prefix - 'a';
		current_list = index_list[index];
		
		//	length = list_length(&word_list[0]);

		if (length > 1){
			index = list_search(current_list, pword->word);
			//printf("index is %d\t",index);
			if (flag_rep == 1) {
				//p = get_data(&word_list[0], index);
				p = get_data(current_list, 2);
				p->freq++;
				flag_rep = 0;
				free(pword);
			} else {
				//insert_data(&word_list[0], index, pword);
				insert_data(current_list,1,pword);
			}

		} else {
			index = 1;
			length++;
			insert_data(&word_list[0], index, pword);
		}


	}

	if(case_flag == 1){
		sort_byfreq();
	}
	printf_word(100, except_word);
	free_list(&word_list[0]);
	//	length = list_length(&word_list[0]);
	//printf("%d",length);
		

}

void sort_byfreq(void)
{
	int i, j, n, change;
	str_pword p1, p2, p3;

	change = 1;
	n = list_length(&word_list[0]);
	p3 = (str_pword)malloc(sizeof(str_word));
	for (i = 2; i < n && change; i++){
		change = 0;
		current_list = &word_list[0];
		current_list = current_list->next;
		for (j = 2; j <= n - 1;j++){
			p1 = current_list->data;
			//printf("%s\n",p1->word);
			current_list = current_list->next;
			p2 = current_list->data;
			if((p1->freq) < (p2->freq)) {
				*p3 = *p1;
				*p1 = *p2;
				*p2 = *p3;
				change = 1;
			}
		}
	}
}


//print all the word in the text file
void printf_word(int percent, char **str)
{
	int k, m;
	int length;
	str_pword p;
	plist pp;

	k = 0;
	pp = &word_list[0];
	pp = pp->next;
	//length = list_length(&word_list[0]);
	while (pp != &word_list[0]) {
		p = pp->data;
		m = 1;
		/*********
		for (j = 0; j < 3; j++, str++) {
			if((strcmp(p->word, str)) == 0) {
				m = 0;
				break;
			}
		}
		**************/
		if (p->freq != 0) {
			printf("%s\t%d\n", p->word, p->freq);
			k++;
		}
	
		pp = pp->next;
	}
}
