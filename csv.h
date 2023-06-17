/*
* @file csv.h
* @version 1.3
* @date 16/06/2023
* @author no
* @title Liberia de analisis de datos
* @brief Funciones de Lectura y escritura sobre archivos .csv
*/
#ifndef CSV_H
#define CSV_H

#define MAX_ROWS 100
/*
* @brief Estructura para las definiciones de las traduccion, cada uno tiene su propio id, traducido al español, y traducido al ingles
*/
typedef struct {
    char id[50];
    char es[1024];
    char en[1024];
} row_t;
/*
* @brief Estructura para las definiciones de los, cada uno tiene su propio id, y su respectitivo valor
*/
typedef struct {
    char id[50];
    char value[1024];
} row_d;
/*
* @brief readTrans_csv Lee las traducciones y las copia (por asi decirlo, ya que su parametro es un puntero) a la variable creada por row_t
* @param rows un parametro puntero de tipo row_t
* @return retorna el numero total de filas encontradas
*/
int readTrans_csv(row_t* rows);
/*
* @brief find_row_by_id encuentra la fila por id
* @param rows un parametro puntero de tipo row_t
* @param row_count la cantidad total de filas
* @param id el id para encontrar
* @return retorna un row_t con su respectiva posicion
*/
row_t* find_row_by_id(row_t* rows, int row_count, const char* id);
/*
* @brief get_text obtiene el texto de una fila en especifico de las traducciones
* @param row un parametro puntero de tipo row_t que tiene almacenado las respectivas traducciones
* @param lang El idioma usado por el usuario
* @return retorna el texto de la fila en especifico del row_t con el lenguaje deseado por el usuario
*/
const char* get_text(row_t* row, const char* lang);
/*
* @brief setLanguage Le pide al usuario el idioma y lo aplica
* @return retorna el idioma puesto por el usuario
*/
char* setLanguage();
/*
* @brief editByID solo cambia su valor
* @param id_buscado el id de la fila en especifico para cambiar su valor
* @param nuevo_valor El valor que va a ser cambiado
*/
void editByID(char* id_buscado, char* nuevo_valor);
/*
* @brief readData_csv Lee los datos y las copia (por asi decirlo, ya que su parametro es un puntero) a la variable creada por row_d
* @param rows un parametro puntero de tipo row_d
* @return retorna el numero total de filas encontradas
*/
int readData_csv(row_d* rows);
/*
* @brief searchByID encuentra la fila por id
* @param rows un parametro puntero de tipo row_d
* @param lenght la cantidad total de filas
* @param id el id para encontrar
* @return retorna la posicion encontrada por ese id
*/
int searchByID(row_d* rows, int lenght, char* id);
#endif
