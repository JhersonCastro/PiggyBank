#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#include "StdLib.h"
#include "PiggyBank.h"
#include "csv.h"
#include "Funcionalities.h"
#include "transactions.h"
bool isTheValueInTheNorm(int value, int Norm[]) {
    for (int i = 0; i < 5; i++) {
        if (value == Norm[i] && value != 0)
            return true;
    }
    return false;
}
void resetPiggyBank() {
    editByID("money", "0");
    editByID("moneyByCoins", "0");
    editByID("moneyByBills", "0");
    editByID("max_bill_capacity", "0");
    editByID("max_coin_capacity", "0");
    editByID("total_bills_entered", "0");
    editByID("total_coins_entered", "0");
    char cadena[50];
    for (size_t i = 0; i < 5; i++)
    {
        snprintf(cadena, sizeof(cadena), "coins_entered[%zu]", i);
        editByID(cadena, "0");
        snprintf(cadena, sizeof(cadena), "bills_entered[%zu]", i);
        editByID(cadena, "0");
        snprintf(cadena, sizeof(cadena), "currentCoinNorm[%zu]", i);
        editByID(cadena, "0");
        snprintf(cadena, sizeof(cadena), "currentBillNorm[%zu]", i);
        editByID(cadena, "0");
    }
	reset_transactions();
}
void piggyBankCreator(int* maxCapacity, int* currentCoinNorm, int* currentBillNorm) {
	resetPiggyBank();
	char cadena[50];
	char valor[50];
	int buffer = 0;
	int Coin = 0, Bill = 1;
	editByID("is_a_new_piggybank", "false");
	printf("Piggy bank creation\n");
	printf("How much capacity (for coins) do you want to give the piggy bank?:");
	do
	{
		buffer = getNumber(" ");
		if (buffer >= 0 && buffer < INT_MAX) {
			maxCapacity[Coin] = buffer;
			snprintf(cadena, sizeof(cadena), "%d", maxCapacity[Coin]);
			editByID("max_coin_capacity", cadena);
			break;
		}
		printf("El limite fue alcanzado o se ingreso un numero negativo, intentalo de nuevo");
	} while (true);

	printf("How much capacity (for bills) do you want to give the piggy bank?:");
	do
	{
		buffer = getNumber(" ");
		if (buffer >= 0 && buffer < INT_MAX) {
			maxCapacity[Bill] = buffer;
			snprintf(cadena, sizeof(cadena), "%d", maxCapacity[Bill]);
			editByID("max_bill_capacity", cadena);
			break;
		}
		printf("El limite fue alcanzado o se ingreso un numero negativo, intentalo de nuevo");
	} while (true);

bool isContinue = true;
	for (int i = 0; i < 5; i++) {
		int currentValue = 0;
		if (isContinue) {
			printf("What denominations do you want (for coins)?\n");
			printf("these are the accepted numbers: 50. 100. 200. 500. 1000: ");
			currentValue = getNumber("");
			if (!isTheValueInTheNorm(currentValue, defaultCoinNorm) || isDuplicateValue(currentCoinNorm, currentValue, 5)) {
				printf("No duplicate amounts are allowed, nor amounts that are not in the default standard");
				i--;
				continue;
			}
			currentCoinNorm[i] = currentValue;

			snprintf(cadena, sizeof(cadena), "currentCoinNorm[%d]", i);
			snprintf(valor, sizeof(valor), "%d", currentValue);
			editByID(cadena, valor);
			isContinue = GetContinue("Do you want to continue? Y/N");
		}
		currentCoinNorm[i] = currentValue;
	}
	isContinue = true;
	for (int i = 0; i < 5; i++) {
		int currentValue = 0;
		if (isContinue) {
			printf("What denominations do you want (for bills)?\n");
			printf("these are the accepted numbers: 2000. 10000. 20000. 50000: ");
			currentValue = getNumber("");
			if (!isTheValueInTheNorm(currentValue, defaultBillNorm) || isDuplicateValue(currentBillNorm, currentValue, 5)) {
				printf("No duplicate amounts are allowed, nor amounts that are not in the default standard\n");
				i--;
				continue;
			}
			currentBillNorm[i] = currentValue;
			snprintf(cadena, sizeof(cadena), "currentBillNorm[%d]", i);
			snprintf(valor, sizeof(valor), "%d", currentValue);
			editByID(cadena, valor);
			isContinue = GetContinue("Do you want to continue? Y/N");
		}
		currentBillNorm[i] = currentValue;
	}
}
void RecoveryCache(int* piggyBankMoney, int* currentCoinNorm, int* currentBillNorm,int* maxCapacity, int* currentCapacity,int* piggyBankMoneyByDiv, int(*countMoneyNorm)[5]) {
	row_d* dataRows = (row_d*)malloc(MAX_ROWS * sizeof(row_d));
	if (dataRows == NULL) {
		printf("Error allocating memory\n");
		return;
	}
	int dataRowCount = readData_csv(dataRows);
	int Coin = 0, Bill = 1;
	char cadena[100];
	*piggyBankMoney = atoi(dataRows[searchByID(dataRows, dataRowCount, "money")].value);
	maxCapacity[Coin] = atoi(dataRows[searchByID(dataRows, dataRowCount, "max_coin_capacity")].value);
	maxCapacity[Bill] = atoi(dataRows[searchByID(dataRows, dataRowCount, "max_bill_capacity")].value);
	currentCapacity[Coin] = atoi(dataRows[searchByID(dataRows, dataRowCount, "total_coins_entered")].value);
	currentCapacity[Bill] = atoi(dataRows[searchByID(dataRows, dataRowCount, "total_bills_entered")].value);
	piggyBankMoneyByDiv[Coin] = atoi(dataRows[searchByID(dataRows, dataRowCount, "moneyByCoins")].value);
	piggyBankMoneyByDiv[Bill] = atoi(dataRows[searchByID(dataRows, dataRowCount, "moneyByBills")].value);

	for (int i = 0; i < 5; i++)
	{
		snprintf(cadena, sizeof(cadena), "coins_entered[%d]", i);
		countMoneyNorm[Coin][i] = atoi(dataRows[searchByID(dataRows, dataRowCount, cadena)].value);
		snprintf(cadena, sizeof(cadena), "bills_entered[%d]", i);
		countMoneyNorm[Bill][i] = atoi(dataRows[searchByID(dataRows, dataRowCount, cadena)].value);


		snprintf(cadena, sizeof(cadena), "currentCoinNorm[%d]", i);
		currentCoinNorm[i] = atoi(dataRows[searchByID(dataRows, dataRowCount, cadena)].value);
		snprintf(cadena, sizeof(cadena), "currentBillNorm[%d]", i);
		currentBillNorm[i] = atoi(dataRows[searchByID(dataRows, dataRowCount, cadena)].value);
	}
	free(dataRows);
	printf("\nLos valores se restablecieron correctamente!\n");
}