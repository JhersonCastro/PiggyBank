#include <stdio.h>
#include "PiggyBank.h"
#define NUM_OPTIONS 3


char* MenuItems[] = { 
				"1. Ingresar Moneda",
				"2. Ingresar Billete",
				"3. Extraer Moneda",
				"4. Extraer Billete"
				"5. Presentar Saldos y Conteos",
				"6. Saldos por Denominación de Monedas",
				"7. Conteo por Denominación de Monedas",
				"8. Saldos por Denominación de Billetes",
				"9. Conteo por Denominación de Billetes",
				"10. Existencias",
				"11. Existencias de Billetes.",
				"12. Existencias de Monedas.",
				"13. Salir"};
typedef void (*func_ptr)(int);
func_ptr menu[NUM_OPTIONS] = {	setValue,
								removeValue,
								printStats};

void printMenu() {
	for (int i = 0; i < 12; i++)
		printf("%s\n", MenuItems[i]);
}
void piggyBank(){
	dimensionPiggyBank();
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
			printf("¡Número ingresado no valido!");
	} while (opc != 13);

	printf("Jajaja el numero chistoso");
}