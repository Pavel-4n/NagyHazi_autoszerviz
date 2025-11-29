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

void felszabaditUgyfelek(Ugyfel *lista) {

    Ugyfel *iter = lista;
    while (iter != NULL) {
        Ugyfel *kov = iter->kov;
        free(iter);
        iter = kov;
    }
}




Ugyfel* ugyfelHozzaad(Ugyfel *ugyfelek, int *db, const Ugyfel *ujUgyfel) {
    Ugyfel *uj = malloc(sizeof(Ugyfel));
    if (uj == NULL) {
        printf("Memoria foglalasi hiba!\n");
        return ugyfelek;
    }

    strcpy(uj->nev, ujUgyfel->nev);
    strcpy(uj->email, ujUgyfel->email);
    strcpy(uj->telSz, ujUgyfel->telSz);

    uj->kov = ugyfelek;

    (*db)++;

    return uj;
}


Ugyfel* ugyfelKeres(Ugyfel *ugyfelek, const char *nev) {
    Ugyfel *p = ugyfelek;
    while (p != NULL) {
        if (strcmp(p->nev, nev) == 0) {
            return p;
        }
        p = p->kov;
    }
    return NULL;
}

void mentUgyfelek(const char *filename, Ugyfel *lista) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("Hiba: nem tudom megnyitni a %s fajlt!\n", filename);
        return;
    }

    for (Ugyfel *p = lista; p != NULL; p = p->kov) {
        fprintf(fp, "%s;%s;%s\n", p->nev, p->email, p->telSz);
    }

    fclose(fp);
}
