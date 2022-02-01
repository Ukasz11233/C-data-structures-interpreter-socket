#include <stdbool.h>
#define MAX 100
#define N 50
typedef struct position{
    int val;
}Position;

typedef struct node{
    Position position;
    struct node * left;
    struct node * right;
}Node;

typedef struct tree{
    Node * root;
    int size;
}Tree;

void initialize(Tree *tree);
//inicjuje drzewo

bool isEmpty(const Tree *tree);
//sprawdza czy drzewo jest puste

bool isFull(const Tree *tree);
//sprawdza czy drzewo jest pelne

int sizeOfTree(const Tree *tree);
//okresla liczbe pozycji w drzewie

bool addPosition(Tree *tree, const Position pos);
//dodaje element do drzewa

bool find(const Tree *tree, const Position *position);
//znaduje pozycje w drzewie

bool delPosition(Tree *tree, const Position *position);
//usuwa element z tablicy

void through(const Tree *tree, void (*pfun)(Position position));
//przechodzi  po drzewie i wywoluje funkcje pfun dla kazdego elementu

void freeTree(Tree *tree);
//zwalnia pamiec drzewa

void inorder(Node *node);
//Wypisuje elementy drzewa w kolejnosci inorder


Tree *copy(Tree *root);
//kopiuje drzewo i zwraca wskaznik do roota.

void copy_util(Node *tmp, Node *original);