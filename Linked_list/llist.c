#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "llist.h"
static void copyToNode(Position pos, Node *node);  // funkcja o zasiegu lokalnym



int main(void)
{
    Llist llist, llist2;
    initialize(&llist);
    initialize(&llist2);
    Position pos;
    for(int i = 0; i < 10; i++)
    {
        pos.value = i;
        if(addElement(&llist, pos) == false)
            fprintf(stderr, "Blad dodaawanie elementu nr %d", i);

    }
    printList(&llist);
    pos.value = 9;
    if(deleteNode(&llist, pos) == 0)
        fprintf(stderr, "Blad usuniecia elementu: %d\n", pos.value);
    printList(&llist);
    pos.value = 5;
    llist2 = copyList(&llist);
    deleteNode(&llist2, pos);
    pos.value = 2;
    addSortedElement(&llist2, pos);
    printList(&llist2);
    return 0;
}



static void copyToNode(Position pos, Node *node)
{
    node -> position = pos;
}


void initialize(Llist *llist)
{
    *llist = NULL;
}


bool isEmpty(const Llist *llist)
{
    if(*llist == NULL)
        return true;
    else
        return false;
}


bool isFull(const Llist *llist)
{
    Node *wsk;
    bool full = false;
    if((wsk = (Node *)malloc(sizeof(Node))) == NULL)
        full = true;
    else
        full = false;
    free(wsk);
    return full;
}


unsigned int llength(const Llist *llist)
{
    unsigned int result = 0;
    Node *tmp = *llist;
    while(tmp != NULL)
    {
        tmp = tmp -> next;
        result++;
    }
    return result;
}

bool addElement(Llist *llist, Position pos)
{
    Node *tmp = *llist;
    Node *new = (Node *)malloc(sizeof(Node));

    if(new == NULL)
        return false;
    copyToNode(pos, new);
    new -> next = NULL;
    if(tmp == NULL)
    {
        *llist = new;
    }
    else
    {
        while(tmp -> next != NULL)
            tmp = tmp -> next;
        tmp -> next = new;
    }
    //free(tmp);  //potencjalny blad
    return true;

}

void through(const Llist *llist, void (*pfun)(Position pos))
{
    Node *tmp = *llist;
    while( tmp != NULL)
    {
        pfun(tmp->position); // lub (*pfun)(tmp->position)
        tmp = tmp -> next;
    }
}

void free_list(Llist *llist)
{
    Node *tmp = *llist;
    while(tmp != NULL)
    {
        tmp = tmp -> next;
        free(*llist);
        *llist = tmp;
    }

}


void printList(const Llist *llist)
{
    Node *tmp = *llist;
    if(*llist == NULL)
    {
        fprintf(stderr, "Pusta lista.\n");
        exit(EXIT_FAILURE);
    }
    while(tmp != NULL)
    {
        printf("%d -> ", tmp -> position.value);
        tmp = tmp -> next;
    }
    printf("NULL\n");
}


bool deleteNode(Llist *llist, Position key)
{
    Node *prev = *llist;
    if(prev -> next == NULL)
    {
        if(compareNodes(key, prev -> position) == 0)
            free(prev);
        return true;
    }
    else
    {
        if(compareNodes(key, (*llist) -> position) == 0)
        {
            (*llist) = (*llist) -> next;
            free(prev);
            return true;
        }
        else
        {
            Node *curr = (*llist) -> next;
            while(curr != NULL)
            {
                if(compareNodes(key, curr -> position) == 0)
                {
                    prev -> next = curr -> next;
                    free(curr);
                    return true;
                }
                prev = curr;
                curr = curr -> next;
            }
        }
    }
    return false;
}



int compareNodes(Position key, Position node)
{
    if(key.value == node.value)
        return 0;
    else if(key.value > node.value)
        return -1;
    else
        return 1;
}


void mergeLlists(Llist *llist1, Llist *llist2)
{
    Node *tmp = *llist1;

    while(tmp -> next != NULL)
    {
        tmp = tmp -> next;
    }
    if(*llist2 != NULL)
        tmp -> next = *llist2;

}

Llist copyList(Llist *llist)
{
    Node *tmp = *llist;
    Llist new;
    initialize(&new);

    while (tmp != NULL)
    {
        addElement(&new, tmp -> position);
        tmp = tmp -> next;
    }
    return new;
}


bool addSortedElement(Llist *llist, Position pos)
{
    Node *tmp = *llist;
    Node *new = (Node *) malloc(sizeof(Node));
    copyToNode(pos, new);
    new -> next = NULL;

    if(tmp == NULL)
    {
        *llist = new;
        return true;
    }

    else
    {
        if(compareNodes(tmp -> position, pos) == -1)
        {
            new -> next = tmp;
            *llist = new;
            return true;
        }
        else
        {
            while(tmp -> next != NULL && compareNodes(tmp -> next -> position,  pos) == 1)
            {
                tmp = tmp -> next;
            }

            new -> next = tmp -> next;
            tmp -> next = new;
            return true;
        }
    }
    return false;
}


