#ifndef UGYFEL_H
#define UGYFEL_H
#include "structs.h"

Ugyfel* betoltUgyfelek(const char* filename);

void felszabaditUgyfelek(Ugyfel *lista);

Ugyfel* ugyfelHozzaad(Ugyfel *ugyfelek, const Ugyfel *ujUgyfel);

Ugyfel* ugyfelKeres(Ugyfel *ugyfelek, const char *nev);

void mentUgyfelek(const char *filename, Ugyfel *lista);

#endif
