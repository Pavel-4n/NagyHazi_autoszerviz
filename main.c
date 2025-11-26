#include "auto.h"
#include "debugmalloc.h"
#include "functions.h"
#include "javitas.h"
#include "structs.h"
#include "ugyfel.h"
#include <stdio.h>
#include <string.h>

int main()
{
	// adatok beolvasasa, tomb meret valtozok inicializalasa
	int ugyfel_db = 0, auto_db = 0, javitas_db = 0;

	Ugyfel *ugyfelek = betoltUgyfelek("data/ugyfelek.txt", &ugyfel_db);
	Auto *autok = betoltAutok("data/autok.txt", &auto_db);
	Javitas *javitasok = betoltJavitasok("data/javitasok.txt", &javitas_db);

	int menuVal = 0;
	while (1)
	{
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
		scanf("%d", &menuVal);

		switch (menuVal)
		{
		case 1:
		{ // Ugyfel hozzadasa
			char nev[100];
			char email[100];
			char telSz[50];

			printf("ugyfel neve: ");
			scanf(" %99[^\n]", nev);

			printf("ugyfel email-cime: ");
			scanf(" %99s", email);

			printf("ugyfel telefonszama: ");
			scanf(" %49s", telSz);

			Ugyfel uj;

			// IDE NEM KELL malloc, csak masolas:
			strcpy(uj.nev, nev);
			strcpy(uj.email, email);
			strcpy(uj.telSz, telSz);

			// a kov pointert is illik inicializalni
			uj.kov = NULL;

			ugyfelHozzaad(&ugyfelek, &ugyfel_db, &uj);
			break;
		}
		case 2:
		{ // Auto hozzaadasa
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
			scanf(" %99[^\n]", tulajNev);

			Auto ujAuto;
			strcpy(ujAuto.rendSz, rendSz);
			strcpy(ujAuto.model, model);
			strcpy(ujAuto.vizsgaErv, vizsgaErv);
			strcpy(ujAuto.tulajNev, tulajNev);

			autoHozzaad(&autok, &auto_db, &ujAuto);
			break;
		}
		case 3:
		{ // Javitas hozzaadasa
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

			Javitas ujJ;
			strcpy(ujJ.rendSz, rendSz);
			strcpy(ujJ.tipus, tipus);
			strcpy(ujJ.datum, datum);
			ujJ.ar = ar;

			javitasHozzaad(&javitasok, &javitas_db, &ujJ);
			break;
		}
		case 4:
		{ // Kereses ugyfel neve szerint
			char keresesNev[100];

			printf("keresendo ugyfel neve: ");
			scanf(" %99[^\n]", keresesNev);

			int index = ugyfelKeres(ugyfelek, ugyfel_db, keresesNev);

			if (index == -1)
			{
				printf("Nincs ilyen nevu ugyfel!\n");
			}
			else
			{
				printf("\nTalalat:\n");
				printf("Nev  : %s\n", ugyfelek[index].nev);
				printf("Email: %s\n", ugyfelek[index].email);
				printf("Tel  : %s\n", ugyfelek[index].telSz);
				printf("\n\n");
			}

			break;
		}

		case 5:
		{ // Kereses auto rendszam szerint
			char keresesRendSz[50];

			printf("keresendo auto rendszama: ");
			scanf(" %99[^\n]", keresesRendSz);

			int index = autoKeres(autok, auto_db, keresesRendSz);

			if (index == -1)
			{
				printf("Nincs ilyen rendszamu auto!\n");
			}
			else
			{
				printf("\nTalalat:\n");
				printf("Rendszam  : %s\n", autok[index].rendSz);
				printf("Model: %s\n", autok[index].model);
				printf("Viszga ervenyessege  : %s\n", autok[index].vizsgaErv);
				printf("Tulajdonos neve  : %s\n", autok[index].tulajNev);
				printf("\n\n");
			}
			break;
		}
		case 6:
		{ // Auto torlese
			char torlendoRendSz[50];

			printf("torlendo auto rendszama: ");
			scanf(" %49s", torlendoRendSz);

			autoTorles(&autok, &auto_db, &javitasok, &javitas_db, torlendoRendSz);
			break;
		}
		case 7:
		{ // Auto szerviz tortenet
			char keresettRendSz[50];

			printf("melyik auto szerviz tortenete erdekel (rendszam): ");
			scanf(" %49s", keresettRendSz);

			autoSzervizTortenet(autok, javitasok, keresettRendSz);
			break;
		}

		case 8:
		{ // Lejaro vizsgaju autok listazasa
			char maiInput[100];

			printf("Add meg a mai datumot (YYYY-MM-DD): ");
			scanf(" %99s", maiInput);

			int n = strlen(maiInput) + 1;

			char *maiDatum = (char *)malloc(n * sizeof(char));
			if (maiDatum == NULL)
			{
				printf("Memoria foglalasi hiba!\n");
				break;
			}

			strcpy(maiDatum, maiInput);

			lejaroVizsgak(autok, maiDatum);

			free(maiDatum);
			break;
		}

		case 9:
		{ // Kilepes
			printf("Kilepes...\n");
			mentUgyfelek("data/ugyfelek.txt", ugyfelek);
			mentAutok("data/autok.txt", autok);
			mentJavitasok("data/javitasok.txt", javitasok);
			break;
		}
		default:
			printf("Valasztott menu: %d\n", menuVal);
		}
	}

	// felszabaditasok
	felszabaditUgyfelek(ugyfelek);
	felszabaditAutok(autok);
	felszabaditJavitasok(javitasok);

	return 0;
}
