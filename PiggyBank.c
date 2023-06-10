#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "PiggyBank.h"
#include "StdLib.h"
#include "Funcionalities.h"
#pragma region Global Variables
int maxCapacity[]			=			{0, 0};
int currentCapacity[]		=			{0, 0};
int piggyBankMoney			=			0;
int piggyBankMoneyByDiv[]	=			{ 0, 0 };
int currentCoinNorm[]		=			{ 0, 0, 0, 0, 0 };
int defaultCoinNorm[]		=			{ 50, 100, 200, 500, 1000 };
int currentBillNorm[]		=			{ 0, 0, 0, 0, 0 };
int defaultBillNorm[]		=			{ 2000, 5000, 10000, 20000, 50000 };
int countMoneyNorm[2][5] =	{
								/*Coins*/	{ 0, 0, 0, 0, 0 },
								/*Bills*/	{ 0, 0, 0, 0, 0 }
							};
int Coin = 0, Bill = 1;
#pragma endregion
#pragma region ModifyPiggyBank
void printCoinNorm(int money);
int getCurrentPosition(int setting, int value); 
void dimensionPiggyBank() {
	printf("Creacion de la alcancia\n");

	maxCapacity[Coin] = getNumber("¿Cuánta capacidad (de monedas) le quieres dar a la alcancia?: ");
	maxCapacity[Bill] = getNumber("¿Cuánta capacidad (de billetes) le quieres dar a la alcancia?: ");
	bool isContinue = true;
	for (int i = 0; i < 5; i++) {
		int currentValue = 0;
		if (isContinue) {
			currentValue = getNumber("¿Cuáles son las demoninaciones que deseas (Para las monedas)?\nestos son los numeros admitidos: 50, 100, 200, 500, 1000: ");
			if (!isTheValueInTheNorm(currentValue, defaultCoinNorm) || isDuplicateValue(currentCoinNorm, currentValue)) {
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
			if (!isTheValueInTheNorm(currentValue, defaultBillNorm) || isDuplicateValue(currentBillNorm, currentValue)) {
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
void setValue(int setting) {
	int currentValue = 0;
	do {
		printCoinNorm(setting);
		currentValue = getNumber("Pls, tell me what is the number that u want deposite in ur piggy bank:D.\n");

		if (!isTheValueInTheNorm(currentValue, setting == 0 ? currentCoinNorm : currentBillNorm)) {
			printf("\nThe value that u entered cannot be process, 'cause the value dont follow the norm. pls, try again \n");
			continue;
		}
		piggyBankMoney += currentValue;
		piggyBankMoneyByDiv[setting] += currentValue;
		currentCapacity[setting]++;
		countMoneyNorm[setting][getCurrentPosition(setting, currentValue)]++;
		printf("\nValue entered successfully .\n");
		break;
	} while (true);
}
void removeValue(int setting) {
	int currentValue = 0;
	do {
		printf("Dinero total de la alcancia: %d\n", piggyBankMoney);
		printCoinNorm(setting);
		currentValue = getNumber("Ingresa el valor que quieres eliminar dentro de la norma.\n");
		if (!isTheValueInTheNorm(currentValue, setting == 0 ? currentCoinNorm : currentBillNorm)) {
			printf("\nEl valor ingresado no puede ser procesado al no seguir la norma. Por favor, inténtelo de nuevo.\n");
			continue;
		}
		if (piggyBankMoney < currentValue) {
			printf("El valor a extraer %d es mayor al valor total de la alcancia %d", currentValue, piggyBankMoney);
			continue;
		}
		int* result = min_combination(currentCoinNorm, currentBillNorm, (piggyBankMoney - currentValue));
		/*if (maxCapacity[setting] > minValueToMoney(setting == 0 ? currentCoinNorm : currentBillNorm,piggyBankMoney))
			currentCapacity[setting] = minValueToMoney(setting == 0 ? currentCoinNorm : currentBillNorm,piggyBankMoney);*/
		if (maxCapacity[0] > result[0] && maxCapacity[1] > result[1])
		{
			currentCapacity[0] = result[0];
			currentCapacity[1] = result[1];
		}
		else {

			printf("No se puede hacer una conversión con el valor asignado, intenta con otro, o salte de la funcion");
			if (GetContinue("Deseas continuar en la funcion de extracion? Y/N"))
				continue;
			break;
		}
		piggyBankMoney -= currentValue;
		piggyBankMoneyByDiv[setting] = piggyBankMoneyByDiv[setting] - currentValue >= 0 ? currentValue : 0;
		if (piggyBankMoneyByDiv[setting] - currentValue < 0)
		{
			int remainder = (piggyBankMoneyByDiv[setting] - currentValue) * -1;
			piggyBankMoneyByDiv[setting == Coin ? Bill : Coin] -= remainder;
		}
		else
			piggyBankMoneyByDiv[setting] -= currentValue;
		countMoneyNorm[setting][getCurrentPosition(setting, currentValue)]
			= countMoneyNorm[setting][getCurrentPosition(setting, currentValue)] == 0
			? 0 : countMoneyNorm[setting][getCurrentPosition(setting, currentValue)]--;

		printf("\nValor removido correctamente.\n");
		break;
	} while (true);
}
#pragma endregion
#pragma region Styles
int getCurrentPosition(int setting, int value) {
	for (int i = 0; i < 5; i++)
	{
		if (value == (setting == Coin ? defaultCoinNorm[i] : defaultBillNorm[i]))
			return i;
	}
	return;
}
void printCoinNorm(int money) {
	printf("La norma es: ");
	int settingCurrentNorm[5];
	for (int i = 0; i < sizeof(currentCoinNorm) / sizeof(currentCoinNorm[0]); i++)
	{
		settingCurrentNorm[i] = money == 0 ? currentCoinNorm[i] : currentBillNorm[i];
	}
	for (int i = 0; i < 5; i++) {
		if (settingCurrentNorm[i] != 0)
			printf("%d ", settingCurrentNorm[i]);
	}
}
void printCountByCoinDenomination(int setting) {
	for (int i = 0; i < 5; i++)
		printf("\nHay %d %s de %d \n", countMoneyNorm[setting][i], setting == Coin ? "monedas" : "billetes", setting == Coin ? defaultCoinNorm[i] : defaultBillNorm[i]);
}
void printStats(int setting) {
	switch (setting)
	{
	case 0:
		printf("El dinero total en la alcancia es de %d\nLas monedas ingresadas es de: %d\nLas capacidad total de monedas es de:%d\nEl restante de las monedas es de: %d\n",
			piggyBankMoney, currentCapacity[Coin], maxCapacity[Coin], (maxCapacity[Coin] - currentCapacity[Coin]));

		printf("Los billetes ingresados es de: %d\nLas capacidad total de billetes es de:%d\nEl restante de los monedas es de: %d\n",
			currentCapacity[Bill], maxCapacity[Bill], (maxCapacity[Bill] - currentCapacity[Bill]));

		printf("El saldo por denominacion de monedas es de: %i\n",piggyBankMoneyByDiv[Coin]);

		printf("El saldo por denominacion de billetes es de: %i\n", piggyBankMoneyByDiv[Bill]);
		printCountByCoinDenomination(Coin);
		printCountByCoinDenomination(Bill);
		break;
	case 1:
	case 3:
		printf("El saldo por denominacion de %s es de: %i",
			setting == 1 ? "monedas" : "billetes",
			piggyBankMoneyByDiv[setting == 1 ? Coin : Bill]);
		break;
	case 2:
	case 4:
		printCountByCoinDenomination(setting == 2 ? Coin : Bill);
		break;

	default:
		break;
	}
	printf("\n");
}
#pragma endregion