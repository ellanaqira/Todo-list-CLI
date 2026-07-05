#include <stdio.h>
#include <string.h>

// constant
#define MAXCHAR 1000

// function declarartion
void add_task(char *argv[]);
void prtlargv(int argc, char *argv[]);
int strcmpr(char str1[], char str2[]);


// struct
typedef struct {
	char todo[MAXCHAR];
	char time[MAXCHAR];
	char date[MAXCHAR];
} Task;

Task add;

// MAIN
int main(int argc, char *argv[]) {
	if (strcmpr(argv[1], "add") == 1) {
		if (argc < 5) {
            printf("Error: add requires <task> <time> <date>\n");
            return 1;
        }
		add_task(argv);
		prtlargv(argc, argv);
	}

	else {
		printf("keyword '%s' not included\n", argv[1]);
		prtlargv(argc, argv);
	}
	return 0;
}


void add_task(char *argv[]) {
	/*
	Add task data to Task struct
	*/
	strcpy(add.todo, argv[2]);
	strcpy(add.time, argv[3]);
	strcpy(add.date, argv[4]);
}


int strcmpr(char str1[], char str2[]) {
	/*
	Compare two string to check if it the same,
	return 1 if two string are the same and
	return 0 if otherwise.
	*/
	int i = 0;

	while (str1[i] == str2[i]) {
		if (str1[i] == '\0' && str2[i] == '\0') {
			return 1;
		}
		i+=1;
	}
	return 0;
}


void prtlargv(int argc, char *argv[]) {
	/*
	Print list of argv line by line
	*/
	for (int i=0; i<argc; i+=1) {
		printf("argv[%d] = %s\n", i, argv[i]);
	}
}