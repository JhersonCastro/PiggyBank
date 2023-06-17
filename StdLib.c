#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "StdLib.h"

bool GetContinue(const char* PrmLabel) {
	char str[10];
	printf("%s\n", PrmLabel);
	while (fgets(str, sizeof(str), stdin) != NULL)
	{
		if (str[0] == 'y' || str[0] == 'Y')
			return true;
		else if (str[0] == 'n' || str[0] == 'N')
			return false;
		else
		{
			printf("Invalid Input. Please enter y or n.\n");
			int c;
			while ((c = getchar()) != '\n' && c != EOF) {}
		}
	}
	return false;
}
int getNumber(const char* prmEtiqueta) {
	char varInput[50];
	float varNumber;
	while (1)
	{
		printf("%s", prmEtiqueta);
		fgets(varInput, 50, stdin);
		char* varEnd;
		varNumber = (int)strtod(varInput, &varEnd);
		if (varEnd == varInput || *varEnd != '\n')
		{
			printf("Invalid Input\n");
			int c;
			while ((c = getchar()) != '\n' && c != EOF) {} // limpiar búfer de entrada
		}
		else
			break;
	}
	printf("\n");
	return (int)varNumber;
}
int compareIntegers(const void* a, const void* b) {
	int intA = *((int*)a);
	int intB = *((int*)b);

	if (intA < intB)
		return -1;
	else if (intA > intB)
		return 1;
	else
		return 0;
}

bool isDuplicateValue(int array[], int value, int size) {
	for (int i = 0; i < size; i++) {
		if (value == array[i])
			return true;
	}
	return false;
}
