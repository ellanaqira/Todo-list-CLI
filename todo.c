#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// constant
#define MAXCHAR 256


// Task structure
typedef struct {
	char todo[MAXCHAR];
	float time;
	int date;
	int month;
	int years;
	int status;
	int mark;
} Task;



// Function Declaration
int write_data(Task data, char file_name[]);
int read_data(Task data, char file_name[]);
void print_help(void);
// Helper Function
void store_to_struct(Task *data, char argv2[], char argv3[], char argv4[], char argv5[], char argv6[], char argv7[], char argv8[]);
int str_compare(char str1[], char str2[]);



// MAIN
int main(int argc, char *argv[]) {
    if (argc == 1) {
        print_help();
    }
    
    else {
        Task to_do;

        if (str_compare(argv[1], "help") == 1) {
            if (argc == 2) {
                print_help();
            }
            else {
                printf("todo: '%s' is not a todo command.\n", argv[2]);
                return 1;            
            }
        }

        else if (str_compare(argv[1], "add") == 1) {
            if (argc == 9) {
                store_to_struct(&to_do, argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
                write_data(to_do, "file.bin");
            }
            else {
                printf("'add' must be include <task> <time(hh.mm)> <date> <month> <years> <status> <mark>\n");
                return 1;
            }
        }

        else if (str_compare(argv[1], "show") == 1) {
            read_data(to_do, "file.bin");
        }

        else {
            printf("todo: '%s' is not a todo command.\n", argv[1]);
            return 1;
        }
    }
    
    return 0;
}



// Function Definition
void print_help(void){
    printf("[ Help ]\n");
    printf("Command:\n");
    printf("    add     to store task and write it to binary file\n");
    printf("    show    print out stored task\n");
}


int write_data(Task data, char file_name[]) {
    FILE *file = fopen(file_name, "ab");
    if (file == NULL) {
        printf("Failed to open file\n");
        return 1;
    }

    // Write data to binary file
    size_t num_written;
    num_written = fwrite(&data, sizeof(data), 1, file);

    if (num_written != 1) {
        printf("Failed adding data to file\n");
        return 1;
    }
    fclose(file);

    printf("Successfully add data to file\n");
    return 0;
}

int read_data(Task data, char file_name[]) {
    FILE *file = fopen(file_name, "rb");
    if (file == NULL) {
        printf("Failed to open file\n");
        return 1;
    }
    
    while(fread(&data, sizeof(data), 1, file) == 1) {
        printf("%s | time: %.2f | %d-%d-%d | urgency: %d | stat: %d\n",
        data.todo, data.time, data.date, data.month, data.years, data.status, data.mark);
    }

    fclose(file);
    return 0;
}

void store_to_struct(Task *data, char argv2[], char argv3[], char argv4[], char argv5[], char argv6[], char argv7[], char argv8[]) {
	strcpy(data->todo, argv2);
	data->time = atof(argv3);
	data->date = atoi(argv4);
	data->month = atoi(argv5);
	data->years = atoi(argv6);
	data->status = atoi(argv7);
	data->mark = atoi(argv8);
}

int str_compare(char str1[], char str2[]) {
    int i = 0;

    while (str1[i] == str2[i]) {
        if (str1[i] == '\0' && str2[i] == '\0') {
            return 1;
        }
        ++i;
    }
    return 0;
}
