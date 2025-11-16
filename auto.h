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
 * @param rendSz - az uj auto rendszama
 * @param model - az uj auto modelje
 * @param vizsgaErv - az uj auto vizsgaeervenyessege
 * @param tulajNev - az uj auto tulajdonosanak neve
 */
void autoHozzaad(Auto **autok, int *db, const char *rendSz, const char *model, const char *vizsgaErv, const char *tulajNev);

/**
 * autot keres egy felhasznalo altal megadott rendszam szerint
 * @param autok - az autok tomje
 * @param db - az autok szama 
 * @param rendSz - a keresendo auto rendszama
 * @return a keresett auto indexe vagy -1 ha nem volt sikeres a kereses
 */
int autoKeres(Auto *autok, int db, const char *rendSz);

/**
 * autot torol az autok tombjebol es az osszes hozza tartozo javitasokat is
 * @param autok - az autok tomje 
 * @param auto_db - az autok szama 
 * @param javitasok - a javitasok tomje
 * @param javitas_db - a javitasok szama
 */
void autoTorles(Auto **autok, int *auto_db, Javitas **javitasok, int *javitas_db);

/**
 * megjeleníti egy auto szerviz tortenetet
 * @param autok - az autok tomje
 * @param auto_db - az autok szama
 * @param javitasok - a javitasok tomje
 * @param javitas_db - a javitasok szama
 */
void autoSzervizTortenet(Auto *autok, int auto_db, Javitas *javitasok, int javitas_db);

/**
 * lejaro vizsgaju autokat listaazza
 * @param autok - az autok tomje
 * @param auto_db - az autok szama
 */
void lejaroVizsgak(Auto *autok, int auto_db);
#endif
