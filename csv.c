#include "csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_csv(const char* filename, row_t* rows) {
    FILE* file;
    errno_t err = fopen_s(&file, filename, "r");
    if (err != 0) {
        printf("Could not open file\n");
        return -1;
    }
    int row_count = 0;
    char line[1024];
    while (fgets(line, 1024, file)) {
        char* tmp = _strdup(line);
        sscanf_s(tmp, "%[^,],%[^,],%[^\n]", rows[row_count].id, sizeof(rows[row_count].id), rows[row_count].es, sizeof(rows[row_count].es), rows[row_count].en, sizeof(rows[row_count].en));
        row_count++;
        free(tmp);
    }
    fclose(file);
    return row_count;
}
row_t* find_row_by_id(row_t* rows, int row_count, const char* id) {
    for (int i = 0; i < row_count; i++) {
        if (strcmp(rows[i].id, id) == 0) {
            return &rows[i];
        }
    }
    return NULL;
}
const char* get_text(row_t* row, const char* lang) {
    if (strcmp(lang, "es") == 0) {
        return row->es;
    }
    else if (strcmp(lang, "en") == 0) {
        return row->en;
    }
    else {
        return NULL;
    }
}