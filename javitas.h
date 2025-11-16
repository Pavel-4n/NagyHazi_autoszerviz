#ifndef JAVITAS_H
#define JAVITAS_H
#include "structs.h"

Javitas* betoltJavitasok(const char* filename, int *db);
void nyomtatJavitasokat(Javitas *javitasok, int db);
void javitasHozzaad(Javitas **javitasok, int *db, const char *rendSz, const char *tipus, const char *datum, int ar);

#endif
