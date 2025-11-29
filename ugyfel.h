#ifndef UGYFEL_H
#define UGYFEL_H
#include "structs.h"

/**
 * Lancolt listakent beolvassa az ugyfeleket az ugyfelek.txt fajlbol.
 * Minden sorbol egy Ugyfel listaelemet hoz letre, es a lista elejere fuz.
 *
 * @param filename - bemeneti fajl neve (ugyfelek.txt)
 * @param db - az olvasott ugyfelek szama
 * @return Ugyfel lista feje (pointer az elso Ugyfel elemre)
 */
Ugyfel* betoltUgyfelek(const char* filename, int *db);

/**
 * Felszabaditja az ugyfelek lancolt listajat.
 * Vegiglepked a lista elemein es mindegyiket felszabaditja.
 *
 * @param lista - az elso Ugyfel listaelem pointere (NULL, ha ures a lista)
 */
void felszabaditUgyfelek(Ugyfel *lista);

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

/**
 * Elmenti az ugyfelek listajat a megadott fajlba CSV formatumban.
 * (nev;email;telefonszam)
 *
 * @param filename - a kimeneti fajl neve (pl. data/ugyfelek.txt)
 * @param lista - az ugyfelek listajanak feje
 */
void mentUgyfelek(const char *filename, Ugyfel *lista);
#endif
