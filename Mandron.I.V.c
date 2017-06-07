#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>


typedef struct node {
	int key;
	struct node *left, *right;
} node;

node* crnode(int val) {
	node* nnode = (node*)malloc(sizeof(node));
	nnode->key = val;
	nnode->left = NULL;
	nnode->right = NULL;
	return nnode;
}

node* create_tree(node *root, int key) {
		if (NULL == root) {
		root = crnode(key);
		printf("The root is created ");
	}
	return root;
}

node* add_tree(node *root, int val, int index) {
	if (root == NULL) {
		return NULL;
	}
	if (index == root->key) {
		if (NULL == root->left)
			root->left = crnode(val);
		else if (NULL == root->right)
			root->right = crnode(val);
		else {
			printf("The branch has a maximum of leaves\n");
			return root;
		}
	}
	else {
		add_tree(root->left, val, index);
		add_tree(root->right, val, index);
	}
	return root;
}

void del_tree(node *root)
{
	if (root != NULL)
	{
		del_tree(root->left);
		del_tree(root->right);
		free(root);
	}
}

void print_tree(node *root, int i) {
	int iter;
	if (root != NULL) {
		printf(" %d\n", root->key);
		if (root->left != NULL) {
			for (iter = 0; iter < i; iter++) printf("-");
			i++;
			print_tree(root->left, i);
			i--;
		}
		if (root->right != NULL) {
			for (iter = 0; iter < i; iter++) printf("-");
			i++;
			print_tree(root->right, i);
			i--;
		}
	}
}

void fprint_tree(FILE *fp, node *root, int i) {
	int iter;
	if (root != NULL) {
		fprintf(fp, " %d\n", root->key);
		if (root->left != NULL) {
			for (iter = 0; iter < i; iter++) fprintf(fp, "-");
			i++;
			fprint_tree(fp, root->left, i);
			i--;
		}
		if (root->right != NULL) {
			for (iter = 0; iter < i; iter++) fprintf(fp, "-");
			i++;
			fprint_tree(fp, root->right, i);
			i--;
		}
	}
}

void save_tree(node *Tree, FILE **openFile) {
	if (Tree != NULL) {
		fwrite(Tree, sizeof(node), 1, *openFile);
		if (Tree->left != NULL)
			save_tree(Tree->left, openFile);
		if (Tree->right != NULL)
			save_tree(Tree->right, openFile);
	}
}

void load_tree(node **Tree, FILE **openFile) {
	if (!feof(*openFile)) {
		(*Tree) = (node*)malloc(sizeof(node));
		fread(*Tree, sizeof(node), 1, *openFile);
		if ((*Tree)->left != NULL)
			load_tree(&((*Tree)->left), openFile);
		if ((*Tree)->right != NULL)
			load_tree(&((*Tree)->right), openFile);
	}
}

int find_tree(node *root, int val) {
	if (NULL == root)
		return 0;
	if (val == root->key)
		return 1;
	return find_tree(root->left, val);
	return find_tree(root->right, val);
}

void status_tree(node *tree, int flag) {
	static int leaf = 0, node = 0;
	if (flag == 1) {
		leaf = 0;
		node = 0;
	}
	if (tree != NULL) {
		node++;
		if (tree->left != NULL)
			status_tree(tree->left, 0);
		if (tree->right != NULL)
			status_tree(tree->right, 0);
		if ((tree->left == NULL) && (tree->right == NULL))
			leaf++;
	}
	if (flag == 1)
		printf("Leaf = %d; All node = %d; Node = %d\n", leaf, node, node - leaf);
}

unsigned int countNodes(node* root)
{
	if (root == NULL)
		return (0);
	return (1 + countNodes(root->left) + countNodes(root->right));
}

int isCompleteUtil(node* root, unsigned int index, unsigned int number_nodes)
{
	if (root == NULL)
		return (1);

	if (index >= number_nodes)
		return (0);

	return (isCompleteUtil(root->left, 2 * index + 1, number_nodes) &&
		isCompleteUtil(root->right, 2 * index + 2, number_nodes));
}

int isHeapUtil(node* root)
{
	if (root->left == NULL && root->right == NULL)
		return (1);

	if (root->right == NULL)
	{

		return (root->key >= root->left->key);
	}
	else
	{

		if (root->key >= root->left->key &&
			root->key >= root->right->key)
			return ((isHeapUtil(root->left)) &&
			(isHeapUtil(root->right)));
		else
			return (0);
	}
}

int isHeap(node* root)
{

	unsigned int node_count = countNodes(root);
	unsigned int index = 0;

	if (isCompleteUtil(root, index, node_count) && isHeapUtil(root))
		return 1;
	return 0;
}

int main() {
	FILE *fp;
	setlocale(LC_ALL, "rus");
	int dei = -1, temp, temp1, flag;
	node *tree = NULL;
	char str[256], txt[]=".txt";
	for (;;) {
		printf("\tSelect an action:\n\t1. Create root\n\t2. Add node\n\t3. Find a node\n\t4. Display the tree on the screen\n");
		printf("\t5. Delete Tree\n\t6. Save the tree to a file\n\t7. Load tree from file\n\t8. Display statistics on the screen\n\t0. Exit\n\t");
		dei = -1;
		for (;;) {
			if ((dei >= 0) && (dei <= 8)) break;
			scanf("%d", &dei);
		}
		switch (dei) {

		case 1:
				printf("Root: ");
				scanf("%d", &temp);
				tree = create_tree(tree, temp);
				printf("Root created\n");

			break;

		case 2:

				printf("Parent's key: ");
				scanf("%d", &temp);
				printf("Node: ");
				scanf("%d", &temp1);
				tree = add_tree(tree, temp1, temp);
				printf("The node is created\n");
				break;


		case 3:
			printf("Node: ");
			scanf("%d", &temp);
			temp1 = find_tree(tree, temp);
			if (temp1 == 1)
				printf("Node exists\n");
			else
				printf("Host does not exist\n");
			break;
		case 4:
			print_tree(tree, 1);
			break;
		case 5:
			del_tree(tree);
			break;
		case 6:
			printf("Enter the file name:\n");
			scanf("%s", str);
			fp = fopen(str, "w");
			save_tree(tree, &fp);
			fclose(fp);
			strcat(str, txt);
			fp = fopen(str, "w");
			fprint_tree(fp, tree, 1);
			fclose(fp);
			break;
		case 7:
			del_tree(tree);
			printf("Enter the file name:\n");
			scanf("%s", str);
			fp = fopen(str, "r");
			if (fp != NULL) {
				load_tree(&tree, &fp);
				fclose(fp);
			}
			else printf("Incorrect filename\n");
			break;
		case 8:
			status_tree(tree, 1);
			flag = isHeap(tree);
			if (flag == 1)
				printf("Not a heap\n");
			else
				printf("Heap\n");
			break;
		case 0:
			return 0;
			break;
		}


	}
	return 0;
}
/*printf("GG\n");*/
