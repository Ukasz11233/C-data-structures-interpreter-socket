#include <stdbool.h>
#define MAX 100

typedef int Position;

typedef struct node
{
    Position position;
    struct node *next;
}Node;

typedef struct queue
{
    Node * front;
    Node * end;
    int length;
}Queue;



void initialize(Queue *queue);
// inicjuje kolejke

bool fullQueue(const Queue *queue);
//sprawdza czy kolejka jest pelna

bool isEmpty(const Queue *queue);
//sprawdza czy jest pusta

int queueLength(const Queue *queue);
//okresla liczbe pozycji w kolejce

bool add(Queue *queue, Position position);
//ustawia pozycje na koncu kolejki

bool get(Queue *queue, Position *position);
//odlacza pozycje z przodu kolejki

void freeQueue(Queue *queue);
//czysci kolejke

