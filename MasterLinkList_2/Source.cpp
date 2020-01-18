#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<locale.h>
#include <math.h>

struct Term {

	int totalNumbers;
	int numberOfDocuments;
	float idf;
	char termName[30];
	struct Term *next;

	struct Term * firstOrder[100];
	struct Term * secondOrder[100];
	struct Term * thirdOrder[100];
};

typedef struct Term Term;

struct Document {

	int docID;
	int docType; // 0 == econ: 1 == health: 2 == magazin
	struct Term * next;
	struct Document * nextDocument;
};

typedef struct Document Document;

int fileExists(const char * filename);
Term * addTerm(Term * t, char name[]);
Term * readAllTerms();
void printStopDiscWords(Term * t, int index);
Term * CopyList(Term * t);
void sortTerms(Term ** t);
void printTerms(Term * term);
Term * readEcons();
Term * readHealths();
Term * readMagazins();
void swap(Term *a, Term *b);
void bubbleSort(Term ** start);
void printTermsWithIndex(Term * term, int count);
Document * constructDocuments();
void printDocuments(Document * doc);
void printFirstOrder(Document * doc);
void printSecondOrder(Document * doc);
void combineDocumentsTerms(Document * doc0, Document * doc1);
Document * getDocForThirdOrder(Document * doc);
void printThirdOrder(Document * doc);
Term * calculateDocumentFrequency(Term * term, Document * doc, int category);
Term * calculateTFValues(Term * term, int documentCount);
int getNumberOfDocuments(Document * doc);
void printMultiplicationOfTFIDF(Term * term, int count);
int getCategoryIndex(char filename[]);
/*
*Abdullah Gulcur ----150116014----  DATA STRUCTURE PROJECT-1
*
*This program constructs Master Linked list........
*
*Compiled in Visual Studio
*/

int main()
{
	setlocale(LC_ALL, "Turkish");

	Document * doc = constructDocuments();

	int numberOfDocuments = getNumberOfDocuments(doc);

	printf("\n\nFIRST ORDER\n\n");
	printFirstOrder(doc);
	printf("\n\nSECOND ORDER\n\n");
	printSecondOrder(doc);
	printf("\n\nTHIRD ORDER\n\n");
	printThirdOrder(doc);

	int econCount = getCategoryIndex("dataset/econ/");
	int healthCount = getCategoryIndex("dataset/health/");
	int magazinCount = getCategoryIndex("dataset/magazin/");
	
	Term * econs = readEcons();
	bubbleSort(&econs);

	Term * healths = readHealths();
	bubbleSort(&healths);


	Term * magazins = readMagazins();
	bubbleSort(&magazins);

	econs = calculateDocumentFrequency(econs, doc, 0);
	healths = calculateDocumentFrequency(healths, doc, 1);
	magazins = calculateDocumentFrequency(magazins, doc, 2);

	econs = calculateTFValues(econs, econCount);
	healths = calculateTFValues(healths, healthCount);
	magazins = calculateTFValues(magazins, magazinCount);

	printf("\n\nECONOMY\n\n");
	printTermsWithIndex(econs, 5);
	printf("\n\nHEALTH\n\n");
	printTermsWithIndex(healths, 5);
	printf("\n\nMAGAZIN\n\n");
	printTermsWithIndex(magazins, 5);
	
	printf("--------------");
	
	printf("\n\nECONOMY\n\n");
	printMultiplicationOfTFIDF(econs, 5);
	printf("\n\nHEALTH\n\n");
	printMultiplicationOfTFIDF(healths, 5);
	printf("\n\nMAGAZIN\n\n");
	printMultiplicationOfTFIDF(magazins, 5);
	
	return 0;
}

void printMultiplicationOfTFIDF(Term * term, int count) {

	while (term->next != NULL && count > 0) {
		printf("%s - %.2f\n", term->termName, term->totalNumbers * term->idf);
		term = term->next;
		count--;
	}

}

Term * calculateTFValues(Term * term, int documentCount) {

	Term * t = term;

	while (t->next != NULL) {
		//printf("--%.2f--", (float)t->numberOfDocuments);
		t->idf = log(documentCount / (float)t->numberOfDocuments);
		t = t->next;
	}

	return term;
}

Term * calculateDocumentFrequency(Term * term, Document * doc, int category) {

	/*That long function reads all files and stores words as terms*/

	Term * t = NULL;
	FILE *f;

	int i;

	Term * iter = term;
	Document * docIter = doc;

	while (iter != NULL) {

		docIter = doc;

		while (docIter != NULL) {

			Term * t = docIter->next;

			while (t != NULL) {

				if (strcmp(t->termName, iter->termName) == 0 && docIter->docType == category) {

					iter->numberOfDocuments++;
					break;
				}
				t = t->next;
			}
			docIter = docIter->nextDocument;
		}
		iter = iter->next;
	}

	return term;
}

int getNumberOfDocuments(Document * doc) {

	

	int count = 0;

	while (doc != NULL) {

		count++;
		doc = doc->nextDocument;
	}
	return count;
}

void printSecondOrder(Document * doc) {
	
	while (doc != NULL) {

		Document * secDoc = doc->nextDocument;

		while (secDoc != NULL) {

			Term * t = doc->next;

			while (t != NULL) {

				Term * secondTerm = secDoc->next;

				while (secondTerm != NULL) {

					if (strcmp(t->termName, secondTerm->termName) == 0) {

						
						combineDocumentsTerms(doc, secDoc);
						
						if (getDocForThirdOrder(secDoc) != NULL)
							combineDocumentsTerms(doc, getDocForThirdOrder(secDoc));
					}

					secondTerm = secondTerm->next;
				}
				t = t->next;
			}
			secDoc = secDoc->nextDocument;
		}
		doc = doc->nextDocument;
	}

}

void printThirdOrder(Document * doc) {

	while (doc != NULL) {

		Document * secDoc = doc->nextDocument;

		while (secDoc != NULL) {

			Term * t = doc->next;

			while (t != NULL) {

				Term * secondTerm = secDoc->next;

				while (secondTerm != NULL) {

					if (strcmp(t->termName, secondTerm->termName) == 0) {

						if (getDocForThirdOrder(secDoc) != NULL)
							combineDocumentsTerms(doc, getDocForThirdOrder(secDoc));
					}

					secondTerm = secondTerm->next;
				}
				t = t->next;
			}
			secDoc = secDoc->nextDocument;
		}
		doc = doc->nextDocument;
	}

}

Document * getDocForThirdOrder(Document * doc) {

	while (doc != NULL) {

		Document * secDoc = doc->nextDocument;

		while (secDoc != NULL) {

			Term * t = doc->next;

			while (t != NULL) {

				Term * secondTerm = secDoc->next;

				while (secondTerm != NULL) {

					if (strcmp(t->termName, secondTerm->termName) == 0) {
						return secDoc;
					}

					secondTerm = secondTerm->next;
				}
				t = t->next;
			}
			secDoc = secDoc->nextDocument;
		}
		doc = doc->nextDocument;
	}
	return NULL;
}

void combineDocumentsTerms(Document * doc0, Document * doc1) {

	Term * t0 = doc0->next;
	Term * t1 = doc1->next;

	while (t0 != NULL) {

		while (t1 != NULL) {

			printf("{%s, %s} - ", t0->termName, t1->termName);

			t1 = t1->next;
		}
		t0 = t0->next;
	}
}

void printFirstOrder(Document * doc) {

	while (doc != NULL) {

		Term * t = doc->next;

		while (t != NULL) {

			Term * secondTerm = t->next;

			while (secondTerm != NULL) {
				printf("{%s, %s} - ", t->termName, secondTerm->termName);
				secondTerm = secondTerm->next;
			}
			t = t->next;
		}
		doc = doc->nextDocument;
	}

}

void printDocuments(Document * doc) {

	while (doc != NULL) {

		printf("Document ID : %d\n", doc->docID);

		Term * t = doc->next;

		while (t != NULL) {
			printf("%s\n", t->termName);
			t = t->next;
		}
		doc = doc->nextDocument;
	}

}

Document * addDocument(Document * doc, int index, int docType) {

	if (doc == NULL) {
		doc = (Document*)malloc(sizeof(Document));
		doc->docID = index;
		doc->docType = docType;
		doc->nextDocument = NULL;
		doc->next = NULL;
		return doc;
	}

	Document * iter = doc;

	while (iter->nextDocument != NULL) {
		iter = iter->nextDocument;
	}

	iter->nextDocument = (Document*)malloc(sizeof(Document));
	iter->nextDocument->docType = docType;
	iter->nextDocument->docID = index;
	iter->nextDocument->nextDocument = NULL;
	iter->nextDocument->next = NULL;
	return doc;
}

Document * constructDocuments() {

	Term * t = NULL;
	FILE *f;

	int i;
	int docID = 1;

	Document * doc = NULL;

	for (i = 0; i < getCategoryIndex("dataset/econ/"); i++) {

		doc = addDocument(doc, docID, 0);

		char s1[25];
		strcpy(s1, "dataset/econ/");
		char s2[5] = ".txt";
		char s3[10];
		char s[20];
		sprintf(s3, "%d", i + 1); // for integer to string

		strcat(s3, s2);
		strcat(s1, s3);

		char str[50];

		char category[15] = "econ";

		f = fopen(s1, "r");

		while (!feof(f)) {

			fscanf(f, "%s ", s);
			sprintf(str, "%s - %s - %d", s, category, i + 1); // formats strings
			t = addTerm(t, s);
		}
		sortTerms(&t);

		Document * iter = doc;

		while (iter->nextDocument != NULL) {
			iter = iter->nextDocument;
		}
		iter->next = t;
		t = NULL;
		iter->nextDocument = NULL;
		docID++;

	}

	for (i = 0; i < getCategoryIndex("dataset/health/"); i++) {

		doc = addDocument(doc, docID, 1);

		char s1[25];
		strcpy(s1, "dataset/health/");
		char s2[5] = ".txt";
		char s3[10];
		char s[20];
		sprintf(s3, "%d", i + 1); // for integer to string

		strcat(s3, s2);
		strcat(s1, s3);

		char str[50];

		char category[15] = "health";

		f = fopen(s1, "r");

		while (!feof(f)) {

			fscanf(f, "%s ", s);
			sprintf(str, "%s - %s - %d", s, category, i + 1); // formats strings
			t = addTerm(t, s);
		}
		sortTerms(&t);

		Document * iter = doc;

		while (iter->nextDocument != NULL) {
			iter = iter->nextDocument;
		}
		iter->next = t;
		t = NULL;
		iter->nextDocument = NULL;
		docID++;
	}

	for (i = 0; i < getCategoryIndex("dataset/magazin/"); i++) {

		doc = addDocument(doc, docID, 2);

		char s1[25];
		strcpy(s1, "dataset/magazin/");
		char s2[5] = ".txt";
		char s3[10];
		char s[20];
		sprintf(s3, "%d", i + 1); // for integer to string

		strcat(s3, s2);
		strcat(s1, s3);

		char str[50];

		char category[15] = "magazin";

		f = fopen(s1, "r");

		while (!feof(f)) {

			fscanf(f, "%s ", s);
			sprintf(str, "%s - %s - %d", s, category, i + 1); // formats strings
			t = addTerm(t, s);
		}
		sortTerms(&t);

		Document * iter = doc;

		while (iter->nextDocument != NULL) {
			iter = iter->nextDocument;
		}
		iter->next = t;
		t = NULL;
		iter->nextDocument = NULL;
		docID++;
	}

	fclose(f);

	return doc;
}

Term * readEcons() {

	Term * t = NULL;
	FILE *f;

	int i;

	for (i = 0; i < getCategoryIndex("dataset/econ/"); i++) {

		char s1[25];
		strcpy(s1, "dataset/econ/");
		char s2[5] = ".txt";
		char s3[10];
		char s[20];
		sprintf(s3, "%d", i + 1); // for integer to string

		strcat(s3, s2);
		strcat(s1, s3);

		char str[50];

		char category[15] = "econ";

		f = fopen(s1, "r");

		while (!feof(f)) {

			fscanf(f, "%s ", s);
			sprintf(str, "%s - %s - %d", s, category, i + 1); // formats strings
			t = addTerm(t, s);
		}
	}
	fclose(f);

	return t;
}

Term * readHealths() {

	Term * t = NULL;
	FILE *f;

	int i;

	for (i = 0; i < getCategoryIndex("dataset/health/"); i++) {

		char s1[25]; // asil
		strcpy(s1, "dataset/health/");
		char s2[5] = ".txt";
		char s3[7];
		char s[20];
		sprintf(s3, "%d", i + 1);

		strcat(s3, s2);
		strcat(s1, s3);

		char str[50];

		char category[15] = "health";

		f = fopen(s1, "r");

		while (!feof(f)) {

			fscanf(f, "%s ", s);
			sprintf(str, "%s - %s - %d", s, category, i + 1);
			t = addTerm(t, s);
		}
	}
	fclose(f);

	return t;
}

Term * readMagazins() {

	Term * t = NULL;
	FILE *f;

	int i;

	for (i = 0; i < getCategoryIndex("dataset/magazin/"); i++) {

		char s1[25];
		strcpy(s1, "dataset/magazin/");
		char s2[5] = ".txt";
		char s3[7];
		char s[20];
		sprintf(s3, "%d", i + 1);

		strcat(s3, s2);
		strcat(s1, s3);

		char str[50];

		char category[15] = "magazin";

		f = fopen(s1, "r");

		while (!feof(f)) {

			fscanf(f, "%s ", s);
			sprintf(str, "%s - %s - %d", s, category, i + 1);
			t = addTerm(t, s);
		}
	}
	fclose(f);

	return t;
}

void printTerms(Term * term) {

	while (term->next != NULL) {
		printf("%s- Term Frequency: %d Number of Documents: %d \n", term->termName, term->totalNumbers, term->numberOfDocuments);

		term = term->next;
	}

}

void printTermsWithIndex(Term * term, int count) {
	/*
	while (term->next != NULL && count > 0) {
		printf("%s- Term Frequency: %d Number of Documents: %d IDF: %.2f \n", term->termName, term->totalNumbers, term->numberOfDocuments, term->idf);
		term = term->next;
		count--;
	}
	*/
	while (term->next != NULL && count > 0) {
		printf("%s- Term Frequency: %d \n", term->termName, term->totalNumbers);
		term = term->next;
		count--;
	}
}

int getCategoryIndex(char filename[]) {

	/*It returns the maximum number of documents in that category*/

	int count = 1;

	while (1) {

		char s1[30];
		strcpy(s1, filename);
		char s2[30] = ".txt";
		char s3[30];
		sprintf(s3, "%d", count);

		strcat(s3, s2);
		strcat(s1, s3);

		if (fileExists(s1) != 1) {
			break;
		}
		else {
			count++;
		}

	}
	count--;

	return count;
}

int fileExists(const char * filename) {

	/*It trys to open that file*/

	FILE *file;
	if (file = fopen(filename, "r")) {
		fclose(file);
		return 1;
	}
	return 0;
}

Term * CopyList(Term * t) {

	/*Copies list, its gonna be useful for storing stopwords vs.*/

	Term * current = t;
	Term * newList = NULL;
	Term * tail = NULL;

	while (current != NULL)
	{

		if (newList == NULL)
		{
			newList = (Term*)malloc(sizeof(Term));
			strcpy(newList->termName, current->termName);
			newList->totalNumbers = current->totalNumbers;
			newList->next = NULL;
			tail = newList;
		}
		else
		{
			tail->next = (Term*)malloc(sizeof(Term));
			tail = tail->next;
			strcpy(tail->termName, current->termName);
			tail->totalNumbers = current->totalNumbers;
			tail->next = NULL;
		}
		current = current->next;
	}

	return newList;
}

Term * readAllTerms() {

	/*That long function reads all files and stores words as terms*/

	Term * t = NULL;
	FILE *f;

	int i;

	for (i = 0; i < getCategoryIndex("dataset/econ/"); i++) {

		char s1[25];
		strcpy(s1, "dataset/econ/");
		char s2[5] = ".txt";
		char s3[10];
		char s[20];
		sprintf(s3, "%d", i + 1); // for integer to string

		strcat(s3, s2);
		strcat(s1, s3);

		char str[50];

		char category[15] = "econ";

		f = fopen(s1, "r");

		while (!feof(f)) {

			fscanf(f, "%s ", s);
			sprintf(str, "%s - %s - %d", s, category, i + 1); // formats strings
			t = addTerm(t, s);
		}
	}

	for (i = 0; i < getCategoryIndex("dataset/health/"); i++) {

		char s1[25]; // asil
		strcpy(s1, "dataset/health/");
		char s2[5] = ".txt";
		char s3[7];
		char s[20];
		sprintf(s3, "%d", i + 1);

		strcat(s3, s2);
		strcat(s1, s3);

		char str[50];

		char category[15] = "health";

		f = fopen(s1, "r");

		while (!feof(f)) {

			fscanf(f, "%s ", s);
			sprintf(str, "%s - %s - %d", s, category, i + 1);
			t = addTerm(t, s);
		}
	}

	for (i = 0; i < getCategoryIndex("dataset/magazin/"); i++) {

		char s1[25];
		strcpy(s1, "dataset/magazin/");
		char s2[5] = ".txt";
		char s3[7];
		char s[20];
		sprintf(s3, "%d", i + 1);

		strcat(s3, s2);
		strcat(s1, s3);

		char str[50];

		char category[15] = "magazin";

		f = fopen(s1, "r");

		while (!feof(f)) {

			fscanf(f, "%s ", s);
			sprintf(str, "%s - %s - %d", s, category, i + 1);
			t = addTerm(t, s);
		}
	}

	fclose(f);

	return t;
}

void sortTerms(Term ** t) { // I used bubble sort here to sort terms alphabetical order

	int swapped, i;
	Term * ptr1;
	Term * lptr = NULL;

	if (t == NULL)
		return;
	do
	{
		swapped = 0;
		ptr1 = *t;

		while (ptr1->next != lptr)
		{
			if (strcmp(ptr1->termName, ptr1->next->termName) == 1)
			{
				char temp[30];
				strcpy(temp, ptr1->termName);
				strcpy(ptr1->termName, ptr1->next->termName);
				strcpy(ptr1->next->termName, temp);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	} while (swapped);

}

/* Bubble sort the given linked list to get higher freq terms*/
void bubbleSort(Term ** start)
{
	int swapped, i;
	Term *ptr1;
	Term *lptr = NULL;

	/* Checking for empty list */
	if (start == NULL)
		return;

	do
	{
		swapped = 0;
		ptr1 = *start;

		while (ptr1->next != lptr)
		{
			if (ptr1->totalNumbers < ptr1->next->totalNumbers)
			{
				swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	} while (swapped);
}

/* function to swap data of two nodes a and b*/
void swap(Term *a, Term *b)
{
	char charTemp[30];

	int temp = a->totalNumbers;
	strcpy(charTemp, a->termName);

	a->totalNumbers = b->totalNumbers;
	strcpy(a->termName, b->termName);

	b->totalNumbers = temp;
	strcpy(b->termName, charTemp);
}

Term * addTerm(Term * t, char name[]) { // add terms

	if (t == NULL) {
		t = (Term*)malloc(sizeof(Term));
		strcpy(t->termName, name);
		t->totalNumbers = 1;
		t->numberOfDocuments = 0;
		t->idf = 0;
		t->next = NULL;
		return t;
	}

	Term * iter = t;

	int addable = 0;

	while (iter->next != NULL) {

		if (strcmp(iter->termName, name) == 0) { // if term exists in list
			addable = 1;
			iter->totalNumbers++;
			iter->numberOfDocuments = 0;
			iter->idf = 0;
			break;
		}
		else
			iter = iter->next;
	}

	if (addable == 0) {

		Term * newTerm = (Term*)malloc(sizeof(Term));
		newTerm->next = NULL;
		newTerm->totalNumbers = 1;
		newTerm->numberOfDocuments = 0;
		newTerm->idf = 0;
		strcpy(newTerm->termName, name);
		iter->next = newTerm;
	}
	return t;
}