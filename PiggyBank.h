#pragma once
/**
* @file PiggyBank.h
* @version 1.3
* @date 16/06/2023
* @author nos
* @brief Alcancia primitiva, puede imprimir la estadistica dada por el usuario
*/
/**
* @brief defaultBillNorm variable que contiene la denominacion por defecto para los billetes
*/
extern int defaultBillNorm[5];
/**
* @brief defaultCoinNorm variable que contiene la denominacion por defecto para las monedas
*/
extern int defaultCoinNorm[5];

/**
* @brief preSetValue Le da los parametros de manera primitiva a la funcion SetValue, que esta en otro archivo (ModifyValue.c)
* @param settings 0 = Coins, setting 1 = Bills
*/
void preSetValue(int settings);

/**
* @brief preRemoveValue Le da los parametros de manera primitiva a la funcion RemoveValue, que esta en otro archivo (ModifyValue.c)
* @param settings 0 = Coins, setting 1 = Bills
*/
void preRemoveValue(int settings);

/**
* @brief dimensionPiggyBank Dimensiona el cerdito :3
*/
void dimensionPiggyBank();
/**
* @brief preSetValue Le da los parametros de manera primitiva a la funcion SetValue, que esta en otro archivo
* @param setting
	0 = Todo;
	1 = Saldos por Denominaci�n de Monedas;
	2 = Conteo por Denominaci�n de Monedas;
	3 = Saldos por Denominaci�n de Billetes;
	4 = Conteo por Denominaci�n de Billetes;
	5 = Existencias;
	6 = Existencias de Billetes;
	7 = Existencias de Monedas.
*/
void printStats(int setting);

