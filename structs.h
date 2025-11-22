#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Ugyfel {
    char nev[64];
    char email[64];
    char telSz[64];
    struct Ugyfel *kov;
} Ugyfel;

typedef struct Auto {
    char rendSz[16];
    char model[64];
    char vizsgaErv[16];  
    char tulajNev[64];
    struct Auto *kov;
} Auto;

typedef struct Javitas {
    char rendSz[16];
    char tipus[64];
    char datum[16];
    int ar;
    struct Javitas *kov;
} Javitas;


#endif