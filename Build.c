// Kenny Jin jjin59@wisc.edu
// Ying Zhang yzhang865@wisc.edu
// Build.c
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define SIZE 1024
#define BUFFSIZE 1024

// This is actually single build specification
typedef struct array_ofstrings{
        char *target;
        char **dependences;
        char *** cmdline;
}Array_ofstrings;

// Create build spec
Array_ofstrings *createAS() {
        Array_ofstrings *construct = (Array_ofstrings*)malloc(sizeof(Array_ofstrings));
   	construct->dependences = (char**)malloc(BUFFSIZE*sizeof(char*));
        construct->cmdline = (char***)malloc(BUFFSIZE*sizeof(char**));
        for(int n = 0; n<BUFFSIZE; n++) {
		construct->cmdline[n] = (char**)malloc(BUFFSIZE * sizeof(char*));
        }
        return construct;
}

// This is an arraylist that stores build specs
typedef struct ArrayList {
	int size;
	int capacity;
	Array_ofstrings **buildSpec;
}ArrayList;

ArrayList *newlist() {
	Array_ofstrings **buildSpec = (Array_ofstrings**)malloc(SIZE*sizeof(Array_ofstrings*));
	ArrayList *list = malloc(sizeof(ArrayList));
	list->size = 0;
	list->capacity = SIZE;
	list->buildSpec = buildSpec;	
	return list;
}

// get size
int getSize(ArrayList *list) {
	return list -> size;
}

//get target
char* getTarget(Array_ofstrings *construct) {
	return construct -> target;
}

// get dependences
char** getDepList(Array_ofstrings *construct) {
	return construct -> dependences;
}


// get cmdline. Actually a 2d array of strings.
char *** getCmdline(Array_ofstrings *construct) {
	return construct -> cmdline;
}

// check if the list need to be expanded.
void check(ArrayList *list) {
	if(list->size == list->capacity) {
		printf("Expanding\n");
        	list->capacity = list->capacity * 2;
		list->buildSpec = realloc(list->buildSpec, list->capacity * sizeof(int));
		if (list->buildSpec == NULL) {
            		printf("realloc failed\n");
            		exit(1);
        	}
	}

}

// add spec to list
void add(ArrayList *list, Array_ofstrings* spec) {
    check(list);
    list->buildSpec[list->size] = spec;
    list->size++;
}

void printList(ArrayList *list) {
    printf("size of arraylist is: %d\n", list->size);
}

void freePointer(Array_ofstrings *construct, ArrayList *list) {
	free(construct->target);
	for(int i = 0; i<BUFFSIZE; i++) {
		free(construct->dependences[i]);
	}
	free(construct->dependences);
	for(int j = 0; j<BUFFSIZE; j++) {
		for(int k = 0; k<BUFFSIZE; k++) {
                	free(construct->cmdline[j][k]);
		}
        }
	free(construct);
	for(int m = 0; m< BUFFSIZE; m++) {
		free(list->buildSpec[m]);
	}
	free(list->buildSpec);
	free(list);
	printf("free them all\n");

}

// Get the specification list
Array_ofstrings ** getSpecList(ArrayList *list){
	return list -> buildSpec;
}
