#pragma once
/**
* @file ModifyValue.h
* @version 1.3
* @date 16/06/2023
* @author no
* @brief Modifica el dinero (agrega o elimina)
*/
/**
* @brief setValue Pide el valor y verifica si esta en la norma de las denominaciones, ademas, si la alcancia no este llena, lo agrega
* @param setting 0 = Coins, setting 1 = Bills
* @param piggyBankMoney puntero para la modificacion del dinero
* @param piggyBankMoneyByDiv puntero para la modificacion del dinero por denominacion
* @param currentCapacity la capacidad actual de las monedas y billites
* @param countMoneyNorm el dinero por denominacion
*/
void setValue(int setting, int* piggyBankMoney, int* piggyBankMoneyByDiv, int* currentCapacity, int(*countMoneyNorm)[5]);
/**
* @brief setCurrentValues Esta funcion solo es para obtener las variables primordiales de otro archivo (PiggyBank.c)
* @param CoinNorm las denominaciones dadas por el usuario de las monedas
* @param BillNorm las denominaciones dadas por el usuario de los billetes
*/
void setCurrentValues(int CoinNorm[], int BillNorm[]);
/**
* @brief removeValue Pide el valor y si esta en la norma de las denominaciones, ademas de que la alcancia no este vacia, lo elimina
* @param setting 0 = Coins, setting 1 = Bills
* @param piggyBankMoney puntero para la modificacion del dinero
* @param piggyBankMoneyByDiv almacena el dinero determinando si es una moneda o un billete
* @param currentCapacity la capacidad actual de las monedas y billites
* @param countMoneyNorm el dinero por denominacion
*/
void removeValue(int setting, int* piggyBankMoney, int* piggyBankMoneyByDiv, int(*countMoneyNorm)[5], int* currentCapacity);
