#include "Funcionalities.h"
#include "csv.h"
#include <string.h>
#include <stdio.h>
#include "StdLib.h"
#include "ModifyValue.h"
#include "csv.h"

row_t transRows[MAX_ROWS];
static int transRowCount;
static char* lang;
int modCurrentCoinNorm[] = { 0, 0, 0, 0, 0 };
int modCurrentBillNorm[] = { 0, 0, 0, 0, 0 };
int modDefaultBillNorm[] = { 2000, 5000, 10000, 20000, 50000 };
int modDefaultCoinNorm[] = { 50, 100, 200, 500, 1000 };
int modCoin = 0, modBill = 1;
void setCurrentValues(int CoinNorm[], int BillNorm[], char* language) {
	transRowCount = readTrans_csv(transRows);
	lang = language;
	for (int i = 0; i < 5; i++)
	{
		modCurrentCoinNorm[i] = CoinNorm[i];
		modCurrentBillNorm[i] = BillNorm[i];
	}
}
void setValue(int setting,int value,int* piggyBankMoney, int* piggyBankMoneyByDiv, int* currentCapacity, int (*countMoneyNorm)[5]) {
	int currentValue = 0;
	char cadena[50];
	char valor[50];
	do {
		printCoinNorm(setting);
		currentValue = getNumber(get_text(find_row_by_id(transRows, transRowCount, "deposit_prompt"), lang));

		if (!isTheValueInTheNorm(currentValue, setting == 0 ? modCurrentCoinNorm : modCurrentBillNorm)) {
			printf("\n%s \n", get_text(find_row_by_id(transRows, transRowCount, "invalid_value_error_2"), lang));
			continue;
		}
		value += currentValue;
		sprintf_s(valor, sizeof(valor), "%d", value);
		editByID("money", valor);
		piggyBankMoney += currentValue;

		piggyBankMoneyByDiv[setting] += currentValue;
		sprintf_s(valor, sizeof(valor), "%d", piggyBankMoneyByDiv[0]);
		editByID("moneyByCoins", valor);
		sprintf_s(valor, sizeof(valor), "%d", piggyBankMoneyByDiv[1]);
		editByID("moneyByBills", valor);

		currentCapacity[setting]++;
		sprintf_s(valor, sizeof(valor), "%d", currentCapacity[setting]);
		editByID(setting == modCoin ? "total_coins_entered" : "total_bills_entered", valor);

		countMoneyNorm[setting][getCurrentPosition(setting, currentValue)]++;
		sprintf_s(cadena, sizeof(cadena), setting == modCoin ? "coins_entered[%d]" : "bills_entered[%d]", getCurrentPosition(setting, currentValue));
		sprintf_s(valor, sizeof(valor), "%d", countMoneyNorm[setting][getCurrentPosition(setting, currentValue)]);
		editByID(cadena, valor);


		printf("\n%s\n", get_text(find_row_by_id(transRows, transRowCount, "successful_entry"), lang));
		break;
	} while (1);
}

void removeValue(int setting, int* piggyBankMoney, int(*countMoneyNorm)[5], int* currentCapacity) {
	int currentValue = 0;
	char id[50];
	char valor[50];
	do {
		printf("%s %d\n", get_text(find_row_by_id(transRows, transRowCount, "total_money"), lang), piggyBankMoney);
		printf("%s:\n", setting == modCoin ? get_text(find_row_by_id(transRows, transRowCount, "stockCoins"), lang) : get_text(find_row_by_id(transRows, transRowCount, "stockBills"), lang));
		for (int i = 0; i < 5; i++)
		{
			if (countMoneyNorm[setting][i] > 0)
			{
				printf("%d %s: %d", setting == modCoin ? modDefaultCoinNorm[i] : modDefaultBillNorm[i],
					get_text(find_row_by_id(transRows, transRowCount, "have"), lang), countMoneyNorm[setting][i]);
			}
		}
		printf("\n");
		currentValue = getNumber(get_text(find_row_by_id(transRows, transRowCount, "enter_value"), lang));
		if (!isTheValueInTheNorm(currentValue, setting == 0 ? modCurrentCoinNorm : modCurrentBillNorm)) {
			printf("\n%s\n", get_text(find_row_by_id(transRows, transRowCount, "invalid_value_error_2"), lang));
			continue;
		}
		if (piggyBankMoney < currentValue) {
			printf("%s %d %s %d", get_text(find_row_by_id(transRows, transRowCount, "extraction_value"), lang),	currentValue,get_text(find_row_by_id(transRows, transRowCount, "greater_than_total"), lang),piggyBankMoney);
			continue;
		}
		for (int i = 0; i < 5; i++)
		{
			if (currentValue == (setting == modCoin ? modDefaultCoinNorm[i] : modDefaultBillNorm[i]) && countMoneyNorm[setting][i] > 0 && currentCapacity[setting] > 0) {
				countMoneyNorm[setting][i]--;
				sprintf_s(id, sizeof(id), setting == modCoin ? "coins_entered[%d]" : "bills_entered[%d]", i);
				sprintf_s(valor, sizeof(valor), "%d", countMoneyNorm[setting][i]);
				editByID(id, valor);
				piggyBankMoney -= currentValue;

				currentCapacity[setting]--;
				sprintf_s(id, sizeof(id), setting == modCoin ? "coins_entered[%d]" : "bills_entered[%d]", i);
				sprintf_s(valor, sizeof(valor), "%d", currentCapacity[setting]);
				editByID(id, valor);

				sprintf_s(valor, sizeof(valor), "%d", piggyBankMoney);
				editByID("money", valor);
				printf("\n Se ha retirado correctamente\n");
				return;
			}
		}
		printf("Ha ocurrido un error, intentalo de nuevo");
	} while (1);
}