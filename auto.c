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
    Auto *iter = lista;
    while (iter != NULL) {
        Auto *kov = iter->kov;
        free(iter);
        iter = kov;
    }
}


void autoHozzaad(Auto **autok, int *db, const Auto *ujAuto){
    Auto *uj = malloc(sizeof(Auto));
    if (uj == NULL){
        printf("Memoria foglalasi hiba!\n");
        return;
    }
    strcpy(uj->rendSz, ujAuto->rendSz);
    strcpy(uj->model, ujAuto->model);
    strcpy(uj->vizsgaErv, ujAuto->vizsgaErv);
    strcpy(uj->tulajNev, ujAuto->tulajNev);
    uj->kov = *autok;
    *autok = uj;
    (*db)++;
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
    //autok torlese majd kerdes hogy akarja e a felhasznalo torolni a hozza tartozo javitasokat is.
  return;
}

void autoSzervizTortenet(Auto *autok, Javitas *javitasok, const char *rendSz) {
    Auto *talaltAuto = NULL;

    for (Auto *n = autok; n != NULL; n = n->kov) {
        if (strcmp(n->rendSz, rendSz) == 0) {
            talaltAuto = n;
            break;
        }
    }

    if (talaltAuto == NULL) {
        printf("Nincs ilyen rendszamu auto: %s\n", rendSz);
        return;
    }

    printf("Szerviz tortenet: %s (%s)\n", talaltAuto->rendSz, talaltAuto->model);
    printf("-----------------------------------------\n");

    int volt = 0;

    for (Javitas *k = javitasok; k != NULL; k = k->kov) {
        if (strcmp(k->rendSz, rendSz) == 0) {
            printf("Datum: %s | Tipus: %s | Ar: %d Ft\n",
                    k->datum, k->tipus, k->ar);
            volt = 1;
        }
    }

    if (!volt) {
        printf("Ehhez az autohoz meg nincs regisztralt javitas.\n");
    }
}


void lejaroVizsgak(Auto *autok, const char *maiDatum) {
    int maiEv, maiHo, maiNap;
    if (sscanf(maiDatum, "%d-%d-%d", &maiEv, &maiHo, &maiNap) != 3) {
        printf("Hibas datum formatum! (YYYY-MM-DD kell)\n");
        return;
    }

    int talalt = 0;

    for (Auto *p = autok; p != NULL; p = p->kov) {
        int ev, ho, nap;
        if (sscanf(p->vizsgaErv, "%d-%d-%d", &ev, &ho, &nap) != 3)
            continue;

        if (ev < maiEv ||
           (ev == maiEv && ho < maiHo) ||
           (ev == maiEv && ho == maiHo && nap < maiNap)) {

            printf("%s | %s | %s | %s\n",
                   p->rendSz, p->model, p->vizsgaErv, p->tulajNev);
            talalt = 1;
        }
    }

    if (!talalt)
        printf("Minden autonak ervenyes a muszaki vizsgaja.\n");
}

void mentAutok(const char *filename, Auto *lista) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("Hiba: nem tudom megnyitni a %s fajlt!\n", filename);
        return;
    }

    for (Auto *p = lista; p != NULL; p = p->kov) {
        fprintf(fp, "%s;%s;%s;%s\n",
                p->rendSz, p->model, p->vizsgaErv, p->tulajNev);
    }

    fclose(fp);
}

