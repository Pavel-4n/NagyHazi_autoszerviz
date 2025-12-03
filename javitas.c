#include "debugmalloc.h"
#include <stdio.h>
#include <string.h>
#include "javitas.h"

Javitas* betoltJavitasok(const char* filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("fajl megnyitasa sikertelen");
        return NULL;
    }

    Javitas *lista = NULL;
    char line[256];

    while (fgets(line, sizeof(line), fp) != NULL) { //egybenm ellenoriz hogy van e meg beolvasni valo es beolvassa az elso sort
        line[strcspn(line, "\n")] = 0;  /* enter levagasa a sor vegerol, kicsereli a new liten sor vegi karakterrre, igy elvalasztja a sorokat egymas kozott */

        Javitas *uj = (Javitas*) malloc(sizeof(Javitas));
        if (uj == NULL) {
            printf("memoria foglalasa sikertelen\n");
            fclose(fp);
            return lista;  /* ha van hiba, a mar beolvasott adatokat azert visszaadjuk */
        }

        if (sscanf(line, "%15[^;];%63[^;];%15[^;];%d", //addig olvass amig talalsz egy ; es ezt menti le a megfelelo mezobe
                   uj->rendSz,
                   uj->tipus,
                   uj->datum,
                   &uj->ar) != 4) { // sscanf char sort olvas be esszomol minden sikeres beolvasasnal, ha nem sikerul nem szamol igy ha nem 4 el egyenlo, valami hiba tortent.
            printf("hibas sor\n");
            free(uj);  /* hibas sor eseten felszabaditjuk a lefoglalt teruletet */
            continue;
        }

        uj->kov = lista;
        lista = uj;  /* uj kovetkezo pointeret raalitja a lista elso elemere majd az uj elemet beallitja az uj elso elemnek */
    }

    fclose(fp);
    return lista;
}

void felszabaditJavitasok(Javitas *lista) { 
    //nem menthetunk fel dinamikus memoria foglalast mert akkor elveeszitjuk azt az informacviot is hogy hol van a kovetkezo elem
    Javitas *iter = lista; //kezdjkuk az elso elemmel
    while (iter != NULL) { //amig nincs felszabaditva
        Javitas *kov = iter->kov; /* mentjuk a kovetkezot, mielott a jelenlegit felszabaditjuk */
        free(iter); //felszabaditjuk a kivalasztott elemet
        iter = kov; //lementjuk az informaciot hogy mi  akovetkezo elem, most az lesz a vizsgalando elem
    }
}

Javitas* javitasHozzaad(Javitas *javitasok, const Javitas *ujJavitas) { //regi lista es uj elem amit nem modositunk
    Javitas *uj = (Javitas*) malloc(sizeof(Javitas)); //uj elemnek memoriat foglalunk
    if (uj == NULL) {
        printf("Memoria foglalasi hiba!\n");
        return javitasok;  /* ha betelt a hely vagy hiba tortent akkor eredeti listat adjuk vissza */
    }

    strcpy(uj->rendSz, ujJavitas->rendSz); //adatok atmasolasa strukturaval
    strcpy(uj->tipus, ujJavitas->tipus);
    strcpy(uj->datum, ujJavitas->datum);
    uj->ar = ujJavitas->ar;

    uj->kov = javitasok;  /* uj elem kovetkezo pointer mutat a regi lista elso elemere, igy az lesz most az uj elso elem */

    return uj; //visszadjuk az uj listat
}

void mentJavitasok(const char *filename, Javitas *lista) {
    FILE *fp = fopen(filename, "w"); //W mert irni fogunk
    if (!fp) {
        printf("Hiba: nem tudom megnyitni a %s fajlt!\n", filename);
        return;  /* ha nem sikerult megnyitni, nem tudunk menteni, kilepunk */
    }

    for (Javitas *p = lista; p != NULL; p = p->kov) { // p pointert raalitjuk a lista elejere, amig p nem nulla(nincs a vegen), kovetkezo elemre lepunk
        fprintf(fp, "%s;%s;%s;%d\n", //file printf, kiirj a fijlba a megfelelo formatumban az adatokat
                p->rendSz, p->tipus, p->datum, p->ar);  /* pontosvesszovel elvalasztva irjuk ki az adatokat */
    }

    fclose(fp); //fajl bezarasa
}

void javitasTorlesRendszamSzerint(Javitas **javitasok, const char *rendSz){ //dupla pointer amivel a lista elso elemet lehet modositani, kezdopont modositasahoz
    Javitas *p = *javitasok; //pointer a lista elso elemere
    Javitas *prev = NULL; //pointer az elozo elemre
    int torolt_db = 0; 

    while (p != NULL) {  //amig vegig nem ertunk a listan
        if (strcmp(p->rendSz, rendSz) == 0) { //ha eggyeznek az adatok, ha nem eggyeznek akkor alltalaban barmilyen mas szamot ad vissza(abc szerint)
            Javitas *torlendo = p;

            if (prev == NULL) { // ha az elso elemet kell torolni 
                *javitasok = p->kov;  //akkor atrakjuk egy csillaggal van a lista tenyelges elso eleme tarolva
                p = *javitasok; //vizsgalt elem atallitodik az uj elso elemre
            } else {
                prev->kov = p->kov;  //az elozo elem kovetkezo pointeret atallitjuk a jelenlegi elem kovetkezojere, igy atugorjuk a torolendo elemet
                p = p->kov; //vizsgalt elem a kovetkezore ugrik
            }

            free(torlendo);  /* a torolendo elemeket felszabaditjuk, toroljuk */
            torolt_db++; //itt toroltunk, ezert noveljuk a szamlalot
        } else {
            prev = p; //ha nem eggyezik akkor az elozo elem most a jelenlegi elem lesz
            p = p->kov;  // lepunk a kovetkezo elemre
        }
    }

    if (torolt_db > 0) {
        printf("%d db javitas torolve a %s rendszamu autohoz.\n", torolt_db, rendSz);
    } else {
        printf("Nincs ehhez az autohoz javitas: %s\n", rendSz);
    }
}
