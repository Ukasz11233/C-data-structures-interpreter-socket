//#ifndef _LLIST_H_
//#define _LLIST_H_

#include <stdbool.h>
#define SIZE 45

struct type
{
    int value;
};

typedef struct type Position;

typedef struct node
{
    Position position;
    struct node *next;
}Node;

typedef Node *Llist;

//prototypy funkcji:

void initialize(Llist *llist);
//inicjalizuje liste

bool isEmpty(const Llist *llist);
//jesli lista jest pusta zwraca true

bool isFull(const Llist *llist);
//jesli lista jest pelna zwraca true

unsigned int llength(const Llist *list);
//zwraca dlugosc listy

bool addElement(Llist *list, Position pos);
//dodaje element do listy

void free_list(Llist *list);
// zwalnia pamiec list

void through(const Llist *list, void (*pfun)(Position pos));
//wywoluje funkcje przekazana przez wskaznik pfun, dla kazdeg elementu listy

void printList(const Llist *list);
//wyswietla elementy listy

bool deleteNode(Llist *llist, Position key);
//usuwa element przekazany jako key

int compareNodes(Position key, Position node);
// porownuje elementy: jesli key > node zwraca 1
//                     jeslit key == node zwraca 0
//                     jesli key < node zwraca -1

void mergeLlists(Llist *llist1, Llist *llist2);
//dopina list2 do list1

Llist copyList(Llist *llist);
// kopiuje liste i zwraca ja


bool addSortedElement(Llist *llist, Position pos);
//dodaje element w kolejnosci rosnacej