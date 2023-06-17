/*
* @file Funcionalities.h
* @version 1.3
* @date 16/06/2023
* @author no
* @title Funciones extra de la alcancia
* @brief Funciones necesarias pero no escenciales
*/

#pragma once
#include <stdbool.h>
/*
* @brief isTheValueInTheNorm verifica si el valor esta en la norma
* @param Norm[] array usado para evaluar
* @param value el valor usado para evaluar
* @return V si esta en la norma; F si no lo esta
*/
bool isTheValueInTheNorm(int value, int Norm[]);
/*
* @brief resetPiggyBank resetea los valores del archivo .csv por defecto
*/
void resetPiggyBank();