
#include <stdio.h>
#include <string.h>

#define ARRAY_SIZE 100
#define BUFFER_SIZE 100

char* names[ARRAY_SIZE];
char* numbers[ARRAY_SIZE];
int i = 0;

void add();
void find();
void status();
void _remove();
void freeAll();

void add() {
	char buffer1[BUFFER_SIZE];
	char buffer2[BUFFER_SIZE];
	
	printf("name : ");
	scanf("%s", buffer1);
	
	printf("number : ");
	scanf("%s", buffer2);
	
	names[i] = strdup(buffer1);
	numbers[i] = strdup(buffer2);
	i++;
	
	printf("%s was added successfully.\n", buffer1);
}

void find() {
	char buffer[BUFFER_SIZE];
	
	printf("name : ");
	scanf("%s", buffer);
	
	int j;
	for(j=0; j<i; j++) {
		if(strcmp(buffer, names[j]) == 0) {
			printf("%s\n", numbers[j]);
			
			return;
		}
	}
	
	printf("No person named '%s' exists.\n", buffer);
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
	scanf("%s", buffer);
	
	int j;
	for(j=0; j<i; j++) {
		if(strcmp(buffer, names[j]) == 0) {
			// move last person to removed space
			names[j] = names[i - 1];
			numbers[j] = numbers[i - 1];
			i--;
			
			printf("'%s' was removed successfully.\n", buffer);
			
			return;
		}
	}
	
	printf("No person named '%s' exists.\n", buffer);
}

void freeAll() {
	int j;
	for(j=0; j<ARRAY_SIZE; j++) {
		free(names[j]);
		free(numbers[j]);
	}
}

int main() {
	char command[BUFFER_SIZE];
	
	while(1) {
		printf("$ ");
		scanf("%s", command);
		
		if(strcmp(command, "add") == 0) {
			add();
			
		} else if(strcmp(command, "find") == 0) {
			find();
			
		} else if(strcmp(command, "status") == 0) {
			status();
			
		} else if(strcmp(command, "remove") == 0) {
			_remove();
			
		} else if(strcmp(command, "exit") == 0) {
			break;
		}
	}
	
	freeAll();
	
	return 0;
}

