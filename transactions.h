/**
* @file transactions.h
* @version 1.3
* @date 16/06/2023
* @author no
* @brief Funciones de Lectura y escritura sobre archivos .csv
*/

/**
* @brief readAndPrintTransactions esta funcion lee e imprime por consola las transacciones que se ubican en el archivo transactions.txt
*/
void readAndPrintTransactions();
/**
* @brief saveTransaction esta funcion guarda la hora exacta de la transaccion,la descripcion del movimiento y la cantidad ingresada o retirada en el archivo transactions.txt 
* @param label una descripcion breve y detallada del movimiento 
* @param amount informa los ingresos y extracciones de monedas y billetes 
*/
void saveTransaction(char* label, int amount);
/**
* @brief reset_transactions esta funcion se encarga de limpiar las transacciones guardadas en el archivo transactions.txt
*/
void reset_transactions();