<<<<<<< HEAD
#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include <math.h>

/*
*
*	ABDULLAH GULCUR ---- 150116014
*	STSTEM PROGRAMMING ---PROJECT 1---
*	
*	THIS PROGRAM COMPILED BY VS 2015 COMMUNITY VER
*
*	MAIN PURPOSE -- THIS PROGRAM CALCULATES NUMBERS DEPENDING ON USERS CHOICE 

*/

void readFile(FILE * fp);
void calculateNumber(char hex[]);
char * switchBytes(char input[]);
char * hexToBin(char * hex);
int setBias(int x);
int setExponent(char bin[], int expBits);
char * getFraction(char bin[], int expBits);
int isEven(char fraction[], int expBits);
char * binaryAdd(char fraction[]);
float getMantissaNormalized(char fraction[]);
int bigENormalized(int exp, int bias);
float getNumber(int signBit, float mantissa, int e);
int isNormalized(char frac[]);
int bigEDenormalized(int bias);
int isNormalized(char frac[]);
float getMantissaDeNormalized(char fraction[]);
char * getExpBits(char bin[], int expBits);
int differentCases(char exp[], char frac[]);
void splitHex(char hex[]);
void calculateUnsignedInt(char hex[]);
void calculateInt(char hex[]);



int bigLittleEnd = 2; // 1:BIG ENDIAN 2: LITTLE ENDIAN							  <<<
int dataType = 1;     // 1: FLOATING POINT 2: UNSIGNED INT 3: SIGNED INT        <<<<<=============== READ THIS !!!
int typeSize = 4;	  // TYPE SIZE (IN BYTES)									  <<<

int main() {

	FILE *fp = fopen("input.txt", "r");

	readFile(fp);

}

void readFile(FILE * fp) {

	char ch;

	char input[100];
	int count = 0;


	while ((ch = fgetc(fp)) != EOF)
	{
		if (ch != ' ') {
			input[count] = ch;
			count++;
		}
		if (ch == '\n') {
			input[count] = '\0';
			splitHex(input);
			printf("\n\n");
			count = 0;
		}
	}

	fclose(fp);

}

void splitHex(char hex[]) {

	//printf("%s", hex);
	int i = 0;
	int j = 0;

	char * splitHexa = (char *)malloc(sizeof(char) * typeSize * 2);

	while (hex[i] != '\0') {

		splitHexa[j] = hex[i];

		i++;
		j++;

		if (j == typeSize * 2) {
			splitHexa[typeSize * 2] = '\0';

			switch (dataType)
			{
			case 1:
				calculateNumber(splitHexa); // floating point
				printf("   ");
				break;
			case 2:
				calculateUnsignedInt(splitHexa); // unsigned
				printf("   ");
				break;
			case 3:
				calculateInt(splitHexa);  // signed int
				printf("   ");
				break;

			}
			
			//printf("%s\n", splitHexa);
			j = 0;
		}
		
	}

}

char * switchBytes(char input[]) {

	int i = 0;
	char * hex = (char *)malloc(sizeof(char) * strlen(input));
	int lastIndex = strlen(input) - 2;

	while (lastIndex >= 0 && hex[i] != '\0') {
		hex[i] = input[lastIndex];
		hex[i + 1] = input[lastIndex + 1];
		lastIndex -= 2;
		i += 2;
	}
	hex[strlen(input)] = '\0';

	return hex;
}

void calculateUnsignedInt(char hex[]) {

	char * binary;



	if (bigLittleEnd == 2) {
		hex = switchBytes(hex);
	}

	binary = hexToBin(hex);

	//printf("Unsigned int bin: %s ", binary);

	int i = typeSize * 8 - 1;

	long long int sum = 0;

	int j = 0;

	while (i >= 0) {

		sum += (binary[i] - 48) * pow(2, j);
		i--;
		j++;
	}

	if (typeSize <= 4)
		printf("Unsigned Number: %d  ", sum);
	else
		printf("Unsigned Number: %lld  ", sum);
}

void calculateInt(char hex[]) {

	char * binary;

	if (bigLittleEnd == 2) {
		hex = switchBytes(hex);
	}

	binary = hexToBin(hex);

	//printf("Signed int bin: %s ", binary);

	int i = typeSize * 8 - 1;

	long long int sum = 0;

	int j = 0;

	while (i >= 1) {

		sum += (binary[i] - 48) * pow(2, j);
		i--;
		j++;
	}

	if(binary[0] == '1')
		sum -= pow(2, typeSize * 8 - 1);


	if (typeSize <= 4)
		printf("Signed Number: %d  ", sum);
	else
		printf("Signed Number: %lld  ", sum);
}

void calculateNumber(char hex[]) {

	int expBits;
	int bias;
	int signBit;
	int exp;
	int E;
	float mantissa;
	float number;
	char * fraction;
	char * expBitsArray;

	char * binary;

	switch (typeSize)
	{
		case 1: expBits = 4; break;
		case 2: expBits = 6; break;
		case 3: expBits = 8; break;
		case 4: expBits = 10; break;
		case 6: expBits = 12; break;
	}

	if (bigLittleEnd == 2) {
		hex = switchBytes(hex);
	}

	bias = setBias(expBits);
	binary = hexToBin(hex);
	expBitsArray = getExpBits(binary, expBits);
	signBit = binary[0] - 48;
	exp = setExponent(binary, expBits);
	fraction = getFraction(binary, expBits);

	//printf("Exp Bits: %s ", expBitsArray);
	//printf("Fraction Bits: %s ", fraction);
	//printf("bin: %s ", binary);

	switch (differentCases(expBitsArray, fraction))
	{
	case 0:// normalized value
		E = bigENormalized(exp, bias);
		mantissa = getMantissaNormalized(fraction);
		number = getNumber(signBit, mantissa, E);
		
		//printf("exp: %d ", exp);
		//printf("bias: %d ", bias);
		//printf("Sign Bit: %d ", signBit);
		//printf("mantissa: %.5f ", mantissa);
		printf("number: %.5f ", number);
		break;
	case 1:// represents zero value
		if(signBit == 1)
			printf("number: -0 ");
		else
			printf("number: 0 ");
		break;
	case 2: // closest zero
		E = bigEDenormalized(bias);
		mantissa = getMantissaDeNormalized(fraction);
		//printf("exp: %d ", exp);
	//	printf("bias: %d ", bias);
	//	printf("Sign Bit: %d ", signBit);
	//	printf("mantissa: %.5f ", mantissa);
		printf("number: %.5e ", pow(-1, signBit) * mantissa * pow(2, 1-bias)); // e li sayi anca bu sekilde basilabiliyo
		break;
	case 3:
		if (signBit == 1)
			printf("number: -INF ");
		else
			printf("number: INF ");
		
		break;
	case 4:
		printf("number: NaN");
		
		break;
	}

	

	//printf("\n");
}

int differentCases(char exp[], char frac[]) {

	int i;

	int expFullZero = 1;
	int fracFullZero = 1;

	int expFullOne = 1;

	i = 0;
	while (exp[i] != '\0') {

		if (exp[i] != '0') {
			expFullZero = 0;
			break;
		}
		i++;
	}

	i = 0;
	while (frac[i] != '\0') {

		if (frac[i] != '0') {
			fracFullZero = 0;
			break;
		}
		i++;
	}

	i = 0;
	while (exp[i] != '\0') {

		if (exp[i] != '1') {
			expFullOne = 0;
			break;
		}
		i++;
	}

	if (!expFullZero  && !expFullOne) // normalized value && !fracFullZero
		return 0;

	if (expFullZero && fracFullZero) // represents zero value
		return 1;

	if (expFullZero && !fracFullZero) // closest to 0.0
		return 2;

	if (expFullOne && fracFullZero) // represents infinity
		return 3;

	if (expFullOne && !fracFullZero) // NaN
		return 4;

}

char * getExpBits(char bin[], int expBits) {

	int i;
	char * expBitsArray = (char *)malloc(sizeof(char) * expBits);

	for (i = 1; i <= expBits; i++) {
		expBitsArray[i - 1] = bin[i];
	}
	expBitsArray[expBits] = '\0';

	return expBitsArray;
}

int isNormalized(char frac[]) {

	int i = 0;

	while (frac[i] != '\0') {
		if (frac[i] != '0') {
			return 1;
		}
		i++;
	}
	return 0;

}

int bigENormalized(int exp, int bias) {

	return exp - bias;
}

int bigEDenormalized(int bias) {

	return 1 - bias;
}

char * getFraction(char bin[], int expBits) {

	static char fraction[14];
	float mantissa = 0;
	float number = 0;

	int i;
	int j = expBits + 1;

	for (i = 0; i < 13; i++) {

		if (bin[j] != '\0') {
			fraction[i] = bin[j];
			j++;
		}
		else
			fraction[i] = '0';
		
		
	}
	fraction[13] = '\0';

	if (bin[j] != '\0') {
		if (bin[j] == '1' && bin[j + 1] == '1') {
			strcpy(fraction, binaryAdd(fraction));
		}
		else if (bin[j] == '1' && bin[j + 1] == '0') {

			if (!isEven(fraction, expBits)) {
				strcpy(fraction, binaryAdd(fraction));
			}
		}
	}

	return fraction;
}

float getNumber(int signBit, float mantissa, int e) {

	return pow(-1, signBit) * mantissa * pow(2, e);

}

float getMantissaNormalized(char fraction[]) {

	float sum = 0;

	int i;

	for (i = 0; i < strlen(fraction); i++) {
		sum += pow(0.5f, i+1) * (fraction[i] - 48);
	}

	return sum + 1;	

}

float getMantissaDeNormalized(char fraction[]) {

	float sum = 0;

	int i;

	for (i = 0; i < strlen(fraction); i++) {
		sum += pow(0.5f, i + 1) * (fraction[i] - 48);
	}

	return sum;

}

char * binaryAdd(char fraction[]) { 

	int last = strlen(fraction) - 1;
	
	while (last >= 0) {

		if (fraction[last] == '0') {
			fraction[last] = '1';
			return fraction;
		}
		else {
			fraction[last] = '0';
			last--;
		}

	}
	return fraction;

}

int isEven(char fraction[], int expBits) {

	int sum = 0;

	int i;

	for (i = 0; i < expBits; i++) {
		sum += pow(2, i) * (fraction[i] - 48);
	}

	if (sum % 2 == 0)
		return 1;
	else
		return 0;

}

int setExponent(char bin[], int expBits) {

	int j;
	int k = expBits - 1;

	int exp = 0;

	for (j = 1; j <= expBits; j++) {
		exp += pow(2, k) * (bin[j] - 48);
		k--;
	}

	return exp;
}

int setBias(int x) {
	return pow(2, x - 1) - 1;
}

char * hexToBin(char * hex) {
	
	int i = 0;
	int j = 0;
	char bin[5000];

	char binStr[5];

	while (hex[j] != NULL) {

		switch (hex[j]) {

		case '0':
			strcpy(binStr, "0000");
			break;
		case '1':
			strcpy(binStr, "0001");
			break;
		case '2':
			strcpy(binStr, "0010");
			break;
		case '3':
			strcpy(binStr, "0011");
			break;
		case '4':
			strcpy(binStr, "0100");
			break;
		case '5':
			strcpy(binStr, "0101");
			break;
		case '6':
			strcpy(binStr, "0110");
			break;
		case '7':
			strcpy(binStr, "0111");
			break;
		case '8':
			strcpy(binStr, "1000");
			break;
		case '9':
			strcpy(binStr, "1001");
			break;
		case 'a':
			strcpy(binStr, "1010");
			break;
		case 'b':
			strcpy(binStr, "1011");
			break;
		case 'c':
			strcpy(binStr, "1100");
			break;
		case 'd':
			strcpy(binStr, "1101");
			break;
		case 'e':
			strcpy(binStr, "1110");
			break;
		case 'f':
			strcpy(binStr, "1111");
			break;
		}

		bin[i] = binStr[0];
		bin[i+1] = binStr[1];
		bin[i+2] = binStr[2];
		bin[i+3] = binStr[3];

		j++;
		i += 4;

	}
	bin[strlen(hex) * 4] = '\0';

	return bin;

}
=======
#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include <math.h>

/*
*
*	ABDULLAH GULCUR ---- 150116014
*	STSTEM PROGRAMMING ---PROJECT 1---
*	
*	THIS PROGRAM COMPILED BY VS 2015 COMMUNITY VER
*
*	MAIN PURPOSE -- THIS PROGRAM CALCULATES NUMBERS DEPENDING ON USERS CHOICE 

*/

void readFile(FILE * fp);
void calculateNumber(char hex[]);
char * switchBytes(char input[]);
char * hexToBin(char * hex);
int setBias(int x);
int setExponent(char bin[], int expBits);
char * getFraction(char bin[], int expBits);
int isEven(char fraction[], int expBits);
char * binaryAdd(char fraction[]);
float getMantissaNormalized(char fraction[]);
int bigENormalized(int exp, int bias);
float getNumber(int signBit, float mantissa, int e);
int isNormalized(char frac[]);
int bigEDenormalized(int bias);
int isNormalized(char frac[]);
float getMantissaDeNormalized(char fraction[]);
char * getExpBits(char bin[], int expBits);
int differentCases(char exp[], char frac[]);
void splitHex(char hex[]);
void calculateUnsignedInt(char hex[]);
void calculateInt(char hex[]);



int bigLittleEnd = 2; // 1:BIG ENDIAN 2: LITTLE ENDIAN							  <<<
int dataType = 1;     // 1: FLOATING POINT 2: UNSIGNED INT 3: SIGNED INT        <<<<<=============== READ THIS !!!
int typeSize = 4;	  // TYPE SIZE (IN BYTES)									  <<<

int main() {

	FILE *fp = fopen("input.txt", "r");

	readFile(fp);

}

void readFile(FILE * fp) {

	char ch;

	char input[100];
	int count = 0;


	while ((ch = fgetc(fp)) != EOF)
	{
		if (ch != ' ') {
			input[count] = ch;
			count++;
		}
		if (ch == '\n') {
			input[count] = '\0';
			splitHex(input);
			printf("\n\n");
			count = 0;
		}
	}

	fclose(fp);

}

void splitHex(char hex[]) {

	//printf("%s", hex);
	int i = 0;
	int j = 0;

	char * splitHexa = (char *)malloc(sizeof(char) * typeSize * 2);

	while (hex[i] != '\0') {

		splitHexa[j] = hex[i];

		i++;
		j++;

		if (j == typeSize * 2) {
			splitHexa[typeSize * 2] = '\0';

			switch (dataType)
			{
			case 1:
				calculateNumber(splitHexa); // floating point
				printf("   ");
				break;
			case 2:
				calculateUnsignedInt(splitHexa); // unsigned
				printf("   ");
				break;
			case 3:
				calculateInt(splitHexa);  // signed int
				printf("   ");
				break;

			}
			
			//printf("%s\n", splitHexa);
			j = 0;
		}
		
	}

}

char * switchBytes(char input[]) {

	int i = 0;
	char * hex = (char *)malloc(sizeof(char) * strlen(input));
	int lastIndex = strlen(input) - 2;

	while (lastIndex >= 0 && hex[i] != '\0') {
		hex[i] = input[lastIndex];
		hex[i + 1] = input[lastIndex + 1];
		lastIndex -= 2;
		i += 2;
	}
	hex[strlen(input)] = '\0';

	return hex;
}

void calculateUnsignedInt(char hex[]) {

	char * binary;



	if (bigLittleEnd == 2) {
		hex = switchBytes(hex);
	}

	binary = hexToBin(hex);

	//printf("Unsigned int bin: %s ", binary);

	int i = typeSize * 8 - 1;

	long long int sum = 0;

	int j = 0;

	while (i >= 0) {

		sum += (binary[i] - 48) * pow(2, j);
		i--;
		j++;
	}

	if (typeSize <= 4)
		printf("Unsigned Number: %d  ", sum);
	else
		printf("Unsigned Number: %lld  ", sum);
}

void calculateInt(char hex[]) {

	char * binary;

	if (bigLittleEnd == 2) {
		hex = switchBytes(hex);
	}

	binary = hexToBin(hex);

	//printf("Signed int bin: %s ", binary);

	int i = typeSize * 8 - 1;

	long long int sum = 0;

	int j = 0;

	while (i >= 1) {

		sum += (binary[i] - 48) * pow(2, j);
		i--;
		j++;
	}

	if(binary[0] == '1')
		sum -= pow(2, typeSize * 8 - 1);


	if (typeSize <= 4)
		printf("Signed Number: %d  ", sum);
	else
		printf("Signed Number: %lld  ", sum);
}

void calculateNumber(char hex[]) {

	int expBits;
	int bias;
	int signBit;
	int exp;
	int E;
	float mantissa;
	float number;
	char * fraction;
	char * expBitsArray;

	char * binary;

	switch (typeSize)
	{
		case 1: expBits = 4; break;
		case 2: expBits = 6; break;
		case 3: expBits = 8; break;
		case 4: expBits = 10; break;
		case 6: expBits = 12; break;
	}

	if (bigLittleEnd == 2) {
		hex = switchBytes(hex);
	}

	bias = setBias(expBits);
	binary = hexToBin(hex);
	expBitsArray = getExpBits(binary, expBits);
	signBit = binary[0] - 48;
	exp = setExponent(binary, expBits);
	fraction = getFraction(binary, expBits);

	//printf("Exp Bits: %s ", expBitsArray);
	//printf("Fraction Bits: %s ", fraction);
	//printf("bin: %s ", binary);

	switch (differentCases(expBitsArray, fraction))
	{
	case 0:// normalized value
		E = bigENormalized(exp, bias);
		mantissa = getMantissaNormalized(fraction);
		number = getNumber(signBit, mantissa, E);
		
		//printf("exp: %d ", exp);
		//printf("bias: %d ", bias);
		//printf("Sign Bit: %d ", signBit);
		//printf("mantissa: %.5f ", mantissa);
		printf("number: %.5f ", number);
		break;
	case 1:// represents zero value
		if(signBit == 1)
			printf("number: -0 ");
		else
			printf("number: 0 ");
		break;
	case 2: // closest zero
		E = bigEDenormalized(bias);
		mantissa = getMantissaDeNormalized(fraction);
		//printf("exp: %d ", exp);
	//	printf("bias: %d ", bias);
	//	printf("Sign Bit: %d ", signBit);
	//	printf("mantissa: %.5f ", mantissa);
		printf("number: %.5e ", pow(-1, signBit) * mantissa * pow(2, 1-bias)); // e li sayi anca bu sekilde basilabiliyo
		break;
	case 3:
		if (signBit == 1)
			printf("number: -INF ");
		else
			printf("number: INF ");
		
		break;
	case 4:
		printf("number: NaN");
		
		break;
	}

	

	//printf("\n");
}

int differentCases(char exp[], char frac[]) {

	int i;

	int expFullZero = 1;
	int fracFullZero = 1;

	int expFullOne = 1;

	i = 0;
	while (exp[i] != '\0') {

		if (exp[i] != '0') {
			expFullZero = 0;
			break;
		}
		i++;
	}

	i = 0;
	while (frac[i] != '\0') {

		if (frac[i] != '0') {
			fracFullZero = 0;
			break;
		}
		i++;
	}

	i = 0;
	while (exp[i] != '\0') {

		if (exp[i] != '1') {
			expFullOne = 0;
			break;
		}
		i++;
	}

	if (!expFullZero  && !expFullOne) // normalized value && !fracFullZero
		return 0;

	if (expFullZero && fracFullZero) // represents zero value
		return 1;

	if (expFullZero && !fracFullZero) // closest to 0.0
		return 2;

	if (expFullOne && fracFullZero) // represents infinity
		return 3;

	if (expFullOne && !fracFullZero) // NaN
		return 4;

}

char * getExpBits(char bin[], int expBits) {

	int i;
	char * expBitsArray = (char *)malloc(sizeof(char) * expBits);

	for (i = 1; i <= expBits; i++) {
		expBitsArray[i - 1] = bin[i];
	}
	expBitsArray[expBits] = '\0';

	return expBitsArray;
}

int isNormalized(char frac[]) {

	int i = 0;

	while (frac[i] != '\0') {
		if (frac[i] != '0') {
			return 1;
		}
		i++;
	}
	return 0;

}

int bigENormalized(int exp, int bias) {

	return exp - bias;
}

int bigEDenormalized(int bias) {

	return 1 - bias;
}

char * getFraction(char bin[], int expBits) {

	static char fraction[14];
	float mantissa = 0;
	float number = 0;

	int i;
	int j = expBits + 1;

	for (i = 0; i < 13; i++) {

		if (bin[j] != '\0') {
			fraction[i] = bin[j];
			j++;
		}
		else
			fraction[i] = '0';
		
		
	}
	fraction[13] = '\0';

	if (bin[j] != '\0') {
		if (bin[j] == '1' && bin[j + 1] == '1') {
			strcpy(fraction, binaryAdd(fraction));
		}
		else if (bin[j] == '1' && bin[j + 1] == '0') {

			if (!isEven(fraction, expBits)) {
				strcpy(fraction, binaryAdd(fraction));
			}
		}
	}

	return fraction;
}

float getNumber(int signBit, float mantissa, int e) {

	return pow(-1, signBit) * mantissa * pow(2, e);

}

float getMantissaNormalized(char fraction[]) {

	float sum = 0;

	int i;

	for (i = 0; i < strlen(fraction); i++) {
		sum += pow(0.5f, i+1) * (fraction[i] - 48);
	}

	return sum + 1;	

}

float getMantissaDeNormalized(char fraction[]) {

	float sum = 0;

	int i;

	for (i = 0; i < strlen(fraction); i++) {
		sum += pow(0.5f, i + 1) * (fraction[i] - 48);
	}

	return sum;

}

char * binaryAdd(char fraction[]) { 

	int last = strlen(fraction) - 1;
	
	while (last >= 0) {

		if (fraction[last] == '0') {
			fraction[last] = '1';
			return fraction;
		}
		else {
			fraction[last] = '0';
			last--;
		}

	}
	return fraction;

}

int isEven(char fraction[], int expBits) {

	int sum = 0;

	int i;

	for (i = 0; i < expBits; i++) {
		sum += pow(2, i) * (fraction[i] - 48);
	}

	if (sum % 2 == 0)
		return 1;
	else
		return 0;

}

int setExponent(char bin[], int expBits) {

	int j;
	int k = expBits - 1;

	int exp = 0;

	for (j = 1; j <= expBits; j++) {
		exp += pow(2, k) * (bin[j] - 48);
		k--;
	}

	return exp;
}

int setBias(int x) {
	return pow(2, x - 1) - 1;
}

char * hexToBin(char * hex) {
	
	int i = 0;
	int j = 0;
	char bin[5000];

	char binStr[5];

	while (hex[j] != NULL) {

		switch (hex[j]) {

		case '0':
			strcpy(binStr, "0000");
			break;
		case '1':
			strcpy(binStr, "0001");
			break;
		case '2':
			strcpy(binStr, "0010");
			break;
		case '3':
			strcpy(binStr, "0011");
			break;
		case '4':
			strcpy(binStr, "0100");
			break;
		case '5':
			strcpy(binStr, "0101");
			break;
		case '6':
			strcpy(binStr, "0110");
			break;
		case '7':
			strcpy(binStr, "0111");
			break;
		case '8':
			strcpy(binStr, "1000");
			break;
		case '9':
			strcpy(binStr, "1001");
			break;
		case 'a':
			strcpy(binStr, "1010");
			break;
		case 'b':
			strcpy(binStr, "1011");
			break;
		case 'c':
			strcpy(binStr, "1100");
			break;
		case 'd':
			strcpy(binStr, "1101");
			break;
		case 'e':
			strcpy(binStr, "1110");
			break;
		case 'f':
			strcpy(binStr, "1111");
			break;
		}

		bin[i] = binStr[0];
		bin[i+1] = binStr[1];
		bin[i+2] = binStr[2];
		bin[i+3] = binStr[3];

		j++;
		i += 4;

	}
	bin[strlen(hex) * 4] = '\0';

	return bin;

}
>>>>>>> f770bb2242ec5fead237ac776bba6c6e068303ed
