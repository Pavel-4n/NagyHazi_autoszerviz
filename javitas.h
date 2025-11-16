#ifndef JAVITAS_H
#define JAVITAS_H
#include "structs.h"

/**
 * javitasokat olvas be az javitasok.txt filebol es eltarolja a memoriaban
 * @param filename - fajl neve jelen esetben a javitasok.txt
 * @param db - avitasok szama 
 * @return pointerjavitasok tombre
 */
Javitas* betoltJavitasok(const char* filename, int *db);

/**
 * uj javitast ad hozza a javitasok tombhoz
 * @param javitasok - javitasok tomb
 * @param db - javitasok szama
 * @param rendSz - javitando auto rendszama
 * @param tipus - javitest tipusa
 * @param datum - javitas datuma
 * @param ar - javitas ara
 */
void javitasHozzaad(Javitas **javitasok, int *db, const char *rendSz, const char *tipus, const char *datum, int ar);

#endif
