#include <stdio.h>
#include <string.h>
#include "debugmalloc.h"
#include "auto.h"

Auto* betoltAutok(const char* filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("fajl megnyitasa sikertelen");
        return NULL;
    }

    Auto *lista = NULL;
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

Auto* autoHozzaad(Auto *autok, const Auto *ujAuto) {
    Auto *uj = malloc(sizeof(Auto));
    if (uj == NULL) {
        printf("Memoria foglalasi hiba!\n");
        return autok;
    }
    
    strcpy(uj->rendSz, ujAuto->rendSz);
    strcpy(uj->model, ujAuto->model);
    strcpy(uj->vizsgaErv, ujAuto->vizsgaErv);
    strcpy(uj->tulajNev, ujAuto->tulajNev);
    
    uj->kov = autok;

    return uj; 
}

Auto* autoKeres(Auto *autok, const char *rendSz) {
    Auto *p = autok;
    while (p != NULL) {
        if (strcmp(p->rendSz, rendSz) == 0) {
            return p;
        }
        p = p->kov;
    }
    return NULL;
}

int autoTorles(Auto **autok, const char *rendSz) {
    Auto *p = *autok;
    Auto *prev = NULL;

    while (p != NULL && strcmp(p->rendSz, rendSz) != 0) {
        prev = p;
        p = p->kov;
    }

    if (p == NULL) {
        printf("Nincs ilyen rendszamu auto: %s\n", rendSz);
        return 0;
    }

    if (prev == NULL)
        *autok = p->kov;
    else
        prev->kov = p->kov;

    free(p);

    printf("Auto torolve: %s\n", rendSz);
    return 1;
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
    if (!talalt){
        printf("Minden autonak ervenyes a muszaki vizsgaja.\n");
    }
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

