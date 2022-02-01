#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"


static void copyToNode(Node *tmp, Position pos);
static void copyToPosition(Node *tmp, Position *pos);

/*

int main(void)
{
    Stack stack;
    initialize(&stack);
    Position pos = 5, pos2;
    add(&stack, pos);
    pos = 6;
    add(&stack, pos);
    add(&stack, pos);
    get(&stack, &pos2);
    printf("%d ", pos2);
    get(&stack, &pos2);
    printf("%d ", pos2);
    get(&stack, &pos2);
    printf("%d ", pos2);
    return 0;
}

*/

void initialize(Stack *stack)
{
    stack ->front = NULL;
    stack ->length = 0;
}

bool fullStack(const Stack *stack)
{
    return stack -> length == MAX;
}

bool isEmpty(const Stack *stack)
{
    return stack ->length == 0;
}

int stackLength(const Stack *stack)
{
    return stack -> length;
}

bool add(Stack *stack, Position pos)
{
    if(fullStack(stack))
        return false;
    Node * new = (Node *) malloc(sizeof(Node));
    copyToNode(new, pos);
    new ->next = NULL;
    if(stack -> front == NULL)
    {
        stack -> front = new;

    }
    else
    {
        new -> next = stack -> front;
        stack -> front = new;
    }

    stack -> length++;
    return  true;
}

bool get(Stack *stack, Position *pos)
{
    if(isEmpty(stack))
        return false;
    Node *tmp = stack -> front;
    stack -> front = stack -> front -> next;
    stack -> length--;
    copyToPosition(tmp, pos);
    free(tmp);
    return true;

}



static void copyToNode(Node *node, Position pos)
{
    node -> position = pos;
}

static void copyToPosition(Node *node, Position *pos)
{
    *pos = node -> position;
}