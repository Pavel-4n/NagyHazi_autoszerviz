#ifndef UGYFEL_H
#define UGYFEL_H
#include "structs.h"

/**
 * ugyfeleket beolvas egy fajlbol es tarrol oket memoriaban
 * @param filename - a fajl neve
 * @param db - az ugyfelek szama (output)
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
 * @param ugyfelek - az ugyfelek tomje
 * @param db - az ugyfelek szama
 * @param nev - a keresendo ugyfel neve
 * @return az ugyfel indexe vagy -1 ha nem talalhato
 */
int ugyfelKeres(Ugyfel *ugyfelek, int db, const char *nev);

#endif
