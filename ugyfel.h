#ifndef UGYFEL_H
#define UGYFEL_H
#include "structs.h"

/**
 * egy sort dolgoz fel az ugyfelek fajlbol es feltolt egy Ugyfel strukturat
 * @param fajlSor - a fajlbol beolvasott sor (nev;email;telefonszam)
 * @param egyUgyfel - a kitoltendo Ugyfel struktura cime
 * @return 1 ha sikeres volt a feldolgozas, 0 ha hiba tortent
 */
int feldolgozUgyfelSort(const char *fajlSor, Ugyfel *egyUgyfel);

/**
 * ugyfeleket olvas be az ugyfelek.txt filebol es eltarolja a memoriaban
 * @param filename - fajl neve jelen esetben a ugyfelek.txt
 * @param db - ugyfelek szama
 * @return pointer az ugyfelek tombre
 */
Ugyfel* betoltUgyfelek(const char* filename, int *db);

/**
 * ugyfelek dinamikusan foglalt adatait szabaditja fel
 * @param ugyfelek - az ugyfelek tombje
 * @param db - az ugyfelek szama
 */
void felszabaditUgyfelek(Ugyfel *ugyfelek, int db);

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
