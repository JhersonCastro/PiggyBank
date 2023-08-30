#include "data.h"
#include "GlobalVariables.h"
#pragma region Global Variables
int maxCapacity[] = { 0, 0 };
int currentCapacity[] = { 0, 0 };
int piggyBankMoney = 0;
int piggyBankMoneyByDiv[] = { 0, 0 };
int currentCoinNorm[] = { 0, 0, 0, 0, 0 };
int defaultCoinNorm[] = { 50, 100, 200, 500, 1000 };
int currentBillNorm[] = { 0, 0, 0, 0, 0 };
int defaultBillNorm[] = { 2000, 5000, 10000, 20000, 50000 };
int countMoneyNorm[2][5] = {
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