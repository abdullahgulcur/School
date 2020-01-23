#include <stdlib.h>
#include <stdio.h>
#include <time.h>
/*
*Abdullah Gulcur ----150116014----  DATA STRUCTURE PROJECT-2
*
*This program constructs different bst topologies........
*
*Compiled in Visual Studio
*/

// algorithm: 
// permutate given sequence and if it constructs same bst with given sequence then it has same bst topology

struct Node {

	int key;
	struct Node* left;
	struct Node* right;
};

typedef struct Node Node; 

Node* insert(Node* node, int key);
void inorder(Node* root);
Node* newNode(int item);
void printarray(int arr[], int size);
void free_tree(Node* node);
int isSameStructure(Node* a, Node* b);
void heapPermutation(int a[], int size, int n);
void heapPermutation1(int a[], int size, int n);
void swap1(int* a, int* b);
int getParent(Node* root, int val);
void printArr(int a[], int n);
int deleteElement(int arr[], int n, int x);
int findNode(Node* node, int key);
void printTree(int arr[], int size);

Node* tree = NULL;
int count = 0;

int main()
{
	clock_t t;
	t = clock();



	int arr_size;

	printf("Enter the size of the array: ");
	scanf_s("%d", &arr_size);
	int * input = (int*)malloc(sizeof(int) * (arr_size));
	int counter = 0;

	while (counter < arr_size)
	{
		printf("Enter array element %d: ", counter);
		scanf_s("%d", (input + counter));
		counter++;
	}

	//int arr[] = {18,12,8,4,2,16,14,15};//,17,36,24,20,21,72,54
	//int arr[] = { 1,2,3,4,5,6,7,8 };//,17,36,24,20,21,72,54

	int * arr = input;

	int size0 = arr_size;
	int* arr0 = (int*)malloc(sizeof(int) * (size0));

	int i;
	for (i = 0; i < size0; i++)
		arr0[i] = arr[i];

	int * newArr = (int*)malloc(sizeof(int) * (size0));
	newArr = arr;

	for (i = 0; i < size0; i++)
		tree = insert(tree, arr[i]);

	printf("\nTraversal\n");
	inorder(tree);
	printf("-------\n");

	printTree(arr0, size0);

	int index = 0;
	int size1 = size0;

	printf("\nPermutation\n");
	printf("-------\n");
	if (tree->left != NULL && tree->right == NULL) {


		int n = deleteElement(newArr, size1, tree->left->key);
		printArr(newArr, --size1);

		n = deleteElement(newArr, size1, tree->key);
		printArr(newArr, --size1);

		heapPermutation(newArr, size1, size1);
	}

	else if (tree->left == NULL && tree->right != NULL) {

		int n = deleteElement(newArr, size1, tree->right->key);
		printArr(newArr, --size1);

		n = deleteElement(newArr, size1, tree->key);
		printArr(newArr, --size1);

		heapPermutation1(newArr, size1, size1);
	}

	
	else if (tree->left != NULL && tree->right != NULL) {

		
		int n = deleteElement(newArr, size1, tree->left->key);
		--size1;

		n = deleteElement(newArr, size1, tree->key);
		--size1;

		heapPermutation(newArr, size1, size1);
		///

		int* newArr1 = (int*)malloc(sizeof(int) * (size0));
		newArr1 = arr0;
		int size2 = size0;

		int m = deleteElement(newArr1, size2, tree->right->key);
		--size2;

		m = deleteElement(newArr1, size2, tree->key);
		--size2;

		heapPermutation1(newArr1, size2, size2);
	}

	printf("\nCount: %d", count);

	t = clock() - t;
	double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds 

	printf("\nTime: %.2f\n", time_taken);

	return 0;
}

void printTree(int arr[], int size) {

	int i;
	for (i = 0; i < size; i++) {

		printf("%d = Root->", arr[i]);
		findNode(tree, arr[i]);
		printf("\n");
	}
}

int deleteElement(int arr[], int n, int x)
{
	// Search x in array 
	int i;
	for (i = 0; i < n; i++)
		if (arr[i] == x)
			break;

	// If x found in array 
	if (i < n)
	{
		// reduce size of array and move all 
		// elements on space ahead 
		n = n - 1;
		for (int j = i; j < n; j++)
			arr[j] = arr[j + 1];
	}

	return n;
}

void free_tree(Node* node) {

	if (node != NULL) {
		free_tree(node->right);
		free_tree(node->left);
		free(node);
	}
}

int isSameStructure(Node* a, Node* b)
{
	// 1. both empty  
	if (a == NULL && b == NULL)
		return 1;

	// 2. both non-empty -> compare them  
	if (a != NULL && b != NULL)
	{
		return
			(
				isSameStructure(a->left, b->left) &&
				isSameStructure(a->right, b->right)
				);
	}

	// 3. one empty, one not -> false  
	return 0;
}

int getParent(Node* root, int val) {
	/*
	if (root == NULL) return NULL;
	else if (root->right>key == key || root->left->key == key) return root;
	else if (root->key > key) getParent(root->left, key);
	else getParent(root->right, key);
	return root;
	*/

	if (root->left != NULL)
	{
		if (root->left->key == val)
			return root->key;
	}

	if (root->right != NULL)
	{
		if (root->right->key == val)
			return root->key;
	}

	return getParent(root->left, val);
	return getParent(root->right, val);

	return -1;
}


void printArr(int a[], int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%d-", a[i]);
	}
	printf("\n");
}

void heapPermutation(int a[], int size, int n)
{
	// if size becomes 1 then prints the obtained 
	// permutation 
	if (size == 1)
	{
		//printArr(a, n);

		Node* treeToCompare = NULL;

		treeToCompare = insert(treeToCompare, tree->key);
		treeToCompare = insert(treeToCompare, tree->left->key);

		int i;
		for (i = 0; i < n; i++) {

			treeToCompare = insert(treeToCompare, a[i]);
		}
		//inorder(tree);

		//printf("\n\n");

		if (isSameStructure(tree, treeToCompare)) {
			//inorder(treeToCompare);
			//printarray(newArray, n + 2);
			//printf("\n");
			count++;

		}

		free_tree(treeToCompare);
		//free(newArray);
		return;
	}

	int i;
	for (i = 0; i < size; i++)
	{
		heapPermutation(a, size - 1, n);

		// if size is odd, swap first and last 
		// element 
		if (size % 2 == 1)
			swap1(&a[0], &a[size - 1]);

		// If size is even, swap ith and last 
		// element 
		else
			swap1(&a[i], &a[size - 1]);
	}
}

void heapPermutation1(int a[], int size, int n)
{
	// if size becomes 1 then prints the obtained 
	// permutation 
	if (size == 1)
	{
		Node* treeToCompare = NULL;

		treeToCompare = insert(treeToCompare, tree->key);
		treeToCompare = insert(treeToCompare, tree->right->key);

		int i;
		for (i = 0; i < n; i++) {

			treeToCompare = insert(treeToCompare, a[i]);
		}
		//inorder(tree);

		//printf("\n\n");

		if (isSameStructure(tree, treeToCompare)) {
			//inorder(treeToCompare);
			//printarray(newArray, n + 2);
			//printf("\n");
			count++;

		}

		free_tree(treeToCompare);
		return;
	}

	int i;
	for (i = 0; i < size; i++)
	{
		heapPermutation1(a, size - 1, n);

		// if size is odd, swap first and last 
		// element 
		if (size % 2 == 1)
			swap1(&a[0], &a[size - 1]);

		// If size is even, swap ith and last 
		// element 
		else
			swap1(&a[i], &a[size - 1]);
	}
}

//function to print the array
void printarray(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		printf("%d-", arr[i]);
	}
	printf("\n");
}

void swap1(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

Node* newNode(int item)
{
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}

void inorder(Node* root)
{
	if (root != NULL)
	{
		inorder(root->left);
		printf("root: %d\n", root->key);
		inorder(root->right);
	}
}

int findNode(Node* node, int key) {

	if (node->key == key) {

		return 1;
	}

	if (key < node->key) {
		printf("left->");
		findNode(node->left, key);
	}

	if (key > node->key) {
		printf("right->");
		findNode(node->right, key);
	}
	return -1;
}

Node* insert(Node* node, int key)
{
	/* If the tree is empty, return a new node */

	if (node == NULL)
		return newNode(key);

	/* Otherwise, recur down the tree */
	if (key < node->key)
		node->left = insert(node->left, key);
	else if (key > node->key)
		node->right = insert(node->right, key);

	/* return the (unchanged) node pointer */
	return node;
}