#include <stdbool.h>
#include "Funcionalities.h"

bool isTheValueInTheNorm(int value, int Norm[]) {
	for (int i = 0; i < 5; i++) {
		if (value == Norm[i] && value != 0)
			return true;
	}
	return false;
}
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
	}
	return coins;
}