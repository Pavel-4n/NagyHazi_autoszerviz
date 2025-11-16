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
	printf("9. Adatok kiirasa\n");
	printf("10. Kilepes\n");
	printf("Valassz egy menupontot: \n");
	scanf("%d" , &userInput);	
	
	switch(userInput) {
		case 1: //Ugyfel hozzadasa
			ugyfelHozzaad();
			break;
		case 2: //Auto hozzaadasa

			break;
		case 3: //Javitas hozzaadasa

			break;
		case 4: //Kereses ugyfel neve szerint

			break;
		case 5: //Kereses auto rendszam szerint

			break;
		case 6: //Auto torlese

			break;
		case 7: //Auto szerviz tortenet

			break;
		case 8: //Lejaro vizsgaju autok listazasa

			break;
		case 9: //Adatok kiirasa

			nyomtatUgyfeleket(ugyfelek, ugyfel_db);
			nyomtatAutokat(autok, auto_db);
			nyomtatJavitasokat(javitasok, javitas_db);
			break;
		case 10: //Kilepes

			break;
		default:
			printf("Valasztott menu: %d\n", userInput);
	}
	
	// Memória felszabadítása
	free(ugyfelek);
	free(autok);
	free(javitasok);
	
  return 0;
}
