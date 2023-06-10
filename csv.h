#ifndef CSV_H
#define CSV_H

#define MAX_ROWS 100

typedef struct {
    char id[50];
    char es[1024];
    char en[1024];
} row_t;

int read_csv(const char* filename, row_t* rows);
row_t* find_row_by_id(row_t* rows, int row_count, const char* id);
const char* get_text(row_t* row, const char* lang);
#endif
