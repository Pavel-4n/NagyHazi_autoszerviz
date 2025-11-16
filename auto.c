#include <stdio.h>
#include <string.h>
#include "debugmalloc.h"
#include "auto.h"

// Autók beolvasása a fájlból
Auto* betoltAutok(const char* filename, int *db) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("betoltAutok: fajl megnyitasa sikertelen");
        *db = 0;
        return NULL;
    }
    
    Auto *autok = (Auto*)malloc(100 * sizeof(Auto));
    if (autok == NULL) {
        fprintf(stderr, "betoltAutok: memoria foglalasa sikertelen\n");
        fclose(fp);
        return NULL;
    }
    
    *db = 0;
    char line[256];
    
    while (fgets(line, sizeof(line), fp) != NULL && *db < 100) {
        line[strcspn(line, "\n")] = 0;
        sscanf(line, "%15[^;];%63[^;];%15[^;];%63s",
               autok[*db].rendSz,
               autok[*db].model,
               autok[*db].vizsgaErv,
               autok[*db].tulajNev);
        (*db)++;
    }
    
    fclose(fp);
    return autok;
}

void autoHozzaad(Auto **autok, int *db, const char *rendSz, const char *model, const char *vizsgaErv, const char *tulajNev){
  return;
}

int autoKeres(Auto *autok, int db, const char *rendSz){
  return -1;
}

void autoTorles(Auto **autok, int *auto_db, Javitas **javitasok, int *javitas_db){
  return;
}

void autoSzervizTortenet(Auto *autok, int auto_db, Javitas *javitasok, int javitas_db){
  return;
}

void lejaroVizsgak(Auto *autok, int auto_db){
  return;
}