
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_POLYS 5
#define MAX_BUFFER 100

typedef struct term {
	int coef; // 계수 
	int expo; // 차수 
	struct Term* next;
} Term;

typedef struct polynomial {
	char* name;
	Term* first;
	int size;
} Poly;

void readLine(char* buffer);
void eraseBlanks(char* buffer);
Term* createTerm();
Poly* createPoly(char* name);
void addTerm(Poly* poly, int coef, int expo);
int _eval(Term* term, int x);
int eval(Poly* poly, int x);
void addParsedTerm(Poly* poly, char* ex, int begin, int end);
Poly* createParsedPoly(char* name, char* body);
void printTerm(Term* term);
void printPoly(Poly* poly);
void handleDefinition(char* ex);
void handlePrint(char* name);
void processCommand();
void insertPoly(Poly* poly);

Poly* polys[MAX_POLYS];
int index_now = 0;

void readLine(char* buffer) {
	char c;
	int i = 0;
	
	while((c = getchar()) != '\n') {
		buffer[i++] = c;
	}
	
	buffer[i] = '\0';
}

void eraseBlanks(char* buffer) {
	char* p1 = buffer;
	char* p2 = buffer;
	
	while(*p1 != NULL) {
		if(*p1 != ' ') {
			*p2 = *p1;
			p2++;
		}
		
		p1++;
	}
	
	*p2 = '\0';
}

Term* createTerm() {
	Term* term = (Term*)malloc(sizeof(Term));
	term->coef = 0;
	term->expo = 0;
	term->next = NULL;

	return term;
}

Poly* createPoly(char* name) {
	Poly* poly = (Poly*)malloc(sizeof(Poly));
	poly->name = strdup(name);
	poly->size = 0;
	poly->first = NULL;
	
	return poly;
}

void addTerm(Poly* poly, int coef, int expo) {
	Term* p1 = poly->first;
	Term* p2 = NULL;
	
	while(p1 != NULL && p1->expo > expo) {
		p2 = p1;
		p1 = p1->next;
	}
	
	if(p1 != NULL && p1->expo == expo) {
		p1->coef += coef;
		
		if(p1->coef == 0) {
			if(p2 == NULL) { // p1 이 첫번째 노드인경우 
				poly->first = p1->next;
			
			} else {
				p2->next = p1->next;
			}
			
			poly->size -= 1;
			
			free(p1);
		}
	
	} else {
		Term* term = createTerm();
		term->coef = coef;
		term->expo = expo;
		
		if(p2 == NULL) {
			poly->first = term;
		
		} else {
			term->next = p2->next;
			p2->next = term;
		}
		
		poly->size += 1;
	}
	
	return;
}

int _eval(Term* term, int x) {
	int result = term->coef;
	int i;
	
	for(i=0; i<term->expo; i++) {
		result *= x;
	}
	
	return result;
}

int eval(Poly* poly, int x) {
	int result = 0;
	Term* term = poly->first;
	
	while(term != NULL) {
		result += _eval(term, x);
		term = term->next;
	}
	
	return result;
}

void addParsedTerm(Poly* poly, char* ex, int begin, int end) {
	int i = begin;
	int coef = 0;
	int expo = 0;
	int coef_sign = 1; // 1 : 양수, -1 : 음수 
	
	if(ex[i] == '+') {
		i++;
			
	} else if(ex[i] == '-') {
		coef_sign = -1;
		i++;
	}
	
	while(i < end && ex[i] >= '0' && ex[i] <= '9') {
		coef = coef * 10 + (int)(ex[i] - '0');
		i++;
	}
	
	if(coef == 0) { // 계수가 없을때(1이 생략된상태) 
		coef = coef_sign;
	
	} else {
		coef *= coef_sign;
	}
	
	if(i >= end) {
		addTerm(poly, coef, 0);
		
		return;
	}
	
	i++;
	
	if(i >= end) {
		addTerm(poly, coef, 1);
		
		return;
	}
	
	i++;
	
	while(i < end && ex[i] >= '0' && ex[i] <= '9') {
		expo = expo * 10 + (int)(ex[i] - '0');
		i++;
	}
	
	addTerm(poly, coef, expo);
	
	return;
}

Poly* createParsedPoly(char* name, char* body) {
	Poly* poly = createPoly(name);
	int i = 0;
	int begin = 0;
	
	while(i < strlen(body)) {
		if(body[i] == '+' || body[i] == '-') {
			i++;
		}
		
		while(i < strlen(body) && body[i] != '+' && body[i] != '-') {
			i++;
		}
		
		addParsedTerm(poly, body, begin, i);
		
		begin = i;
	}
	
	return poly;
}

void insertPoly(Poly* poly) {
	polys[index_now++] = poly;
}

void printTerm(Term* term) {
	printf("%dx^%d", term->coef, term->expo);
}

void printPoly(Poly* poly) {
	printf("%s = ", poly->name);
	
	Term* term = poly->first;
	
	while(term->next != NULL) {
		printTerm(term);
		printf("+");
		
		term = term->next;
	}
	
	printTerm(term);
	printf("\n");
}

void handleDefinition(char* ex) {
	eraseBlanks(ex);
	
	char* func_name = strtok(ex, "=");
	char* body = strtok(NULL, "=");
	Poly* poly;
	
	if(isdigit(body[0]) == 0) {
//		char* func1 = strtok(body, "+");
//		char* func2 = strtok(NULL, "+");
//		
////		poly = createAddedPoly(func_name, func1, func2);
	
	} else {
		poly = createParsedPoly(func_name, body);
	}
	
	insertPoly(poly);
}

void handlePrint(char* name) {
	int i;
	
	for(i=0; i<index_now; i++) {
		if(strcmp(polys[i]->name, name) == 0) {
			printPoly(polys[i]);
			
			break;
		}
	}
}

void handleCalc(char* name, int x) {
	int i;
	
	for(i=0; i<index_now; i++) {
		if(strcmp(polys[i]->name, name) == 0) {
			printf("result : %d\n", eval(polys[i], x));
			
			break;
		}
	} 
}

void processCommand() {
	char buffer[MAX_BUFFER];
	char buffer2[MAX_BUFFER];
	char* command;
	char* arg1;
	char* arg2;
	
	while(1) {
		printf("$ ");
		readLine(buffer);
		
		if(strlen(buffer) == 0) {
			continue;
		}
		
		strcpy(buffer2, buffer);
		command = strtok(buffer, " ");
		
		if(strcmp(command, "print") == 0) {
			arg1 = strtok(NULL, " ");
			
			handlePrint(arg1);
		
		} else if(strcmp(command, "calc") == 0) {
			arg1 = strtok(NULL, " ");
			arg2 = strtok(NULL, " ");
			int arg2_int = 0;
			int i = 0;
			
			while(arg2[i] >= '0' && arg2[i] <= '9') {
				arg2_int += arg2_int * 10 + (arg2[i] - '0');
				i++;
			}
			
			handleCalc(arg1, arg2_int);
		
		} else if(strcmp(command, "exit") == 0) {
			break;
		
		} else {
			handleDefinition(buffer2);
		}
	}
}

void freeAll() {
	int i;
	
	for(i=0; i<index_now; i++) {
		Term* term = polys[i]->first;
		
		while(term != NULL) {
			Term* temp = term->next;
			
			free(term);
			
			term = temp;
		}
		
		free(polys[i]->name);
		free(polys[i]);
	}
}

int main(void) {
	Poly* poly = createPoly("test");
	
	addTerm(poly, 2, 2);
	printPoly(poly);
	insertPoly(poly);
	processCommand();
	freeAll();
	
	return 0;
}

























