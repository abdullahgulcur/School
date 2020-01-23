#include <string.h>
#include<stdio.h> 
#include<stdlib.h> 
#include <ctype.h>
#include<time.h>
#include<locale.h>

int a = 0;
int b = 0;

char *append(const char *input, const char c);
char * encryptMessage(char msg[]);
void *_allocator(size_t element, size_t typeSize);
int randomA();
int randomB();
int randomNumber(int x, int y);

#define ERR_MESSAGE__NO_MEM "Not enough memory!"
#define allocator(element, type) _allocator(element, sizeof(type))

int main()
{

	

	setlocale(LC_ALL, "Turkish");

//	printf("“");

	srand(time(0));
	int aValues[] = { 1,3,5,7,9,11,15,17,19,21,23,25 };

	a = randomA();
	b = randomB();

	printf("a:%d b:%d\n", a, b);

	FILE * f = fopen("input1.txt", "r");
	FILE * f1 = fopen("output1.txt", "w");

	char s[100];

	while (!feof(f)) {

		fscanf(f, "%s ", s);
		fprintf(f1, "%s ", encryptMessage(s));
	}
	fclose(f);
	fclose(f1);
	printf("input file 1 encrypted!\n");


	char s1[100];

	FILE * f2 = fopen("input2.txt", "r");
	FILE * f3 = fopen("output2.txt", "w");

	while (!feof(f2)) {

		fscanf(f2, "%s ", s1);
		printf("%s ", s1);
		fprintf(f3, "%s ", encryptMessage(s1));
	}
	fclose(f2);
	fclose(f3);
	printf("input file 2 encrypted!\n");

	
	return 0;
}

int randomA() {

	int aValue[] = { 1,3,5,7,9,11,15,17,19,21,23,25 };
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
	int i;

	for (i = 0; i < strlen(msg); i++)
	{
		if (isalpha(msg[i]) && isupper(msg[i]))
			cipher = append(cipher, (char)((((a * (msg[i] - 'A')) + b) % 26) + 'A'));
		else if (isalpha(msg[i]) && islower(msg[i]))
			cipher = append(cipher, (char)((((a * (msg[i] - 'a')) + b) % 26) + 'a'));
		else
			cipher = append(cipher, msg[i]);

	}

	return cipher;
}
