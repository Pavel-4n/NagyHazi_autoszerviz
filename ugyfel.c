#include "debugmalloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"


int feldolgozUgyfelSort(const char *fajlSor, Ugyfel *egyUgyfel) {
    char masolat[256];
    strcpy(masolat, fajlSor);

    char *nev = strtok(masolat, ";");
    char *email = strtok(NULL, ";");
    char *telSz = strtok(NULL, ";");

    if (!nev || !email || !telSz)
        return 0;

    egyUgyfel->nev   = malloc(strlen(nev) + 1);
    egyUgyfel->email = malloc(strlen(email) + 1);
    egyUgyfel->telSz = malloc(strlen(telSz) + 1);

    if (!egyUgyfel->nev || !egyUgyfel->email || !egyUgyfel->telSz) {
        // ha barmelyik lefoglalas nem sikerul, ne hagyjunk szemetet
        if (egyUgyfel->nev)   free(egyUgyfel->nev);
        if (egyUgyfel->email) free(egyUgyfel->email);
        if (egyUgyfel->telSz) free(egyUgyfel->telSz);
        return 0;
    }

    strcpy(egyUgyfel->nev,   nev);
    strcpy(egyUgyfel->email, email);
    strcpy(egyUgyfel->telSz, telSz);

    return 1;
}

void felszabaditUgyfelek(Ugyfel *ugyfelek, int db) {
    if (!ugyfelek) return;

    for (int i = 0; i < db; i++) {
        free(ugyfelek[i].nev);
        free(ugyfelek[i].email);
        free(ugyfelek[i].telSz);
    }

    free(ugyfelek);
}

Ugyfel* betoltUgyfelek(const char* filename, int *db) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("fajl megnyitasa sikertelen");
        *db = 0;
        return NULL;
    }

    Ugyfel *ugyfelek = NULL;
    *db = 0;

    char sor[256];

    while (fgets(sor, sizeof(sor), fp) != NULL) {
        // uj sor jel eltavolitasa
        sor[strcspn(sor, "\n")] = 0;

        Ugyfel uj;
        if (!feldolgozUgyfelSort(sor, &uj)) {
            printf("Hibas sor az ugyfelek fileban, kihagyom: %s\n", sor);
            continue;
        }

        Ugyfel *ujTomb = realloc(ugyfelek, (*db + 1) * sizeof(Ugyfel));
        if (!ujTomb) {
            printf("memoria foglalasa sikertelen\n");

            // az eppen letrehozott uj ugyfel stringjeit elengedjuk
            free(uj.nev);
            free(uj.email);
            free(uj.telSz);

            // eddig betoltott ugyfelek felszabaditasa
            felszabaditUgyfelek(ugyfelek, *db);
            fclose(fp);
            *db = 0;
            return NULL;
        }

        ugyfelek = ujTomb;
        ugyfelek[*db] = uj;
        (*db)++;
    }

    fclose(fp);
    return ugyfelek;
}



void ugyfelHozzaad(Ugyfel **ugyfelek, int *db, const Ugyfel *ujUgyfel){
  return;
}

int ugyfelKeres(Ugyfel *ugyfelek, int db, const char *nev){
  return -1;
}