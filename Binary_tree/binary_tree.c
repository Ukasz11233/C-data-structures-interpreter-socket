#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "binary_tree.h"


//struktura uzywana do usuwania wezla
typedef struct pair{
    Node *parent;
    Node *child;
}Pair;


static bool left(const Position *pos1, const Position *pos2);
static bool equal(const Position *pos1, const Position *pos2);
static Node *createNode(const Position *position);
static void addNode(Node *root, Node *new);
static Pair findPosition(const Tree *tree, const Position *pos);
static void delNode(Node **ptr);


/*
int main(void)
{
    Tree tree;
    initialize(&tree);
    Position pos;
    strcpy(pos.word, "co tam");

    addPosition(&tree, pos);
    strcpy(pos.word, "siemanko");
    addPosition(&tree, pos);
    inorder(tree.root);
    return 0;

}
*/


/*

            4
        /       \
       2          6
     /   \      /   \
    1     -    5     8
              /        \
             5          11

 */



int main(void)
{
    Tree btree;
    initialize(&btree);
    Position pos;
    bool flag;
    int arr[] = {4, 2, 6, 5, 1, 8, 11, 5};
    for(int i = 0; i < sizeof(arr)/sizeof(int); i++)
    {
        pos.val = arr[i];
        addPosition(&btree, pos);
    }
    inorder(btree.root);
    //Tree *btree2;
    //btree2 = copy(&btree);
    //inorder(btree2->root);
    putchar('\n');
    pos.val = 1;
    //printf("%d\n", pos.val);
    //printf("%d, %d\n", btree.root->position.val, btree.root->right->position.val);
    //flag = left(&btree.root->position, &btree.root->right->position);
    //printf("%d\n", flag);
    //inorder(btree.root); // print
    flag = delPosition(&btree, &pos);
    putchar('\n');
    printf("%d\n", flag);
    inorder(btree.root);
    return 0;
}


static Node *createNode(const Position *pos)
{
    Node *new;
    if((new = (Node *) malloc(sizeof(Node))) != NULL)
    {
        new -> position = *pos;
        new -> left = NULL;
        new -> right = NULL;
    }
    return new;
}


static bool left(const Position *pos1, const Position *pos2)
{
    /*
    if(strcmp(pos1 -> word, pos2 -> word) == 0)
        return true;
    else
        return false;
    */

    if(pos1 -> val <= pos2 -> val)
        return true;
    else
        return false;

}


static bool equal(const Position *pos1, const Position *pos2)
{
    if(pos1 -> val == pos2 -> val)
        return true;
    else
        return false;
}



bool addPosition(Tree *tree, Position position)
{
    if(isFull(tree))
    {
        fprintf(stderr, "Drzewo jest pelne.\n");
        return false;
    }

    Node *new;
    if((new = createNode(&position)) == NULL)
    {
        fprintf(stderr, "Nie mozna utworzyc wezla.\n");
        return false;
    }
    tree -> size++;
    if(tree -> root == NULL)
        tree -> root = new;
    else
        addNode(tree -> root, new);
    return true;

}


static void addNode(Node * root, Node *new)
{
    if(left(&(new -> position), &(root -> position)))
    {
        if(root -> left == NULL)
            root -> left = new;
        else
            addNode(root -> left, new);
    }
    else
        if(root -> right == NULL)
            root -> right = new;
        else
            addNode(root -> right, new);
}



bool find(const Tree *tree, const Position *pos)
{
    return (findPosition(tree, pos).child == NULL) ? false : true;
}


static Pair findPosition(const Tree *tree, const Position *pos)
{
    Pair find;
    find.parent = NULL;
    find.child = tree -> root;
    if(find.child == NULL)
        return find;

    while(find.child != NULL)
    {
        if(equal(&(find.child -> position), pos))
            break;
        else if(left(pos, &(find.child -> position)))
        {
            find.parent = find.child;
            find.child = find.child -> left;
        }
        else if(!left(pos, &(find.child -> position)))
        {
            find.parent = find.child;
            find.child = find.child -> right;
        }
    }

    return find;
}


bool delPosition(Tree *tree, const Position *pos)
{
    Pair find;
    find = findPosition(tree, pos);
    if(find.child == NULL)
        return false;
    if(find.parent == NULL)
        delNode(&tree -> root);
    else if(find.parent->left == find.child)
        delNode(&find.parent->left);
    else
        delNode(&find.parent->right);
    tree -> size--;
    return true;
}


static void delNode(Node **ptr)
{
    Node *tmp;
    if((*ptr) -> left == NULL)
    {
        tmp = *ptr;
        *ptr = (*ptr) -> right;
        free(tmp);
    }
    else if( (*ptr) -> right == NULL)
    {
        tmp = *ptr;
        *ptr = (*ptr) -> left;
        free(tmp);
    }
    else
    {
        for(tmp = (*ptr) -> left; tmp -> right != NULL; tmp = tmp -> right)
            continue;
        tmp -> right = (*ptr) -> right;
        tmp = *ptr;
        *ptr = (*ptr) -> left;
        free(tmp);
    }
}


void initialize(Tree *tree)
{
    tree -> root = NULL;
    tree ->size = 0;
}


bool isEmpty(const Tree *tree)
{
    return tree -> size == 0;
}


bool isFull(const Tree *tree)
{
    return tree -> size == MAX;
}


int sizeOfTree(const Tree *tree)
{
    return tree -> size;
}



void free_tree(Node *node)
{
    if(node == NULL)
        return;

    free_tree(node -> left);
    free_tree(node -> right);
    free(node);

}

void inorder(Node *node)
{
    if(node == NULL)
        return;

    inorder(node -> left);
    printf("%d ", node -> position.val);
    inorder(node -> right);

}


void copy_util(Node *tmp, Node *original)
{
    if(original == NULL)
        return;
    else
    {
        if(original -> left != NULL)
        {
            Node *new = (Node*) malloc(sizeof(Node));
            new ->position.val = original -> left ->position.val;
            tmp -> left = new;
            copy_util(tmp->left, original->left);
        }
        if(original -> right != NULL)
        {
            Node *new = (Node*) malloc(sizeof(Node));
            new ->position.val = original -> right ->position.val;
            tmp -> right = new;
            copy_util(tmp->right, original->right);
        }
    }
}


Tree *copy(Tree *tree)
{

    Tree *new_tree = (Tree *) malloc(sizeof(Tree));
    new_tree -> size = tree->size;
    if(tree -> root == NULL)
        return NULL;

    Node *new = (Node*) malloc(sizeof(Node));
    new ->position.val = tree->root->position.val;
    copy_util(new, tree->root);
    new_tree -> root = new;

    return new_tree;

}
