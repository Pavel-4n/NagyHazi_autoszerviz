#include "debugmalloc.h"
#include <stdio.h>
#include <string.h>
#include "ugyfel.h"


Ugyfel* betoltUgyfelek(const char* filename, int *db) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("fajl megnyitasa sikertelen");
        *db = 0;
        return NULL;
    }
    
    Ugyfel *ugyfelek = NULL;
    *db = 0;
    char line[256];
    
    while (fgets(line, sizeof(line), fp) != NULL) {
        Ugyfel *temp = (Ugyfel*)realloc(ugyfelek, (*db + 1) * sizeof(Ugyfel));
        if (temp == NULL) {
            printf("memoria foglalasa sikertelen\n");
            free(ugyfelek);
            fclose(fp);
            return NULL;
        }
        ugyfelek = temp;
        
        line[strcspn(line, "\n")] = 0;
        sscanf(line, "%[^;];%[^;];%s", ugyfelek[*db].nev, ugyfelek[*db].email, ugyfelek[*db].telSz);
        (*db)++;
    }
    fclose(fp);
    return ugyfelek;
}

void ugyfelHozzaad(Ugyfel **ugyfelek, int *db, const char *nev, const char *email, const char *telSz){
  return;
}

int ugyfelKeres(Ugyfel *ugyfelek, int db, const char *nev){
  return -1;
}