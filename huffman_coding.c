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
void traverse(Node* head, int arr[], int top, int *huffman);
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
    if(val >= 26) val -= 6;
    return val;
}

Node* pop(Node** head)
{
    Node* temp;
    temp = *head;
    *head = temp->next;
    temp->next = NULL;
    return temp;
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
    int i, j;
    int PQ_size = 0;
    char letter;
    Node* head = NULL;
    for(i = 0; i < LETTER_COUNT; i++)
    {
	frequency[i] = 0;
    }

    f = fopen(argv[1], "r");
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

    int huffman[52][100];
    for(i = 0; i < 52; i++)
    {
	huffman[i][0] = -1;
    }
    int arr[100];
    traverse(head, arr, 0, *huffman);
    
    for(i = 0; i < 52; i++)
    {
	if(i >= 26) letter = i + 65 + 6;
	else letter = i + 65;
	if(huffman[i][0] != -1)
	    printf("%c ", letter);
	for(j = 0; j < 100; j++)
	{
	    if(huffman[i][j] == -1) break;
	    
	    printf("%d", huffman[i][j]);
	}
	if(huffman[i][0] != -1)
	    printf("\n");
    }
}

Node* build(Node** head, int PQ_size)
{
    int i;
    Node* node;
    for(i = 0; i < PQ_size - 2; i++)
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

void traverse(Node* head, int arr[], int top, int *huffman)
{
    int i;
    if((head)->LSON)
    {
	arr[top] = 0;
	traverse((head)->LSON, arr, top + 1, huffman);	
    }
    if((head)->RSON)
    {
	arr[top] = 1;
	traverse((head)->RSON, arr, top + 1, huffman);
    }

    if(is_leaf(head))
    {	
	//printf("%c ", head->symbol);
	int letter_val = get_letter_value(head->symbol);
	for(i = 0; i < top; i++)
	{
	    *((huffman+letter_val*100) + i) = arr[i];
	    //printf("%d", arr[i]);
	}
	*((huffman+letter_val*100) + top) = -1;
    }
}
