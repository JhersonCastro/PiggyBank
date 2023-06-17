/**
* @file csv.h
* @version 1.3
* @date 16/06/2023
* @author no
* @brief Funciones de Lectura y escritura sobre archivos .csv
*/
#ifndef CSV_H
#define CSV_H

#define MAX_ROWS 100
/**
* @brief Estructura para las definiciones de los, cada uno tiene su propio id, y su respectitivo valor
*/
typedef struct {
    char id[50];
    char value[1024];
} row_d;
/**
* @brief editByID solo cambia su valor
* @param id_buscado el id de la fila en especifico para cambiar su valor
* @param nuevo_valor El valor que va a ser cambiado
*/
void editByID(char* id_buscado, char* nuevo_valor);
/**
* @brief readData_csv Lee los datos y las copia (por asi decirlo, ya que su parametro es un puntero) a la variable creada por row_d
* @param rows un parametro puntero de tipo row_d
* @return retorna el numero total de filas encontradas
*/
int readData_csv(row_d* rows);
/**
* @brief searchByID encuentra la fila por id
* @param rows un parametro puntero de tipo row_d
* @param lenght la cantidad total de filas
* @param id el id para encontrar
* @return retorna la posicion encontrada por ese id
*/
int searchByID(row_d* rows, int lenght, char* id);
#endif
