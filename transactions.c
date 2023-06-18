#include <stdio.h>
#include <time.h>
#include "transactions.h"
void saveTransaction(char* label,int amount) {
    FILE* file;
    time_t current_time;
    struct tm time_info;
    char timeString[9];
    int err;
    time(&current_time);
    localtime_s(&time_info, &current_time);
    strftime(timeString, sizeof(timeString), "%H:%M:%S", &time_info);

    err = fopen_s(&file,"transactions.txt", "a");
    if (err != 0)
    {
        return;
    }

    fprintf(file, "%s: %s %d\n", timeString, label, amount);
    fclose(file);
}
void readAndPrintTransactions() {
    FILE* file;
    char line[256];
    int err;
    err = fopen_s(&file,"transactions.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}
void reset_transactions() {
    FILE* file;
    int err = fopen_s(&file, "transactions.txt", "w");
    if (err != 0) {
        return;
    }
    fclose(file);
}