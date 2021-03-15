
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readLineWithoutSpace(char* buffer) {
	char c;
	int i = 0;
	
	while((c = getchar()) != '\n') {
		if(c != ' ' || (i > 0 && buffer[i - 1] != ' ')) {
			buffer[i++] = c;	
		}
	}
	
	if(buffer[i - 1] == ' ') {
		i--;
	}
	
	buffer[i] = '\0';
	
	return buffer;
}

int main(void) {
	char* buffer[100];
	
	while(1) {
		printf("$ ");
		readLineWithoutSpace(buffer);
		printf("%s:%d\n", buffer, strlen(buffer));
	}
	
	return 0;
}
