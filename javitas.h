#ifndef JAVITAS_H
#define JAVITAS_H
#include "structs.h"

Javitas* betoltJavitasok(const char* filename);

void felszabaditJavitasok(Javitas *lista);

Javitas* javitasHozzaad(Javitas *javitasok, const Javitas *ujJavitas);

void mentJavitasok(const char *filename, Javitas *lista);

void javitasTorlesRendszamSzerint(Javitas **javitasok, const char *rendSz);
#endif
