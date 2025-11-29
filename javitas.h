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
Javitas* betoltJavitasok(const char* filename);

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
Javitas* javitasHozzaad(Javitas *javitasok, const Javitas *ujJavitas);
/**
 * elmenti a javitasok listajat a megadott fajlba CSV formatumban.
 * (rendszam;tipus;datum;ar)
 *
 * @param filename - a kimeneti fajl neve (pl. data/javitasok.txt)
 * @param lista - a javitasok listajanak feje
 */
void mentJavitasok(const char *filename, Javitas *lista);/**
 * torli az osszes javitasi bejegyzest a listabol a megadott rendszam alapjan.
 * Vegigmegy a teljes listan, es minden egyezo rendszamu elemet eltavolit
 * es felszabadit, frissitve a lista szerkezetet.
 *
 * @param javitasok - a javitasok listajanak fejere mutato pointer cime (modosithato a fej)
 * @param db - a javitasok szama (csokken a torolt elemek szamaval)
 * @param rendSz - a torlendo javitasokhoz tartozo auto rendszama
 */
void javitasTorlesRendszamSzerint(Javitas **javitasok, const char *rendSz);
#endif
