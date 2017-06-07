#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef int T;

typedef struct Node {
	T data;
	struct Node *left;
	struct Node *right;
	struct Node *parent;
} Node;

Node* getFreeNode(T value, Node *parent) {
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->left = tmp->right = NULL;
	tmp->data = value;
	tmp->parent = parent;
	return tmp;
}

void insertRoot(Node **head, int value) {
	Node *tmp = NULL;
	Node *ins = NULL;
	if (*head == NULL) {
		*head = getFreeNode(value, NULL);
		return;
	}
}
void insertDescendant(Node**head, Node**parent, int value) {
	Node *tmp = NULL;
	Node *ins = NULL;
	tmp = *parent;

	if (tmp->left) {
		tmp = tmp->left;
	}
	else {
		tmp->left = getFreeNode(value, tmp);
		return;
	}
}
void insertSibling(Node**head, Node**parent, int value) {
	Node *tmp = NULL;
	Node *ins = NULL;
	tmp = *parent;

	if (tmp->right) {
		tmp = tmp->right;
	}
	else {
		tmp->right = getFreeNode(value, tmp);
		return;
	}
}
Node *getNodeByValue(Node *tree, int value) {
	 static Node *found=NULL;
	if (tree != NULL) {
		getNodeByValue(tree->left, value);
		if (value == tree->data) {
			found = tree;
		}
		getNodeByValue(tree->right, value);
	}
	return found;
}
void showtree(struct Node *tree, int whitespace) {
	for (int i = 0; i < whitespace; i++)
		printf("	");
	if (tree != NULL) {
		printf("%d\n", tree->data);
		showtree(tree->left, whitespace + 1);
		showtree(tree->right, whitespace + 1);
	}
	else printf("\n");
}

int write(FILE *fp, Node *tree) {
	if (tree != NULL) {
		if (tree->left != NULL)
			fprintf(fp, "%d of parent %d\n", tree->left->data, tree->data);
		if (tree->right != NULL)
			fprintf(fp, "%d of parent %d\n", tree->right->data, tree->data);
		write(fp, tree->left);
		write(fp, tree->right);
	}
}
int main() {
	int quit = 0;
	int value; int value2;
	int choise;
	Node*root = NULL;
	Node*node = NULL;
	FILE* in;
	FILE* out;
	while (!quit) {
		printf("1.Add root\n");
		printf("2.Add node N parent M\n");
		printf("3.Add node N sibling(input parent) M\n");
		printf("4.Show\n");
		printf("5.load *filename*\n");
		printf("6.save *filename*\n");
		printf("7.Quit\n");
		scanf("%d", &choise);
		switch (choise) {
		case 1:
			scanf("%d", &value);
			insertRoot(&root, value);
			break;
		case 2:
			printf("N: \n");
			scanf("%d", &value);
			printf("M: \n");
			scanf("%d", &value2);
			node = getNodeByValue(root, value2);
			insertDescendant(&root,&node, value);
			break;
		case 3:
			printf("N: \n");
			scanf("%d", &value);
			printf("M: \n");
			scanf("%d", &value2);
			node = getNodeByValue(root, value2);
			insertSibling(&root,&node, value);
			break;
		case 4:
			showtree(root, 0);
			printf("\n");
			break;
		case 5:
			in = fopen("input.txt", "r");
			fscanf(in, "root %d", &value);
			insertRoot(&root, value);
			while (fscanf(in, "%d of parent %d", &value, &value2) == 2)
				node= getNodeByValue(root, value2);
				insertDescendant(&root, &node, value2);
			fclose(in);
			break;
		case 6:
			out = fopen("output.txt", "w");
			fprintf(out, "root %d\n", root->data);
			write(out, root);
			fclose(out);
			break;
		case 7:
			quit = 1;
			break;
		}
	}
}