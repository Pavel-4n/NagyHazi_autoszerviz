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

        line[strcspn(line, "\n")] = 0;  /* enter levagasa a sor vegerol */

        Auto *uj = (Auto*) malloc(sizeof(Auto));
        if (uj == NULL) {
            printf("memoria foglalasa sikertelen\n");
            fclose(fp);
            return lista;  /* ha van hiba, a mar beolvasott adatokat azert visszaadjuk */
        }
        
        sscanf(line, "%15[^;];%63[^;];%15[^;];%63[^\n]",
               uj->rendSz,
               uj->model,
               uj->vizsgaErv,
               uj->tulajNev); 
        uj->kov = lista;
        lista = uj;  /* befuzes a lista elejere */
    }
    fclose(fp);
    return lista;
}

void felszabaditAutok(Auto *lista) {
    Auto *iter = lista;
    while (iter != NULL) {
        Auto *kov = iter->kov;  /* mentjuk a kovetkezot, mielott a jelenlegit felszabaditjuk */
        free(iter);
        iter = kov;
    }
}

Auto* autoHozzaad(Auto *autok, const Auto *ujAuto) {
    Auto *uj = (Auto*) malloc(sizeof(Auto));
    if (uj == NULL) {
        printf("Memoria foglalasi hiba!\n");
        return autok;  /* hiba eseten az eredeti listaval terunk vissza, nem veezutjuk el az adatot */
    }
    
    strcpy(uj->rendSz, ujAuto->rendSz);
    strcpy(uj->model, ujAuto->model);
    strcpy(uj->vizsgaErv, ujAuto->vizsgaErv);
    strcpy(uj->tulajNev, ujAuto->tulajNev);
    
    uj->kov = autok;  /* az uj elem kerul a lista elejere */

    return uj; 
}

Auto* autoKeres(Auto *autok, const char *rendSz) {
    Auto *p = autok;
    while (p != NULL) {
        if (strcmp(p->rendSz, rendSz) == 0) {
            return p;  /* megtalaltuk az autot */
        }
        p = p->kov;
    }
    return NULL;  /* nem talat a rendszam */
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
        return 0;  /* nem talaltuk meg, nincs mit torolni */
    }

    if (prev == NULL)
        *autok = p->kov;  /* az elso elemet toroljuk, ezert a lista mostantol a masodiknal kezdodik */
    else
        prev->kov = p->kov;  /* atugorjuk a torlendo elemet, igy az kiesik */

    free(p);  /* memoria felszabaditasa */

    printf("Auto torolve: %s\n", rendSz);
    return 1;
}

void autoSzervizTortenet(Auto *autok, Javitas *javitasok, const char *rendSz) {
    Auto *talaltAuto = NULL;

    for (Auto *n = autok; n != NULL; n = n->kov) {
        if (strcmp(n->rendSz, rendSz) == 0) {
            talaltAuto = n;
            break;  /* megtalaltuk az autot, kilepunk a keresesbol */
        }
    }

    if (talaltAuto == NULL) {
        printf("Nincs ilyen rendszamu auto: %s\n", rendSz);
        return;  /* ha nem letezik az auto, nincs mit listazni */
    }

    printf("Szerviz tortenet: %s (%s)\n", talaltAuto->rendSz, talaltAuto->model);
    printf("-----------------------------------------\n");

    int volt = 0;

    for (Javitas *k = javitasok; k != NULL; k = k->kov) {
        if (strcmp(k->rendSz, rendSz) == 0) {
            printf("Datum: %s | Tipus: %s | Ar: %d Ft\n",
                    k->datum, k->tipus, k->ar);
            volt = 1;  /* rogzitjuk, hogy talaltunk legalabb egy bejegyzest */
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
        return;  /* ervenytelen bemeneti datum eseten kilepunk */
    }

    int talalt = 0;

    for (Auto *p = autok; p != NULL; p = p->kov) {
        int ev, ho, nap;
        if (sscanf(p->vizsgaErv, "%d-%d-%d", &ev, &ho, &nap) != 3)
            continue;  /* hibas adatbazis-bejegyzes eseten atugorjuk az autot */

        if (ev < maiEv ||
           (ev == maiEv && ho < maiHo) ||
           (ev == maiEv && ho == maiHo && nap < maiNap)) {  /* ha a vizsga datuma korabbi a mai napnal, akkor lejart */

            printf("%s | %s | %s | %s\n",
                   p->rendSz, p->model, p->vizsgaErv, p->tulajNev);
            talalt = 1;  /* rogzitjuk, hogy talaltunk legalabb egyet */
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
        return;  /* ha nem sikerult megnyitni, nem tudunk menteni, kilepunk */
    }

    for (Auto *p = lista; p != NULL; p = p->kov) {
        fprintf(fp, "%s;%s;%s;%s\n",
                p->rendSz, p->model, p->vizsgaErv, p->tulajNev);  /* pontosvesszovel elvalasztva irjuk ki az adatokat a konnyu beolvasasert */
    }

    fclose(fp);
}

