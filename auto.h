#ifndef AUTO_H
#define AUTO_H
#include "structs.h"

/**
 * autokat olvas be az autok.txt filebol es eltarolja a memoriaban
 * @param filename - autok.txt 
 * @param db - az autok szama
 * @return autok tombre mutato pointer
 */
Auto* betoltAutok(const char* filename, int *db);

/**
 * uj autot ad hozza a tombjehez
 * @param autok - az autok tomje
 * @param db - az autok szama 
 * @param ujAuto - az uj auto adatai egy Auto strukturaban
 */
void autoHozzaad(Auto **autok, int *db, const Auto *ujAuto);

/**
 * autot keres egy felhasznalo altal megadott rendszam szerint
 * @param autok - az autok tomje
 * @param db - az autok szama 
 * @param rendSz - a keresendo auto rendszama
 * @return a keresett auto indexe vagy -1 ha nem volt sikeres a kereses
 */
int autoKeres(Auto *autok, int db, const char *rendSz);

/**
 * autot torol az autok tombjebol es az osszes hozza tartozo javitast is
 * @param autok - az autok tomje 
 * @param auto_db - az autok szama 
 * @param javitasok - a javitasok tomje
 * @param javitas_db - a javitasok szama
 * @param rendSz - a torlendo auto rendszama
 */
void autoTorles(Auto **autok, int *auto_db, Javitas **javitasok, int *javitas_db, const char *rendSz);

/**
 * megjeleniti egy auto szerviz tortenetet
 * @param autok - az autok tomje
 * @param auto_db - az autok szama
 * @param javitasok - a javitasok tomje
 * @param javitas_db - a javitasok szama
 * @param rendSz - a vizsgalt auto rendszama
 */
void autoSzervizTortenet(Auto *autok, int auto_db, Javitas *javitasok, int javitas_db, const char *rendSz);

/**
 * lejaro vizsgaju autokat listazza
 * @param autok - az autok tomje
 * @param auto_db - az autok szama
 */
void lejaroVizsgak(Auto *autok, int auto_db);

#endif