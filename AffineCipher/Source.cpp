#include <string.h>
#include<stdio.h> 
#include<stdlib.h> 
#include <ctype.h>
#include<locale.h>
#include<time.h>

int a = 0; 
int b = 0; 

int newA = 0;
int newB = 0;

struct Values
{
	int a;
	int b;
};
typedef struct Values Value;

struct Node
{
	char word[50];
	struct Node *left;
	struct Node *right;
	int height;
};
typedef struct Node Node;

char *append(const char *input, const char c);
char * encryptMessage(char msg[]);
int decryptCipher(char * cipher, int aValues[], Node * root);
void *_allocator(size_t element, size_t typeSize);
int randomA();
int randomB();
int randomNumber(int x, int y);
Value mostFrequent(Value arr[], int n);
Node* insert(Node* node, char word[]);
void preOrder(Node *root);
Node* newNode(char word[]);
Node *rightRotate(Node *y);
Node *leftRotate(Node *x);
int getBalance(Node *N);
int max1(int x, int y);
int * search(Node* root, char word[]);

#define ERR_MESSAGE__NO_MEM "Not enough memory!"
#define allocator(element, type) _allocator(element, sizeof(type))

int main()
{

	//setlocale(LC_ALL, "Turkish");
	srand(time(0));
	int aValues[] = { 1,3,5,7,9,11,15,17,19,21,23,25 };

	a = randomA();
	b = randomB();

	printf("a:%d b:%d", a, b);

	FILE * f = fopen("input1.txt", "r");
	FILE * f1 = fopen("output1.txt", "w");

	char s[100];

	while (!feof(f)) {

		fscanf(f, "%s ", s);
		fprintf(f1, "%s ", encryptMessage(s));
	}
	fclose(f);
	fclose(f1);
	printf(" encrypted!\n");
	
	char s1[100];

	FILE * f2 = fopen("output1.txt", "r");
	FILE * f3 = fopen("output2.txt", "w");

	int count = 0;
	int maxCount = 10;

	Node * root = NULL;
	FILE *f5 = fopen("HW4_dictionary.dat", "r");
	char str[50];

	while (!feof(f5)) {
		fscanf(f5, "%s ", str);
		root = insert(root, str);
	}

	Value v[10];

	while (!feof(f2)) {
		fscanf(f2, "%s ", s1);
		if (decryptCipher(s1, aValues, root)) {
			v[count].a = newA;
			v[count].b = newB;
			count++;
		}
		if (count == maxCount) {
			break;
		}
	}

	newA = mostFrequent(v, maxCount).a;
	newB = mostFrequent(v, maxCount).b;
	
	printf("values found! ");
	printf("a:%d b:%d \n", newA, newB);
	fclose(f2);
	
	return 0;
}

int randomA() {

	int aValue[] = {1,3,5,7,9,11,15,17,19,21,23,25};
	return aValue[randomNumber(0, 11)];
}

int randomB() {

	return randomNumber(1, 26);
}

int randomNumber(int x, int y) {

	int a = rand() % (y - x + 1);
	x += a;

	return x;
}

void *_allocator(size_t element, size_t typeSize)
{
	void *ptr = NULL;
	if ((ptr = calloc(element, typeSize)) == NULL)
	{
		printf(ERR_MESSAGE__NO_MEM); exit(1);
	}
	return ptr;
}

char *append(const char *input, const char c)
{
	char *newString, *ptr;
	newString = allocator((strlen(input) + 2), char);
	ptr = newString;
	for (; *input; input++) { *ptr = *input; ptr++; }
	*ptr = c;
	return newString;
}

char * encryptMessage(char msg[])
{
    char * cipher = "";  
    for (int i = 0; i < strlen(msg); i++) 
    {
		
		if (msg[i] == '’')
			continue;

		if(msg[i] == '“')
			continue;

		if (msg[i] == '”')
			continue;
			
		if (isalpha(msg[i]) && isupper(msg[i]))
			cipher = append(cipher, (char)((((a * (msg[i] - 'A')) + b) % 26) + 'A'));
		else if (isalpha(msg[i]) && islower(msg[i]))
			cipher = append(cipher, (char)((((a * (msg[i] - 'a')) + b) % 26) + 'a'));
		//else
		//	cipher = append(cipher, msg[i]);
			
    } 

    return cipher; 
} 

int decryptCipher(char * cipher, int aValues[], Node * root)
{ 
	char * msg = "";
    int a_inv = 0; 
    int flag = 0; 
	int x;
	int y;

	Value v[10];

	int count = 0;
	int maxCount = 10;

	FILE *f = fopen("HW4_dictionary.dat", "r");
	char s[50];

	for (x = 0; x < 12; x++) {

		for (y = 1; y <= 26; y++) {

			for (int i = 0; i < 26; i++)
			{
				flag = (aValues[x] * i) % 26;

				if (flag == 1)
				{
					a_inv = i;
				}
			}

			for (int i = 0; i < strlen(cipher); i++)
			{
				if (isalpha(cipher[i]) && isupper(cipher[i])) {

					if (a_inv * ((cipher[i] - 'A' - y)) % 26 >= 0)
						msg = append(msg, (char)(((a_inv * ((cipher[i] - 'A' - y)) % 26)) + 'A'));
					else
						msg = append(msg, (char)(((a_inv * ((cipher[i] - 'A' - y)) % 26) + 26) + 'A'));

				}

				else if (isalpha(cipher[i]) && islower(cipher[i])) {

					if (a_inv * ((cipher[i] - 'a' - y)) % 26 >= 0)
						msg = append(msg, (char)(((a_inv * ((cipher[i] - 'a' - y)) % 26)) + 'a'));
					else
						msg = append(msg, (char)(((a_inv * ((cipher[i] - 'a' - y)) % 26) + 26) + 'a'));

				}

				//else
					//msg = append(msg, cipher[i]);
			}
		
			if (search(root, msg) == 1) {
				newA = aValues[x];
				newB = y;
				return 1;
			}

			msg = "";
			fseek(f, 0, SEEK_SET);
		}
	}
	return 0;
} 

Value mostFrequent(Value arr[], int n) {

	int max_count = 1;
	int res_a = arr[0].a;
	int res_b = arr[0].b;
	int curr_count = 1;

	for (int i = 0; i < n; i++) {
		if (arr[i].a == arr[i - 1].a && arr[i].b == arr[i - 1].b)
			curr_count++;
		else {
			if (curr_count > max_count) {
				max_count = curr_count;
				res_a = arr[i - 1].a;
				res_b = arr[i - 1].b;
			}
			curr_count = 1;
		}
	}

	if (curr_count > max_count) {
		max_count = curr_count;
		res_a = arr[n - 1].a;
		res_b = arr[n - 1].b;
	}

	Value newStrct;
	newStrct.a = res_a;
	newStrct.b = res_b;

	return newStrct;
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
	y->height = max1(height(y->left), height(y->right)) + 1;
	x->height = max1(height(x->left), height(x->right)) + 1;

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