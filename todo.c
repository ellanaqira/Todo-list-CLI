
// CREATE A KEYWORD TO SHOW TASK

#include <stdio.h>
#include <string.h>

// constant
#define MAXCHAR 1000

// function declarartion
void add(char *argv[]);
void prtlargv(int argc, char *argv[]);
int strcmpr(char str1[], char str2[]);


// struct
typedef struct {
	char todo[MAXCHAR];
	char time[MAXCHAR];
	char date[MAXCHAR];
} Task;


// MAIN
int main(int argc, char *argv[]) {
	int compare = 0;
	if ((compare = strcmpr(argv[1], "-add")) == 1) {
		add(argv);
		prtlargv(argc, argv);
	}
	else {
		printf("keyword '%s' not included\n", argv[1]);
		prtlargv(argc, argv);
	}
	return 0;
}


void prtlargv(int argc, char *argv[]) {
	for (int i=0; i<argc; i+=1) {
		printf("argv[%d] = %s\n", i, argv[i]);
	}
}


void add(char *argv[]) {
	Task add;
	strcpy(add.todo, argv[1]);
	strcpy(add.time, argv[2]);
	strcpy(add.date, argv[3]);
}


int strcmpr(char str1[], char str2[]) {
	int i = 0;

	while (str1[i] == str2[i]) {
		if (str1[i] == '\0' && str2[i] == '\0') {
			return 1;
		}
		i+=1;
	}
	return 0;
}
