#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
    char nev[64];
    char email[64];
    char telSz[32];
} Ugyfel;

typedef struct {
    char rendSz[16];
    char model[64];
    char vizsgaErv[16];  
    char tulajNev[64];
} Auto;

typedef struct {
    char rendSz[16];
    char tipus[64];
    char datum[16];
    int ar;
} Javitas;

#endif
