
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	char* data;
	struct Node* next;
} node;
 
node* head = NULL;

void createHeadNode(char* data) {
	head = (node*)malloc(sizeof(node));
	head->data = strdup(data);
	head->next = NULL;
}

void addBackNode(node* head, char* data) {
	node* pointer = head;
	
	while(pointer->next != NULL) {
		pointer = pointer->next;
	}

	node* new_node = (node*)malloc(sizeof(node));
	new_node->data = strdup(data);
	new_node->next = NULL; 
	pointer->next = new_node;
}

void addFrontNode(node** head, char* data) {
	node* temp = (node*)malloc(sizeof(node));
	temp->data = strdup(data);
	temp->next = *head;
	*head = temp;
}

void addBetweenNode(node* prev, char* data) {
	node* temp = (node*)malloc(sizeof(node));
	temp->data = strdup(data);
	temp->next = prev->next;
	prev->next = temp;
}

void removeFrontNode(node** head) {
	node* next_node = (*head)->next;

	free((*head)->data);
	free(*head);

	*head = next_node;
}

void removeBetweenNode(node* prev) {
	node* next_node = prev->next;
	prev->next = prev->next->next;
	
	free(next_node->data);
	free(next_node);
}

node* findNamedNode(node* head, char* name) {
	node* pointer = head;

	while(pointer != NULL) {
		if(strcmp(name, pointer->data) == 0) {
			return pointer;
		}

		pointer = pointer->next;
	}

	return NULL;
}

void freeAll(node* head) {
	node* pointer = head;
	
	while(pointer != NULL) {
		node* temp_next = pointer->next;
		
		free(pointer->data);
		free(pointer);
		
		pointer = temp_next;
	}
} 

int main(void) {
	// test flow
	createHeadNode("original_head");
	addBackNode(head, "node1");
	removeFrontNode(&head);
	addBetweenNode(head, "node0");
	removeBetweenNode(head);

	node* pointer = head;
	
	while(pointer != NULL) {
		printf("%s\n", pointer->data);

		pointer = pointer->next;
	}

	freeAll(head);

	return 0;
}



