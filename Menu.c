#include <stdio.h>
#include "StdLib.h"
#include <stdlib.h>
#include "csv.h"
#include "PiggyBank.h"
#define NUM_OPTIONS 3

typedef void (*func_ptr)(int);
func_ptr menu[NUM_OPTIONS] = { preSetValue,
								preRemoveValue,
								printStats };
char* MenuItems[] = {
	"1. Enter Coin",
		"2. Enter Bill",
		"3. Extract Coin",
		"4. Extract Bill",
		"5. Present Balances and Counts",
		"6. Balances by Denomination of Coins",
		"7. Count by Denomination of Coins",
		"8. Balances by Denomination of Bills",
		"9. Count by Denomination of Bills",
		"10. Inventories",
		"11. Bill Inventories.",
		"12. Coin Inventories.",
		"13. Exit.",
};
void printMenu() {

	for (int i = 0; i < 13; i++)
		printf("%s\n", MenuItems[i]);
}
void piggyBank() {
	dimensionPiggyBank();
	int opc = 0;
	do
	{
		printMenu();
		opc = getNumber("Which option do you want to choose?:");
		if (opc == 1 || opc == 2)
			menu[0](opc == 1 ? 0 : 1);
		else if (opc == 3 || opc == 4)
			menu[1](opc == 3 ? 0 : 1);
		else if (opc >= 5 && opc <= 12)
			menu[2](opc - 5);
		else if (opc == 13)
			break;
		else
			printf("Invalid number entered! \n");
		system("pause");
		system("cls");
	} while (true);
	printf("Haha the funny number\n");
}
