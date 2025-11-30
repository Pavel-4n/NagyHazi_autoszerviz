#include "debugmalloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"


Ugyfel* betoltUgyfelek(const char* filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("fajl megnyitasa sikertelen");
        return NULL;
    }

    Ugyfel *lista = NULL;
    char line[256];

    while (fgets(line, sizeof(line), fp) != NULL) {
        line[strcspn(line, "\n")] = 0;  /* enter levagasa a sor vegerol */

        Ugyfel *uj = (Ugyfel*) malloc(sizeof(Ugyfel));
        if (uj == NULL) {
            printf("memoria foglalasa sikertelen\n");
            fclose(fp);
            return lista;  /* ha van hiba, a mar beolvasott adatokat azert visszaadjuk */
        }

        sscanf(line, "%63[^;];%63[^;];%63s",
               uj->nev,
               uj->email,
               uj->telSz);

        uj->kov = lista;
        lista = uj;  /* befuzes a lista elejere */
    }

    fclose(fp);
    return lista;
}

void felszabaditUgyfelek(Ugyfel *lista) {

    Ugyfel *iter = lista;
    while (iter != NULL) {
        Ugyfel *kov = iter->kov;  /* menjtuk a kovetkezot, mielott a jelenlegit felszabaditjuk */
        free(iter);
        iter = kov;
    }
}


Ugyfel* ugyfelHozzaad(Ugyfel *ugyfelek, const Ugyfel *ujUgyfel) {
    Ugyfel *uj = (Ugyfel*) malloc(sizeof(Ugyfel));
    if (uj == NULL) {
        printf("Memoria foglalasi hiba!\n");
        return ugyfelek;  /* hiba eseten az eredeti listaval terunk vissza */
    }

    strcpy(uj->nev, ujUgyfel->nev);
    strcpy(uj->email, ujUgyfel->email);
    strcpy(uj->telSz, ujUgyfel->telSz);

    uj->kov = ugyfelek;  /* az uj elem kerul a lista elejere */

    return uj;
}


Ugyfel* ugyfelKeres(Ugyfel *ugyfelek, const char *nev) {
    Ugyfel *p = ugyfelek;
    while (p != NULL) {
        if (strcmp(p->nev, nev) == 0) {
            return p;  /* megtalaltuk az ugyfelet */
        }
        p = p->kov;
    }
    return NULL;  /* nem szerepel ilyen nev a listaban */
}

void mentUgyfelek(const char *filename, Ugyfel *lista) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("Hiba: nem tudom megnyitni a %s fajlt!\n", filename);
        return;  /* ha nem sikerult megnyitni, nem tudunk menteni, kilepunk */
    }

    for (Ugyfel *p = lista; p != NULL; p = p->kov) {
        fprintf(fp, "%s;%s;%s\n", p->nev, p->email, p->telSz);  /* pontosvesszovel elvalasztva irjuk ki az adatokat */
    }

    fclose(fp);
}