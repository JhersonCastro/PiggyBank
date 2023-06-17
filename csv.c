#include "csv.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

const char* dataFilename = "data.csv";

int readData_csv(row_d* rows) {
    FILE* file; 
    fopen_s(&file,dataFilename, "r");
    int err = 0;
    int row_count = 0;
    char line[1024];
    while (fgets(line, 1024, file)) {
        char* tmp = _strdup(line);
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
    fopen_s(&archivo,dataFilename, "r");

    char temp[] = "temp.csv";
    FILE* temporal;
    fopen_s(&temporal,temp, "w");

    char id[1024];
    char valor[1024];
    int encontrado = 0;

    while (fscanf_s(archivo, "%1023[^,],%1023[^\n]\n", id, (int)sizeof(id), valor, (int)sizeof(valor)) == 2) {
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
