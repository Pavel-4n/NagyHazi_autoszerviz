#include <stdio.h>
#include <string.h>
#include "debugmalloc.h"
#include "auto.h"


Auto* betoltAutok(const char* filename, int *db) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("fajl megnyitasa sikertelen");
        *db = 0;
        return NULL;
    }
    
    Auto *autok = NULL;
    *db = 0;
    char line[256];
    
    while (fgets(line, sizeof(line), fp) != NULL) {
        Auto *temp = (Auto*)realloc(autok, (*db + 1) * sizeof(Auto));
        if (temp == NULL) {
            printf("memoria foglalasa sikertelen\n");
            free(autok);
            fclose(fp);
            return NULL;
        }
        autok = temp;
        
        line[strcspn(line, "\n")] = 0;
        sscanf(line, "%[^;];%[^;];%[^;];%s", autok[*db].rendSz, autok[*db].model, autok[*db].vizsgaErv, autok[*db].tulajNev);
        (*db)++;
    }
    fclose(fp);
    return autok;
}

void autoHozzaad(Auto **autok, int *db, const Auto *ujAuto){
  return;
}

int autoKeres(Auto *autok, int db, const char *rendSz){
    for (int i = 0; i < db; i++) {
        if (strcmp(autok[i].rendSz, rendSz) == 0) {
            return i;
        }
    }
    return -1;
}

void autoTorles(Auto **autok, int *auto_db, Javitas **javitasok, int *javitas_db, const char *rendSz){
  return;
}

void autoSzervizTortenet(Auto *autok, int auto_db, Javitas *javitasok, int javitas_db, const char *rendSz){
  return;
}

void lejaroVizsgak(Auto *autok, int auto_db){
  return;
}