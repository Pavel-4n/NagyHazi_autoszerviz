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
 * uj javitast ad hozza a tombjehez
 * @param javitasok - a javitasok tombje (pointer)
 * @param db - a javitasok szama (output)
 * @param ujJavitas - az uj javitas adatai egy Javitas strukturaban
 */
void javitasHozzaad(Javitas **javitasok, int *db, const Javitas *ujJavitas);


#endif
