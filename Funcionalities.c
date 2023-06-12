#include <stdbool.h>
#include <limits.h>
#include "Funcionalities.h"

bool isTheValueInTheNorm(int value, int Norm[]) {
	for (int i = 0; i < 5; i++) {
		if (value == Norm[i] && value != 0)
			return true;
	}
	return false;
}
int* min_combination(int coins[], int bills[], int value) {
    int* result = malloc(2 * sizeof(int));
    int* min_num = malloc((value + 1) * sizeof(int));
    int* coin_used = malloc((value + 1) * sizeof(int));
    min_num[0] = 0;
    for (int i = 1; i <= value; i++) {
        min_num[i] = INT_MAX;
        for (int j = 0; coins[j] != 0; j++) {
            if (coins[j] <= i && min_num[i - coins[j]] + 1 < min_num[i]) {
                min_num[i] = min_num[i - coins[j]] + 1;
                coin_used[i] = coins[j];
            }
        }
        for (int j = 0; bills[j] != 0; j++) {
            if (bills[j] <= i && min_num[i - bills[j]] + 1 < min_num[i]) {
                min_num[i] = min_num[i - bills[j]] + 1;
                coin_used[i] = bills[j];
            }
        }
    }

    int remaining_value = value;
    int num_coins = 0;
    int num_bills = 0;
    while (remaining_value > 0) {
        int coin_or_bill_used = coin_used[remaining_value];
        if (coin_or_bill_used < bills[0]) {
            num_coins++;
        }
        else {
            num_bills++;
        }
        remaining_value -= coin_or_bill_used;
    }

    result[0] = num_coins;
    result[1] = num_bills;

    free(min_num);
    free(coin_used);

    return result;
}/*
int minValueToMoney(int currentNorm[], int value) {

	int currentValue = 0;
int coins = 0;

	while (currentValue != value) {
		int remainingValue = value - currentValue;
		for (int i = 4; i >= 0; i--) {
			if (currentNorm[i] <= remainingValue && currentNorm[i] != 0) {
				coins++;
				currentValue += currentNorm[i];
				break;
			}
		}
	return coins;
}*/
