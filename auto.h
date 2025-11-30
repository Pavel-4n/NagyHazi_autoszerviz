#ifndef AUTO_H
#define AUTO_H
#include "structs.h"

/**
 * Lancolt listakent beolvassa az autokat az autok.txt fajlbol.
 * Minden sorbol egy Auto listaelemet hoz letre, es a lista elejere fuz.
 *
 * @param filename - bemeneti fajl neve (autok.txt)
 * @return Auto lista feje (pointer az elso Auto elemre)
 */
Auto* betoltAutok(const char* filename);

/**
 * Vegiglepked a lista elemein es mindegyiket felszabaditja.
 *
 * @param lista - az elso Auto listaelem pointere (NULL, ha ures a lista)
 */
void felszabaditAutok(Auto *lista);

/**
 * Uj autot ad hozza a listahoz.
 *
 * @param autok - az autok listajanak feje
 * @param ujAuto - az uj auto adatai egy Auto strukturaban
 * @return A lista (esetlegesen uj) feje
 */
Auto* autoHozzaad(Auto *autok, const Auto *ujAuto);

/**
 * Autot keres egy felhasznalo altal megadott rendszam szerint a listaban.
 *
 * @param autok - autok listaja
 * @param rendSz - keresendo auto rendszama
 * @return Pointer a megtalalt autora, vagy NULL ha nem volt sikeres a kereses
 */
Auto* autoKeres(Auto *autok, const char *rendSz);

/**
 * Torol egy autot a listabol a megadott rendszam alapjan.
 * Kezeli a lista ujralancolasat es a memoria felszabaditasat is.
 *
 * @param autok - az autok listajanak fejere mutato pointer cime (hogy a fej is modosithato legyen)
 * @param rendSz - a torlendo auto rendszama
 * @return 1 ha sikeres volt a torles, 0 ha nem talalhato az auto
 */
int autoTorles(Auto **autok, const char *rendSz);

/**
 * Megjeleniti egy auto szerviz tortenetet.
 *
 * @param autok - az autok listaja
 * @param javitasok - a javitasok listaja
 * @param rendSz - a vizsgalt auto rendszama
 */
void autoSzervizTortenet(Auto *autok, Javitas *javitasok, const char *rendSz);

/**
 * Lejaro vizsgaju autokat listazza.
 *
 * @param autok - az autok listaja
 * @param maiDatum - a mai datum (YYYY-MM-DD formatumban)
 */
void lejaroVizsgak(Auto *autok, const char *maiDatum);

/**
 * Elmenti az autok listajat a megadott fajlba CSV formatumban.
 * (rendszam;model;vizsga_datum;tulaj_nev)
 *
 * @param filename - a kimeneti fajl neve (pl. data/autok.txt)
 * @param lista - az autok listajanak feje
 */
void mentAutok(const char *filename, Auto *lista);
#endif