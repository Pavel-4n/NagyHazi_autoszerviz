#include "debugmalloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"


Ugyfel* betoltUgyfelek(const char* filename, int *db) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("fajl megnyitasa sikertelen");
        *db = 0;
        return NULL;
    }

    Ugyfel *lista = NULL;
    *db = 0;
    char line[256];

    while (fgets(line, sizeof(line), fp) != NULL) {
        line[strcspn(line, "\n")] = 0;

        Ugyfel *uj = malloc(sizeof(Ugyfel));
        if (uj == NULL) {
            printf("memoria foglalasa sikertelen\n");
            fclose(fp);
            return lista;
        }

        sscanf(line, "%63[^;];%63[^;];%63s",
               uj->nev,
               uj->email,
               uj->telSz);

        uj->kov = lista;
        lista = uj;

        (*db)++;
    }

    fclose(fp);
    return lista;
}

void felszabaditUgyfelek(Ugyfel *lista, int db) {
    (void)db; 

    Ugyfel *iter = lista;
    while (iter != NULL) {
        Ugyfel *kov = iter->kov;
        free(iter);
        iter = kov;
    }
}




void ugyfelHozzaad(Ugyfel **ugyfelek, int *db, const Ugyfel *ujUgyfel) {
    Ugyfel *uj = malloc(sizeof(Ugyfel));
    if (uj == NULL) {
        printf("Memoria foglalasi hiba!\n");
        return;
    }

    strcpy(uj->nev, ujUgyfel->nev);
    strcpy(uj->email, ujUgyfel->email);
    strcpy(uj->telSz, ujUgyfel->telSz);

    uj->kov = *ugyfelek;
    *ugyfelek = uj;

    (*db)++;
}


int ugyfelKeres(Ugyfel *ugyfelek, int db, const char *nev) {
    for (int i = 0; i < db; i++) {
        if (strcmp(ugyfelek[i].nev, nev) == 0) {
            return i;
        }
    }
    return -1;
}
