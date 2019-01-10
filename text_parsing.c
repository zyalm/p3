// Kenny Jin jjin59@wisc.edu
// Ying Zhang yzhang865@wisc.edu
// text_parsing.c

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Build.h"
#define BUFFSIZE 1024
#define SIZE 1024


// Read file and return an arraylist of build spec
ArrayList *readFile(char* argv) {
	char c;
	char ch = ':';
	int p = 0;
	char *filename = argv;
	FILE *fptr;
	fptr = fopen(filename, "r");
	if (fptr == NULL)
    	{
        	printf("Cannot open makefile \n");
        	fptr = fopen("Makefile", "r");
        	if(fptr == NULL) {
        		printf("open Makefile \n");
        		exit(1);
        	}
    	}

	int num_cmd = 0;
	int line_counter = 0;
	ArrayList *list = newlist();
	Array_ofstrings *construct = NULL;
	
	while(1){
		char *str = malloc(BUFFSIZE * sizeof(char));
		char *str_pointer = malloc(BUFFSIZE * sizeof(char));
		char *str_cmd = malloc(BUFFSIZE* sizeof(char));
		char *str_whole = malloc(BUFFSIZE* sizeof(char));
		int j = 0;
		int m = 0;
		int q = 0;
		int flag = 1;
		int cmd = 1;
		int first_char = 0;
		int check_line = 0;
		int comment_line = 0;
	
		for(int i = 0; i<BUFFSIZE; i++){	
			c = fgetc(fptr);
			str_whole[i] = c;
			if(c == EOF) { 
				//no newline before EOF
				if(q!= 0) {
					construct->cmdline[num_cmd][p] = str_cmd;
					line_counter++;
				}
				if(j != 0) {
					construct->dependences[m] = str_pointer; 
					line_counter++;
				}
				
				return list;
			}
			if(c != '\n') {
				check_line++;
				if(first_char == 0 && c == '#') {
				//when the first character in the line is #
					first_char = 1;
					comment_line = 1;
					continue;
				}
		       	if(first_char == 1) {
					continue;
		       	}
		       	if(line_counter == 0 && c == '\t') {
		       		first_char = 1;
		       		continue;
		       	}

				if(c == ch) {
					str[i] = '\0';
					construct = createAS();
					num_cmd = 0;
					flag = 0;
					construct->target = str;
					str = malloc(BUFFSIZE * sizeof(char));
					//add to arraylist according to target number	
					add(list, construct);
					continue;

				}
				if(flag) {
					str[i] = c;
				}
				if(flag == 0) {
					if(c!= ' '){
						str_pointer[j] = c;
						j++;
					}
					if(c == ' ' && j!=0) {
						//clear str_pointer one character by one character
						construct->dependences[m] = str_pointer; 
						str_pointer = malloc(BUFFSIZE * sizeof(char));
						j = 0;
						m++;
			
					}
				}
				if(c == '\t'){
					if(q != 0){
						//when cmdline is separated by tab
						construct->cmdline[num_cmd][p] = str_cmd;
                        			str_cmd = malloc(BUFFSIZE* sizeof(char));
                        			q = 0;
                        			p++;
						continue;
					}
					//else when it's the beginning of one line
					p = 0;
					cmd = 0;
					continue;
				}
				if(cmd == 0) {//when the line starts with the tab
                    			if(c != ' ') {
                       				str_cmd[q] = c;
                        			q++;
		
					}
					if(c == ' ' && q != 0){ //when cmdline is separated by several space
						construct->cmdline[num_cmd][p] = str_cmd;
						str_cmd = malloc(BUFFSIZE* sizeof(char));
                                                
						q = 0;
						p++;
			
					}
			
                }

				if(i == BUFFSIZE -1){ 
					//when line is too long
					fprintf(stderr, "%d: Invalid line "" %s""\n", line_counter, str_whole);
					for(int a = 0; a<i; a++) {
						str_whole[a] = 0;
					}
					exit(1);
				}
					
			}
			if(c == '\n') {
				if(check_line > 0) {
					if(line_counter == 0) {
						//check the first line if it is target line
							if(flag) {
								fprintf(stderr, "%s is the first line but isn't the target line\n", str_whole);
								exit(1);
							}
					}
					if(cmd && flag) {
						//ignore the comment line
						if(comment_line) {
							break;
						}
						printf("%d: Invalid line "" %s""\n", line_counter, str_whole);
						for(int b = 0; b<i; b++) {
                            				str_whole[b] = 0;
                        			}
						exit(1);
					}
					if(j!= 0) {//free dependence pointer
						construct->dependences[m] = str_pointer; 
						str_pointer = malloc(BUFFSIZE* sizeof(char));
					}
					
					if(!cmd || !flag){
						//when it is cmdline
						if(cmd == 0) {
                        			//since 6 commands only have 5 spaces, add the last name into construct_cmdline
                            				if(p!= 0) {
							//in case the cmdline is really long
                                				construct->cmdline[num_cmd][p] = str_cmd;
                                				
								str_cmd = malloc(BUFFSIZE* sizeof(char));
	                            				num_cmd++;
						
							}
							if(num_cmd >= BUFFSIZE){
								fprintf(stderr, "%d: Invalid line: %s\n", line_counter, str_whole);
                                				exit(1);
							}

                    				}
						//when it is target and dependences line
	                    			line_counter++;
                	               	 	break;
					}

				}else {
					//when it is the empty line
                                        break;
				}
			
			}

		}

	}

}
/*
int main(int argc, char *argv[]) {
	readFile(argv[1]);
	return 0;
}

*/
