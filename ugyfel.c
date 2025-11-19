#include "debugmalloc.h"
#include <stdio.h>
#include <string.h>
#include "ugyfel.h"


Ugyfel* betoltUgyfelek(const char* filename, int *db) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("betoltUgyfelek: fajl megnyitasa sikertelen");
        *db = 0;
        return NULL;
    }
    
    Ugyfel *ugyfelek = (Ugyfel*)malloc(100 * sizeof(Ugyfel));
    if (ugyfelek == NULL) {
        fprintf(stderr, "betoltUgyfelek: memoria foglalasa sikertelen\n");
        fclose(fp);
        return NULL;
    }
    
    *db = 0;
    char line[256];
    
    while (fgets(line, sizeof(line), fp) != NULL && *db < 100) {
        line[strcspn(line, "\n")] = 0;
        sscanf(line, "%63[^;];%63[^;];%31s", 
               ugyfelek[*db].nev, 
               ugyfelek[*db].email, 
               ugyfelek[*db].telSz);
        (*db)++;
    }
    
    fclose(fp);
    return ugyfelek;
}

void ugyfelHozzaad(Ugyfel **ugyfelek, int *db, const Ugyfel *ujUgyfel){
  return;
}

int ugyfelKeres(Ugyfel *ugyfelek, int db, const char *nev){
  return -1;
}