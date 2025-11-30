#ifndef UGYFEL_H
#define UGYFEL_H
#include "structs.h"

/**
 * Lancolt listakent beolvassa az ugyfeleket az ugyfelek.txt fajlbol.
 * Minden sorbol egy Ugyfel listaelemet hoz letre, es a lista elejere fuz.
 *
 * @param filename - bemeneti fajl neve (ugyfelek.txt)
 * @return Ugyfel lista feje (pointer az elso Ugyfel elemre)
 */
Ugyfel* betoltUgyfelek(const char* filename);

/**
 * Felszabaditja az ugyfelek lancolt listajat.
 * Vegiglepked a lista elemein es mindegyiket felszabaditja.
 *
 * @param lista - az elso Ugyfel listaelem pointere (NULL, ha ures a lista)
 */
void felszabaditUgyfelek(Ugyfel *lista);

/**
 * Uj ugyfelet ad hozza a listahoz.
 *
 * @param ugyfelek - az ugyfelek listajanak feje
 * @param ujUgyfel - az uj ugyfel adatai egy Ugyfel strukturaban
 * @return A lista (esetlegesen uj) feje
 */
Ugyfel* ugyfelHozzaad(Ugyfel *ugyfelek, const Ugyfel *ujUgyfel);

/**
 * Ugyfelet keres a neve szerint a listaban.
 *
 * @param ugyfelek - az ugyfelek listaja
 * @param nev - keresendo ugyfel neve
 * @return Pointer a megtalalt ugyfelre, vagy NULL ha nem talalhato
 */
Ugyfel* ugyfelKeres(Ugyfel *ugyfelek, const char *nev);

/**
 * Elmenti az ugyfelek listajat a megadott fajlba CSV formatumban.
 * (nev;email;telefonszam)
 *
 * @param filename - a kimeneti fajl neve (pl. data/ugyfelek.txt)
 * @param lista - az ugyfelek listajanak feje
 */
void mentUgyfelek(const char *filename, Ugyfel *lista);

#endif
