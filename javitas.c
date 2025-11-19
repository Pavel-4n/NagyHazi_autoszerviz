#include "debugmalloc.h"
#include <stdio.h>
#include <string.h>
#include "javitas.h"

Javitas* betoltJavitasok(const char* filename, int *db) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("fajl megnyitasa sikertelen");
        *db = 0;
        return NULL;
    }
    
    Javitas *javitasok = NULL;
    *db = 0;
    char line[256];
    
    while (fgets(line, sizeof(line), fp) != NULL) {
        Javitas *temp = (Javitas*)realloc(javitasok, (*db + 1) * sizeof(Javitas));
        if (temp == NULL) {
            printf("memoria foglalasa sikertelen\n");
            free(javitasok);
            fclose(fp);
            return NULL;
        }
        javitasok = temp;
        
        line[strcspn(line, "\n")] = 0;
        int ar_temp;
        sscanf(line, "%[^;];%[^;];%[^;];%d", javitasok[*db].rendSz, javitasok[*db].tipus, javitasok[*db].datum, &ar_temp);
        javitasok[*db].ar = ar_temp;
        
        (*db)++;
    }
    fclose(fp);
    return javitasok;
}

void javitasHozzaad(Javitas **javitasok, int *db, const Javitas *ujJavitas){
  return;
}