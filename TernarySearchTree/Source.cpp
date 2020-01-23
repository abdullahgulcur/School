#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/*Abdullah Gulcur 150116014
*Adds intergers to tst according to specific formula
*There are lotta useful functions like min, max, min&max depth, total numbers
*They useful for getting 4 max dephted tree
*And also remove function to remove specific node
*/

struct Node {

	int value;
	struct Node *left;
	struct Node *middle;
	struct Node *right;

};

typedef struct Node Node;

void findSecFormula(int x, Node * n);
Node * add(int x, Node * n);
Node * remove(int x, Node * n);
void find(int x, Node * n);
void print(Node * n);
int max(Node * n);
int min(Node * n);
void scanAdd(Node * n, Node ** r, int x);
void insert(Node ** tree, int val);
void insertSecFormula(Node ** tree, int val);
int minDepth(Node * root);
int min(int x, int y);
int min(int x, int y, int z);
int max(int x, int y, int z);
int max(int x, int y);
int maxDepth(Node * n);
int totalNumbers(Node * n);
void try_insert(Node ** tree, int val, int x, int y, int z);

int main() {

	Node * n = NULL; // for triple

	FILE *f = fopen("input.txt", "r");
	char s[20];

	/*
	while (!feof(f)) {

		fscanf(f, "%s ", s);
		int number = atoi(s);
		insert(&n, number);
	}
	
	//n = remove(6, n);
	//n = remove(2000, n);

	fseek(f, 0, SEEK_SET);
	
	while (!feof(f)) {
		fscanf(f, "%s ", s);
		int number = atoi(s);
		find(number, n); printf("\n");
	}
	*/
	
	
	//Second formula

	
	while (!feof(f)) {

		fscanf(f, "%s ", s);
		int number = atoi(s);
		insertSecFormula(&n, number);
	}

	fseek(f, 0, SEEK_SET);

	while (!feof(f)) {
		fscanf(f, "%s ", s);
		int number = atoi(s);
		findSecFormula(number, n); printf("\n");
	}
	

	
	/*
	//finding formula is below

	int x = 0;
	int y = 0;
	int z = 0;

	int a = 0;
	int b = 0;
	int c = 0;

	int offset = 300;

	while (z < offset) {

		y = 0;
		while (y < offset) {

			x = 0;
			while (x < offset) {

				n = NULL;

				while (!feof(f)) {

					fscanf(f, "%s ", s);
					int number = atoi(s);
					try_insert(&n, number, x, y, z);
				}

				if (totalNumbers(n) == 19 && maxDepth(n) == 4) {
					a = x;
					b = y;
					c = z;
					printf("---------------------");
					x = y = z = offset;
					break;
				}
				x++;
				fseek(f, 0, SEEK_SET);
				free(n);
			}
			y++;
		}
		z++;
	}

	printf("a: %.2f b: %.2f c: %d  \n", (float)a/100, (float)b / 100, c);
	
	*/

	// for triple
	print(n);

	printf("total: %d ", totalNumbers(n));

	printf("min depth: %d ", minDepth(n));
	printf("max depth: %d ", maxDepth(n));
	

}

void try_insert(Node ** tree, int val, int x, int y, int z) // it try to insert nodes to get better tree
{
	float a = 0.01f * x;
	float b = 0.01f * y;
	//float c = 0.01f * z;

	//printf("-----%1.2f", a);

	Node *temp = NULL;
	if (!(*tree))
	{
		temp = (Node *)malloc(sizeof(Node));
		temp->left = temp->right = temp->middle = NULL;
		temp->value = val;
		*tree = temp;
		return;
	}

	if (val < pow((*tree)->value, a) + z)
		try_insert(&(*tree)->left, val, x, y, z);

	else if (val >= pow((*tree)->value, a) + z && val <= pow((*tree)->value, b) + z)
		try_insert(&(*tree)->middle, val, x, y, z);

	else if (val > pow((*tree)->value, b) + z)
		try_insert(&(*tree)->right, val, x, y, z);

}

void findSecFormula(int x, Node * n) { // finds for sec formula

	if (x == n->value) {
		printf("%d ", x);
		return;
	}

	if (n == NULL) {
		printf("not found!");
		return;
	}


	if (x < pow(n->value,1.17) + 1) {
		printf("left-");
		findSecFormula(x, n->left);
	}

	if (x >= pow(n->value, 1.17) + 1 && x <= pow(n->value, 2.02) + 1) {
		printf("middle-");
		findSecFormula(x, n->middle);
	}

	if (x > pow(n->value, 2.02) + 1) {
		printf("right-");
		findSecFormula(x, n->right);
	}

	

}

void insert(Node ** tree, int val) // inserts new node
{
	Node *temp = NULL;
	if (!(*tree))
	{
		temp = (Node *)malloc(sizeof(Node));
		temp->left = temp->right = temp->middle = NULL;
		temp->value = val;
		*tree = temp;
		return;
	}

	if (val < pow((*tree)->value, 1))
		insert(&(*tree)->left, val);

	else if (val >(*tree)->value && val <= pow((*tree)->value, 2))
		insert(&(*tree)->middle, val);

	else if (val > pow((*tree)->value, 2))
		insert(&(*tree)->right, val);

}

void insertSecFormula(Node ** tree, int val)// 1.17 , 2.02 , 1
{
	
	Node *temp = NULL;
	if (!(*tree))
	{
		temp = (Node *)malloc(sizeof(Node));
		temp->left = temp->right = temp->middle = NULL;
		temp->value = val;
		*tree = temp;
		return;
	}

	if (val < pow((*tree)->value, 1.17) + 1)
		insertSecFormula(&(*tree)->left, val);

	else if (val >= pow((*tree)->value, 1.17) + 1 && val <= pow((*tree)->value, 2.02) + 1)
		insertSecFormula(&(*tree)->middle, val);

	else if (val > pow((*tree)->value, 2.02) + 1)
		insertSecFormula(&(*tree)->right, val);

}

int totalNumbers(Node * n) { // returns total number of nodes in tree

	int c = 1;
	if (n == NULL)
		return 0;
	else
	{
		c += totalNumbers(n->left);
		c += totalNumbers(n->middle);
		c += totalNumbers(n->right);
		return c;
	}
}

int maxDepth(Node * n) { // finds max depth in tree

	if (n == NULL)
		return 0;
	///
	if (n->left == NULL && n->right == NULL && n->middle == NULL)
		return 1;
	///
	if (n->left == NULL && n->right == NULL && n->middle != NULL)
		return maxDepth(n->middle) + 1;

	if (n->left == NULL && n->right != NULL && n->middle == NULL)
		return maxDepth(n->right) + 1;

	if (n->left != NULL && n->right == NULL && n->middle == NULL)
		return maxDepth(n->left) + 1;
	///

	if (n->left != NULL && n->right != NULL && n->middle == NULL)
		return max(maxDepth(n->left), maxDepth(n->right)) + 1;

	if (n->left != NULL && n->right == NULL && n->middle != NULL)
		return max(maxDepth(n->left), maxDepth(n->middle)) + 1;

	if (n->left == NULL && n->right != NULL && n->middle != NULL)
		return max(maxDepth(n->middle), maxDepth(n->right)) + 1;


	if (n->left != NULL && n->right != NULL && n->middle != NULL)
		return max(maxDepth(n->left), maxDepth(n->right), maxDepth(n->middle)) + 1;

}

int minDepth(Node * n) { // finds min depth in tree

	if (n == NULL)
		return 0;
	///
	if (n->left == NULL && n->right == NULL && n->middle == NULL)
		return 1;
	///
	if (n->left == NULL && n->right == NULL && n->middle != NULL)
		return minDepth(n->middle) + 1;

	if (n->left == NULL && n->right != NULL && n->middle == NULL)
		return minDepth(n->right) + 1;

	if (n->left != NULL && n->right == NULL && n->middle == NULL)
		return minDepth(n->left) + 1;
	///

	if (n->left != NULL && n->right != NULL && n->middle == NULL)
		return min(minDepth(n->left), minDepth(n->right)) + 1;

	if (n->left != NULL && n->right == NULL && n->middle != NULL)
		return min(minDepth(n->left), minDepth(n->middle)) + 1;

	if (n->left == NULL && n->right != NULL && n->middle != NULL)
		return min(minDepth(n->middle), minDepth(n->right)) + 1;


	if (n->left != NULL && n->right != NULL && n->middle != NULL)
		return min(minDepth(n->left), minDepth(n->right), minDepth(n->middle)) + 1;


}

int max(int x, int y) { // returns bigger int
	if (x >= y)
		return x;
	else
		return y;
}\

int max(int x, int y, int z) { // returns biggest int
	if (max(x, y) >= z)
		return max(x, y);
	else
		return z;
}

int min(int x, int y) { // returns smaller int
	if (x <= y)
		return x;
	else 
		return y;
}

int min(int x, int y, int z) { // returns smallest int
	if (min(x,y) <= z)
		return min(x, y);
	else 
		return z;
}

void find(int x, Node * n) { // finds node

	if (n == NULL) {
		printf("not found!");
		return;
	}
		

	if (x < n->value) {
		printf("left-");
		find(x, n->left);
	}

	if (x > n->value && x <= pow(n->value, 2)) {
		printf("middle-");
		find(x, n->middle);
	}

	if (x > pow(n->value, 2)) {
		printf("right-");
		find(x, n->right);
	}

	if (x == n->value) {
		printf("%d ", x);
		return;
	}

}

int max(Node * n) { // finds max in tree
	while (n->right != NULL)
		n = n->right;
	return n->value;
}

int min(Node * n) {// finds min in tree
	while (n->left != NULL)
		n = n->left;
	return n->value;
}


Node * remove(int x, Node * n) { // removes node

	if (n == NULL)
		return NULL;

	if (n->value == x) {

		Node * root = NULL;
		scanAdd(n, &root, x);
		return root;
	}

	if (x < n->value)
		n->left = remove(x, n->left);

	if (x > n->value && x <= pow(n->value, 2))
		n->middle = remove(x, n->middle);


	if (x > pow(n->value, 2))
		n->right = remove(x, n->right);
	

	return n;

}


void scanAdd(Node * n, Node ** r, int x) { // its gonna be used for remove function
	// node is removed in remove function and comes here to add new nodes

	if (n->value != x) {
		insert(&(*r), n->value);
		//insertSecFormula(&(*r), n->value);
	}

	if (n->middle != NULL) {
		scanAdd(n->middle, &(*r), x);
	}

	if (n->left != NULL) {
		scanAdd(n->left, &(*r) ,x);
	}

	if (n->right != NULL) {
		scanAdd(n->right, &(*r), x);
	}


}


void print(Node * n) { // prints the all tree

	if (n->left != NULL) {
		print(n->left);
	}
		

	printf("%d\n", n->value);
	
	if (n->middle != NULL) {
		print(n->middle);
	}
		
	if (n->right != NULL) {
		print(n->right);
	}
		
}
