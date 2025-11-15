#include "debugmalloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

// Ügyfelek beolvasása a fájlból
Ugyfel* betoltUgyfelek(const char* filename, int *db) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Hiba: Nem lehet megnyitni az %s fajlt!\n", filename);
        *db = 0;
        return NULL;
    }
    
    Ugyfel *ugyfelek = (Ugyfel*)malloc(100 * sizeof(Ugyfel));
    if (!ugyfelek) {
        printf("Hiba: Nincs eleg memoria!\n");
        fclose(f);
        return NULL;
    }
    
    *db = 0;
    char line[256];
    
    while (fgets(line, sizeof(line), f) && *db < 100) {
        line[strcspn(line, "\n")] = 0;  // newline eltávolítása
        sscanf(line, "%63[^;];%63[^;];%31s", 
               ugyfelek[*db].nev, 
               ugyfelek[*db].email, 
               ugyfelek[*db].telSz);
        (*db)++;
    }
    
    fclose(f);
    return ugyfelek;
}

// Autók beolvasása a fájlból
Auto* betoltAutok(const char* filename, int *db) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Hiba: Nem lehet megnyitni az %s fajlt!\n", filename);
        *db = 0;
        return NULL;
    }
    
    Auto *autok = (Auto*)malloc(100 * sizeof(Auto));
    if (!autok) {
        printf("Hiba: Nincs eleg memoria!\n");
        fclose(f);
        return NULL;
    }
    
    *db = 0;
    char line[256];
    
    while (fgets(line, sizeof(line), f) && *db < 100) {
        line[strcspn(line, "\n")] = 0;
        sscanf(line, "%15[^;];%63[^;];%15[^;];%63s",
               autok[*db].rendSz,
               autok[*db].model,
               autok[*db].vizsgaErv,
               autok[*db].tulajNev);
        (*db)++;
    }
    
    fclose(f);
    return autok;
}

// Javítások beolvasása a fájlból
Javitas* betoltJavitasok(const char* filename, int *db) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Hiba: Nem lehet megnyitni az %s fajlt!\n", filename);
        *db = 0;
        return NULL;
    }
    
    Javitas *javitasok = (Javitas*)malloc(100 * sizeof(Javitas));
    if (!javitasok) {
        printf("Hiba: Nincs eleg memoria!\n");
        fclose(f);
        return NULL;
    }
    
    *db = 0;
    char line[256];
    
    while (fgets(line, sizeof(line), f) && *db < 100) {
        line[strcspn(line, "\n")] = 0;
        sscanf(line, "%15[^;];%63[^;];%15[^;];%d",
               javitasok[*db].rendSz,
               javitasok[*db].tipus,
               javitasok[*db].datum,
               &javitasok[*db].ar);
        (*db)++;
    }
    
    fclose(f);
    return javitasok;
}

// Ügyfelek nyomtatása
void nyomtatUgyfeleket(Ugyfel *ugyfelek, int db) {
    if (!ugyfelek || db == 0) {
        printf("Nincsenek ugyfelek!\n");
        return;
    }
    printf("\n========== UGYFELEK ==========\n");
    for (int i = 0; i < db; i++) {
        printf("%d. %s | %s | %s\n", i+1, ugyfelek[i].nev, ugyfelek[i].email, ugyfelek[i].telSz);
    }
    printf("==============================\n\n");
}

// Autók nyomtatása
void nyomtatAutokat(Auto *autok, int db) {
    if (!autok || db == 0) {
        printf("Nincsenek autok!\n");
        return;
    }
    printf("\n========== AUTOK ==========\n");
    for (int i = 0; i < db; i++) {
        printf("%d. %s | %s | Vizsgaerv: %s | Tulajdonos: %s\n", 
               i+1, autok[i].rendSz, autok[i].model, autok[i].vizsgaErv, autok[i].tulajNev);
    }
    printf("===========================\n\n");
}

// Javítások nyomtatása
void nyomtatJavitasokat(Javitas *javitasok, int db) {
    if (!javitasok || db == 0) {
        printf("Nincsenek javitasok!\n");
        return;
    }
    printf("\n========== JAVITASOK ==========\n");
    for (int i = 0; i < db; i++) {
        printf("%d. %s | %s | Datum: %s | Ar: %d Ft\n", 
               i+1, javitasok[i].rendSz, javitasok[i].tipus, javitasok[i].datum, javitasok[i].ar);
    }
    printf("================================\n\n");
}