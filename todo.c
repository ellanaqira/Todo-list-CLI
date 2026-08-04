#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// constant
#define MAXCHAR 256
#define REQUIRED_HELP_ARGC 2
#define REQUIRED_ADD_ARGC 9
#define REQUIRED_SHOW_ARGC 2
#define REQUIRED_LOOK_ARGC 3
#define DB_FILE "todolist.bin"



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
int look_task(Task data, char file_name[], char argv2[]);
int get_numof_task(Task data, char file_name[]);
void print_help(void);
// Helper Function
int longest_str(Task data, char file_name[]);
void store_to_struct(Task *data, char argv2[], char argv3[], char argv4[], char argv5[], char argv6[], char argv7[], char argv8[]);
void loopchar(int n, char c);



// MAIN
int main(int argc, char *argv[]) {
    if (argc == 1) {
        print_help();
    }
    
    else {
        Task to_do;

        if (strcmp(argv[1], "help") == 0) {
            if (argc == REQUIRED_HELP_ARGC) {
                print_help();
            }
            else {
                printf("todo: '%s' is not a todo command.\n", argv[2]);
                return 1;            
            }
        }

        else if (strcmp(argv[1], "add") == 0) {
            if (argc == REQUIRED_ADD_ARGC) {
                store_to_struct(&to_do, argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
                write_data(to_do, DB_FILE);
            }
            else {
                printf("todo: 'add' must be include <task> <time(hh.mm)> <date> <month> <years> <status> <mark>\n");
                return 1;
            }
        }

        else if (strcmp(argv[1], "show") == 0) {
            if (argc == REQUIRED_SHOW_ARGC) {
                read_data(to_do, DB_FILE);
            }
            else {
                printf("todo: '%s' is not a todo command.\n", argv[2]);
                return 1;            
            }
        }

        else if (strcmp(argv[1], "look") == 0) {
            if (argc == REQUIRED_LOOK_ARGC) {
                if (look_task(to_do, DB_FILE, argv[2]) == 1) {
                    printf("todo: cant find task '%s'\n", argv[2]);
                    return 1;
                }
            }
            else {
                printf("todo: 'look' must be include <task>\n");
                return 1;            
            }
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
    printf("            'add' <task> <time(hh.mm)> <date> <month> <years> <status> <mark>\n");
    printf("            <status> : 0 = not at all urgent, 1 = not urgent, 2 = quite urgent, 3 = urgent\n");
    printf("            <mark>   : 0 = not finish, 1 = finish\n");
    printf("    look    'look' <task>\n");
    printf("    show    print out stored task\n");
}


void loopchar(int n, char c) {
    for(int i=0; i<n; i+=1) {
        putchar(c);
    }
}


int longest_str(Task data, char file_name[]) {
    FILE *file = fopen(file_name, "rb");

    if (file == NULL) {
        printf("Failed to open file\n");
        return 1;
    }

    int templen = 0;
    while(fread(&data, sizeof(data), 1, file) == 1) {
        size_t textlen = strlen(data.todo);
        if (templen < textlen) {
            templen = textlen;
        }
        else {
            templen;
        }
    }
    return templen;
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

    return 0;
}


int read_data(Task data, char file_name[]) {

// Get number of task by the urgent status ==========|

    FILE *file = fopen(file_name, "rb");
    if (file == NULL) {
        printf("Failed to open file\n");
        return 1;
    }
    
    int numof_urgent3 = 0;
    int numof_urgent2 = 0;
    int numof_urgent1 = 0;
    int numof_urgent0 = 0;

    while(fread(&data, sizeof(data), 1, file) == 1) {
        if (data.status == 3) {
            numof_urgent3 += 1;
        }
        else if (data.status == 2) {
            numof_urgent2 += 1;
        }
        else if (data.status == 1) {
            numof_urgent1 += 1;
        }
        else if (data.status == 0) {
            numof_urgent0 += 1;
        }
    }
    // Reset the pointer file
    rewind(file); 

// Allocate memory for the array of string pointers ==========|

    // Dynamic Array of string to store task by the urgency
    char **urgent3_task = (char **)malloc(numof_urgent3 * sizeof(char *));
    if (urgent3_task== NULL) {
        return 1;
    }

    // Temporary Number
    int tempnum_urgent3 = 0;

    while(fread(&data, sizeof(data), 1, file) == 1) {
        // Strore task to urgent3_task if data.status is equal to 3
        if (data.status == 3) {
            // Combine formated string
            char buffer[1000];
            snprintf(buffer, sizeof(buffer), "%s | time: %5.2f | %2d-%2d-%4d | urgency: %d | stat: %d", data.todo, data.time, data.date, data.month, data.years, data.status, data.mark);

            urgent3_task[tempnum_urgent3] = (char *)malloc(strlen(buffer) * sizeof(char));
            if (urgent3_task[tempnum_urgent3] == NULL) {
                return 1;
            }

            strcpy(urgent3_task[tempnum_urgent3], buffer);

            if (tempnum_urgent3 < numof_urgent3) {
                tempnum_urgent3 += 1;
            }
        }
    }


    for(int i = 0; i < numof_urgent3; i+=1) {
        printf("%s\n", urgent3_task[i]);
    }

    // 4. Free the allocated memory (reverse order)
    for (int i = 0; i < numof_urgent3; i+=1) {
        free(urgent3_task[i]); // Free each string
    }

    free(urgent3_task);

    fclose(file);
    return 0;
}

 
int look_task(Task data, char file_name[], char argv2[]) {
    FILE *file = fopen(file_name, "rb");
    if (file == NULL) {
        printf("Failed to open file\n");
        return 1;
    }

    int find = 0;
    while(fread(&data, sizeof(data), 1, file) == 1) {
        if ((strcmp(argv2, data.todo)) == 0) {
            printf("%s | time: %5.2f | %d-%d-%d | urgency: %d | stat: %d\n",
            data.todo, data.time, data.date, data.month, data.years, data.status, data.mark);
            find = 1;
        }
    }
    
    if (find == 0) {
        return 1;
    }

    return 0;
}

int get_numof_task(Task data, char file_name[]) {
    FILE *file = fopen(file_name, "rb");
    if (file == NULL) {
        return 1;
    }

    fseek(file, 0, SEEK_END);
    int numof_task = ftell(file) / sizeof(data);

    return numof_task;
}


void store_to_struct(Task *data, char argv2[], char argv3[], char argv4[], char argv5[], char argv6[], char argv7[], char argv8[]) {
	strncpy(data->todo, argv2, MAXCHAR-1);
    data->todo[MAXCHAR-1] = '\0'; // Ensure null termination
	data->time = atof(argv3);
	data->date = atoi(argv4);
	data->month = atoi(argv5);
	data->years = atoi(argv6);
	data->status = atoi(argv7);
	data->mark = atoi(argv8);
}

