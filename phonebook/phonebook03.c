
#include <stdio.h>
#include <string.h>

#define DEFAULT_SIZE 1
#define BUFFER_SIZE 100

void readLine(char* buffer);
int search(char* name);
void init();
void remalloc();
void read(char* file_name);
void add();
void find();
void status();
void _remove();
void save();
void process();
void freeAll();

char** names;
char** numbers;
int size = DEFAULT_SIZE;
int i = 0;

void readLine(char* buffer) {
	char c;
	int j = 0;
	
	while((c = getchar()) != '\n') {
		buffer[j++] = c;	
	}
	
	buffer[j] = '\0';
}

int search(char* name) {
	int j;
	for(j=0; j<i; j++) {
		if(strcmp(name, names[j]) == 0) {
			return j;
		}
	}
	
	return -1;
}

void init() {
	names = (char**)malloc(DEFAULT_SIZE * sizeof(char *));
	numbers = (char**)malloc(DEFAULT_SIZE * sizeof(char *)); 
}

void remalloc() {
	if(i >= size) {
		size += DEFAULT_SIZE;
		char** temp_names = (char**)malloc(size * sizeof(char *));
		char** temp_numbers = (char**)malloc(size * sizeof(char *));
		
		int j;
		for(j=0; j<i; j++) {
			temp_names[j] = names[j];
			temp_numbers[j] = numbers[j];
		}
		
		freeAll();
		
		names = temp_names;
		numbers = temp_numbers;
	}
}

void read(char* file_name) {
	char buffer1[BUFFER_SIZE];
	char buffer2[BUFFER_SIZE];
	
	FILE* fp = fopen(file_name, "r");
	
	if(fp == NULL) {
		printf("Open failed.\n");
		
		return;
	}
	
	while(fscanf(fp, "%s", buffer1) != EOF) {
		fscanf(fp, "%s", buffer2);
		remalloc();
		
		names[i] = strdup(buffer1);
		numbers[i] = strdup(buffer2);
		i++;
	}
	
	fclose(fp);
}

void add(char* name, char* number) {
	remalloc();
		
	// sort
	int j = i - 1;
	while(j >= 0 && strcmp(names[j], name) > 0) {
		names[j + 1] = names[j];
		numbers[j + 1] = numbers[j];
		j--;
	}
		
	names[j + 1] = strdup(name);
	numbers[j + 1] = strdup(number);
	i++;
	
	printf("%s was added successfully.\n", name);
}

void find(char* name) {
	int index = search(name);
	
	if(index == -1) {
		printf("No person named '%s' exists.\n", name);
	
	} else {
		printf("%s\n", numbers[index]);
	}
}

void status() {
	int j;
	for(j=0; j<i; j++) {
		printf("%s : %s\n", names[j], numbers[j]);
	}
	
	printf("Total %d persons.\n", i);
}

void _remove(char* name) {
	int index = search(name);
	
	if(index == -1) {
		printf("No person named '%s' exists.\n", name);
		
		return;
	}
	
	int j = index;
	for(; j<i-1; j++) {
		names[j] = names[j + 1];
		numbers[j] = numbers[j + 1];
	}
	
	i--;
	
	printf("'%s' was removed successfully.\n", name);
}

void save(char* file_name) {
	FILE* fp = fopen(file_name, "w");
	
	if(fp == NULL) {
		printf("Open failed.\n");
		
		return;
	}
	
	int j;
	for(j=0; j<i; j++) {
		fprintf(fp, "%s %s\n", names[j], numbers[j]);
	}
	
	fclose(fp);
}

void process() {
	char buffer[BUFFER_SIZE];
	char* command;
	char* argument1;
	char* argument2;
	
	while(1) {
		printf("$ ");
		readLine(buffer);
		
		command = strtok(buffer, " ");
		
		if(command == NULL) {
			continue;
		}
		
		if(strcmp(command, "read") == 0) {
			argument1 = strtok(NULL, " ");
			
			if(argument1 == NULL) {
				printf("File name required.\n");
				
				continue;
			}
			
			read(argument1);
		
		} else if(strcmp(command, "add") == 0) {
			argument1 = strtok(NULL, " ");
			argument2 = strtok(NULL, " ");
			
			if(argument1 == NULL || argument2 == NULL) {
				printf("Invaild arguments.\n");
				
				continue;	
			}
			
			add(argument1, argument2);
			
		} else if(strcmp(command, "find") == 0) {
			argument1 = strtok(NULL, " ");
			
			if(argument1 == NULL) {
				printf("Invaild arguments.\n");
				
				continue;
			}
			
			find(argument1);
			
		} else if(strcmp(command, "status") == 0) {
			status();
		
		} else if(strcmp(command, "remove") == 0) {
			argument1 = strtok(NULL, " ");
			
			if(argument1 == NULL) {
				printf("Invaild arguments.\n");
				
				continue;
			}
			
			_remove(argument1);
			
		} else if(strcmp(command, "save") == 0) {
			argument1 = strtok(NULL, " ");
			
			if(argument1 == NULL) {
				continue;
			}
			
			save(argument1);
		
		} else if(strcmp(command, "exit") == 0) {
			break;
		}
	}
}

void freeAll() {
	free(names);
	free(numbers);
}

void main(void) {
	init();
	process();
	freeAll();
	
	return 0;
}






















