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
/**
* @brief piggyBankCreator Funcion encargada de crear una alcancia desde cero
* @param maxCapacity un puntero para editar el contenido
* @param currentCoinNorm un puntero para editar el contenido
* @param currentBillNorm un puntero para editar el contenido
*/
void piggyBankCreator(int* maxCapacity, int* currentCoinNorm, int* currentBillNorm);
/**
* @brief RecoveryCache funcion encargada de restablecer la alcancia desde un archivo .csv
* @param piggyBankMoney un puntero para editar el contenido
* @param currentCoinNorm un puntero para editar el contenido
* @param currentBillNorm un puntero para editar el contenido
* @param maxCapacity un puntero para editar el contenido
* @param currentCapacity un puntero para editar el contenido
* @param piggyBankMoneyByDiv un puntero para editar el contenido
* @param countMoneyNorm un puntero para editar el contenido
*/
void RecoveryCache(int* piggyBankMoney, int* currentCoinNorm, int* currentBillNorm, int* maxCapacity, int* currentCapacity, int* piggyBankMoneyByDiv, int(*countMoneyNorm)[5]);