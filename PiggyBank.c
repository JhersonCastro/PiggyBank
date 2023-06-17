#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include "csv.h"
#include "PiggyBank.h"
#include "StdLib.h"
#include "Funcionalities.h"
#include "ModifyValue.h"
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
row_t transRows[MAX_ROWS];
row_d dataRows[MAX_ROWS];
static int transRowCount;
static int dataRowCount;
static char* lang = "es";
#pragma endregion
#pragma region ModifyPiggyBank
void printCountByCoinDenomination(int setting);
void printCoinNorm(int money);
int getCurrentPosition(int setting, int value); 
void piggyBankCreator();
void updateValues();
void dimensionPiggyBank(char* language) {
	lang = language;
	transRowCount = readTrans_csv(transRows);
	dataRowCount = readData_csv(dataRows);
	if (strcmp(dataRows[0].value, "true") == 0)
	{
		printf("Se ha encontrado datos antiguos\n");
		for (int i = 1; i < dataRowCount; i++)
			printf("%s: %s\n", dataRows[i].id, dataRows[i].value);
		if (GetContinue("¿Quieres usar los datos nuevos o antiguos? Y/N"))
		{
			updateValues();
		}
		else {
			resetPiggyBank();
			piggyBankCreator();
		}
	}
	else
		piggyBankCreator();

	qsort(currentCoinNorm, 5, sizeof(int), compareIntegers);
	qsort(currentBillNorm, 5, sizeof(int), compareIntegers);
	setCurrentValues(currentCoinNorm, currentBillNorm, language);
	editByID("is_a_new_piggybank","true");
}
void updateValues() {
	dataRowCount = readData_csv(dataRows);
	char cadena[100];
	piggyBankMoney = atoi(dataRows[searchByID(dataRows, dataRowCount, "money")].value);
	maxCapacity[Coin] = atoi(dataRows[searchByID(dataRows, dataRowCount, "max_coin_capacity")].value);
	maxCapacity[Bill] = atoi(dataRows[searchByID(dataRows, dataRowCount, "max_bill_capacity")].value);
	currentCapacity[Coin] = atoi(dataRows[searchByID(dataRows, dataRowCount, "total_coins_entered")].value);
	currentCapacity[Bill] = atoi(dataRows[searchByID(dataRows, dataRowCount, "total_bills_entered")].value);
	piggyBankMoneyByDiv[Coin] = atoi(dataRows[searchByID(dataRows, dataRowCount, "moneyByCoins")].value);
	piggyBankMoneyByDiv[Bill] = atoi(dataRows[searchByID(dataRows, dataRowCount, "moneyByBills")].value);
	for (int i = 0; i < 5; i++)
	{
		sprintf_s(cadena, sizeof(cadena), "coins_entered[%d]", i);
		countMoneyNorm[Coin][i] = atoi(dataRows[searchByID(dataRows, dataRowCount, cadena)].value);
		sprintf_s(cadena, sizeof(cadena), "bills_entered[%d]", i);
		countMoneyNorm[Bill][i] = atoi(dataRows[searchByID(dataRows, dataRowCount, cadena)].value);


		sprintf_s(cadena, sizeof(cadena), "currentCoinNorm[%d]", i);
		currentCoinNorm[i] = atoi(dataRows[searchByID(dataRows, dataRowCount, cadena)].value);
		sprintf_s(cadena, sizeof(cadena), "currentBillNorm[%d]", i);
		currentBillNorm[i] = atoi(dataRows[searchByID(dataRows, dataRowCount, cadena)].value);
	}
	printf("\nLos valores se restablecieron correctamente!\n");
}
void piggyBankCreator() {
	char cadena[50];
	char valor[50];
	int buffer = 0;
	printf("%s\n", get_text(find_row_by_id(transRows, transRowCount, "piggy_bank_creation"), lang));
	printf("%s", get_text(find_row_by_id(transRows, transRowCount, "coin_capacity"), lang));
	do
	{
		buffer = getNumber(" ");
		if (buffer >= 0 && buffer < INT_MAX) {
			maxCapacity[Coin] = buffer;
			sprintf_s(cadena, sizeof(cadena), "%d", maxCapacity[Coin]);
			editByID("max_coin_capacity", cadena);
			break;
		}
		printf("El limite fue alcanzado o se ingreso un numero negativo, intentalo de nuevo");
	} while (true);

	printf("%s:", get_text(find_row_by_id(transRows, transRowCount, "bill_capacity"), lang));
	do
	{
		buffer = getNumber(" ");
		if (buffer >= 0 && buffer < INT_MAX) {
			maxCapacity[Bill] = buffer;
			sprintf_s(cadena, sizeof(cadena), "%d", maxCapacity[Bill]);
			editByID("max_bill_capacity", cadena);
			break;
		}
		printf("El limite fue alcanzado o se ingreso un numero negativo, intentalo de nuevo");
	} while (true);

	bool isContinue = true;
	for (int i = 0; i < 5; i++) {
		int currentValue = 0;
		if (isContinue) {
			printf("%s", get_text(find_row_by_id(transRows, transRowCount, "coin_denominations"), lang));
			printf("%s", get_text(find_row_by_id(transRows, transRowCount, "accepted_numbers"), lang));
			currentValue = getNumber("");
			if (!isTheValueInTheNorm(currentValue, defaultCoinNorm) || isDuplicateValue(currentCoinNorm, currentValue)) {
				printf("%s", get_text(find_row_by_id(transRows, transRowCount, "no_duplicates"), lang));
				i--;
				continue;
			}
			currentCoinNorm[i] = currentValue;

			sprintf_s(cadena, sizeof(cadena), "currentCoinNorm[%d]", i);
			sprintf_s(valor, sizeof(valor), "%d", currentValue);
			editByID(cadena, valor);
			isContinue = GetContinue(get_text(find_row_by_id(transRows, transRowCount, "continue_prompt"), lang));
		}
		currentCoinNorm[i] = currentValue;
	}
	isContinue = true;
	for (int i = 0; i < 5; i++) {
		int currentValue = 0;
		if (isContinue) {
			printf("%s\n", get_text(find_row_by_id(transRows, transRowCount, "bill_denominations"), lang));
			currentValue = getNumber("");
			if (!isTheValueInTheNorm(currentValue, defaultBillNorm) || isDuplicateValue(currentBillNorm, currentValue)) {
				printf(get_text(find_row_by_id(transRows, transRowCount, "no_duplicates"), lang));
				i--;
				continue;
			}
			currentBillNorm[i] = currentValue;
			sprintf_s(cadena, sizeof(cadena), "currentBillNorm[%d]", i);
			sprintf_s(valor, sizeof(valor), "%d", currentValue);
			editByID(cadena, valor);
			isContinue = GetContinue(get_text(find_row_by_id(transRows, transRowCount, "continue_prompt"), lang));
		}
		currentBillNorm[i] = currentValue;
	}
}
void preSetValue(int settings) {
	setValue(settings, piggyBankMoney,&piggyBankMoney, &piggyBankMoneyByDiv, &currentCapacity, &countMoneyNorm);
}
void preRemoveValue(int settings) {
	removeValue(settings, &piggyBankMoney, &countMoneyNorm, &currentCapacity);
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
	printf(get_text(find_row_by_id(transRows, transRowCount, "standard"), lang));
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
		printf("\n%s %d %s %s %d \n", 
			get_text(find_row_by_id(transRows, transRowCount, "there_are"), lang),
			countMoneyNorm[setting][i], setting == Coin ? 
			get_text(find_row_by_id(transRows, transRowCount, "coins"), lang) : 
			get_text(find_row_by_id(transRows, transRowCount, "bills"), lang),
			get_text(find_row_by_id(transRows, transRowCount, "of"), lang),
			setting == Coin ? defaultCoinNorm[i] : defaultBillNorm[i]);
}
void printStats(int setting) {
	updateValues();
switch (setting)
	{
	case 0:
		printf("%s %d\n%s %d\n%s%d\n%s %d\n",
			get_text(find_row_by_id(transRows, transRowCount, "total_money"), lang),
			piggyBankMoney,
			get_text(find_row_by_id(transRows, transRowCount, "coins_entered"), lang),
			currentCapacity[Coin],
			get_text(find_row_by_id(transRows, transRowCount, "total_coin_capacity"), lang),
			maxCapacity[Coin],
			get_text(find_row_by_id(transRows, transRowCount, "remaining_coins"), lang),
			(maxCapacity[Coin] - currentCapacity[Coin]));


		printf("%s %d\n%s%d\n%s %d\n",
			get_text(find_row_by_id(transRows, transRowCount, "bills_entered"), lang),
			currentCapacity[Bill], 
			get_text(find_row_by_id(transRows, transRowCount, "total_bill_capacity"), lang),
			maxCapacity[Bill],
			get_text(find_row_by_id(transRows, transRowCount, "remaining_bills"), lang),
			(maxCapacity[Bill] - currentCapacity[Bill]));

		printf("%s %i\n",
			get_text(find_row_by_id(transRows, transRowCount, "coin_balance"), lang),
			piggyBankMoneyByDiv[Coin]);

		printf("%s %i\n", 
			get_text(find_row_by_id(transRows, transRowCount, "balance_by_denomination"), lang),
			piggyBankMoneyByDiv[Bill]);
		printCountByCoinDenomination(Coin);
		printCountByCoinDenomination(Bill);
		break;
	case 1:
	case 3:
		printf("%s %s %s %i",
			get_text(find_row_by_id(transRows, transRowCount, "balance_by_denomination"), lang),
			setting == 1 ? get_text(find_row_by_id(transRows, transRowCount, "coins"), lang) : 
			get_text(find_row_by_id(transRows, transRowCount, "bills"), lang),
			get_text(find_row_by_id(transRows, transRowCount, "is_of"), lang),
			piggyBankMoneyByDiv[setting == 1 ? Coin : Bill]);
		break;
	case 2:
	case 4:
		printCountByCoinDenomination(setting == 2 ? Coin : Bill);
		break;
	case 5:
		printf("%s %d\n%s %d\n%s%d\n%s %d\n",
			get_text(find_row_by_id(transRows, transRowCount, "total_money"), lang),
			piggyBankMoney,
			get_text(find_row_by_id(transRows, transRowCount, "coins_entered"), lang),
			currentCapacity[Coin],
			get_text(find_row_by_id(transRows, transRowCount, "total_coin_capacity"), lang),
			maxCapacity[Coin],
			get_text(find_row_by_id(transRows, transRowCount, "remaining_coins"), lang),
			(maxCapacity[Coin] - currentCapacity[Coin]));
		printf("%s %d\n%s%d\n%s %d\n",
			get_text(find_row_by_id(transRows, transRowCount, "bills_entered"), lang),
			currentCapacity[Bill],
			get_text(find_row_by_id(transRows, transRowCount, "total_bill_capacity"), lang),
			maxCapacity[Bill],
			get_text(find_row_by_id(transRows, transRowCount, "remaining_bills"), lang),
			(maxCapacity[Bill] - currentCapacity[Bill]));
		break;
	case 6:
		printf("%s %d\n%s%d\n%s %d\n",
			get_text(find_row_by_id(transRows, transRowCount, "bills_entered"), lang),
			currentCapacity[Bill],
			get_text(find_row_by_id(transRows, transRowCount, "total_bill_capacity"), lang),
			maxCapacity[Bill],
			get_text(find_row_by_id(transRows, transRowCount, "remaining_bills"), lang),
			(maxCapacity[Bill] - currentCapacity[Bill]));
		break;
	case 7:
		printf("%s %d\n%s %d\n%s%d\n%s %d\n",
			get_text(find_row_by_id(transRows, transRowCount, "total_money"), lang),
			piggyBankMoney,
			get_text(find_row_by_id(transRows, transRowCount, "coins_entered"), lang),
			currentCapacity[Coin],
			get_text(find_row_by_id(transRows, transRowCount, "total_coin_capacity"), lang),
			maxCapacity[Coin],
			get_text(find_row_by_id(transRows, transRowCount, "remaining_coins"), lang),
			(maxCapacity[Coin] - currentCapacity[Coin]));
		break;
	default:
		break;
	}
	printf("\n");
	system("pause");

	system("cls");
}
#pragma endregion