#ifndef AUTO_H
#define AUTO_H
#include "structs.h"

Auto* betoltAutok(const char* filename);

void felszabaditAutok(Auto *lista);

Auto* autoHozzaad(Auto *autok, const Auto *ujAuto);

Auto* autoKeres(Auto *autok, const char *rendSz);

int autoTorles(Auto **autok, const char *rendSz);

void autoSzervizTortenet(Auto *autok, Javitas *javitasok, const char *rendSz);

void lejaroVizsgak(Auto *autok, const char *maiDatum);

void mentAutok(const char *filename, Auto *lista);
#endif