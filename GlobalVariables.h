#ifndef DATA_H
#define DATA_H
extern int maxCapacity[];
extern int currentCapacity[];
extern int piggyBankMoney;
extern int piggyBankMoneyByDiv[];
extern int currentCoinNorm[];
extern int defaultCoinNorm[];
extern int currentBillNorm[];
extern int defaultBillNorm[];
extern int countMoneyNorm[2][5];
extern int Coin, Bill;
extern row_t transRows[MAX_ROWS];
extern row_d dataRows[MAX_ROWS];
extern int transRowCount;
extern int dataRowCount;
extern char* lang;

#endif
