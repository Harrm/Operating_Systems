#include <stdio.h>
#include <stdlib.h>

typedef struct linked_list {

	int value;
	struct linked_list* next;
	struct linked_list* previous;

} linked_list;



linked_list* create_list(int value) {

	linked_list* new_node = malloc(sizeof(linked_list));
	new_node->next = NULL;
	new_node->previous = NULL;
	new_node->value = value;
	return new_node;
}



linked_list* insert_node(int value, linked_list* root, size_t i) {
	if(i == 0 || root == NULL) {
		return NULL;
	}

	linked_list* current = root;
	while(--i && current != NULL) {
		current = current->next;	
	}
	if(current == NULL) {
		return NULL;
	}

	linked_list* new_node = create_list(value);
	new_node->next = current->next;
	new_node->previous = current;

	if(current->next != NULL) {
		current->next->previous = new_node;
	}

	current->next = new_node;

	return new_node;
}



void delete_node(linked_list** root, size_t i) {
	linked_list* current = *root;
	while(i-- && current != NULL) {
		current = current->next;	
	}
	if(current == NULL) {
		return;
	}
	if(current == *root) {
		*root = NULL;
		return;
	}
	
	if(current->previous != NULL) {
		current->previous->next = current->next;
	}
	if(current->next != NULL) {
		current->next->previous = current->previous;
	}
	current->next = NULL;
	current->previous = NULL;
	free(current);
}



void print_list(const linked_list* root) {
	if(root == NULL) {
		printf("EMPTY\n");
		return;
	}
	const linked_list* current = root;
	printf("{");
	while(current != NULL) {
		printf("%d ", current->value);
		current = current->next;
	}
	printf("}\n");
}



int main() {

	linked_list* l = create_list(5);

	print_list(l);

	insert_node(15, l, 1);
	insert_node(55, l, 2);

	print_list(l);

	delete_node(&l, 1);

	print_list(l);

	delete_node(&l, 1);
	delete_node(&l, 0);

	print_list(l);

	return 0;
}
