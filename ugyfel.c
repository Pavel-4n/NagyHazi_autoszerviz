#include "debugmalloc.h"
#include <stdio.h>
#include <string.h>
#include "ugyfel.h"

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

void ugyfelHozzaad(){
  return;
}

void ugyfelKeres(){
  return;
}