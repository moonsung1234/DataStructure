
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	char* data;
	struct Node* next;
} node;
 
void createHeadNode(char* data);
void addBackNode(node* head, char* data);
void addFrontNode(node** head, char* data);
void addBetweenNode(node* prev, char* data);
void addIndexedNode(node* head, int index, char* data);
void removeFrontNode(node** head);
void removeBetweenNode(node* prev);
void removeIndexedNode(node* head, int index);
void removeHaddataNode(node* head, char* data);
node* findNamedNode(node* head, char* name);
node* findIndexedNode(node* head, int index);
void freeAll(node* head);

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

void addIndexedNode(node* head, int index, char* data) {
	if(index == 0) {
		addFrontNode(&head, data);

		return;
	}

	node* after_node = findIndexedNode(head, index - 1);
	addBetweenNode(after_node, data);
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

void removeIndexedNode(node* head, int index) {
	if(index == 0) {
		removeFrontNode(&head);

		return;
	}

	node* after_node = findIndexedNode(head, index - 1);
	removeBetweenNode(after_node);
}

void removeHaddataNode(node* head, char* data) {
	node* after_node = NULL;
	node* pointer = head;

	while(pointer != NULL && strcmp(data, pointer->data) != 0) {
		after_node = pointer;
		pointer = pointer->next;
	}
	
	if(after_node == NULL) {
		removeFrontNode(&head);
		
		return;
	}

	removeBetweenNode(after_node);
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

node* findIndexedNode(node* head, int index) {
	node* pointer = head;

	int i;
	for(i=0; i<index && pointer != NULL; i++) {
		pointer = pointer->next;
	}

	return pointer;
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
	addIndexedNode(head, 1, "node_1");
	addIndexedNode(head, 2, "node_2");
	removeIndexedNode(head, 1);
	removeHaddataNode(head, "node_2");

	node* pointer = head;
	
	while(pointer != NULL) {
		printf("%s\n", pointer->data);

		pointer = pointer->next;
	}

	freeAll(head);

	return 0;
}



