#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "csv.h"
#include "Miscellaneous.h"
#include "PiggyBank.h"
#include "StdLib.h"
#include "Funcionalities.h"
#include "ModifyValue.h"

#pragma region Variables
int maxCapacity[2] = { 0, 0 };
int currentCapacity[2] = { 0, 0 };
int piggyBankMoney = 0;
int piggyBankMoneyByDiv[2] = { 0, 0 };
int currentCoinNorm[5] = { 0, 0, 0, 0, 0 };
int defaultCoinNorm[5] = { 50, 100, 200, 500, 1000 };
int currentBillNorm[5] = { 0, 0, 0, 0, 0 };
int defaultBillNorm[5] = { 2000, 5000, 10000, 20000, 50000 };
int countMoneyNorm[2][5] = {/*Coins*/{ 0, 0, 0, 0, 0 },
							/*Bills*/{ 0, 0, 0, 0, 0 } };
int Coin = 0, Bill = 1;
#pragma endregion
#pragma region Funcs
void dimensionPiggyBank() {
	row_d* dataRows;
	int dataRowCount;

	dataRows = (row_d*)malloc(MAX_ROWS * sizeof(row_d));
	if (dataRows == NULL) {
		printf("Error allocating memory\n");
		return;
	}

	dataRowCount = readData_csv(dataRows);
	if (strcmp(dataRows[0].value, "true") == 0)
	{
		printf("Oh, I see that we have old records of you in our database.\n");
		for (int i = 1; i < 8; i++)
			printf("%s: %s\n", dataRows[i].id, dataRows[i].value);
		if (GetContinue("Do want to recover your data? Y / N"))
			RecoveryCache(&piggyBankMoney, currentCoinNorm, currentBillNorm, maxCapacity, currentCapacity, piggyBankMoneyByDiv, countMoneyNorm);
		else
			piggyBankCreator(maxCapacity, currentCoinNorm, currentBillNorm);
	}
	else
		piggyBankCreator(maxCapacity, currentCoinNorm, currentBillNorm);

	qsort(currentCoinNorm, 5, sizeof(int), compareIntegers);
	qsort(currentBillNorm, 5, sizeof(int), compareIntegers);
	setCurrentValues(currentCoinNorm, currentBillNorm);
	editByID("is_a_new_piggybank", "true");
	system("cls");
	free(dataRows);
}
void printStats(int setting) {
	system("cls");
	switch (setting)
	{
	case 0:
		printf("%s %d\n%s %d\n%s%d\n%s %d\n", "The total money in the piggy bank is:", piggyBankMoney, "The coins entered is:", currentCapacity[Coin], "The total coin capacity is:", maxCapacity[Coin], "The remaining coins are:", (maxCapacity[Coin] - currentCapacity[Coin]));
		printf("The bills entered is: %d\nThe total bill capacity is:%d\nThe remaining bills are: %d\n", currentCapacity[Bill], maxCapacity[Bill], (maxCapacity[Bill] - currentCapacity[Bill]));
		printf("The balance by denomination of coins is: %i\n", piggyBankMoneyByDiv[Coin]);
		printf("The balance by denomination of: %i\n", piggyBankMoneyByDiv[Bill]);
		printCountByCoinDenomination(Coin, countMoneyNorm, defaultCoinNorm, defaultBillNorm);
		printCountByCoinDenomination(Bill, countMoneyNorm, defaultCoinNorm, defaultBillNorm);
		break;
	case 1:
	case 3:
		printf("The balance by denomination of %s is of %i", setting == 1 ? "coins" : "bills", piggyBankMoneyByDiv[setting == 1 ? Coin : Bill]);
		break;
	case 2:
	case 4:
		printCountByCoinDenomination(setting == 2 ? Coin : Bill, countMoneyNorm, defaultCoinNorm, defaultBillNorm);
		break;
	case 5:
		printf("%s %d\n%s %d\n%s%d\n%s %d\n", "The total money in the piggy bank is:", piggyBankMoney, "The coins entered is:", currentCapacity[Coin], "The total coin capacity is:", maxCapacity[Coin], "The remaining coins are:", (maxCapacity[Coin] - currentCapacity[Coin]));
		printf("%s %d\n%s%d\n%s %d\n", "The bills entered is:", currentCapacity[Bill], "The total bill capacity is:", maxCapacity[Bill], "The remaining bills are:", (maxCapacity[Bill] - currentCapacity[Bill]));
		break;
	case 6:
		printf("%s %d\n%s%d\n%s %d\n", "The bills entered is:", currentCapacity[Bill], "The total bill capacity is:", maxCapacity[Bill], "The remaining bills are:", (maxCapacity[Bill] - currentCapacity[Bill]));
		break;
	case 7:
		printf("%s %d\n%s %d\n%s%d\n%s %d\n", "The total money in the piggy bank is:", piggyBankMoney, "The coins entered is:", currentCapacity[Coin], "The total coin capacity is:", maxCapacity[Coin], "The remaining coins are:", (maxCapacity[Coin] - currentCapacity[Coin]));
		break;
	default:
		break;
	}
}
#pragma endregion
#pragma region preFuncs()
void preSetValue(int settings) {
	if (currentCapacity[settings] < maxCapacity[settings])
		setValue(settings, &piggyBankMoney, piggyBankMoneyByDiv, currentCapacity, countMoneyNorm);
	else
		printf("Remove some %s to continue", settings == Coin ? "coins" : "bills");
}
void preRemoveValue(int settings) {
	if (currentCapacity[settings] > 0)
		removeValue(settings, &piggyBankMoney, piggyBankMoneyByDiv, countMoneyNorm, currentCapacity);
	else
		printf("Add some %s to continue\n", settings == Coin ? "coins" : "bills");
}

#pragma endregion
