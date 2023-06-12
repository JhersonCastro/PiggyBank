#include "data.h"
#include "GlobalVariables.h"

int getCurrentPosition(int setting, int value) {
	for (int i = 0; i < 5; i++)
	{
		if (value == (setting == Coin ? defaultCoinNorm[i] : defaultBillNorm[i]))
			return i;
	}
	return;
}
void printCoinNorm(int money, int lenght) {
	printf(get_text(find_row_by_id(transRows, transRowCount, "standard"), lang));
	int settingCurrentNorm[5];
	for (int i = 0; i < lenght; i++)
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