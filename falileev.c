
//  main.c
//  1.lab
//
//  Created by Георгий Фалилеев on 28.05.17.
//  Copyright © 2017 Георгий Фалилеев. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
struct node {
    int value;
    struct node *left;
    struct node *right;
};
struct node* tree = NULL;
struct node* searchel = NULL;
struct node* parent = NULL;
struct node *tmp = NULL;
int count(struct node *n);
int countLeaves(struct node* node);
int isBST(struct node* root);
void destroy_tree(struct node* node);
void insert(int value, struct node** node);
void search(struct node** tree, int value);
void search1 (struct node** tree, int value);
void search2 (struct node** tree, int value);
void WriteInFile (struct node **p, FILE* output);
struct node* ReadFromFile (struct node **p, FILE* input);
int _print_t(struct node *tree, int is_left, int offset, int depth, char s[20][255]);
void print_t(struct node *tree);
int commands (int a);
void CreateTree();
FILE* openfile(FILE* file);
int main() {
    int command;
    while (command != 7)
    {
        printf("\n1.Создать дерево\n2.Считать из файла\n3.Показать дерево\n4.Сохранить в файл\n5.Информация о дереве\n6.Найти элемент дерева\n7.Выйти\n");
        scanf("%d", &command);
        if (command == 1)
            CreateTree();
        else if (command == 2)
        {
            char *fname=(char *)malloc(20);
            printf("Введите название файла, с которого нужно прочитать: ");
            scanf("%s",fname);
            FILE* input;
            input = fopen(fname, "rb");
            if(input == NULL)
                input = openfile(input);
            ReadFromFile(&tree, input);
            printf("\n");
            fclose(input);
            free(fname);
        }
        else if (command == 3)
            print_t(tree);
        else if (command == 4)
        {
            char *fname=(char *)malloc(20);
            printf("Введите название файла, в который нужно сохранить: ");
            scanf("%s",fname);
            FILE* output;
            output = fopen(fname, "w");
            WriteInFile(&tree, output);
            printf("\nСохранено в файл %s", fname);
            fclose (output);
            free(fname);
        }
        else if (command == 5)
        {
            printf("Узлы:%d\n", count(tree));
            printf("Ветки:%d\n", countLeaves(tree));
            if (isBST(tree))
                printf("It BST\n");
            else
                printf("Not BST\n");
            
        }
        else if (command == 6){
            int s;
            printf("\nВведите значение, которое нужно найти:");
            scanf("%d", &s);
            searchel = NULL;
            search(&tree, s);
            if(searchel)
                printf("Значение %d не найдено\n", s);
            else
                printf("Значение %d не найдено\n", s);
        }
    }
    return 0;
}
int count(struct node *n)
{
    int c = 1;
    if (n == NULL)
        return 0;
    else
    {
        c += count(n->left);
        c += count(n->right);
        return c;
    }
}
int isBST(struct node* root)
{
    static struct node *prev = NULL;
    if (root)
    {
        if (!isBST(root->left))
            return 0;
        if (prev != NULL && root->value <= prev->value)
            return 0;
        prev = root;
        return isBST(root->right);
    }
    return 1;
}
int countLeaves(struct node* node)
{
    if(node==NULL) {
        return 0;
    }
    if(node->left == NULL && node->right == NULL) {
        return 1;
    }
    return countLeaves(node->left) + countLeaves(node->right);
}
void insert(int value, struct node** node) {
    struct node *temp = NULL;
    if(!(*node)) {
        temp = (struct node*)malloc(sizeof(struct node));
        temp->left = NULL;
        temp->right = NULL;
        temp->value = value;
        *node = temp;
        return;
    }
    else printf("\nКорень уже существует\n");
}
void destroy_tree(struct node* node) {
    if (node != 0) {
        destroy_tree(node->left);
        destroy_tree(node->right);
        free(node);
    }
}
void search(struct node** tree, int value) {
    if(!(*tree)) {
        return;
    }
    if (value == (*tree)->value) {
        searchel = *tree;
        return;
    }
    else
        search(&((*tree)->left), value);
    search(&((*tree)->right), value);
}
void search1 (struct node** tree, int value)
{
    if(!(*tree)) {
        return;
    }
    else
    {
        if (value == (*tree)->value)
        {
            if((*tree)->left == NULL)
            {
                searchel = *tree;
                parent = tmp;
                return;
            }
            if((*tree)->right == NULL)
            {
                searchel = *tree;
                parent = tmp;
                return;
            }
            else
            {
                tmp = *tree;
                search1(&((*tree)->left), value);
                search1(&((*tree)->right), value);
            }
        }
        else
        {
            tmp = *tree;
            search1(&((*tree)->left), value);
            search1(&((*tree)->right), value);
        }
    }
}
void search2 (struct node** tree, int value) {
    if(!(*tree))
        return;
    else
    {
        if (value == (*tree)->value)
        {
            if(tmp->left == NULL)
                if (tmp->right == *tree)
                {
                    searchel = *tree;
                    parent = tmp;
                    return;
                }
            if((tmp->right == NULL) && (tmp->left == *tree))
            {
                searchel = *tree;
                parent = tmp;
                return;
            }
            else
            {
                tmp = *tree;
                search2(&((*tree)->left), value);
                search2(&((*tree)->right), value);
            }
        }
        else
        {
            tmp = *tree;
            search2(&((*tree)->left), value);
            search2(&((*tree)->right), value);
        }
    }
}
void WriteInFile (struct node **p, FILE* output) {
    if (!(*p)) {
        fprintf(output,"# ");
    } else {
        fprintf(output ,"%d ",(*p)->value);
        WriteInFile(&((*p)->left), output);
        WriteInFile(&((*p)->right), output);
    }
}
struct node* ReadFromFile (struct node **p, FILE* input) {
    char* token;
    int in;
    token = (char *) malloc (sizeof(char)*10);
    if (fscanf(input,"%s", token))
        if(token[0] != '#')
        {
            in = atoi (token);
            insert (in, p);
            printf("%d ", (*p)->value);
            ReadFromFile(&((*p)->left), input);
            ReadFromFile(&((*p)->right), input);
        }
    return *p;
}
int _print_t(struct node *tree, int is_left, int offset, int depth, char s[20][255])
{
    int i = 0;
    char b[20];
    int width = 5;
    if (!tree) return 0;
    sprintf(b, "(%03d)", tree->value);
    int left  = _print_t(tree->left,  1, offset,                depth + 1, s);
    int right = _print_t(tree->right, 0, offset + left + width, depth + 1, s);
    for (i = 0; i < width; i++)
        s[depth][offset + left + i] = b[i];
    if (depth && is_left) {
        for ( i = 0; i < width + right; i++)
            s[depth - 1][offset + left + width/2 + i] = '-';
        s[depth - 1][offset + left + width/2] = '.';
    } else if (depth && !is_left) {
        for ( i = 0; i < left + width; i++)
            s[depth - 1][offset - width/2 + i] = '-';
        s[depth - 1][offset + left + width/2] = '.';
    }
    return left + width + right;
}
void print_t(struct node *tree)
{
    int i;
    char s[20][255];
    for (i = 0; i < 20; i++)
        sprintf(s[i], "%80s", " ");
    _print_t(tree, 0, 0, 0, s);
    for (i = 0; i < 20; i++)
        printf("%s\n", s[i]);
}
int commands (int a){
    int N, M;
    if (a == 1)
    {
        printf("Введите значение корневого узла:\n");
        scanf("%d", &N);
        insert(N, &tree);
    }
    else if (a == 2)
    {
        printf("Значение N:\n");
        scanf("%d", &N);
        printf("Потомок M:\n");
        scanf("%d", &M);
        searchel = NULL;
        search1 (&tree, M);
        if (searchel != NULL)
        {
            if (searchel->left == NULL)
                insert(N, &(searchel->left));
            else if (searchel->right == NULL)
                insert(N, &(searchel->right));
            else printf("\n%d Имеется два узла", searchel->value);
        }
        else
            printf("Значение не найдено\n");
    }
    else if (a == 3)
    {
        printf("Значение N:\n");
        scanf("%d", &N);
        printf("Ровесник M:\n");
        scanf("%d", &M);
        searchel = NULL;
        parent = NULL;
        tmp = tree;
        search2 (&tree, M);
        if (parent != NULL)
        {
            if (!parent->left)
                insert(N, &(parent->left));
            if (!parent->right)
                insert(N, &(parent->right));
            else printf("\n%d Имеется два узла", parent->value);
        }
        else
            printf ("Не найдено или уже есть два узла");
    }
    else if (a == 4)
        print_t(tree);
    else if (a == 5)
        printf("\n...\n");
    else
        printf("Ошибка\n");
    return 0;
}

void CreateTree()
{
    int a;
    while(a != 5)
    {
        printf("\n1.добавить корневой узел\n2.добавить узел N потомок M\n3.добавить узел N ровесник M\n4.вывести\n5.выйти\n");
        scanf("%d", &a);
        commands(a);
    }
}

FILE* openfile(FILE* file){
    char fname [30];
    while (file == NULL){
        printf("Ошибка открытия файла, попробуйте еще раз:");
        scanf("%s", fname);
        file=fopen(fname, "rb");
    }
    return file;
}
