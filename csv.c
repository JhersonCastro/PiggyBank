#include "csv.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

const char* dataFilename = "data.csv";

int readData_csv(row_d* rows) {
    FILE* file; 
    int err = fopen_s(&file, dataFilename, "r");
    if (err != 0) {
        return 0;
    }
    char* tmp;
    int row_count = 0;
    char line[1024];
    while (fgets(line, 1024, file)) {
        tmp = _strdup(line);
        if (tmp == NULL) {
            printf("Error: not enough memory\n");
            fclose(file);
            return 0;
        }
        err = sscanf_s(tmp, "%[^,],%[^\n]", rows[row_count].id, (unsigned int)sizeof(rows[row_count].id), rows[row_count].value, (unsigned int)sizeof(rows[row_count].value)); 
        if (err != 2) {
            printf("Error");
        }
        row_count++;
        free(tmp);
    }
    fclose(file);
    return row_count;
}
int searchByID(row_d* rows, int lenght, char* id) {
    for (int i = 0; i < lenght; i++)
    {
        if (strcmp(rows[i].id, id) == 0)
            return i;
    }
    return 0;
}
void editByID(char* id_buscado, char* nuevo_valor) {
    FILE* archivo;
    if (fopen_s(&archivo, dataFilename, "r") != 0)
    {
        return;
    }
    char temp[] = "temp.csv";
    FILE* temporal;
    if (fopen_s(&temporal, temp, "w") != 0)
    {
        return;
    }
    char id[1024];
    char valor[1024];
    int encontrado = 0;

    while (fscanf_s(archivo, "%1023[^,],%1023[^\n]\n", id, (int)sizeof(id), valor, (int)sizeof(valor)) == 2) {
        id[1023] = '\0';
        if(strcmp(id, id_buscado) == 0) {
            fprintf(temporal, "%s,%s\n", id_buscado, nuevo_valor);
            encontrado = 1;
        }
        else 
            fprintf(temporal, "%s,%s\n", id, valor);
    }
    fclose(archivo);
    fclose(temporal);

    if (encontrado) {
        remove(dataFilename);
        if (rename(temp, dataFilename) != 0) {
            printf("Error renaming file\n");
        }
    }
}
