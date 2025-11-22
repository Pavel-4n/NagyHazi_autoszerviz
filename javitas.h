#ifndef JAVITAS_H
#define JAVITAS_H
#include "structs.h"

/**
 * Lancolt listakent beolvassa a javitasokat a javitasok.txt fajlbol.
 * Minden sorbol egy Javitas listaelemet hoz letre, es a lista elejere fuz.
 *
 * @param filename - bemeneti fajl neve (javitasok.txt)
 * @param db - az olvasott javitasok szama
 * @return Javitas lista feje (pointer az elso Javitas elemre)
 */
Javitas* betoltJavitasok(const char* filename, int *db);

/**
 * Felszabaditja a javitasok lancolt listajat.
 * Vegiglepked a lista elemein es mindegyiket felszabaditja.
 *
 * @param lista - az elso Javitas listaelem pointere (NULL, ha ures a lista)
 */
void felszabaditJavitasok(Javitas *lista);

/**
 * uj javitast ad hozza a tombjehez
 * @param javitasok - a javitasok tombje (pointer)
 * @param db - a javitasok szama (output)
 * @param ujJavitas - az uj javitas adatai egy Javitas strukturaban
 */
void javitasHozzaad(Javitas **javitasok, int *db, const Javitas *ujJavitas);


#endif
