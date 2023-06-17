#pragma once
/*
* @file ModifyValue.h
* @version 1.3
* @date 16/06/2023
* @author no
* @title Modificacion de la alcancia
* @brief Modifica el dinero (agrega o elimina)
*/
/*
* @brief setValue Pide el valor y si esta en la norma de las denominaciones, ademas de que la alcancia no este llena, lo agrega
* @param setting 0 = Coins, setting 1 = Bills
* @param value el valor actual del dinero total
* @param piggyBankMoney puntero para la modificacion del dinero 
* @param currentCapacity la capacidad actual de las monedas y billites
* @param countMoneyNorm el dinero por denominacion
*/
void setValue(int setting, int value, int* piggyBankMoney, int* piggyBankMoneyByDiv, int* currentCapacity, int(*countMoneyNorm)[5]);
/*
* @brief setCurrentValues Esta funcion solo es para obtener las variables primordiales en otro archivo
* @param CoinNorm las denominaciones dadas por el usuario de las monedas
* @param BillNorm las denominaciones dadas por el usuario de los billetes
* @param language el idioma elegido por el usuario
*/
void setCurrentValues(int CoinNorm[], int BillNorm[], char* language);
/*
* @brief removeValue Pide el valor y si esta en la norma de las denominaciones, ademas de que la alcancia no este vacia, lo elimina
* @param setting 0 = Coins, setting 1 = Bills
* @param piggyBankMoney puntero para la modificacion del dinero
* @param currentCapacity la capacidad actual de las monedas y billites
* @param countMoneyNorm el dinero por denominacion
*/
void removeValue(int setting, int* piggyBankMoney, int(*countMoneyNorm)[5], int* currentCapacity);
