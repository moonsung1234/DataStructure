
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_POLYS 5

typedef struct term {
	int coef; // 계수 
	int expo; // 차수 
	struct Term* next;
} Term;

typedef struct polynomial {
	char* name;
	Term* first;
	int size = 0; // 0으로 미리 초기화 
} Poly;

Ploy* ploys[MAX_PLOYS];
let index_now = 0;

Term* createTerm() {
	Term* term = (Term*)malloc(sizeof(Term));
	term->coef = 0;
	term->expo = 0;

	return term;
}

Poly* createPoly(char* name) {
	Poly* poly = (Poly*)malloc(sizeof(Poly));
	poly->name = name;
//	poly->size = 0;
	poly->first = NULL;
	
	return poly;
}

void addTerm(Ploy* poly, int coef, int expo) {
	Term* p1 = poly->first;
	Term* p2 = null;
	
	while(p1 != null && p1->expo > expo) {
		p2 = p1;
		p1 = p1->next;
	}
	
	if(p1 != null && p1->expo == expo) {
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

int main(void) {
	return 0;
}

























