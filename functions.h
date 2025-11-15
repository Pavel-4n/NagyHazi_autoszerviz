#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "structs.h"

// Beolvasás függvények
Ugyfel* betoltUgyfelek(const char* filename, int *db);
Auto* betoltAutok(const char* filename, int *db);
Javitas* betoltJavitasok(const char* filename, int *db);

// Nyomtatás függvények
void nyomtatUgyfeleket(Ugyfel *ugyfelek, int db);
void nyomtatAutokat(Auto *autok, int db);
void nyomtatJavitasokat(Javitas *javitasok, int db);

#endif
