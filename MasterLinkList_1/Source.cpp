#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<locale.h>

struct Document {

	int docID;
	int totalNumbersInDoc;
	int length;
	char category[20];
	struct Document *next;
};

typedef struct Document Document;

struct Term {

	int totalNumbers;
	char termName[30];
	struct Term *next;
	struct Document *nextDoc;
};

typedef struct Term Term;

int fileExists(const char * filename);
Term * addTerm(Term * t, char name[]);
Term * read_Terms();
void printDoc(Term * t);
Document * addDocument(Document * d, int docID, char category[], int length, int tot);
Term * addDoc(Term * t);
Term * findingStopWords(Term * t);
Term * addStopWords(Term * t, Term * t1);
void printStopDiscWords(Term * t, int index);
Term * CopyList(Term * t);
Term * findingDiscriminatingWords(Term * t, char category[]);
void sortTerms(Term ** t);
void writeToFile(Term * t, int index, FILE * f);
Term * addStopWordsDecreasingOrder(Term * t, Term * t1);

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
	
	Term * t = NULL;
	t = read_Terms();
	
	sortTerms(&t);

	t = addDoc(t);

	/*
	printf("\n--MASTER LINKED LIST--\n");      //    HERE U CAN PRINT MLL
	printDoc(t);
	

	

	/////////////////////////////////
	//
	//    CONSOLE OUTPUT
	Term * stopWords = NULL;
	stopWords = CopyList(t);
	stopWords = findingStopWords(stopWords);
	printf("\n---STOP WORD LIST---\n");
	printStopDiscWords(stopWords,5);

	Term * discriminated_Econs = NULL;
	discriminated_Econs = CopyList(t);
	printf("---Discriminated Econs---\n");
	discriminated_Econs = findingDiscriminatingWords(discriminated_Econs, "econ");         /// THIS AREA PRINTS REQUESTED OUTPUT
	printStopDiscWords(discriminated_Econs,5);

	Term * discriminated_Healths = NULL;
	discriminated_Healths = CopyList(t);
	printf("---Discriminated Healths---\n");
	discriminated_Healths = findingDiscriminatingWords(discriminated_Healths, "health");
	printStopDiscWords(discriminated_Healths, 5);

	Term * discriminated_Magazins = NULL;
	discriminated_Magazins = CopyList(t);
	printf("---Discriminated Magazins---\n");
	discriminated_Magazins = findingDiscriminatingWords(discriminated_Magazins, "magazin");
	printStopDiscWords(discriminated_Magazins, 5);

	//
	//
	//////////////////////////////////////
	
	*/
	/////////////////////////////////
	//
	//    FILE OUTPUT
	FILE * f = fopen("output.txt", "w");

	Term * stopWords = NULL;
	stopWords = CopyList(t);
	stopWords = findingStopWords(stopWords);
	fprintf(f,"\n---STOP WORD LIST---\n");
	writeToFile(stopWords, 5, f);
	printStopDiscWords(stopWords, 5);

	Term * discriminated_Econs = NULL;
	discriminated_Econs = CopyList(t);
	fprintf(f, "\n---DISCRIMINATED ECONS---\n");
	discriminated_Econs = findingDiscriminatingWords(discriminated_Econs, "econ");         /// THIS AREA PRINTS REQUESTED OUTPUT
	writeToFile(discriminated_Econs, 5, f);
	//printStopDiscWords(discriminated_Econs, 5);

	Term * discriminated_Healths = NULL;
	discriminated_Healths = CopyList(t);
	fprintf(f, "\n---DISCRIMINATED HEALTHS---\n");
	discriminated_Healths = findingDiscriminatingWords(discriminated_Healths, "health");
	writeToFile(discriminated_Healths, 5, f);
	//printStopDiscWords(discriminated_Healths, 5);

	Term * discriminated_Magazins = NULL;
	discriminated_Magazins = CopyList(t);
	fprintf(f, "\n---DISCRIMINATED MAGAZINS---\n");
	discriminated_Magazins = findingDiscriminatingWords(discriminated_Magazins, "magazin");
	writeToFile(discriminated_Magazins, 5, f);
	//printStopDiscWords(discriminated_Magazins, 5);

	fclose(f);

	char ch, file_name[25];
	FILE * fp = fopen("dataset/econ/5.txt", "r");

	while ((ch = fgetc(fp)) != EOF)
		printf("%c", ch);

	fclose(fp);
	//
	//
	//////////////////////////////////////
	
	return 0;
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


Term * addStopWords(Term * t, Term * t1) {

	/*Adds terms to the stopword list*/

	if (t == NULL) {
		t = t1;
		t1->next = NULL;
		return t1;
	}
	Term * iter = t;
	if (iter->next == NULL) {
	}
	while (iter->next != NULL) {
		iter = iter->next;
	}
	iter->next = t1;
	t1->next = NULL;
	return t;

}

Term * addStopWordsDecreasingOrder(Term * t, Term * t1) {

	/*Adds terms to the stopword list*/

	if (t == NULL) {
		t = t1;
		t1->next = NULL;
		return t1;
	}

	if (t1->totalNumbers >= t->totalNumbers) {
		t1->next = t;
		return t1;
	}

	Term * iter = t;

	while (iter->next != NULL && iter->next->totalNumbers > t1->totalNumbers) {
		iter = iter->next;
	}
	Term * temp = iter->next;
	iter->next = t1;
	t1->next = temp;

	return t;
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
			newList->nextDoc = current->nextDoc;
			newList->totalNumbers = current->totalNumbers;
			newList->next = NULL;
			tail = newList;
		}
		else
		{
			tail->next = (Term*)malloc(sizeof(Term));
			tail = tail->next;
			strcpy(tail->termName, current->termName);
			tail->nextDoc = current->nextDoc;
			tail->totalNumbers = current->totalNumbers;
			tail->next = NULL;
		}
		current = current->next;
	}

	return newList;
}


Term * findingDiscriminatingWords(Term * t, char category[]) {

	/*It finds discriminating words in specific category*/

	Term * discriminated_Words = NULL;

	int isDiscriminated;

	while (t != NULL) {

		Document * d = NULL;

		d = t->nextDoc;

		isDiscriminated = 0;

		while (d != NULL) {

				if (strcmp(d->category, category) != 0) {
					isDiscriminated = 0;
					break;
				}
				else
					isDiscriminated = 1;

			d = d->next;
		}

		if (isDiscriminated == 1) {
			Term * oneDiscriminatedWord = t;
			t = t->next;
			oneDiscriminatedWord->next = NULL;
			//discriminated_Words = addStopWords(discriminated_Words, oneDiscriminatedWord);
			discriminated_Words = addStopWordsDecreasingOrder(discriminated_Words, oneDiscriminatedWord);
		}
		else
			t = t->next;

	}

	return discriminated_Words;
}

Term * findingStopWords(Term * t) {

	/*It finds stopwords in specific category*/

	Term * stopWords = NULL;

	int econ_Count;
	int health_Count;
	int magazin_Count;

	int isStopWord;

	while (t != NULL) {

		econ_Count = 0;
		health_Count = 0;
		magazin_Count = 0;

		isStopWord = 0;

		Document * doc = NULL;

		doc = t->nextDoc;

		while (doc != NULL) {

			if (strcmp(doc->category, "econ") == 0) {
				econ_Count = 1;
			}
			else if (strcmp(doc->category, "health") == 0) {
				health_Count = 1;
			}
			else if (strcmp(doc->category, "magazin") == 0) {
				magazin_Count = 1;
			}

			if (econ_Count + health_Count + magazin_Count == 3) {
				isStopWord = 1;
				break;
			}

			doc = doc->next;
		}

		if (isStopWord == 1) {
			Term * oneStopWord = t;
			t = t->next;
			oneStopWord->next = NULL;
			//stopWords = addStopWords(stopWords,oneStopWord);//
			stopWords = addStopWordsDecreasingOrder(stopWords, oneStopWord);
		}else
			t = t->next;

	}

	return stopWords;
}

void writeToFile(Term * t, int index, FILE * f) {

	//FILE *f = fopen("file.txt", "w");


	int count = 0;
	Term * iter = t;

	while (t != NULL && count < index) {

		fprintf(f, "\n-%s: Total Number of Documents: %d\n", t->termName, t->totalNumbers);
		Document * doc = NULL;

		doc = t->nextDoc;

		while (doc != NULL) {
			fprintf(f, "DocID-%d %s  TotNums:%d  LengthOfDoc:%d\n", doc->docID, doc->category, doc->totalNumbersInDoc, doc->length);
			doc = doc->next;
		}
		t = t->next;
		count++;
	}

}

Term * read_Terms() {

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


Term * addDoc(Term * t) {  // It merges terms and documents which is belong for that specific term

	Term * iter = t;

	int count = 0;
	int count1 = 0;

	while (iter != NULL ) {

		Document * doc = NULL;

		int i;

		int totalNumberOfDoc = 0;

		for (i = 0; i < getCategoryIndex("dataset/econ/"); i++) {

			FILE *f;

			int doclength = 0;
			int repetations = 0;

			char s1a[50];
			strcpy(s1a, "dataset/econ/");
			char s2a[50] = ".txt";
			char s3a[50];
			char sa[50];
			sprintf(s3a, "%d", i + 1);

			strcat(s3a, s2a);
			strcat(s1a, s3a);

			char category[50] = "econ";

			f = fopen(s1a, "r");

			while (!feof(f)) {

				fscanf(f, "%s ", sa);

				if (strcmp(sa, iter->termName) == 0) {
					repetations++;
				}
				doclength++;
			}
			if (repetations != 0) {
				doc = addDocument(doc, i + 1, "econ", doclength, repetations);
				totalNumberOfDoc++;
			}
			fclose(f);
		}

		for (i = 0; i < getCategoryIndex("dataset/health/"); i++) {
			FILE *f;

			int doclength = 0;
			int repetations = 0;

			char s1b[50];
			strcpy(s1b, "dataset/health/");
			char s2b[50] = ".txt";
			char s3b[50];
			char sb[50];
			sprintf(s3b, "%d", i + 1);

			strcat(s3b, s2b);
			strcat(s1b, s3b);

			char category[50] = "health";

			f = fopen(s1b, "r");

			while (!feof(f)) {

				fscanf(f, "%s ", sb);

				if (strcmp(sb, iter->termName) == 0) {
					repetations++;
				}
				doclength++;
			}
			if (repetations != 0) {
				doc = addDocument(doc, i + 1, "health", doclength, repetations);
				totalNumberOfDoc++;
			}
			fclose(f);
		}

		for (i = 0; i < getCategoryIndex("dataset/magazin/"); i++) {
			FILE *f;

			int doclength = 0;
			int repetations = 0;

			char s1[50];
			strcpy(s1, "dataset/magazin/");
			char s2[50] = ".txt";
			char s3[50];
			char s[50];
			sprintf(s3, "%d", i + 1);

			strcat(s3, s2);
			strcat(s1, s3);

			char category[50] = "magazin";

			f = fopen(s1, "r");

			while (!feof(f)) {

				fscanf(f, "%s ", s);

				if (strcmp(s, iter->termName) == 0) {
					repetations++;
				}
				doclength++;
			}

			if (repetations != 0) {
				doc = addDocument(doc, i + 1, "magazin", doclength, repetations);
				totalNumberOfDoc++;
			}
			fclose(f);
		}

		iter->totalNumbers = totalNumberOfDoc;
		iter->nextDoc = doc;
		iter = iter->next;

	}

	return t;
}

void printDoc(Term * t) { // It actually prints MLL
	int count = 0;
	
	while (t != NULL ) {
		count++;
		printf("\n-%s: Total Number of Documents: %d      --%d--\n", t->termName, t->totalNumbers,count);
		Document * doc = NULL;

		doc = t->nextDoc;

		while (doc != NULL) {
			printf("DocID-%d %s  TotNums:%d  LengthOfDoc:%d\n", doc->docID, doc->category, doc->totalNumbersInDoc, doc->length);
			doc = doc->next;
		}
		t = t->next;
	}
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

void printStopDiscWords(Term * t, int index) { // It prints stopwords of discriminating words up to specific index

	int count = 0;
	Term * iter = t;

	while (t != NULL && count < index) {
		printf("\n-%s: Total Number of Documents: %d\n", t->termName, t->totalNumbers);
		Document * doc = NULL;

		doc = t->nextDoc;

		while (doc != NULL) {
			printf("DocID-%d %s  TotNums:%d  LengthOfDoc:%d\n", doc->docID, doc->category, doc->totalNumbersInDoc, doc->length);
			doc = doc->next;
		}
		t = t->next;
		count++;
	}

	/*
	while (count < index-1 && t->next != NULL) {

		iter = iter->next;
	}
	iter->next = NULL;

	while (t != NULL) {
		printf("-%s\n", t->termName);

		t = t->next;
	}
	*/
}

Term * addTerm(Term * t, char name[]) { // add terms

	if (t == NULL) {
		t = (Term*)malloc(sizeof(Term));
		strcpy(t->termName, name);
		t->next = NULL;
		t->nextDoc = NULL;
		return t;
	}

	Term * iter = t;

	int addable = 0;

	while (iter->next != NULL) {

		if (strcmp(iter->termName, name) == 0) { // if term does not exist in list
			addable = 1;
			break;
		}
		else
			iter = iter->next;

	}

	if (addable == 0) {
		if (strcmp(iter->termName, name) == 1) {

		}
		Term * newTerm = (Term*)malloc(sizeof(Term));
		newTerm->next = NULL;
		newTerm->nextDoc = NULL;
		strcpy(newTerm->termName, name);
		iter->next = newTerm;
	}


	return t;

}


Document * addDocument(Document * d, int docID, char category[], int length, int tot) { // add new document

	int count = 0;
	if (d == NULL) {

		d = (Document*)malloc(sizeof(Document));
		strcpy(d->category, category);
		d->docID = docID;
		d->length = length;
		d->totalNumbersInDoc = tot;

		d->next = NULL;
		return d;
	}

	Document * iter = d;

	while (iter->next != NULL) {
		iter = iter->next;
	}
	Document * newDocument = (Document*)malloc(sizeof(Document));
	newDocument->next = NULL;
	strcpy(newDocument->category, category);
	newDocument->docID = docID;

	newDocument->length = length;
	newDocument->totalNumbersInDoc = tot;
	iter->next = newDocument;

	return d;

}
