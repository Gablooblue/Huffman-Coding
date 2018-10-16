#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define LETTER_COUNT 52

typedef struct Node
{
    int frequency;
    char symbol;
    struct Node *LSON;
    struct Node *RSON;
    struct Node *next;
} Node;

int get_letter_value(char c);
Node* build(Node** head, int PQ_size);
//void traverse(Node** head);
void traverse(Node* head, int arr[], int top);
Node* new_node(int frequency, char symbol);
int get_letter_value(char c);
Node* pop(Node** head);
void push(Node** head, Node* node);
int is_empty(Node** head);

int is_leaf(Node* node)
{
    return node->LSON == NULL && node->RSON ==NULL;
}

Node* new_node(int frequency, char symbol)
{
    Node* node;
    node = (Node*) malloc(sizeof(Node));
    node->frequency = frequency;
    node->symbol = symbol;
    node->LSON = NULL;
    node->RSON = NULL;
    node->next = NULL;

    return node;
}


int get_letter_value(char c)
{
    int val = (int) c;
    val -= 65; //Ascii value for A
    return val;
}

Node* pop(Node** head)
{
    Node* temp;
    temp = *head;
    *head = (*head)->next;
    return (temp);
}

void push(Node** head, Node* node)
{
    Node* temp = (*head);

    if((*head)->frequency > node->frequency)
    {
	node->next = *head;
	(*head) = node;
    }
    else
    {
	while(temp->next != NULL && temp->next->frequency < node->frequency)
	{
	    temp = temp->next;
	}

	node->next = temp->next;
	temp->next = node;
    }
}

int is_empty(Node** head)
{
    return (*head) == NULL;
}

int main(int argc, char *argv[])
{
    char c;
    FILE *f;
    int frequency[LETTER_COUNT];
    int i;
    int PQ_size = 0;
    Node* head = NULL;
    f = fopen(argv[1], "r");
    for(i = 0; i < LETTER_COUNT; i++)
    {
	frequency[i] = 0;
    }
    do
    {
	c = fgetc(f);
	if(isalpha(c))
	{
	    i = get_letter_value(c);
	    frequency[i]++;
	}
	
    }while(c != EOF);

    for(i = 0; i < LETTER_COUNT; i++)
    {
	char letter;
	if (i < 26) letter = (i + 65);
	else letter = (i + 6 +65);
	if(frequency[i] != 0 )
	{
	    //printf("%c %d\n", letter, frequency[i]);
	    if(head == NULL)
	    {
		head = new_node(frequency[i], letter);
		PQ_size = 1;
	    }
	    else
	    {
		Node* push_node = new_node(frequency[i], letter);
		push(&head, push_node);
		PQ_size++;
	    }
	}	
    }

    /*
    for(i = 0; i < LETTER_COUNT; i++)
    {
	char letter;
	if (i < 26) letter = (i + 65);
	else letter = (i + 6 +65);
	if(frequency[i] != 0 )
	{
	    //printf("%c %d\n", letter, frequency[i]);
	    if(head == NULL)
		head = new_node(frequency[i], letter);
	    else
		push(&head, frequency[i], letter);
	}	
    }*/

    /* For printing PQ
    Node* temp;
    while(!is_empty(&head))
    {
	temp = pop(&head);
	printf("%c %d\n", temp->symbol, temp->frequency);
    }*/

    Node* root;
    root = build(&head, PQ_size);

    int arr[100];
    //traverse(head, arr, 0);
}

Node* build(Node** head, int PQ_size)
{
    int i;
    Node* node;
    for(i = 0; i < PQ_size ; i++)
    {
	node = new_node(0, '|');
	node->LSON = pop(head);
	node->RSON = pop(head);
	node->frequency = node->LSON->frequency + node->RSON->frequency;
	push(head, node);
    }
    Node* root = pop(head);
    return root;
}

/*
void traverse(Node** head)
{
    int i;
    char outputs[52][200];
    Node* temp = *head;

    for(i = 0; i < LETTER_COUNT; i++)
    {
	char letter;
	if (i < 26) letter = (i + 65);
	else letter = (i + 6 +65);

	while(temp->symbol != letter)
	{
	     
	}

	temp = *head;
    }
    

    
}*/

void traverse(Node* head, int arr[], int top)
{
    int i;
    if((head)->LSON)
    {
	arr[top] = 0;
	traverse((head)->LSON, arr, top + 1);
    }
    if((head)->RSON)
    {
	arr[top] = 0;
	traverse((head)->RSON, arr, top + 1);
    }

    if(is_leaf(head))
    {
	int size = sizeof(*arr) / sizeof(int);
	printf("%c", head->frequency);
	for(i = 0; i < size; i++)
	{
	    printf("%d", arr[i]);
	}
    }
}
