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

    Javitas *lista = NULL;
    *db = 0;
    char line[256];

    while (fgets(line, sizeof(line), fp) != NULL) {
        line[strcspn(line, "\n")] = 0;

        Javitas *uj = malloc(sizeof(Javitas));
        if (uj == NULL) {
            printf("memoria foglalasa sikertelen\n");
            fclose(fp);
            return lista;
        }

        if (sscanf(line, "%15[^;];%63[^;];%15[^;];%d",
                   uj->rendSz,
                   uj->tipus,
                   uj->datum,
                   &uj->ar) != 4) {
            printf("hibas sor a javitasok fajlban, kihagyom: %s\n", line);
            free(uj);
            continue;
        }

        uj->kov = lista;
        lista = uj;

        (*db)++;
    }

    fclose(fp);
    return lista;
}

void felszabaditJavitasok(Javitas *lista) {
    Javitas *iter = lista;
    while (iter != NULL) {
        Javitas *kov = iter->kov;
        free(iter);
        iter = kov;
    }
}

void javitasHozzaad(Javitas **javitasok, int *db, const Javitas *ujJavitas){
    Javitas *uj = malloc(sizeof(Javitas));
    if (uj == NULL){
        printf("Memoria foglalasi hiba!\n");
        return;
    }
    strcpy(uj->rendSz, ujJavitas->rendSz);
    strcpy(uj->tipus, ujJavitas->tipus);
    strcpy(uj->datum, ujJavitas->datum);
    uj->ar = ujJavitas->ar;
    uj->kov = *javitasok;
    *javitasok = uj;
    (*db)++;
}
