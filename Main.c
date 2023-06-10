#include "Menu.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "csv.h"
char* setLanguage();
int main(void) {
    piggyBank(setLanguage());
    return 0;
}
char* setLanguage() {
        char str[10];
        printf("Enter language (es/en): ");
        fgets(str, 10, stdin);

        char* start = str;
        while (isspace(*start)) {
            start++;
        }
        char* end = start + strlen(start) - 1;
        while (end >= start && isspace(*end)) {
            end--;
        }

        // Check if input is "es" or "en"
        if (end - start == 1 && tolower(start[0]) == 'e' && tolower(start[1]) == 's') {
            printf("Language set to Spanish\n");
            return "es";
        }
        else if (end - start == 1 && tolower(start[0]) == 'e' && tolower(start[1]) == 'n') {
            printf("Language set to English\n");
            return "en";
        }
        else {
            printf("Invalid language\n");
            return "es";
        }
}