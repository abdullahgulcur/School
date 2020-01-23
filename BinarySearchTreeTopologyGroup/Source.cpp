#include <stdlib.h>
#include <stdio.h>
/*
*Abdullah Gulcur ----150116014----  DATA STRUCTURE PROJECT-2
*
*This program constructs different bst topologies........
*
*Compiled in Visual Studio
*/




// algorithm: traverse tree and store number of childs for every node and multiply by depth of that node,
// if it is same for the second tree (sequence is not important) 
// then it has same bst topology

/*
* example
* 0 2 1 0 1 1 1 2 0
* 0 2 0 2 1 1 1 0 1
*/

struct Node {

	int key;
	int numberOfChilds;
	int depth;
	struct Node* left;
	struct Node* right;
};

typedef struct Node Node;

Node* insert(Node* node, int key, int depth);
Node* newNode(int item, int depth);
void inorder(Node* root);
void printarray(int arr[], int size);
void permutation(int* arr, int start, int end);
void swap(int* a, int* b);
void setNumberOfChilds(Node** tree);
void inorder1(Node* root, int arr[], int * index);
void createChildsOfNodeArr(Node* root, int arr[]);
int cmpfunc(const void* a, const void* b);
int areEqual(int arr1[], int arr2[], int n);
void setDepthOfNode(Node** tree);
void free_tree(Node* node);

int* totalChildsArr;
int count = 0;

#ifdef WIN32

#include <windows.h>
double get_time()
{
	LARGE_INTEGER t, f;
	QueryPerformanceCounter(&t);
	QueryPerformanceFrequency(&f);
	return (double)t.QuadPart / (double)f.QuadPart;
}

#else

#include <sys/time.h>
#include <sys/resource.h>

double get_time()
{
	struct timeval t;
	struct timezone tzp;
	gettimeofday(&t, &tzp);
	return t.tv_sec + t.tv_usec * 1e-6;
}

#endif

int main()
{
	float start = get_time();
	
	int numberArr[] = {18,12,8,4,2 };//,16,14,15,17,36,24,20,21,72,54
	//int numberArr[] = { 5,1,8,7};//

	Node* tree = NULL;

	/*
	int a = 5;
	int * b = &a;
	printf("address b = %d decimal of address b = %p decimal of address a = %d \n", b, b, &a);
	*/
	int i;
	int size = (&numberArr)[1] - numberArr;
	for (i = 0; i < size; i++) {

		int depth = 0;
		tree = insert(tree, numberArr[i], depth);
	}

	setNumberOfChilds(&tree);
	printf("Traversal\n");
	inorder(tree);
	printf("-------\n");

	

	totalChildsArr = (int*)malloc(sizeof(int) * size); // this is for storing childs of main arr

	printf("Size: %d\n", size);
	createChildsOfNodeArr(tree, totalChildsArr);

	printf("\nChilds arr:\n"); // print sorted array
	for (i = 0; i < size; i++)
		printf("%d -", totalChildsArr[i]);


	qsort(totalChildsArr, size, sizeof(int), cmpfunc); // sort array



	printf("\nChilds arr:\n"); // print sorted array
	for (i = 0; i < size; i++)
		printf("%d -", totalChildsArr[i]);



	printf("\nPermutation\n");
	permutation(numberArr, 0, (&numberArr)[1] - numberArr - 1);
	printf("-------\n");

	printf("\nCount: %d", count);

	float end = get_time();
	printf("\nTIME: %.2f\n", end - start);

	return 0;
}

int cmpfunc(const void* a, const void* b) {
	return (*(int*)a - *(int*)b);
}

void setDepthOfNode(Node** tree) {

	Node* root = *tree;

	if (root != NULL)
	{
		if (root->left != NULL && root->right != NULL)
			root->numberOfChilds = 2;
		else if (root->left != NULL && root->right == NULL || root->left == NULL && root->right != NULL)
			root->numberOfChilds = 1;

		setNumberOfChilds(&(root->left));
		setNumberOfChilds(&(root->right));
	}

}

void setNumberOfChilds(Node** tree) {

	Node* root = *tree;

	if (root != NULL)
	{
		if (root->left != NULL && root->right != NULL)
			root->numberOfChilds = 2;
		else if (root->left != NULL && root->right == NULL || root->left == NULL && root->right != NULL)
			root->numberOfChilds = 1;

		setNumberOfChilds(&(root->left));
		setNumberOfChilds(&(root->right));
	}

}

void createChildsOfNodeArr(Node* root, int arr[]) {

	int * index = 0;
	inorder1(root, arr, &index);
}

void inorder1(Node* root, int arr[], int * index)
{
	if (root != NULL)
	{
		arr[(*index)++] = root->numberOfChilds * root->depth;
		inorder1(root->left, arr, index);
		inorder1(root->right, arr, index);

	}
}

int areEqual(int arr1[], int arr2[], int n)
{
	int i;

	for (i = 0; i < n; i++)
		if (arr1[i] != arr2[i])
			return 0;

	return 1;
}

void free_tree(Node* node) {
	//post-order like FatalError hinted at
	if (node != NULL) {
		free_tree(node->right);

		//free(node->depth);
		//free(node->key);
		//free(node->numberOfChilds);

		free_tree(node->left);
		free(node);
	}
}

void permutation(int* arr, int start, int end)
{
	if (start == end)
	{

		printarray(arr, end + 1);

		Node* tree = NULL;
		int i;
		for (i = 0; i < end + 1; i++) {

			int depth = 0;
			tree = insert(tree, arr[i], depth);
		}
		//free(tree);
		
		setNumberOfChilds(&tree);
		inorder(tree);


		int* totalChildsArrToCompare = (int*)malloc(sizeof(int) * (end + 1)); // this is for storing childs of main arr
		createChildsOfNodeArr(tree, totalChildsArrToCompare);

		printf("Childs arr:\n"); // print unsorted array
		for (i = 0; i < end + 1; i++)
			printf("%d -", totalChildsArrToCompare[i]);

		qsort(totalChildsArrToCompare, end + 1, sizeof(int), cmpfunc);

		
		printf("Childs arr:\n"); // print sorted array
		for (i = 0; i < end + 1; i++)
			printf("%d -", totalChildsArrToCompare[i]);
			
		// compare here
		if (areEqual(totalChildsArr, totalChildsArrToCompare, end + 1) == 1) {
			count++;
			printf("Equal\n");
		}
		//free(tree);

		free_tree(tree);
		free(totalChildsArrToCompare);


		printf("\n\n");
		
		return;
	}
	int i;
	for (i = start; i <= end; i++)
	{
		//swapping numbers
		swap((arr + i), (arr + start));
		//fixing one first digit
		//and calling permutation on
		//the rest of the digits
		permutation(arr, start + 1, end);
		swap((arr + i), (arr + start));
	}
}

//function to print the array
void printarray(int arr[], int size)
{
	int i, j;
	for (i = 0; i < size; i++)
	{
		printf("%d-", arr[i]);
	}
	printf("\n");
}

//function to swap the variables
void swap(int* a, int* b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

Node* newNode(int item, int depth)
{
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->key = item;
	temp->depth = depth;
	temp->numberOfChilds = 0;
	temp->left = temp->right = NULL;
	return temp;
}

void inorder(Node* root)
{
	if (root != NULL)
	{
		inorder(root->left);
		printf("root: %d depth: %d childs: %d\n", root->key, root->depth, root->numberOfChilds);
		inorder(root->right);
	}
}

Node* insert(Node* node, int key, int depth)
{
	/* If the tree is empty, return a new node */

	depth++;

	if (node == NULL)
		return newNode(key , depth);

	/* Otherwise, recur down the tree */
	if (key < node->key)
		node->left = insert(node->left, key, depth);
	else if (key > node->key)
		node->right = insert(node->right, key, depth);

	/* return the (unchanged) node pointer */
	return node;
}