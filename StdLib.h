/**
* @file StdLib.h
* @version 1.3
* @date 16/06/2023
* @author no
* @brief Funciones de utileria
* @code
* int main(){
* int example = 0;
* example = getNumber("Tell me a number");
* printf("The number is: %i", example);
* //Output: Tell me a number
* //Input: 5
* //Output: The number is 5
* }
* @endcode
*/
#include <stdbool.h>
#pragma once

/**
* @brief GetContinue Pregunta al usuario si quiere seguir.
* @param PrmLabel Una simple etiqueta
* @return retorna verdadero si la respuesta del usuario es positiva, sino retorna falso
*/
bool GetContinue(const char* PrmLabel);
/**
* @brief getNumber Pregunta al usuario por un numero, y comprueba si lo ingresado si es un numero.
* @param prmEtiqueta Una simple etiqueta
* @return retorna el numero dado
*/
int getNumber(const char* prmEtiqueta);
/**
* @brief isDuplicateValue verifica si en el array pasado por parametro es igual al valor dado por el parametro.
* @param array el arreglo a evaluar
* @param value el valor para evaluar
* @return retorna verdadero si hay una equivalencia, falso si no
*/
bool isDuplicateValue(int array[], int value, int size);
/**
* @brief compareIntegers Compara dos enteros
* @param a none
* @param b none
* @return -1 menor, 0 igual, 1 mayor
*/
int compareIntegers(const void* a, const void* b);
