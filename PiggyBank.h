#pragma once

/*setting 0 = Coins, setting 1 = Bills*/
void setValue(int settings);
/*setting 0 = Coins, setting 1 = Bills*/
void removeValue(int settings);
float getNumber(char* prmEtiqueta);
void dimensionPiggyBank(char* language);
/*setting
0 = Todo;
1 = Saldos por Denominaci�n de Monedas;
2 = Conteo por Denominaci�n de Monedas;
3 = Saldos por Denominaci�n de Billetes;
4 = Conteo por Denominaci�n de Billetes
5 = Existencias
6 = Existencias de Billetes.
7 = Existencias de Monedas.*/
void printStats(int setting);