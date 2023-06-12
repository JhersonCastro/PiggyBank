#ifndef CSV_H
#define CSV_H

#define MAX_ROWS 100

typedef struct {
    char id[50];
    char es[1024];
    char en[1024];
} row_t;
typedef struct {
    char id[50];
    char value[1024];
} row_d;
int readTrans_csv(row_t* rows);
row_t* find_row_by_id(row_t* rows, int row_count, const char* id);
const char* get_text(row_t* row, const char* lang);

void editByID(char* id_buscado, char* nuevo_valor);
int readData_csv(row_d* rows);
int searchByID(row_d* rows, int lenght, char* id);
#endif
