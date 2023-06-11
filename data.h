#pragma once
#ifndef DATA_H
#define DATA_H



typedef struct {
    char id[50];
    char value[1024];
} row_d;

void editar_csv(char* id, char* nuevo_valor);

char* obtener_valor(char* id);
char* setLanguage();
int read_data(const char* filename, row_d* rows);
#endif
