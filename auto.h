#ifndef AUTO_H
#define AUTO_H
#include "structs.h"

Auto* betoltAutok(const char* filename, int *db);
void nyomtatAutokat(Auto *autok, int db);
void autoHozzaad(Auto **autok, int *db, const char *rendSz, const char *model, const char *vizsgaErv, const char *tulajNev);
int autoKeres(Auto *autok, int db, const char *rendSz);
void autoTorles(Auto **autok, int *auto_db, Javitas **javitasok, int *javitas_db);
void autoSzervizTortenet(Auto *autok, int auto_db, Javitas *javitasok, int javitas_db);
void lejaroVizsgak(Auto *autok, int auto_db);
#endif
