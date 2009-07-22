#include <stdio.h>
#include <getopt.h>
#include "helpdoc.h"
#include "word.h"

extern int case_flag;

int main(int argc, char *argv[])
{
	int next_option;
	const char *const short_options = "hvab";
	const struct option long_options [] = {
		{"help", 0, NULL, 'h'},
		{"version", 0, NULL, 'v'},
		{"a", 0, NULL, 'a'},
		{"b", 0, NULL, 'b'},
		{NULL, 0, NULL, 0}
	};


	int i;
	FILE *fp;
	char *str;
	char *filename;


	case_flag = 0;
	while((next_option = getopt_long(argc, argv,short_options,
					 long_options, NULL)) != -1){
	
		switch(next_option){
		case 'h':
			printf("help %s\n", case_help);
			break;
		case 'v':
			printf("%s\n", case_version);
			break;
		case 'a':
			case_flag = 1;         //sort by freqence of word
			break;
		case 'b':
			case_flag = 2;         //sort by dictionary
			break;
		case '?':
			printf("%s\n,", case_other);
			break;
		default:
			break;
		}
	}
	filename = argv[optind];              //get the inputfile
	printf("%d\n",filename);

	
	if(argv[optind] != NULL) {
		printf("input:%s\n",filename);
		if((fp = fopen(filename,"rt")) == NULL){
			printf("can't open file, press"
			       " any key to exit\n");
			exit(1);
		}
		} else {
		printf("oknull\n");
		fp = NULL;
}


	sys_init();	
	add_to_list(fp);


	
	
	
	return 0;
}


