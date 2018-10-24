#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define LETTER_COUNT 52
#define PQ_MAX 100 

typedef struct Node
{
    int frequency;
    char symbol;
    struct Node *LSON;
    struct Node *RSON;
    int time;
} Node;

int get_letter_value(char c);
Node* build(Node** PQ);
void traverse(Node* head, int arr[], int top, int *huffman);
Node* new_node(int frequency, char symbol);
int get_letter_value(char c);
Node* pop(Node** head);
void push(Node** head, Node* node);
int is_empty(Node** head);
void Heapify(Node** B, int r);
void PQ_Insert(Node** P, Node* node);
Node** PQ_Extract(Node** P);
void extract_after(Node** P);

int PQ_size = 0; 
int pushed = 0;

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
    node->time = pushed;
    pushed++;

    return node;
}


int get_letter_value(char c)
{
    int val = (int) c;
    val -= 65; //Ascii value for A
    if(val > 26) val -= 6;
    return val;
}

int is_empty(Node** head)
{
    return PQ_size == 0;
}

int main(int argc, char *argv[])
{
    char c;
    FILE *f;
    int frequency[LETTER_COUNT];
    int i, j;
    Node *(PQ[PQ_MAX]);
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
	    Node* push_node = new_node(frequency[i], letter);
	    PQ_Insert(PQ, push_node);
	}	
    }
    Node* root;
    root = build(PQ);

    int huffman[52][100];
    for(i = 0; i < 52; i++)
    {
	for(j = 0; j < 100; j++)
	{
	    huffman[i][j] = -1;
	}
    }

    int arr[100];
    traverse(root, arr, 0, *huffman);
    
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

Node* build(Node** PQ)
{
    int i;
    Node* node;
    while(PQ_size > 1)
    {
	node = new_node(0, '|');
	node->LSON = *(PQ_Extract(PQ));
	extract_after(PQ);
	node->RSON = *(PQ_Extract(PQ));
	extract_after(PQ);
	node->frequency = node->LSON->frequency + node->RSON->frequency;
	PQ_Insert(PQ, node);
    }
    Node* root = *(PQ_Extract(PQ));
	extract_after(PQ);
    return root;
}

void traverse(Node* head, int arr[], int top, int *huffman)
{
    int i;
    if(head->LSON)
    {
	arr[top] = 0;
	traverse((head)->LSON, arr, top + 1, huffman);	
    }
    if(head->RSON)
    {
	arr[top] = 1;
	traverse((head)->RSON, arr, top + 1, huffman);
    }

    if(is_leaf(head))
    {	
	int letter_val = get_letter_value(head->symbol);
	for(i = 0; i < top; i++)
	{
	    *((huffman+letter_val*100) + i) = arr[i];
	}
	*((huffman+letter_val*100) + top) = -1;
    }
}

void PQ_Insert(Node** P, Node* node)
{
    int i, j;

    //Overflow
    if (PQ_size == PQ_MAX)
    {
	printf("PQ OVERFLOW");
	return;
    }

    PQ_size++;
    i = PQ_size;
    j = i/2;

    while(i > 1 && P[j]->frequency > node->frequency ||
	    (i > 1 && P[j]->frequency == node->frequency && 
	     (P[j]->time) > (node->time)
		)
)
    {
	P[i] = P[j];
	i = j;
	j = i/2;
    }

    P[i] = node;
}

Node** PQ_Extract(Node** P)
{
    if(PQ_size <= 0)
    {
	printf("PQ UNDERFLOW");
	return NULL;
    }
    Node** x;
    x = &P[1];
    return x;
}

void extract_after(Node** P)
{
    P[1] = P[PQ_size];
    PQ_size--;
    Heapify(P, 1);
}

void Heapify(Node** B, int r)
{
    int i, j;
    Node* k  = B[r];
    i = r;
    j = 2 * i;
    
    while(j <= PQ_size)
    {
	if( j < PQ_size && B[j + 1]->frequency < B[j]->frequency ||
	    (B[j]->frequency == B[j + 1]->frequency && 
	     (B[j]->time) > (B[j + 1]->time)
		)
)
	{
	    j++;
	}
	if( B[j]->frequency < k->frequency ||
	    (B[j]->frequency == k->frequency && 
	     (B[j]->time) < (k->time)
		)
	    )
	{
	    B[i] = B[j];
	    i = j;
	    j = i * 2;
	}
	else break;
    }
    B[i] = k;

}
