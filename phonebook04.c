
#include <stdio.h>
#include <string.h>

#define DEFAULT_SIZE 1
#define BUFFER_SIZE 100

typedef struct Person {
	char* name;
	char* number;
	char* email;
	char* group;
} ps;

void readLine(FILE* fp, char* buffer);
int search(char* name);
void init();
void remalloc();
void read(char* file_name);
void add(char* name, char* number, char* email, char* group);
void find();
void status();
void _remove();
void save();
void process();
void freeAll();

ps* persons;
int size = DEFAULT_SIZE;
int i = 0;

void readLine(FILE* fp, char* buffer) {
	char c;
	int j = 0;
	
	while((c = fgetc(fp)) != '\n' && c != EOF) {
		if(c != ' ' || (j > 0 && buffer[j - 1] != ' ')) {
			buffer[j++] = c;	
		}
	}
	
	if(buffer[j - 1] == ' ') {
		j--;
	}
	
	buffer[j] = '\0';
}

int search(char* name) {
	int j;
	for(j=0; j<i; j++) {
		if(strcmp(name, persons[j].name) == 0) {
			return j;
		}
	}
	
	return -1;
}

void init() {
	persons = (ps*)malloc(DEFAULT_SIZE * sizeof(ps));
}

void remalloc() {
	if(i >= size) {
		size += DEFAULT_SIZE;
		ps* temp_persons = (ps*)malloc(size * sizeof(ps));
		
		int j;
		for(j=0; j<i; j++) {
			temp_persons[j] = persons[j];
		}
		
		freeAll();
		
		persons = temp_persons;
	}
}

void read(char* file_name) {
	char buffer[BUFFER_SIZE];
	char* name;
	char* number;
	char* email;
	char* group;
	
	FILE* fp = fopen(file_name, "r");
	
	if(fp == NULL) {
		printf("Open failed.\n");
		
		return;
	}
	
	while(1) {
		readLine(fp, buffer);
		
		if(strlen(buffer) <= 0) {
			break;
		}
		
		name = strtok(buffer, "#");
		number = strtok(NULL, "#");
		email = strtok(NULL, "#");
		group = strtok(NULL, "#");
		
		add(name, number, email, group);
	}
	
	fclose(fp);
}

void add(char* name, char* number, char* email, char* group) {
	remalloc();
		
	// sort
	int j = i - 1;
	while(j >= 0 && strcmp(name, persons[j].name) > 0) {
		persons[j + 1] = persons[j];
		j--;
	}
	
	persons[j + 1].name = strdup(name);
	persons[j + 1].number = strdup(number);
	persons[j + 1].email = strdup(email);
	persons[j + 1].group = strdup(group);
	i++;
	
	printf("%s was added successfully.\n", name);
}

void find(char* name) {
	int index = search(name);
	
	if(index == -1) {
		printf("No person named '%s' exists.\n", name);
	
	} else {
		printf("%s\n%s\n%s\n", persons[index].number, persons[index].email, persons[index].group);
	}
}

void status() {
	int j;
	for(j=0; j<i; j++) {
		printf("%s : %s\n", "name", persons[j].name);
		printf("%s : %s\n", "number", persons[j].number);
		printf("%s : %s\n", "email", persons[j].email);
		printf("%s : %s\n", "group", persons[j].group);
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
		persons[j] = persons[j + 1];
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
		fprintf(fp, "%s#", persons[j].name);
		fprintf(fp, "%s#", persons[j].number);
		fprintf(fp, "%s#", persons[j].email);
		fprintf(fp, "%s#\n", persons[j].group);
	}
	
	fclose(fp);
}

void process() {
	char buffer[BUFFER_SIZE];
	char* command;
	char* arg1;
	char* arg2;
	char* arg3;
	char* arg4;
	
	while(1) {
		printf("$ ");
		readLine(stdin, buffer);
		
		command = strtok(buffer, " ");
		
		if(command == NULL) {
			continue;
		}
		
		if(strcmp(command, "read") == 0) {
			arg1 = strtok(NULL, " ");
			
			if(arg1 == NULL) {
				printf("File name required.\n");
				
				continue;
			}
			
			read(arg1);
		
		} else if(strcmp(command, "add") == 0) {
			arg1 = strtok(NULL, " ");
			arg2 = strtok(NULL, " ");
			arg3 = strtok(NULL, " ");
			arg4 = strtok(NULL, " ");
			
			if(arg1 == NULL || arg2 == NULL || arg3 == NULL || arg4 == NULL) {
				printf("Invaild arguments.\n");
				
				continue;	
			}
			
			add(arg1, arg2, arg3, arg4);
			
		} else if(strcmp(command, "find") == 0) {
			arg1 = strtok(NULL, " ");
			
			if(arg1 == NULL) {
				printf("Invaild arguments.\n");
				
				continue;
			}
			
			find(arg1);
			
		} else if(strcmp(command, "status") == 0) {
			status();
		
		} else if(strcmp(command, "remove") == 0) {
			arg1 = strtok(NULL, " ");
			
			if(arg1 == NULL) {
				printf("Invaild arguments.\n");
				
				continue;
			}
			
			_remove(arg1);
			
		} else if(strcmp(command, "save") == 0) {
			arg1 = strtok(NULL, " ");
			
			if(arg1 == NULL) {
				continue;
			}
			
			save(arg1);
		
		} else if(strcmp(command, "exit") == 0) {
			break;
		}
	}
}

void freeAll() {
	free(persons);
}

void main(void) {
	init();
	process();
	freeAll();
	
	return 0;
}






















