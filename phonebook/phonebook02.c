
#include <stdio.h>
#include <string.h>

#define ARRAY_SIZE 100
#define BUFFER_SIZE 100

char* names[ARRAY_SIZE];
char* numbers[ARRAY_SIZE];
int i = 0;

void readLine();
int search(char* name);
void read();
void add();
void find();
void status();
void _remove();
void save();
void freeAll();

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

void read() {
	char file_name[BUFFER_SIZE];
	char buffer1[BUFFER_SIZE];
	char buffer2[BUFFER_SIZE];
	
	printf("file name : ");
	readLine(file_name);
	
	FILE* fp = fopen(file_name, "r");
	
	if(fp == NULL) {
		printf("Open failed.\n");
		
		return;
	}
	
	while(fscanf(fp, "%s", buffer1) != EOF) {
		fscanf(fp, "%s", buffer2);
		
		names[i] = strdup(buffer1);
		numbers[i] = strdup(buffer2);
		i++;
	}
	
	fclose(fp);
}

void add() {
	char buffer1[BUFFER_SIZE];
	char buffer2[BUFFER_SIZE];
	
	printf("name : ");
	readLine(buffer1);
	
	printf("number : ");
	readLine(buffer2);
	
	// sort
	int j = i - 1;
	while(j >= 0 && strcmp(names[j], buffer1) > 0) {
		names[j + 1] = names[j];
		numbers[j + 1] = numbers[j];
		j--;
	}
		
	names[j + 1] = strdup(buffer1);
	numbers[j + 1] = strdup(buffer2);
	i++;
	
	printf("%s was added successfully.\n", buffer1);
}

void find() {
	char buffer[BUFFER_SIZE];
	
	printf("name : ");
	readLine(buffer);
	
	int index = search(buffer);
	
	if(index == -1) {
		printf("No person named '%s' exists.\n", buffer);
	
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

void _remove() {
	char buffer[BUFFER_SIZE];
	
	printf("name : ");
	readLine(buffer);
	
	int index = search(buffer);
	
	if(index == -1) {
		printf("No person named '%s' exists.\n", buffer);
		
		return;
	}
	
	int j = index;
	for(; j<i-1; j++) {
		names[j] = names[j + 1];
		numbers[j] = numbers[j + 1];
	}
	
	i--;
	
	printf("'%s' was removed successfully.\n", buffer);
}

void save() {
	char file_name[BUFFER_SIZE];
	
	printf("file name : ");
	readLine(file_name);

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

void freeAll() {
	int j;
	for(j=0; j<ARRAY_SIZE; j++) {
		free(names[j]);
		free(numbers[j]);
	}
}

int main(void) {
	char buffer[BUFFER_SIZE];
	
	while(1) {
		printf("$ ");
		readLine(buffer);
		
		if(strcmp(buffer, "read") == 0) {
			read();
		
		} else if(strcmp(buffer, "add") == 0) {
			add();
			
		} else if(strcmp(buffer, "find") == 0) {
			find();
			
		} else if(strcmp(buffer, "status") == 0) {
			status();
			
		} else if(strcmp(buffer, "remove") == 0) {
			_remove();
			
		} else if(strcmp(buffer, "save") == 0) {
			save();
			
		} else if(strcmp(buffer, "exit") == 0) {
			break;
		}
		
		printf("\n");
	}
	
	freeAll();
	
	return 0;
}
