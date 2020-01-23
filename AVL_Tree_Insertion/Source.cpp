#include<stdio.h> 
#include<stdlib.h> 
#include <math.h>
#include <string.h>

struct Node
{
	char word[50];
	struct Node *left;
	struct Node *right;
	int height;
};

typedef struct Node Node;

Node* insert(Node* node, char word[]);
void preOrder(Node *root);
Node* newNode(char word[]);
Node *rightRotate(Node *y);
Node *leftRotate(Node *x);
int getBalance(Node *N);
int max1(int x, int y);
int * search(Node* root, char word[]);

int main()
{
	Node * root = NULL;

	/* Constructing tree given in the above figure */
	

	FILE *f = fopen("HW4_dictionary.dat", "r");
	char s[50];

	while (!feof(f)) {
		fscanf(f, "%s ", s);
		root = insert(root, s);

	}

	printf("Preorder traversal of the constructed AVL"
		" tree is \n");
	//preOrder(root);

	if (search(root, "duck") == 1) {
		printf(" ----FOUND ! ----");
	}
	else {
		printf(" ---- NOT FOUND ! ----");
	}

	return 0;
}

Node* insert(Node* node, char word[])
{
	/* 1.  Perform the normal BST insertion */
	if (node == NULL)
		return(newNode(word));

	if (strcmp(word, node->word) < 0)/// 
		node->left = insert(node->left, word);
	else if (strcmp(word, node->word) > 0)
		node->right = insert(node->right, word);
	else // Equal keys are not allowed in BST 
		return node;

	/* 2. Update height of this ancestor node */
	node->height = 1 + max1(height(node->left),
		height(node->right));

	/* 3. Get the balance factor of this ancestor
	node to check whether this node became
	unbalanced */
	int balance = getBalance(node);

	// If this node becomes unbalanced, then 
	// there are 4 cases 

	// Left Left Case 
	if (balance > 1 && strcmp(word, node->left->word) < 0)
		return rightRotate(node);

	// Right Right Case 
	if (balance < -1 && strcmp(word, node->right->word) > 0)
		return leftRotate(node);

	// Left Right Case 
	if (balance > 1 && strcmp(word, node->left->word) > 0)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	// Right Left Case 
	if (balance < -1 && strcmp(word, node->right->word) < 0)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	/* return the (unchanged) node pointer */
	return node;
}

int * search(Node* root, char word[])
{
	// Base Cases: root is null or key is present at root 
	if (root == NULL)
		return 0;

	if (strcmp(root->word, word) == 0)
		return 1;

	// Key is greater than root's key 
	if (strcmp(root->word, word) < 0)
		return search(root->right, word);

	// Key is smaller than root's key 
	return search(root->left, word);


}

void preOrder(Node *root)
{
	if (root != NULL)
	{
		printf("%s ", root->word);
		preOrder(root->left);
		preOrder(root->right);
	}
}

Node* newNode(char word[])
{
	Node* node = (Node*)malloc(sizeof(Node));
	strcpy(node->word, word);
	node->left = NULL;
	node->right = NULL;
	node->height = 1;  // new node is initially added at leaf 
	return(node);
}

// A utility function to right rotate subtree rooted with y 
// See the diagram given above. 
Node *rightRotate(Node *y)
{
	Node *x = y->left;
	Node *T2 = x->right;

	// Perform rotation 
	x->right = y;
	y->left = T2;

	// Update heights 
	y->height = max(height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;

	// Return new root 
	return x;
}

// A utility function to left rotate subtree rooted with x 
// See the diagram given above. 
Node *leftRotate(Node *x)
{
	Node *y = x->right;
	Node *T2 = y->left;

	// Perform rotation 
	y->left = x;
	x->right = T2;

	//  Update heights 
	x->height = max1(height(x->left), height(x->right)) + 1;
	y->height = max1(height(y->left), height(y->right)) + 1;

	// Return new root 
	return y;
}

// Get Balance factor of node N 
int getBalance(Node *N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}



// A utility function to get the height of the tree 
int height(Node *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

// A utility function to get maximum of two integers 
int max1(int x, int y) {
	if (x >= y)
		return x;
	else
		return y;
}