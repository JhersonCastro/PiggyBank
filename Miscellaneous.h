#pragma once

/**
* @file Miscellaneous.h
* @version 1.3
* @date 16/06/2023
* @author no
* @brief Funciones de Lectura y escritura sobre archivos .csv
*/

/**
* @brief printCountByCoinDenomination imprime el conteo por denominacion
* @param setting si es 0 son monedas, si es 1 son billetes
* @param countMoneyNorm aqui se almacena el dinero total por denominacion
* @param defaultCoinNorm la norma por defecto para monedas
* @param defaultBillNorm la norma por defecto para billetes
*/
void printCountByCoinDenomination(int setting, int countMoneyNorm[2][5], int defaultCoinNorm[], int defaultBillNorm[]);
/**
* @brief printCoinNorm imprime la norma
* @param setting si es 0 son monedas, si es 1 son billetes
* @param currentCoinNorm la norma personalizada hecha por el usuario para las monedas
* @param currentBillNorm la norma personalizada hecha por el usuario para los billetes
* @param size el tamaño de los areglos
*/
void printCoinNorm(int setting, int currentCoinNorm[], int currentBillNorm[], int size);
/**
* @brief getCurrentPosition encuentra la posicion por un valor
* @param setting si es 0 son monedas, si es 1 son billetes
* @param value el valor dado por el usuario
* @param defaultCoinNorm la norma por defecto para monedas
* @param defaultBillNorm la norma por defecto para billetes
* @return retorna la posicion encontrada por ese valor, -1 si no se encuentra
*/
int getCurrentPosition(int setting, int value, int defaultCoinNorm[], int defaultBillNorm[]);