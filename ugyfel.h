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
 * uj ugyfelet ad hozza a tombhoz
 * @param ugyfelek - az ugyfelek tombje (pointer)
 * @param db - az ugyfelek szama
 * @param ujUgyfel - az uj ugyfel adatai egy Ugyfel strukturaban
 */
void ugyfelHozzaad(Ugyfel **ugyfelek, int *db, const Ugyfel *ujUgyfel);

/**
 * ugyfelet keres a neve szerint
 * @param ugyfelek - ugyfelek tomb
 * @param db - ugyfelek szama
 * @param nev - keresendo ugyfel neve
 * @return ugyfel indexe vagy -1 ha nem talalhato
 */
int ugyfelKeres(Ugyfel *ugyfelek, int db, const char *nev);

#endif
