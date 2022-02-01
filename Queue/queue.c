#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"

static void copyToNode(Node *node, Position position);
static void copyToPosition(Node * node, Position *pos);

/*
int main(void)
{
    Queue queue;
    initialize(&queue);
    Position k = 0;
    for(int i = 0; i < 5; i++)
    {
        k++;
        add(&queue, k);
    }

    while(!isEmpty(&queue))
    {
        get(&queue, &k);
        printf("%d\n", k);

    }
    return 0;
}

*/

static void copyToNode(Node *node, Position position)
{
    node -> position = position;
}

static void copyToPosition(Node *node, Position *pos)
{
    *pos = node -> position;
}


void initialize(Queue *queue)
{
    queue -> front = queue -> end = NULL;
    queue -> length = 0;
}

bool fullQueue(const Queue *queue)
{
    return queue -> length == MAX;
}

bool isEmpty(const Queue *queue)
{
    return queue -> length == 0;
}

int queueLength(const Queue *queue)
{
    return queue -> length;
}

bool add(Queue *queue, Position pos)
{
    if(fullQueue(queue))
        return false;
    Node *new = (Node *) malloc(sizeof(Node));
    if(new == NULL)
    {
        fprintf(stderr, "Blad alokacji pamieci.\n");
        exit(EXIT_FAILURE);
    }
    copyToNode(new, pos);
    new -> next = NULL;

    if(isEmpty(queue))
        queue -> front = new;
    else
        queue -> end -> next = new;
    queue -> end = new;
    queue -> length++;
    return true;

}

bool get(Queue *queue, Position *pos)
{
    Node *tmp;
    if(isEmpty(queue))
        return false;
    copyToPosition(queue -> front, pos);
    tmp = queue -> front;
    queue -> front = queue -> front -> next;
    free(tmp);
    queue -> length--;
    if(queue -> length == 0)
        queue -> end = NULL;
    return true;
}

void freeQueue(Queue *queue)
{
    Position tmp;
    while(!isEmpty(queue))
        get(queue, &tmp);
}

