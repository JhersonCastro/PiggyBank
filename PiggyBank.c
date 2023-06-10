#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "csv.h"
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
row_t rows[MAX_ROWS];
static int row_count;

static char* lang = "es";
#pragma endregion
#pragma region ModifyPiggyBank
void printCoinNorm(int money);
int getCurrentPosition(int setting, int value); 
void dimensionPiggyBank(char* language) {
	lang = language;
	row_count = read_csv("trans.csv", rows);
	printf("%s\n", get_text(find_row_by_id(rows, row_count, "piggy_bank_creation"), lang));
	printf("%s", get_text(find_row_by_id(rows, row_count, "coin_capacity"), lang));
	maxCapacity[Coin] = getNumber(" ");
	printf("%s:", get_text(find_row_by_id(rows, row_count, "bill_capacity"), lang));
	maxCapacity[Bill] = getNumber(" ");
	
	bool isContinue = true;
	for (int i = 0; i < 5; i++) {
		int currentValue = 0;
		if (isContinue) {
			printf("%s", get_text(find_row_by_id(rows, row_count, "coin_denominations"), lang));
			printf("%s", get_text(find_row_by_id(rows, row_count, "accepted_numbers"), lang));
			currentValue = getNumber("");
			if (!isTheValueInTheNorm(currentValue, defaultCoinNorm) || isDuplicateValue(currentCoinNorm, currentValue)) {
				printf("%s", get_text(find_row_by_id(rows, row_count, "no_duplicates"), lang));
				i--; 
				continue;
			}
			currentCoinNorm[i] = currentValue;
			isContinue = GetContinue(get_text(find_row_by_id(rows, row_count, "continue_prompt"), lang));
		}
		currentCoinNorm[i] = currentValue;
	}
	isContinue = true;
	for (int i = 0; i < 5; i++) {
		int currentValue = 0;
		if (isContinue) {
			printf("%s\n", get_text(find_row_by_id(rows, row_count, "bill_denominations"), lang));
			currentValue = getNumber("");
			if (!isTheValueInTheNorm(currentValue, defaultBillNorm) || isDuplicateValue(currentBillNorm, currentValue)) {
				printf(get_text(find_row_by_id(rows, row_count, "no_duplicates"), lang)); 
				i--; 
				continue;
			}
			currentBillNorm[i] = currentValue;
			isContinue = GetContinue(get_text(find_row_by_id(rows, row_count, "continue_prompt"), lang));
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
		currentValue = getNumber(get_text(find_row_by_id(rows, row_count, "deposit_prompt"), lang));

		if (!isTheValueInTheNorm(currentValue, setting == 0 ? currentCoinNorm : currentBillNorm)) {
			printf("\n%s \n", get_text(find_row_by_id(rows, row_count, "invalid_value_error_2"),lang));
			continue;
		}
		piggyBankMoney += currentValue;
		piggyBankMoneyByDiv[setting] += currentValue;
		currentCapacity[setting]++;
		countMoneyNorm[setting][getCurrentPosition(setting, currentValue)]++;
		printf("\n%s\n", get_text(find_row_by_id(rows, row_count, "successful_entry"), lang));
		break;
	} while (true);
}
void removeValue(int setting) {
	int currentValue = 0;
	do {
		printf("%s %d\n", get_text(find_row_by_id(rows, row_count, "total_money"), lang),piggyBankMoney);
		printCoinNorm(setting);
		currentValue = getNumber(get_text(find_row_by_id(rows, row_count, "enter_value"), lang));
		if (!isTheValueInTheNorm(currentValue, setting == 0 ? currentCoinNorm : currentBillNorm)) {
			printf("\n%s\n", get_text(find_row_by_id(rows, row_count, "invalid_value_error_2"), lang));
			continue;
		}
		if (piggyBankMoney < currentValue) {
			printf("%s %d %s %d", 
				get_text(find_row_by_id(rows, row_count, "extraction_value"), lang), 
				currentValue, 
				get_text(find_row_by_id(rows, row_count, "greater_than_total"), lang),
				piggyBankMoney);
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

			printf("%s\n", get_text(find_row_by_id(rows, row_count, "conversion_error"), lang));
			if (GetContinue(get_text(find_row_by_id(rows, row_count, "continue_extraction"), lang)))
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

		printf("\n%s\n", get_text(find_row_by_id(rows, row_count, "value_removed"), lang));
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
	printf(get_text(find_row_by_id(rows, row_count, "standard"), lang));
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
			get_text(find_row_by_id(rows, row_count, "there_are"), lang),
			countMoneyNorm[setting][i], setting == Coin ? 
			get_text(find_row_by_id(rows, row_count, "coins"), lang) : 
			get_text(find_row_by_id(rows, row_count, "bills"), lang),
			get_text(find_row_by_id(rows, row_count, "of"), lang),
			setting == Coin ? defaultCoinNorm[i] : defaultBillNorm[i]);
}
void printStats(int setting) {
	switch (setting)
	{
	case 0:
		printf("%s %d\n%s %d\n%s%d\n%s %d\n",
			get_text(find_row_by_id(rows, row_count, "total_money"), lang),
			piggyBankMoney,
			get_text(find_row_by_id(rows, row_count, "coins_entered"), lang),
			currentCapacity[Coin],
			get_text(find_row_by_id(rows, row_count, "total_coin_capacity"), lang),
			maxCapacity[Coin],
			get_text(find_row_by_id(rows, row_count, "remaining_coins"), lang),
			(maxCapacity[Coin] - currentCapacity[Coin]));


		printf("%s %d\n%s%d\n%s %d\n",
			get_text(find_row_by_id(rows, row_count, "bills_entered"), lang),
			currentCapacity[Bill], 
			get_text(find_row_by_id(rows, row_count, "total_bill_capacity"), lang),
			maxCapacity[Bill],
			get_text(find_row_by_id(rows, row_count, "remaining_bills"), lang),
			(maxCapacity[Bill] - currentCapacity[Bill]));

		printf("%s %i\n",
			get_text(find_row_by_id(rows, row_count, "coin_balance"), lang),
			piggyBankMoneyByDiv[Coin]);

		printf("%s %i\n", 
			get_text(find_row_by_id(rows, row_count, "balance_by_denomination"), lang),
			piggyBankMoneyByDiv[Bill]);
		printCountByCoinDenomination(Coin);
		printCountByCoinDenomination(Bill);
		break;
	case 1:
	case 3:
		printf("%s %s %s %i",
			get_text(find_row_by_id(rows, row_count, "balance_by_denomination"), lang),
			setting == 1 ? get_text(find_row_by_id(rows, row_count, "coins"), lang) : 
			get_text(find_row_by_id(rows, row_count, "bills"), lang),
			get_text(find_row_by_id(rows, row_count, "is_of"), lang),
			piggyBankMoneyByDiv[setting == 1 ? Coin : Bill]);
		break;
	case 2:
	case 4:
		printCountByCoinDenomination(setting == 2 ? Coin : Bill);
		break;
	case 5:
		printf("%s %d\n%s %d\n%s%d\n%s %d\n",
			get_text(find_row_by_id(rows, row_count, "total_money"), lang),
			piggyBankMoney,
			get_text(find_row_by_id(rows, row_count, "coins_entered"), lang),
			currentCapacity[Coin],
			get_text(find_row_by_id(rows, row_count, "total_coin_capacity"), lang),
			maxCapacity[Coin],
			get_text(find_row_by_id(rows, row_count, "remaining_coins"), lang),
			(maxCapacity[Coin] - currentCapacity[Coin]));
		printf("%s %d\n%s%d\n%s %d\n",
			get_text(find_row_by_id(rows, row_count, "bills_entered"), lang),
			currentCapacity[Bill],
			get_text(find_row_by_id(rows, row_count, "total_bill_capacity"), lang),
			maxCapacity[Bill],
			get_text(find_row_by_id(rows, row_count, "remaining_bills"), lang),
			(maxCapacity[Bill] - currentCapacity[Bill]));
		break;
	case 6:
		printf("%s %d\n%s%d\n%s %d\n",
			get_text(find_row_by_id(rows, row_count, "bills_entered"), lang),
			currentCapacity[Bill],
			get_text(find_row_by_id(rows, row_count, "total_bill_capacity"), lang),
			maxCapacity[Bill],
			get_text(find_row_by_id(rows, row_count, "remaining_bills"), lang),
			(maxCapacity[Bill] - currentCapacity[Bill]));
		break;
	case 7:
		printf("%s %d\n%s %d\n%s%d\n%s %d\n",
			get_text(find_row_by_id(rows, row_count, "total_money"), lang),
			piggyBankMoney,
			get_text(find_row_by_id(rows, row_count, "coins_entered"), lang),
			currentCapacity[Coin],
			get_text(find_row_by_id(rows, row_count, "total_coin_capacity"), lang),
			maxCapacity[Coin],
			get_text(find_row_by_id(rows, row_count, "remaining_coins"), lang),
			(maxCapacity[Coin] - currentCapacity[Coin]));
		break;
	default:
		break;
	}
	printf("\n");
}
#pragma endregion