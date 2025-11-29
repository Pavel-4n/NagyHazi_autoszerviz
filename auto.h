#ifndef AUTO_H
#define AUTO_H
#include "structs.h"

/**
 * Lancolt listakent beolvassa az autokat az autok.txt fajlbol.
 * Minden sorbol egy Auto listaelemet hoz letre, es a lista elejere fuz.
 *
 * @param filename - bemeneti fajl neve (autok.txt)
 * @param db - az olvasott autok szama
 * @return Auto lista feje (pointer az elso Auto elemre)
 */
Auto* betoltAutok(const char* filename, int *db);

/**
 * Felszabaditja az autok lancolt listajat.
 * Vegiglepked a lista elemein es mindegyiket felszabaditja.
 *
 * @param lista - az elso Auto listaelem pointere (NULL, ha ures a lista)
 */
void felszabaditAutok(Auto *lista);

/**
 * uj autot ad hozza a tombjehez
 * @param autok - az autok tomje
 * @param db - az autok szama 
 * @param ujAuto - az uj auto adatai egy Auto strukturaban
 */
void autoHozzaad(Auto **autok, int *db, const Auto *ujAuto);

/**
 * autot keres egy felhasznalo altal megadott rendszam szerint
 * @param autok - autok tomb
 * @param db - autok szama 
 * @param rendSz - keresendo auto rendszama
 * @return keresett auto indexe vagy -1 ha nem volt sikeres a kereses
 */
int autoKeres(Auto *autok, int db, const char *rendSz);

/**
 * Torol egy autot a listabol a megadott rendszam alapjan.
 * Kezeli a lista ujralancolasat es a memoria felszabaditasat is.
 *
 * @param autok - az autok listajanak fejere mutato pointer cime (hogy a fej is modosithato legyen)
 * @param auto_db - az autok szama (csokken eggyel sikeres torles eseten)
 * @param rendSz - a torlendo auto rendszama
 * @return 1 ha sikeres volt a torles, 0 ha nem talalhato az auto
 */
int autoTorles(Auto **autok, int *auto_db, const char *rendSz);
/**
 * megjeleniti egy auto szerviz tortenetet
 * @param autok - az autok tomje
 * @param auto_db - az autok szama
 * @param javitasok - a javitasok tomje
 * @param javitas_db - a javitasok szama
 * @param rendSz - a vizsgalt auto rendszama
 */
void autoSzervizTortenet(Auto *autok, Javitas *javitasok, const char *rendSz);

/**
 * lejaro vizsgaju autokat listazza
 * @param autok - az autok tomje
 * @param auto_db - az autok szama
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