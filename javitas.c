#include "debugmalloc.h"
#include <stdio.h>
#include <string.h>
#include "javitas.h"

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

void javitasHozzaad(Javitas **javitasok, int *db, const char *rendSz, const char *tipus, const char *datum, int ar){
  return;
}