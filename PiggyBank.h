#pragma once
/**
* @file PiggyBank.h
* @version 1.3
* @date 16/06/2023
* @author nos
* @brief Alcancia primitiva, puede imprimir la estadistica dada por el usuario
*/

extern int defaultBillNorm[5];
extern int defaultCoinNorm[5];

/**
* @brief preSetValue Le da los parametros de manera primitiva a la funcion SetValue, que esta en otro archivo
* @param settings 0 = Coins, setting 1 = Bills
*/
void preSetValue(int settings);

/**
* @brief preRemoveValue Le da los parametros de manera primitiva a la funcion RemoveValue, que esta en otro archivo
* @param settings 0 = Coins, setting 1 = Bills
*/
void preRemoveValue(int settings);

/**
* @brief dimensionPiggyBank Dimensiona el cerdito :3
* @param language el idioma puesto por el usuario
*/
void dimensionPiggyBank();
/**
* @brief preSetValue Le da los parametros de manera primitiva a la funcion SetValue, que esta en otro archivo
* @param setting
	0 = Todo;
	1 = Saldos por Denominación de Monedas;
	2 = Conteo por Denominación de Monedas;
	3 = Saldos por Denominación de Billetes;
	4 = Conteo por Denominación de Billetes;
	5 = Existencias;
	6 = Existencias de Billetes;
	7 = Existencias de Monedas.
*/
void printStats(int setting);

