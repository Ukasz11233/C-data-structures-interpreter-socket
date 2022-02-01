#include <stdbool.h>
#define MAX 100

typedef int Position;

typedef struct node
{
    Position position;
    struct node *next;
}Node;

typedef struct stack
{
    Node * front;
    int length;
}Stack;



void initialize(Stack *stack);
// inicjuje stos

bool fullStack(const Stack *stack);
//sprawdza czy stos jest pelny

bool isEmpty(const Stack *stack);
//sprawdza czy jest pusty

int stackLength(const Stack *stack);
//okresla liczbe pozycji w stosie

bool add(Stack *stack, Position position);
//ustawia pozycje na stosie

bool get(Stack *stack, Position *position);
//zdjemuje pierwszy element ze stosu

void freeStack(Stack *stack);
//czysci stos

