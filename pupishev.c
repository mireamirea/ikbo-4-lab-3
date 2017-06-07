#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i, readen, writen, nodes, internal;

struct node {
    int key;
    struct node *left;
    struct node *right;
};

struct node * parent(struct node *tree, int first);
struct node init(int first);
struct node * search(struct node *tree, int first);
int insert(struct node *tree, int first, int ds, int second);
void show(struct node *tree, int whitespace);
void traverse(struct node *tree, int *nodes, int *internal);

int main(void){
    int first, second;
    struct node tree;
    printf("Корень: \n");
    scanf("%d", &first);
    tree = init(first);
    printf("number of number as s/d\n");
    char ds[2];
    while (scanf("%d of %d as %c", &first, &second, &ds) == 3)
        if (strcmp(ds, "d") == 0)
            insert(&tree, first, 1, second);
        else if (strcmp(ds, "s") == 0)
            insert(&tree, first, 2, second);
    show(&tree, 0);
    traverse(&tree, &nodes, &internal);
    printf("%d узлов, %d веток, %d внутренних узлов\n", nodes, nodes-internal, internal);
    return 0;
}

struct node init(int first) {
    struct node *poin;
    poin = (struct node*)malloc (sizeof(struct node));
    poin->key = first;
    poin->right = NULL;
    poin->left = NULL;
    return *poin;
}

struct node * parent(struct node *tree, int first) {
    static struct node *found;
    if (tree != NULL) {
        if (tree->left != NULL)
            if (tree->left->key == first)
                found = tree;
        if (tree->right != NULL)
            if (tree->right->key == first)
                found = tree;
        parent(tree->left, first);
        parent(tree->right, first);
    }
    return found;
}

struct node * search(struct node *tree, int first){
    static struct node *found;
    if (tree != NULL) {
        search(tree->left, first);
        if (first == tree->key){
            found = tree;
        }
        search(tree->right, first);
    }
    return found;
}

int insert(struct node *tree, int first, int ds, int second) {
    struct node *ison = NULL;
    if (ds == 1)
        ison = search(tree, second);
    else if (ds == 2) {
        ison = parent(tree, second);
    }
    if ((ison == NULL) || ((ison->left != NULL) && (ison->right != NULL)))
        return 1;
    if (ison->left == NULL) {
        ison->left = (struct node *) malloc(sizeof(struct node));
        *(ison->left) = init(first);
    }
    else
        if (ison->right == NULL) {
            ison->right = (struct node *) malloc(sizeof(struct node));
            *(ison->right) = init(first);
        }
    return  -1;
}

void show(struct node *tree, int whitespace) {
    int i;
    for (i = 0; i < whitespace; i++)
        printf("	");
    if (tree != NULL) {
        printf("%d\n", tree->key);
        show(tree->left, whitespace+1);
        show(tree->right, whitespace+1);
    }
    else
        printf("\n");
}

void traverse(struct node *tree, int *nodes, int *internal) {
    if (tree != NULL) {
        if ((tree->left != NULL) || (tree->left != NULL))
            (*internal)++;
        (*nodes)++;
        traverse(tree->left, nodes, internal);
        traverse(tree->right, nodes, internal);
    }
}
