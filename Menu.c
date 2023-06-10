#include <stdio.h>
#include "csv.h"
#include "PiggyBank.h"
#define NUM_OPTIONS 3
static char* lang = "es";


typedef void (*func_ptr)(int);
func_ptr menu[NUM_OPTIONS] = {	setValue,
								removeValue,
								printStats};

void printMenu() {
	row_t rows[MAX_ROWS];
	int row_count = read_csv("trans.csv", rows);
	char* MenuItems[] = { 
		get_text(find_row_by_id(rows, row_count, "enter_coin"), lang),
		get_text(find_row_by_id(rows, row_count, "enter_bill"), lang),
		get_text(find_row_by_id(rows, row_count, "extract_coin"), lang),
		get_text(find_row_by_id(rows, row_count, "extract_bill"), lang),
		get_text(find_row_by_id(rows, row_count, "present_balances_and_counts"), lang),
		get_text(find_row_by_id(rows, row_count, "coin_balances_by_denomination"), lang),
		get_text(find_row_by_id(rows, row_count, "coin_counts_by_denomination"), lang),
		get_text(find_row_by_id(rows, row_count, "bill_balances_by_denomination"), lang),
		get_text(find_row_by_id(rows, row_count, "inventories"), lang),
		get_text(find_row_by_id(rows, row_count, "bill_inventories"), lang),
		get_text(find_row_by_id(rows, row_count, "coin_inventories"), lang),
		get_text(find_row_by_id(rows, row_count, "exit_option"), lang),
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
		opc = getNumber("¿Cuál opcion quieres elegir?: ");
		if (opc == 1 || opc == 2)
			menu[0](opc == 1 ? 0 : 1);
		else if (opc == 3 || opc == 4)
			menu[1](opc == 3 ? 0 : 1);
		else if (opc >= 5 && opc <= 12)
			menu[2](opc - 5);
		else
			printf("¡Número ingresado no válido!");
	} while (opc != 13);

	printf("Jajaja el numero chistoso");
}