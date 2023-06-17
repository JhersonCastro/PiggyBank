#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "csv.h"
#include "Funcionalities.h"

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
        sprintf_s(cadena, sizeof(cadena), "coins_entered[%d]", i);
        editByID(cadena, "0");
        sprintf_s(cadena, sizeof(cadena), "bills_entered[%d]", i);
        editByID(cadena, "0");
        sprintf_s(cadena, sizeof(cadena), "currentCoinNorm[%d]", i);
        editByID(cadena, "0");
        sprintf_s(cadena, sizeof(cadena), "currentBillNorm[%d]", i);
        editByID(cadena, "0");
    }
}