/**
* @file Funcionalities.h
* @version 1.3
* @date 16/06/2023
* @author no
* @brief Funciones necesarias pero no escenciales
*/

#pragma once
#include <stdbool.h>
/**
* @brief isTheValueInTheNorm verifica si el valor esta en la norma
* @param Norm[] array usado para evaluar
* @param value el valor usado para evaluar
* @return V si esta en la norma; F si no lo esta
*/
bool isTheValueInTheNorm(int value, int Norm[]);
/**
* @brief resetPiggyBank resetea los valores del archivo .csv por defecto
*/
void resetPiggyBank();

void piggyBankCreator(int* maxCapacity, int defaultCoinNorm[], int defaultBillNorm[], int* currentCoinNorm, int* currentBillNorm);

void RecoveryCache(int* piggyBankMoney, int* currentCoinNorm, int* currentBillNorm, int* maxCapacity, int* currentCapacity, int* piggyBankMoneyByDiv, int(*countMoneyNorm)[5]);