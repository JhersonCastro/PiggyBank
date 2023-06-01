#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "variables.h"
#include "PiggyBank.h"
#include "StdLib.h"
#pragma region Global Variables
int maxCapacity[] =				{0, 0};
int currentCoinsCapacity[] =	{0, 0};
int piggyBankMoney =			0;
int currentCoinNorm[] =			{ 0, 0, 0, 0, 0 };
int defaultCoinNorm[] =			{ 50, 100, 200, 500, 1000 };
int currentBillNorm[] =			{ 0, 0, 0, 0, 0 };
int defaultBillNorm[] =			{ 50, 100, 200, 500, 1000 };
#pragma endregion

void dimensionPiggyBank() {
	printf("Creacion de la alcancia\n");

	maxCoinsCapacity = getNumber("¿Cuánta capacidad le quieres dar a la alcancia?: ");
	bool isContinue = true;
	for (int i = 0; i < 5; i++) {
		int currentValue = 0;
		if (isContinue) {
			currentValue = getNumber("¿Cuáles son las demoninaciones que deseas?\nestos son los numeros admitidos: 50, 100, 200, 500, 1000: ");
			if (!isTheValueInTheNormCoin(currentValue, defaultCoinNorm) || isDuplicateValue(currentCoinNorm, currentValue)) {
				printf("No se permiten cantidades duplicadas, tampoco cantidades que no estan en la norma default"); i--; continue;
			}
			currentCoinNorm[i] = currentValue;
			isContinue = GetContinue("¿Quieres seguir? Y/N");
		}
		currentCoinNorm[i] = currentValue;
	}
	qsort(currentCoinNorm, 5, sizeof(int), compareIntegers);
}
bool isTheValueInTheNormCoin(int value, int coinNorm[]) {
	for (int i = 0; i < 5; i++) {
		if (value == coinNorm[i] && value != 0)
			return true;
	}
	return false;
}
void printCoinNorm() {
	printf("La norma es: ");
	for (int i = 0; i < 5; i++) {
		if (currentCoinNorm[i] != 0)
			printf("%d ", currentCoinNorm[i]);
	}
}
void setValue() {
	int currentValue = 0;
	do {
		printCoinNorm();
		currentValue = getNumber("Pls, tell me what is the number that u want deposite in ur piggy bank:D.\n");

		if (!isTheValueInTheNormCoin(currentValue, currentCoinNorm)) {
			printf("\nThe value that u entered cannot be process, 'cause the value dont follow the norm. pls, try again \n");
			continue;
		}
		piggyBankMoney += currentValue;
		currentCoinsCapacity++;
		printf("\nValue entered successfully .\n");
		break;
	} while (true);
}
int minCoinsToMoney(int value) {
	
	int currentValue = 0;
	int coins = 0;

	while (currentValue != value) {
		int remainingValue = value - currentValue;

		for (int i = 4; i >= 0; i--) {
			if (currentCoinNorm[i] <= remainingValue && currentCoinNorm[i] != 0) {
				coins++;
				currentValue += currentCoinNorm[i];
				break;
			}
		}
	}
	return coins;
}
void removeCoin() {
	int currentValue = 0;
	do {
		printf("Dinero total de la alcancia: %d\n", piggyBankMoney);
		printCoinNorm();
		currentValue = getNumber("Ingresa el valor que quieres eliminar dentro de la norma.\n");
		if (!isTheValueInTheNormCoin(currentValue, currentCoinNorm)) {
			printf("\nEl valor ingresado no puede ser procesado al no seguir la norma. Por favor, inténtelo de nuevo.\n");
			continue;
		}
		if (piggyBankMoney < currentValue) {
			printf("El valor a extraer %d es mayor al valor total de la alcancia %d", currentValue, piggyBankMoney);
			continue;
		}
		piggyBankMoney -= currentValue;
		if (maxCoinsCapacity > minCoinsToMoney(piggyBankMoney))
			currentCoinsCapacity = minCoinsToMoney(piggyBankMoney);
		else {
			printf("No se puede hacer una conversión con el valor asignado, intenta con otro, o salte de la funcion");
			if (GetContinue("Deseas continuar en la funcion de extracion? Y/N"))
				continue;
			break;
		}
		printf("\nValor removido correctamente.\n");
		break;
	} while (true);
}
void piggyBank() {
	/*Logical control of the piggy bank, the methods are:
		GETCURRENT VALUE in this method the user can view the current money in ur/his/her piggy bank
		SETVALUE EQUALS A COIN in this method the user can modify or add a coin with its equivalence {50, 100, 200, 500, 1000}
		REMOVECOIN with its equivalence {50, 100, 200, 500, 1000}
	*/
	int opc = getNumber("1. Ingresar Moneda\n2. Extraer Moneda\n3. Presentar Saldos y Conteos\n");
	switch (opc) {
	case 1:
		if (currentCoinsCapacity == maxCoinsCapacity)
			printf("¡Elimina algunas monedas!, la capacidad esta en el limite");
		else
			setValue();
		break;
	case 2:
		if (currentCoinsCapacity == 0)
			printf("¡Agrega algunas monedas!, la alcancia esta vacia");
		else
			removeCoin();
		break;
	case 3:
		printf("El dinero total en la alcancia es de %d\nLas monedas ingresadas es de: %d\nLas capacidad total de monedas es de:%d\nEl restante: %d\n",
			piggyBankMoney, currentCoinsCapacity, maxCoinsCapacity, (maxCoinsCapacity - currentCoinsCapacity));
		break;
	default:
		printf("Intentalo de nuevo");
		break;
	}
}