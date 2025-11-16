#ifndef AUTO_H
#define AUTO_H
#include "structs.h"

/**
 * autokat olvas be az autok.txt filebol es eltarolja a memoriaban
 * @param filename - autok.txt 
 * @param db - autok szama
 * @return autok tombre mutato pointer
 */
Auto* betoltAutok(const char* filename, int *db);

/**
 * uj autot ad hozza a autok tombhoz
 * @param autok - autok tomb
 * @param db - autok szama 
 * @param rendSz - uj auto rendszama
 * @param model - uj auto modelje
 * @param vizsgaErv - uj auto vizsgaeervenyessege
 * @param tulajNev - uj auto tulajdonosanak neve
 */
void autoHozzaad(Auto **autok, int *db, const char *rendSz, const char *model, const char *vizsgaErv, const char *tulajNev);

/**
 * autot keres egy felhasznalo altal megadott rendszam szerint
 * @param autok - autok tomb
 * @param db - autok szama 
 * @param rendSz - keresendo auto rendszama
 * @return keresett auto indexe vagy -1 ha nem volt sikeres a kereses
 */
int autoKeres(Auto *autok, int db, const char *rendSz);

/**
 * autot torol az autok tombjebol es az osszes hozza tartozo javitasokat is
 * @param autok - autok tomb 
 * @param auto_db - autok szama 
 * @param javitasok - javitasok tomb
 * @param javitas_db - javitasok tomb
 */
void autoTorles(Auto **autok, int *auto_db, Javitas **javitasok, int *javitas_db);

/**
 * megjeleniti egy auto szerviz tortenetet
 * @param autok - autok tomb
 * @param auto_db - autok szama
 * @param javitasok -javitasok tomb
 * @param javitas_db - javitasok tomb
 */
void autoSzervizTortenet(Auto *autok, int auto_db, Javitas *javitasok, int javitas_db);

/**
 * lejaro vizsgaju autokat listaazza
 * @param autok - autok tomb
 * @param auto_db - autok szama
 */
void lejaroVizsgak(Auto *autok, int auto_db);
#endif
