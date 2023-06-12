#include "csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const char* transFilename = "trans.csv";
const char* dataFilename = "data.csv";
#pragma region translations
int readTrans_csv(row_t* rows) {
    FILE* file;
    errno_t err = fopen_s(&file, transFilename, "r");
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
char* setLanguage() {
    char str[10];
    printf("Enter language (es/en): ");
    do
    {
        fgets(str, 10, stdin);

        char* start = str;
        while (isspace(*start)) {
            start++;
        }
        char* end = start + strlen(start) - 1;
        while (end >= start && isspace(*end)) {
            end--;
        }
        if (end - start == 1 && tolower(start[0]) == 'e' && tolower(start[1]) == 's') {
            printf("Idioma puesto al castellano\n");
            return "es";
        }
        else if (end - start == 1 && tolower(start[0]) == 'e' && tolower(start[1]) == 'n') {
            printf("Language set to English\n");
            return "en";
        }
        else {
            printf("Invalid language, please try again\n");
        }
    } while (1);
}
#pragma endregion
#pragma region data
int readData_csv(row_d* rows) {
    FILE* file;
    errno_t err = fopen_s(&file, dataFilename, "r");
    if (err != 0) {
        printf("Could not open file\n");
        return -1;
    }
    int row_count = 0;
    char line[1024];
    while (fgets(line, 1024, file)) {
        char* tmp = _strdup(line);
        sscanf_s(tmp, "%[^,],%[^\n]", rows[row_count].id, sizeof(rows[row_count].id), rows[row_count].value, sizeof(rows[row_count].value));
        row_count++;
        free(tmp);
    }
    fclose(file);
    return row_count;
}
int searchByID(row_d* rows, int lenght, char* id) {
    for (size_t i = 0; i < lenght ;i++)
    {
        if (strcmp(rows[i].id, id) == 0)
            return i;
    }
    return 0;
}
void editByID(char* id_buscado, char* nuevo_valor) {
    FILE* archivo;
    errno_t err = fopen_s(&archivo, dataFilename, "r");
    if (err != 0) {
        printf("No se pudo abrir el archivo\n");
        exit(1);
    }

    char temp[] = "temp.csv";
    FILE* temporal;
    errno_t err1 = fopen_s(&temporal, temp, "w");
    if (err1 != 0) {
        printf("No se pudo abrir el archivo temporal\n");
        exit(1);
    }

    char id[1024];
    char valor[1024];
    int encontrado = 0;
    while (fscanf_s(archivo, "%1023[^,],%1023[^\n]\n", id, sizeof(id), valor, sizeof(valor)) == 2) {
        if (strcmp(id, id_buscado) == 0) {
            fprintf(temporal, "%s,%s\n", id_buscado, nuevo_valor);
            encontrado = 1;
        }
        else {
            fprintf(temporal, "%s,%s\n", id, valor);
        }
    }

    fclose(archivo);
    fclose(temporal);

    if (encontrado) {
        remove(dataFilename);
        rename(temp, dataFilename);
    }
    else {
        return;
    }
}
#pragma endregion