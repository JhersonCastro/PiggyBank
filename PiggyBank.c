#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "variables.h"
#include "PiggyBank.h"
#include "StdLib.h"
#pragma region Global Variables
int maxCapacity[] =				{0, 0};
int currentCapacity[] =			{0, 0};
int piggyBankMoney =			0;
int currentCoinNorm[] =			{ 0, 0, 0, 0, 0 };
int defaultCoinNorm[] =			{ 50, 100, 200, 500, 1000 };
int currentBillNorm[] =			{ 0, 0, 0, 0, 0 };
int defaultBillNorm[] =			{ 2000, 5000, 10000, 20000, 50000 };
int Coin = 0, Bill = 1;
#pragma endregion

void dimensionPiggyBank() {
	printf("Creacion de la alcancia\n");
	
	maxCapacity[Coin] = getNumber("¿Cuánta capacidad (de monedas) le quieres dar a la alcancia?: ");
	maxCapacity[Bill] = getNumber("¿Cuánta capacidad (de billetes) le quieres dar a la alcancia?: ");
	bool isContinue = true;
	for (int i = 0; i < 5; i++) {
		int currentValue = 0;
		if (isContinue) {
			currentValue = getNumber("¿Cuáles son las demoninaciones que deseas (Para las monedas)?\nestos son los numeros admitidos: 50, 100, 200, 500, 1000: ");
			if (!isTheValueInTheNormCoin(currentValue, defaultCoinNorm) || isDuplicateValue(currentCoinNorm, currentValue)) {
				printf("No se permiten cantidades duplicadas, tampoco cantidades que no estan en la norma default"); i--; continue;
			}
			currentCoinNorm[i] = currentValue;
			isContinue = GetContinue("¿Quieres seguir? Y/N");
		}
		currentCoinNorm[i] = currentValue;
	}
	isContinue = true;
	for (int i = 0; i < 5; i++) {
		int currentValue = 0;
		if (isContinue) {
			currentValue = getNumber("¿Cuáles son las demoninaciones que deseas (Para los billetes)?\nestos son los numeros admitidos: 2000, 5000, 10000, 20000, 50000: ");
			if (!isTheValueInTheNormCoin(currentValue, defaultBillNorm) || isDuplicateValue(currentBillNorm, currentValue)) {
				printf("No se permiten cantidades duplicadas, tampoco cantidades que no estan en la norma default"); i--; continue;
			}
			currentBillNorm[i] = currentValue;
			isContinue = GetContinue("¿Quieres seguir? Y/N");
		}
		currentBillNorm[i] = currentValue;
	}
	qsort(currentCoinNorm, 5, sizeof(int), compareIntegers);
	qsort(currentBillNorm, 5, sizeof(int), compareIntegers);
}
bool isTheValueInTheNormCoin(int value, int coinNorm[]) {
	for (int i = 0; i < 5; i++) {
		if (value == coinNorm[i] && value != 0)
			return true;
	}
	return false;
}
void printCoinNorm(int money) {
	printf("La norma es: ");
	int settingCurrentNorm[5];
	for (int i = 0; i < sizeof(currentCoinNorm)/sizeof(currentCoinNorm[0]); i++)
	{
		settingCurrentNorm[i] = money == 0 ? currentCoinNorm[i] : currentBillNorm[i];
	}
	for (int i = 0; i < 5; i++) {
		if (settingCurrentNorm[i] != 0)
			printf("%d ", settingCurrentNorm[i]);
	}
}
/*setting 0 = Coins, setting 1 = Bills*/
void setValue(int setting) {
	int currentValue = 0;
	do {
		printCoinNorm(setting);
		currentValue = getNumber("Pls, tell me what is the number that u want deposite in ur piggy bank:D.\n");

		if (!isTheValueInTheNormCoin(currentValue, currentCoinNorm)) {
			printf("\nThe value that u entered cannot be process, 'cause the value dont follow the norm. pls, try again \n");
			continue;
		}
		piggyBankMoney += currentValue;
		currentCapacity[setting]++;
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
/*setting 0 = Coins, setting 1 = Bills*/
void removeValue(int setting) {
	int currentValue = 0; 
	do {
		printf("Dinero total de la alcancia: %d\n", piggyBankMoney);
		printCoinNorm(setting);
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
		if (maxCapacity[setting] > minCoinsToMoney(piggyBankMoney))
			currentCapacity[setting] = minCoinsToMoney(piggyBankMoney);
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

	int opc = getNumber("1. Ingresar Moneda\n2. Extraer Moneda\n3. Ingresar billete\n4. Extraer Billete\n5. Presentar Saldos y Conteos\n");
	switch (opc) {
	#pragma region Coins
	case 1:
		if (currentCapacity[0] == maxCapacity[Coin])
			printf("¡Elimina algunas monedas!, la capacidad esta en el limite");
		else
			setValue(Coin);
		break;
	case 2:
		if (currentCapacity[Coin] == 0)
			printf("¡Agrega algunas monedas!, la alcancia esta vacia");
		else
			removeValue(Coin);
		break;
	#pragma endregion
	#pragma region Bills
	case 3:
		if (currentCapacity[Bill] == maxCapacity[Bill])
			printf("¡Elimina algunas monedas!, la capacidad esta en el limite");
		else
			setValue(Bill);
		break;
	case 4:
		if (currentCapacity[Coin] == 0)
			printf("¡Agrega algunas monedas!, la alcancia esta vacia");
		else
			removeValue(Coin);
		break;
	#pragma endregion
	case 5:
		printf("El dinero total en la alcancia es de %d\nLas monedas ingresadas es de: %d\nLas capacidad total de monedas es de:%d\nEl restante de las monedas es de: %d\n",
			piggyBankMoney, currentCapacity[Coin], maxCapacity[Coin], (maxCapacity[Coin] - currentCapacity[Coin]));
		printf("Los billetes ingresados es de: %d\nLas capacidad total de billetes es de:%d\nEl restante de los monedas es de: %d\n",
			 currentCapacity[Bill], maxCapacity[Bill], (maxCapacity[Bill] - currentCapacity[Bill]));
		break;
	default:
		printf("Intentalo de nuevo");
		break;
	}
}