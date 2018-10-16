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

Node* new_node(int frequency, char symbol)
{
    Node* node;
    node = (Node*) malloc(sizeof(Node));
    node->frequency = frequency;
    node->symbol = symbol;
    node->LSON = NULL;
    node->RSON = NULL;

    return node;
}

Node* new_PQ_node(int frequency, char symbol)
{
    Node* node;
    node = (Node*) malloc(sizeof(Node));
    node->frequency = frequency;
    node->symbol = symbol;
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

void push(Node** head, int frequency, char symbol)
{
    Node* temp = (*head);

    Node* node = new_PQ_node(frequency, symbol);

    if((*head)->frequency > frequency)
    {
	node->next = *head;
	(*head) = node;
    }
    else
    {
	while(temp->next != NULL && temp->next->frequency < frequency)
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
		head = new_PQ_node(frequency[i], letter);
	    else
		push(&head, frequency[i], letter);
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
		head = new_PQ_node(frequency[i], letter);
	    else
		push(&head, frequency[i], letter);
	}	
    }*/

    Node* temp;
    while(!is_empty(&head))
    {
	temp = pop(&head);
	printf("%c %d\n", temp->symbol, temp->frequency);
	
    }
}

Node* build(int* frequency)
{
}
