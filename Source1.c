#include <stdio.h>
#include <stdlib.h>

struct Tree {
	int value;
	struct Tree *Left;
	struct Tree *Right;
};

void TCreate();
void TInsert(int value, Tree** tree);
void Write(Tree **p, FILE* output);
Tree* Read(Tree **tree, FILE* fp);
int TCount(Tree *node);
int TCountLeaves(Tree* tree);
int isBST(Tree* tree);
void TDelete(Tree* Tree);
Tree *TSearch(Tree** tree, int value);
Tree *TSearch1(Tree** tree, int value);/*searching leaves*/
void *TSearch2(Tree** tree, int value);/*searching parent*/
int TPrint(Tree *tree, int is_Left, int offset, int depth, char s[20][255]);
void print_t(Tree *tree);

Tree* tree = NULL;
Tree* par = NULL;
Tree* tmp = NULL;

void TCreate() {
	int a = 0, N, M;
	Tree *tmp1 = NULL, *par = NULL;
	while (a != 5) {
		printf("\n1. Add root\n2. Add Tree N parent M\n3. Add Tree N sibling M.\n4. Print\n5. Exit\n");
		scanf("%d", &a);
		switch (a) {
		case 1:
			printf("Root value:\n");
			scanf("%d", &N);
			TInsert(N, &tree);
			break;
		case 2:
			printf("Value N:\n");
			scanf("%d", &N);
			printf("par M:\n");
			scanf("%d", &M);
			tmp1 = TSearch1(&tree, M);
			if (tmp1 != NULL) {
				if (tmp1->Left == NULL)
					TInsert(N, &(tmp->Left));
				else if (tmp1->Right == NULL)
					TInsert(N, &(tmp1->Right));
				else
					printf("\n%d We already have two trees", tmp1->value);
			}
			else
				printf("Value not found\n");
			break;
		case 3:
			printf("Value N:\n");
			scanf("%d", &N);
			printf("Sibling M:\n");
			scanf("%d", &M);
			tmp = NULL;
			par = NULL;
			tmp = tree;
			TSearch2(&tree, M);
			if (par != NULL) {
				if (!par->Left)
					TInsert(N, &(par->Left));
				if (!par->Right)
					TInsert(N, &(par->Right));
				else
					printf("\n%d We already have two trees", par->value);
			}
			else
				printf("Not found or we already have two Trees");
			break;
		case 4:
			print_t(tree);
			break;
		default:
			printf("Error\n");
			break;

		}
		if (a == 5)
			break;
	}
}

void TInsert(int value, Tree** tree) {
	struct Tree *newTree = NULL;
	if (!(*tree)) {
		newTree = (Tree*)malloc(sizeof(Tree));
		newTree->Left = NULL;
		newTree->Right = NULL;
		newTree->value = value;
		*tree = newTree;
		return;
	}
	else printf("\n Root is already existed \n");
}

void Write(Tree **p, FILE* output) {
	if (!(*p)) {
		fprintf(output, "# ");
	}
	else {
		fprintf(output, "%d ", (*p)->value);
		Write(&((*p)->Left), output);
		Write(&((*p)->Right), output);
	}
}

Tree* Read(Tree **tree, FILE* fp) {
	char* a;
	int in;
	a = (char *)malloc(sizeof(char) * 10);
	if (fscanf(fp, "%s", a))
		if (a[0] != '#') {
			in = atoi(a);
			TInsert(in, tree);
			printf("%d ", (*tree)->value);
			Read(&((*tree)->Left), fp);
			Read(&((*tree)->Right), fp);
		}
	return *tree;
}

int TCount(Tree *node) {
	int number = 1;
	if (node == NULL)
		return 0;
	else {
		number += TCount(node->Left);
		number += TCount(node->Right);
		return number;
	}
}

int TCountLeaves(Tree* tree) {
	if (tree == NULL) {
		return 0;
	}
	if (tree->Left == NULL && tree->Right == NULL) {
		return 1;
	}
	return TCountLeaves(tree->Left) + TCountLeaves(tree->Right);
}

int isBST(Tree* tree) {
	static struct Tree *prev = NULL;
	if (tree) {
		if (!isBST(tree->Left))
			return 0;
		if (prev != NULL && tree->value <= prev->value)
			return 0;
		prev = tree;
		return isBST(tree->Right);
	}
	return 1;
}

void TDelete(Tree* tree) {
	if (tree != 0) {
		TDelete(tree->Left);
		TDelete(tree->Right);
		free(tree);
	}
}

Tree *TSearch(Tree** tree, int value) {
	if (!(*tree)) {
		return NULL;
	}
	if (value == (*tree)->value) {
		return *tree;
	}
	else
		TSearch(&((*tree)->Left), value);
	TSearch(&((*tree)->Right), value);
}

Tree *TSearch1(Tree** tree, int value)
{
	if (!(*tree)) {
		return NULL;
	}
	else {
		if (value == (*tree)->value) {
			if ((*tree)->Left == NULL) {
				par = tmp;
				return *tree;
			}
			if ((*tree)->Right == NULL) {
				par = tmp;
				return *tree;
			}
			else {
				tmp = *tree;
				TSearch1(&((*tree)->Left), value);
				TSearch1(&((*tree)->Right), value);
			}
		}
		else {
			tmp = *tree;
			TSearch1(&((*tree)->Left), value);
			TSearch1(&((*tree)->Right), value);
		}
	}
}

void *TSearch2(Tree** tree, int value) {
	if (!(*tree))
		return NULL;
	else {
		if (value == (*tree)->value) {
			if (tmp->Left == NULL)
				if (tmp->Right == *tree) {
					par = tmp;
					return *tree;
				}
			if ((tmp->Right == NULL) && (tmp->Left == *tree)) {
				par = tmp;
				return *tree;
			}

			else {
				tmp = *tree;
				TSearch2(&((*tree)->Left), value);
				TSearch2(&((*tree)->Right), value);
			}
		}
		else {
			tmp = *tree;
			TSearch2(&((*tree)->Left), value);
			TSearch2(&((*tree)->Right), value);
		}
	}
}


int TPrint(Tree *tree, int is_Left, int offset, int depth, char s[20][255]) {
	int i = 0;
	char b[20];
	int width = 5;
	if (!tree) return 0;
	sprintf(b, "(%03d)", tree->value);
	int Left = TPrint(tree->Left, 1, offset, depth + 1, s);
	int Right = TPrint(tree->Right, 0, offset + Left + width, depth + 1, s);

	for (i = 0; i < width; i++)
		s[depth][offset + Left + i] = b[i];

	if (depth && is_Left) {

		for (i = 0; i < width + Right; i++)
			s[depth - 1][offset + Left + width / 2 + i] = '-';

		s[depth - 1][offset + Left + width / 2] = '.';

	}
	else if (depth && !is_Left) {

		for (i = 0; i < Left + width; i++)
			s[depth - 1][offset - width / 2 + i] = '-';

		s[depth - 1][offset + Left + width / 2] = '.';
	}


	return Left + width + Right;
}

void print_t(Tree *tree) {
	int i;
	char s[20][255];
	for (i = 0; i < 20; i++)
		sprintf(s[i], "%80s", " ");
	TPrint(tree, 0, 0, 0, s);
	for (i = 0; i < 20; i++)
		printf("%s\n", s[i]);
}

int main() {
	int num = 0;
	char fname[30];
	Tree *newT = NULL;
	FILE* out;
	while (num != 8) {
		printf("\n1. Create/edit tree\n2. Read from file\n3. Save in file\n4. Print tree\n5. Information about tree\n6. Search element\n7. Delete tree\n8. Exit\n");
		scanf("%d", &num);
		switch (num) {
		case 1:
			TCreate();
			break;
		case 2:
			FILE* fp;
			fp = fopen("test.txt", "rb");
			if (fp == NULL)
				while (fp == NULL) {
					printf("Error opening file\n");
					scanf("%s", fname);
					fp = fopen(fname, "rb");
				}
			Read(&tree, fp);
			printf("\n");
			fclose(fp);
			break;
		case 3:
			out = fopen("out.txt", "w");
			Write(&tree, out);
			printf("Saved in out.txt");
			fclose(out);
			break;
		case 4:
			print_t(tree);
			break;
		case 5:
			printf("Number of nodes:%d\n", TCount(tree));
			printf("Number of leaves:%d\n", TCountLeaves(tree));
			if (isBST(tree))
				printf("This tree is BST\n");
			else
				printf("This tree is not BST\n");
			break;
		case 6:
			int s;
			printf("\nSearch value is:");
			scanf("%d", &s);
			newT = TSearch(&tree, s);
			if (newT != NULL)
				printf("Value %d is found\n", s);
			else
				printf("Value %d is not found\n", s);
			break;
		case 7:
			TDelete(tree);
			break;
		}
	}
	return 0;
}