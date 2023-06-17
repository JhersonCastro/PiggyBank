#include "Funcionalities.h"
#include "csv.h"
#include <string.h>
#include <stdio.h>
#include "StdLib.h"
#include "piggyBank.h"
#include "ModifyValue.h"
#include "Miscellaneous.h"
#include "csv.h"
int modCurrentCoinNorm[] = { 0, 0, 0, 0, 0 };
int modCurrentBillNorm[] = { 0, 0, 0, 0, 0 };
int modDefaultBillNorm[] = { 2000, 5000, 10000, 20000, 50000 };
int modDefaultCoinNorm[] = { 50, 100, 200, 500, 1000 };
int modCoin = 0, modBill = 1;
void setCurrentValues(int CoinNorm[], int BillNorm[]) {
	for (int i = 0; i < 5; i++)
	{
		modCurrentCoinNorm[i] = CoinNorm[i];
		modCurrentBillNorm[i] = BillNorm[i];
	}
}

void setValue(int setting, int* piggyBankMoney, int* piggyBankMoneyByDiv, int* currentCapacity, int(*countMoneyNorm)[5]) {
	int currentValue = 0;
	char cadena[50];
	char valor[50];
	do {
		printCoinNorm(setting, modCurrentCoinNorm, modCurrentBillNorm, (sizeof(modCurrentCoinNorm)/sizeof(modCurrentCoinNorm[0])));
		currentValue = getNumber("Please tell me which number you want to deposit in your piggy bank:");

		if (!isTheValueInTheNorm(currentValue, setting == 0 ? modCurrentCoinNorm : modCurrentBillNorm)) {
			printf("\n%s \n", "The entered value cannot be processed for not following the standard. Please try again.");
			continue;
		}

		*piggyBankMoney += currentValue;
		snprintf(valor, sizeof(valor), "%d", *piggyBankMoney);
		editByID("money", valor);

		piggyBankMoneyByDiv[setting] += currentValue;
		snprintf(valor, sizeof(valor), "%d", piggyBankMoneyByDiv[0]);
		editByID("moneyByCoins", valor);
		snprintf(valor, sizeof(valor), "%d", piggyBankMoneyByDiv[1]);
		editByID("moneyByBills", valor);

		currentCapacity[setting]++;
		snprintf(valor, sizeof(valor), "%d", currentCapacity[setting]);
		editByID(setting == modCoin ? "total_coins_entered" : "total_bills_entered", valor);

		countMoneyNorm[setting][getCurrentPosition(setting, currentValue, modDefaultCoinNorm, modDefaultBillNorm)]++;
		snprintf(cadena, sizeof(cadena), setting == modCoin ? "coins_entered[%d]" : "bills_entered[%d]", getCurrentPosition(setting, currentValue, modDefaultCoinNorm, modDefaultBillNorm));
		snprintf(valor, sizeof(valor), "%d", countMoneyNorm[setting][getCurrentPosition(setting, currentValue, modDefaultCoinNorm, modDefaultBillNorm)]);
		editByID(cadena, valor);


		printf("Value entered successfully\n");
		break;
	} while (1);
}

void removeValue(int setting, int* piggyBankMoney, int* piggyBankMoneyByDiv, int(*countMoneyNorm)[5], int* currentCapacity) {
	int currentValue = 0;
	char id[50];
	char valor[50];
	do {
		printf("The total money in the piggy bank is: %d\n", *piggyBankMoney);
		printf("%s\n", setting == modCoin ? "Coins Stocks: " : "Bill Stocks:");
		for (int i = 0; i < 5; i++)
		{
			if (countMoneyNorm[setting][i] > 0)
			{
				printf("%d %s: %d\n", setting == modCoin ? modDefaultCoinNorm[i] : modDefaultBillNorm[i],
					"have", countMoneyNorm[setting][i]);
			}
		}
		printf("\n");
		currentValue = getNumber("Enter the value you want to remove within the standard.");
		if (!isTheValueInTheNorm(currentValue, setting == 0 ? modCurrentCoinNorm : modCurrentBillNorm)) {
			printf("Por favor, inténtelo de nuevo.,The entered value cannot be processed for not following the standard. Please try again.\n");
			continue;
		}
		for (int i = 0; i < 5; i++)
		{
			if (currentValue == (setting == modCoin ? modDefaultCoinNorm[i] : modDefaultBillNorm[i]) && countMoneyNorm[setting][i] > 0 && currentCapacity[setting] > 0) {
				countMoneyNorm[setting][i]--;
				snprintf(id, sizeof(id), setting == modCoin ? "coins_entered[%d]" : "bills_entered[%d]", i);
				snprintf(valor, sizeof(valor), "%d", countMoneyNorm[setting][i]);
				editByID(id, valor);
				*piggyBankMoney -= currentValue;

				currentCapacity[setting]--;
				snprintf(id, sizeof(id), setting == modCoin ? "coins_entered[%d]" : "bills_entered[%d]", i);
				snprintf(valor, sizeof(valor), "%d", currentCapacity[setting]);
				editByID(id, valor);
				snprintf(valor, sizeof(valor), "%d", *piggyBankMoney);
				editByID("money", valor);
				piggyBankMoneyByDiv[setting] -= currentValue;
				snprintf(valor, sizeof(valor), "%d", piggyBankMoneyByDiv[setting]);
				editByID(setting == modCoin ? "moneyByCoins" : "moneyByBills", valor);
				printf("Se ha retirado correctamente\n");
				return;
			}
		}
		printf("Ha ocurrido un error, intentalo de nuevo");
	} while (1);
}
