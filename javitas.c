#include "debugmalloc.h"
#include <stdio.h>
#include <string.h>
#include "javitas.h"

Javitas* betoltJavitasok(const char* filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("fajl megnyitasa sikertelen");
        return NULL;
    }

    Javitas *lista = NULL;
    char line[256];

    while (fgets(line, sizeof(line), fp) != NULL) {
        line[strcspn(line, "\n")] = 0;  /* enter levagasa a sor vegerol */

        Javitas *uj = (Javitas*) malloc(sizeof(Javitas));
        if (uj == NULL) {
            printf("memoria foglalasa sikertelen\n");
            fclose(fp);
            return lista;  /* ha van hiba, a mar beolvasott adatokat azert visszaadjuk */
        }

        if (sscanf(line, "%15[^;];%63[^;];%15[^;];%d",
                   uj->rendSz,
                   uj->tipus,
                   uj->datum,
                   &uj->ar) != 4) {
            printf("hibas sor\n");
            free(uj);  /* hibas sor eseten felszabaditjuk a lefoglalt teruletet */
            continue;
        }

        uj->kov = lista;
        lista = uj;  /* befuzes a lista elejere */
    }

    fclose(fp);
    return lista;
}

void felszabaditJavitasok(Javitas *lista) {
    Javitas *iter = lista;
    while (iter != NULL) {
        Javitas *kov = iter->kov; /* mentjuk a kovetkezot, mielott a jelenlegit felszabaditjuk */
        free(iter);
        iter = kov;
    }
}

Javitas* javitasHozzaad(Javitas *javitasok, const Javitas *ujJavitas) {
    Javitas *uj = (Javitas*) (Javitas*) malloc(sizeof(Javitas));
    if (uj == NULL) {
        printf("Memoria foglalasi hiba!\n");
        return javitasok;  /* hiba eseten az eredeti listaval terunk vissza */
    }

    strcpy(uj->rendSz, ujJavitas->rendSz);
    strcpy(uj->tipus, ujJavitas->tipus);
    strcpy(uj->datum, ujJavitas->datum);
    uj->ar = ujJavitas->ar;

    uj->kov = javitasok;  /* az uj elem kerul a lista elejere */

    return uj;
}

void mentJavitasok(const char *filename, Javitas *lista) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("Hiba: nem tudom megnyitni a %s fajlt!\n", filename);
        return;  /* ha nem sikerult megnyitni, nem tudunk menteni, kilepunk */
    }

    for (Javitas *p = lista; p != NULL; p = p->kov) {
        fprintf(fp, "%s;%s;%s;%d\n",
                p->rendSz, p->tipus, p->datum, p->ar);  /* pontosvesszovel elvalasztva irjuk ki az adatokat */
    }

    fclose(fp);
}

void javitasTorlesRendszamSzerint(Javitas **javitasok, const char *rendSz){
    Javitas *p = *javitasok;
    Javitas *prev = NULL;
    int torolt_db = 0;

    while (p != NULL) {
        if (strcmp(p->rendSz, rendSz) == 0) {
            Javitas *torlendo = p;

            if (prev == NULL) {
                *javitasok = p->kov;  /* az elso elemet toroljuk, ezert a lista fejet modositjuk */
                p = *javitasok;
            } else {
                prev->kov = p->kov;  /* atugorjuk a torlendo elemet */
                p = p->kov; 
            }

            free(torlendo);  /* memoria felszabaditasa */
            torolt_db++;
        } else {
            prev = p;
            p = p->kov;  /* ha nem toroltunk, lephetunk a kovetkezore */
        }
    }

    if (torolt_db > 0) {
        printf("%d db javitas torolve a %s rendszamu autohoz.\n", torolt_db, rendSz);
    } else {
        printf("Nincs ehhez az autohoz javitas: %s\n", rendSz);
    }
}
