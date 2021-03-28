
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readLine(char* buffer) {
	char c;
	int i = 0;
	
	while((c = getchar()) != '\n') {
		buffer[i++] = c;
	}
	
	buffer[i] = '\0';
	
	return buffer;
}

int main(void) {
	char buffer[100];
	
	while(1) {
		printf("$ ");
		readLine(buffer);
		printf("%s:%d\n", buffer, strlen(buffer));
	}
	
	return 0;
}
