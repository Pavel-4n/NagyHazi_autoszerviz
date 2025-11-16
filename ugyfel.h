#ifndef UGYFEL_H
#define UGYFEL_H
#include "structs.h"

/**
 * ugyfeleket olvas be az ugyfelek.txt filebol es eltarolja a memoriaban
 * @param filename - fajl neve jelen esetben a ugyfelek.txt
 * @param db - ugyfelek szama
 * @return pointer az ugyfelek tombre
 */
Ugyfel* betoltUgyfelek(const char* filename, int *db);

/**
 * uj ugyfelet ad hozza az ugyfelek tombhoz
 * @param ugyfelek - ugyfelek tomb
 * @param db - ugyfelek szama
 * @param nev - uj ugyfel neve
 * @param email - uj ugyfel emailje
 * @param telSz - uj ugyfel telefonszama
 */
void ugyfelHozzaad(Ugyfel **ugyfelek, int *db, const char *nev, const char *email, const char *telSz);

/**
 * ugyfelet keres a neve szerint
 * @param ugyfelek - ugyfelek tomb
 * @param db - ugyfelek szama
 * @param nev - keresendo ugyfel neve
 * @return ugyfel indexe vagy -1 ha nem talalhato
 */
int ugyfelKeres(Ugyfel *ugyfelek, int db, const char *nev);

#endif
