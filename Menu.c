#include <stdio.h>
#include "csv.h"
#include "PiggyBank.h"
#define NUM_OPTIONS 3
static char* lang = "es";
row_t transRows[MAX_ROWS];
static int transRowCount;

typedef void (*func_ptr)(int);
func_ptr menu[NUM_OPTIONS] = {	setValue,
								removeValue,
								printStats};

void printMenu() {
	transRowCount = readTrans_csv(transRows);
	char* MenuItems[] = { 
		get_text(find_row_by_id(transRows, transRowCount, "enter_coin"), lang),
		get_text(find_row_by_id(transRows, transRowCount, "enter_bill"), lang),
		get_text(find_row_by_id(transRows, transRowCount, "extract_coin"), lang),
		get_text(find_row_by_id(transRows, transRowCount, "extract_bill"), lang),
		get_text(find_row_by_id(transRows, transRowCount, "present_balances_and_counts"), lang),
		get_text(find_row_by_id(transRows, transRowCount, "coin_balances_by_denomination"), lang),
		get_text(find_row_by_id(transRows, transRowCount, "coin_counts_by_denomination"), lang),
		get_text(find_row_by_id(transRows, transRowCount, "bill_balances_by_denomination"), lang),
		get_text(find_row_by_id(transRows, transRowCount, "inventories"), lang),
		get_text(find_row_by_id(transRows, transRowCount, "bill_inventories"), lang),
		get_text(find_row_by_id(transRows, transRowCount, "coin_inventories"), lang),
		get_text(find_row_by_id(transRows, transRowCount, "exit_option"), lang),
							};
	for (int i = 0; i < 12; i++)
		printf("%s\n", MenuItems[i]);
}
void piggyBank(char* language){
	lang = language;
	dimensionPiggyBank(lang);
	int opc = 0;
	do
	{
		printMenu();
		opc = getNumber(get_text(find_row_by_id(transRows, transRowCount, "option_choice"), lang));
		if (opc == 1 || opc == 2)
			menu[0](opc == 1 ? 0 : 1);
		else if (opc == 3 || opc == 4)
			menu[1](opc == 3 ? 0 : 1);
		else if (opc >= 5 && opc <= 12)
			menu[2](opc - 5);
		else
			printf("%s", get_text(find_row_by_id(transRows, transRowCount, "invalid_number"), lang));
	} while (opc != 13);

	printf("%s", get_text(find_row_by_id(transRows, transRowCount, "funny_number"), lang));
}