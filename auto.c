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

    Auto *lista = NULL;
    *db = 0;
    char line[256];

    while (fgets(line, sizeof(line), fp) != NULL) {

        line[strcspn(line, "\n")] = 0;

    
        Auto *uj = malloc(sizeof(Auto));
        if (uj == NULL) {
            printf("memoria foglalasa sikertelen\n");
            fclose(fp);
            return lista;  
        }

        
        sscanf(line, "%15[^;];%63[^;];%15[^;];%63s",
               uj->rendSz,
               uj->model,
               uj->vizsgaErv,
               uj->tulajNev);

        
        uj->kov = lista;
        lista = uj;

        (*db)++;
    }

    fclose(fp);
    return lista;
}

void felszabaditAutok(Auto *lista) {
    Auto *p = lista;
    while (p != NULL) {
        Auto *kov = p->kov;
        free(p);
        p = kov;
    }
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