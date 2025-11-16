#include "auto.h"
#include "debugmalloc.h"
#include "functions.h"
#include "javitas.h"
#include "structs.h"
#include "ugyfel.h"
#include <stdio.h>

int main() {
	// Adatok beolvasása
	int ugyfel_db = 0, auto_db = 0, javitas_db = 0;
	
	Ugyfel *ugyfelek = betoltUgyfelek("data/ugyfelek.txt", &ugyfel_db);
	Auto *autok = betoltAutok("data/autok.txt", &auto_db);
	Javitas *javitasok = betoltJavitasok("data/javitasok.txt", &javitas_db);

	int userInput = 0;
	printf("                 _                               _     \n");
	printf("     /\\        | |                             (_)    \n");
	printf("    /  \\  _   _| |_ ___  ___ _______ _ ____   ___ ____\n");
	printf("   / /\\ \\| | | | __/ _ \\/ __|_  / _ \\ '__\\ \\ / / |_  /\n");
	printf("  / ____ \\ |_| | || (_) \\__ \\/ /  __/ |   \\ V /| |/ / \n");
	printf(" /_/    \\_\\__,_|\\__\\___/|___/___\\___|_|    \\_/ |_/___| \n");
	printf("1. Ugyfel hozzadasa\n");
	printf("2. Auto hozzaadasa\n");
	printf("3. Javitas hozzaadasa\n");
	printf("4. Kereses ugyfel neve szerint\n");
	printf("5. Kereses auto rendszam szerint\n");
	printf("6. Auto torlese\n");
	printf("7. Auto szerviz tortenet\n");
	printf("8. Lejaro vizsgaju autok listazasa\n");
	printf("9. Kilepes\n");
	printf("Valassz egy menupontot: \n");
	scanf("%d" , &userInput);	
	
	switch(userInput) {
		case 1: //Ugyfel hozzadasa
			char nev[100];
			char email[100];
			char telSz[50];
		
			printf("ugyfel neve: ");
			scanf(" %99[^\n]", nev);

			printf("ugyfel email-cime: ");
			scanf(" %99s", email);

			printf("ugyfel telefonszama: ");
			scanf(" %49s", telSz);

			ugyfelHozzaad(&ugyfelek, &ugyfel_db, nev, email, telSz);
			break;
		case 2: { //Auto hozzaadasa
			char rendSz[100];
			char model[100];
			char vizsgaErv[50];
			char tulajNev[100];

			printf("auto rendszama: ");
			scanf(" %99[^\n]", rendSz);

			printf("auto modelje: ");
			scanf(" %99[^\n]", model);

			printf("auto vizsga ervenyessegenek datuma: ");
			scanf(" %49s", vizsgaErv);

			printf("auto tulajdonosanak neve: ");
			scanf(" %99s", tulajNev);

			autoHozzaad(&autok, &auto_db, rendSz, model, vizsgaErv, tulajNev);
			break;
		}
		case 3: { //Javitas hozzaadasa
			char rendSz[100];
			char tipus[100];
			char datum[50];
			int ar;

			printf("auto rendszama: ");
			scanf(" %99[^\n]", rendSz);

			printf("javitas tipusa: ");
			scanf(" %99[^\n]", tipus);

			printf("javitas datuma (yyyy-mm-dd): ");
			scanf(" %49s", datum);

			printf("javitas ara: ");
			scanf("%d", &ar);

			javitasHozzaad(&javitasok, &javitas_db, rendSz, tipus, datum, ar);
			break;
		}
		case 4: { //Kereses ugyfel neve szerint
			char keresesNev[100];
			printf("keresendo ugyfel neve: ");
			scanf(" %99[^\n]", keresesNev);
			break;
		}
		case 5: { //Kereses auto rendszam szerint
			char keresesRendSz[50];
			printf("keresendo auto rendszama: ");
			scanf(" %49s", keresesRendSz);
			break;
		}
		case 6: { //Auto torlese
			autoTorles(&autok, &auto_db, &javitasok, &javitas_db);
			break;
		}
		case 7: { //Auto szerviz tortenet
			autoSzervizTortenet(autok, auto_db, javitasok, javitas_db);
			break;
		}
		case 8: { //Lejaro vizsgaju autok listazasa
			lejaroVizsgak(autok, auto_db);
			break;
		}
		case 9: { //Kilepes
			printf("Kilepes...\n");
			break;
		}
		default:
			printf("Valasztott menu: %d\n", userInput);
	}
	
	// Memória felszabadítása
	free(ugyfelek);
	free(autok);
	free(javitasok);
	
  return 0;
}
