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
void mentJavitasok(const char *filename, Javitas *lista) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("Hiba: nem tudom megnyitni a %s fajlt!\n", filename);
        return;
    }

    for (Javitas *p = lista; p != NULL; p = p->kov) {
        fprintf(fp, "%s;%s;%s;%d\n",
                p->rendSz, p->tipus, p->datum, p->ar);
    }

    fclose(fp);
}

void javitasTorlesRendszamSzerint(Javitas **javitasok, int *javitas_db, const char *rendSz)
{
    Javitas *p = *javitasok;
    Javitas *prev = NULL;
    int torolt_db = 0;

    while (p != NULL) {
        if (strcmp(p->rendSz, rendSz) == 0) {
            Javitas *torlendo = p;

            if (prev == NULL) {
                *javitasok = p->kov;
                p = *javitasok;
            } else {
                prev->kov = p->kov;
                p = p->kov; 
            }

            free(torlendo);
            (*javitas_db)--;
            torolt_db++;
        } else {
            prev = p;
            p = p->kov;
        }
    }

    if (torolt_db > 0) {
        printf("%d db javitas torolve a %s rendszamu autohoz.\n", torolt_db, rendSz);
    } else {
        printf("Nincs ehhez az autohoz javitas: %s\n", rendSz);
    }
}
