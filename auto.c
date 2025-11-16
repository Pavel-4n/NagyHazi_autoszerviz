#include <stdio.h>
#include <string.h>
#include "debugmalloc.h"
#include "auto.h"

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

void autoHozzaad(){
  return;
}

void autoKeres(){
  return;
}

void autoTorles(){
  return;
}

void autoSzervizTortenet(){
  
}

void lejaroVizsgak(){
  return;
}