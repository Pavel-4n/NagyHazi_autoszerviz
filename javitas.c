#include "debugmalloc.h"
#include <stdio.h>
#include <string.h>
#include "javitas.h"

// Javítások beolvasása a fájlból
Javitas* betoltJavitasok(const char* filename, int *db) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("betoltJavitasok: fajl megnyitasa sikertelen");
        *db = 0;
        return NULL;
    }
    
    Javitas *javitasok = (Javitas*)malloc(100 * sizeof(Javitas));
    if (javitasok == NULL) {
        fprintf(stderr, "betoltJavitasok: memoria foglalasa sikertelen\n");
        fclose(fp);
        return NULL;
    }
    
    *db = 0;
    char line[256];
    
    while (fgets(line, sizeof(line), fp) != NULL && *db < 100) {
        line[strcspn(line, "\n")] = 0;
        sscanf(line, "%15[^;];%63[^;];%15[^;];%d",
               javitasok[*db].rendSz,
               javitasok[*db].tipus,
               javitasok[*db].datum,
               &javitasok[*db].ar);
        (*db)++;
    }
    
    fclose(fp);
    return javitasok;
}

void javitasHozzaad(Javitas **javitasok, int *db, const char *rendSz, const char *tipus, const char *datum, int ar){
  return;
}