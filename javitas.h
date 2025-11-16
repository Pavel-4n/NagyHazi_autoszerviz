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
 * uj javitest ad hozza a tombjehez
 * @param javitasok - a javitasok tomje (pointer)
 * @param db - a javitasok szama (output)
 * @param rendSz - az auto rendszama
 * @param tipus - a javitest tipusa
 * @param datum - a javitas datuma
 * @param ar - a javitas ara
 */
void javitasHozzaad(Javitas **javitasok, int *db, const char *rendSz, const char *tipus, const char *datum, int ar);

#endif
