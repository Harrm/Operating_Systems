#include <stdio.h>
#include <stdlib.h>

struct List 
{

	int data;
	struct List* next;
	struct List* prev;

};



void insert_node(int data, struct List* l, int i) 
{
	if(i == 0 || l == NULL)
		return;

	struct List* c = l;
	while(--i && c != NULL) 
		c = c->next;	

	struct List* c1 = malloc(sizeof(struct List));
	c1->data = data;
	c1->next = c->next;
	c1->prev = c;

	if(c->next != NULL)
		c->next->prev = c1;


	c->next = c1;
}


void delete_node(struct List* root, size_t i) {
	struct List* c = root;
	while(i-- && c != NULL)
		c = c->next;	

	if(c == NULL) 
		return;
	
	if(c->prev != NULL) 
		c->prev->next = c->next;
	
	if(c->next != NULL) 	
		c->next->prev = c->prev;
}

void print_list(struct List* root) 
{
	if(root == NULL) 
	{
		printf("EMPTY\n");
		return;
	}
	struct List* c = root;
	while(c != NULL) 
	{
		printf("%d ", c->data);
		c = c->next;
	}
	printf("\n");
}



int main() 
{

	struct List* l = malloc(sizeof(struct List));
	print_list(l);
	insert_node(15, l, 1);
	print_list(l);
	delete_node(l, 1);
	print_list(l);

	return 0;
}
