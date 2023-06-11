#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 1024
#include "data.h"
const char* filename = "data.csv";
void editar_csv(char* id, char* nuevo_valor) {
    FILE* archivo = fopen(filename, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo %s\n", filename);
        exit(1);
    }

    char temp[] = "temp.csv";
    FILE* temporal = fopen(temp, "w");
    if (temporal == NULL) {
        printf("No se pudo crear el archivo temporal\n");
        exit(1);
    }

    char linea_id[1024];
    char linea_valor[1024];
    int encontrado = 0;
    while (fscanf(archivo, "%1023[^,],%1023[^\n]\n", linea_id, linea_valor) == 2) {
        if (strcmp(linea_id, id) == 0) {
            fprintf(temporal, "%s,%s\n", id, nuevo_valor);
            encontrado = 1;
        }
        else {
            fprintf(temporal, "%s,%s\n", linea_id, linea_valor);
        }
    }

    fclose(archivo);
    fclose(temporal);

    if (encontrado) {
        remove(filename);
        rename(temp, filename);
        printf("Valor actualizado con éxito.\n");
    }
    else {
        printf("No se encontró el ID especificado.\n");
    }
}
int read_data(const char* filename, row_d* rows) {
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
        sscanf_s(tmp, "%[^,],%[^\n]", rows[row_count].id, sizeof(rows[row_count].id), rows[row_count].value, sizeof(rows[row_count].value));
        row_count++;
        free(tmp);
    }
    fclose(file);
    return row_count;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* obtener_valor(char* id) {
    FILE* archivo = fopen(filename, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo %s\n", filename);
        exit(1);
    }

    char linea[1024];
    char* valor = NULL;
    while (fgets(linea, 1024, archivo)) {
        char* token = strtok(linea, ",");
        if (strcmp(token, id) == 0) {
            token = strtok(NULL, ",");
            valor = malloc(strlen(token) + 1);
            strcpy(valor, token);
            break;
        }
    }

    fclose(archivo);

    if (valor != NULL) {
        size_t len = strlen(valor);
        if (valor[len - 1] == '\n') {
            valor[--len] = '\0';
        }
        if (len > 0 && valor[len - 1] == '\r') {
            valor[--len] = '\0';
        }
    }

    return valor;
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