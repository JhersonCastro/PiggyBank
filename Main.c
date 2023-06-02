#include <stdbool.h>
#include "PiggyBank.h"
#include "StdLib.h"


int main(void) {
	dimensionPiggyBank();
	do {
		piggyBank();
	} while (GetContinue("Do u want continue? Y/N"));
	return 0;
}
