#ifndef UGYFEL_H
#define UGYFEL_H
#include "structs.h"

Ugyfel* betoltUgyfelek(const char* filename, int *db);
void nyomtatUgyfeleket(Ugyfel *ugyfelek, int db);
void ugyfelHozzaad(Ugyfel **ugyfelek, int *db, const char *nev, const char *email, const char *telSz);
int ugyfelKeres(Ugyfel *ugyfelek, int db, const char *nev);

#endif
