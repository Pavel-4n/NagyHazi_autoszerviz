#ifndef JAVITAS_H
#define JAVITAS_H
#include "structs.h"

/**
 * javitasokat beolvas egy fajlbol es tarrol oket memoriaban
 * @param filename - a fajl neve
 * @param db - a javitasok szama (output)
 * @return pointer a javitasok tombre
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
