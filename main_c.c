#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node* crnode(int val);
int add_tree(struct node *root, int val,int a,int b);
struct node* find_tree(struct node *root, int val);
void print_tree(struct node *root, int stage);
int obhod(struct node *root, int *nnode, int *inner);
struct node * roditeli(struct node *root, int val);
int categorization(FILE *file, struct node *root);

//îïèñàíèå ñòðóêòóðû, õðàíÿùåé óçåë äåðåâà
typedef struct node
{
	int key;
	struct node *left, *right;
} node;
//глобальные переменные 
int i, rd, wt, nnode, inner;

#define CHILD 1
#define BROTHERS 2
#define N 255

int main(int argc,char *argv[])
{
    FILE *rd_from, *wt_to;

    char *p = (char*)malloc (sizeof(char)*N);
    if (argc==1){
        printf("application %s methods\n", argv[0]);
        printf(":rd-rd_from\n:wt-wt_to\n");
    }
    for (i=1;i<argc;i++)
    if (strstr(argv[i], ":rd")==argv[i]){
        strcpy(p, 2+(strstr(argv[i],":rd")));
        if (fopen(p,"r"))
            rd_from = fopen(p, "r");
        else{
            printf("%s - error of reading\n", p);
            continue;
        }
        rd = 1;
    }
        else
        if (strstr(argv[i],":wt")==argv[i]){
            strcpy(p, 2+(strstr(argv[i], ":wt")));
            wt_to = fopen(p, "w");

        wt = 1;
        }
    int val, b;
    struct node* root;

    if (rd){
        fscanf(rd_from, "root %d", &val);
        root = crnode(val);
        while(fscanf(rd_from, "%d roditel %d", &val, &b)==2)
            add_tree(root,val,CHILD,b);
        fclose(rd_from);
    }
        else{
            printf("root\n");
            scanf("%d", &val);
            root = crnode(val);
        }
    printf("enter instruction:(value of value like CHILD/BROTHERS\n)");

    char a[30];
    while (scanf("%d of %d like %s", &val,&b, a)==3)
        if(strcmp(a,"CHILD")==0)
            add_tree(root, val,CHILD, b);
        else
            if (strcpy(a, "BROTHERS")==0)
                add_tree(root, val,BROTHERS, b);
        print_tree(root, 0);
        obhod(root, &nnode, &inner);
        printf("%d node, %d leaves, %d inner\n", nnode, nnode-inner, inner);

    if (wt){
        fprintf(wt_to, "root %d\n", root->key);
        categorization(wt_to, root);
        fclose(wt_to);
    }
    return 0;
}

//ñîçäàíèå êîðíåâîãî óçëà
node* crnode(int val)
{
	node* root = (node*) malloc(sizeof(node));
	root->key = val;
	root->left = NULL;
	root->right = NULL;
	return root;
}
//ôóíêöèÿ äîáàâëåíèÿ, êîòîðàÿ áóäåò ïîëó÷àòü íà âõîä óêàçàòåëü íà êîðåíü
//äåðåâà è êëþ÷ äîáàâëÿåìîãî ýëåìåíòà
int add_tree(struct node *root, int val, int a, int b)
{
    struct node *dat;
	if (a==CHILD)
        dat=find_tree(root,b);
    else
    if (a==BROTHERS){
        dat=roditeli(root,b);
    }
    if (((NULL!=dat->left)&&(NULL!=dat->right))||(NULL==dat))
        return 1;
    if (NULL==dat->left){
        (dat->left)=crnode(val);
    }
    else if (NULL==dat->right){
        (dat->right)=crnode(val);
        }
}

//îáõîä äåðåâà
int obhod (struct node *root, int *nnode, int *inner) {
 	if (NULL!=root) {
 		if ((NULL!=root->left) || (NULL!=root->right))
 			(*inner)++;
 		(*nnode)++;
 		obhod(root->left, nnode, inner);
		obhod(root->right, nnode, inner);
	}
 }
//ôóíêöèÿ ïîèñêà ýëåìåíòà, êîòîðàÿ âîçâðàùàåò óêàçàòåëü íà ýëåìåíò, ñîäåðæàùèé èñêîìûé êëþ÷ èëè NULL
struct node* find_tree(struct node *root, int val)
{
    struct node*temp=0;
	if (NULL == root)
		return NULL;
	if (val == root->key)
		return root;
	if ((temp=find_tree(root->left, val))!=0)
        return temp;
    if ((temp=find_tree(root->right, val))!=0)
        return temp;
    }
//ôóíêöèÿ âûâîäà ìàññèâà ïî äåðåâó
void print_tree(struct node *root, int stage)
{
    int i;
    for(i=0;i<stage;i++)
        printf("    ");
	if (NULL!=root) {
		print_tree(root->left,stage+1);
		printf("%d ", root->key);
		print_tree(root->right,stage+1);
	}
}
int categorization(FILE *file, struct node *root) {
	if (NULL!=root) {
 		if (NULL!=root->left)
			fprintf(file, "%d roditel %d\n", root->left->key, root->key);
 		if (NULL!=root->right)
 			fprintf(file, "%d roditel %d\n", root->right->key, root->key);
		categorization(file, root->left);
 		categorization(file, root->right);
	}
}
struct node * roditeli(struct node *root, int val) {
    struct node*temp=0;
        if (NULL==root)
            return NULL;
        else if (NULL!=root->left)
        {
                    if (root->left->key == val)
 				return temp=root;
        }
 		else if (NULL!=root->right)
        {
                    if (root->right->key == val)
 				return temp=root;
        }
 		roditeli(root->left, val);
 		roditeli(root->right, val);
 }


