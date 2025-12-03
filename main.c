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

	Ugyfel *ugyfelek = betoltUgyfelek("data/ugyfelek.txt");
	Auto *autok = betoltAutok("data/autok.txt");
	Javitas *javitasok = betoltJavitasok("data/javitasok.txt");

	int menuVal = 0;
	while (1)
	{
		printf("Autoszerviz Program\n");
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

		while (getchar() != '\n');

		switch (menuVal)
		{
		case 1:
		{ // Ugyfel hozzadasa
			char nev[100];
			char email[100];
			char telSz[50];

			printf("ugyfel neve: ");
			scanf(" %99[^\n]", nev); /* enterig olvassuk be, szokozoket is tartalmazo nev beolvasasa biztonsagosan */

			if (ugyfelKeres(ugyfelek, nev) != NULL)
			{
				printf("HIBA: Ilyen nevu ugyfel mar letezik! Ellenorizd a nevet vagy adj hozza megkulombozo karaktert\n");
				break; /* ha mar letezik, nem engedjuk hozzadni */
			}

			printf("ugyfel email-cime: ");
			scanf(" %99s", email);

			printf("ugyfel telefonszama: ");
			scanf(" %49s", telSz);

			Ugyfel uj;

			strcpy(uj.nev, nev);
			strcpy(uj.email, email);
			strcpy(uj.telSz, telSz); /* adatok osszegyujtese */

			uj.kov = NULL;

			printf("\nBiztosan hozza akarod adni? (I/N): ");

			char valasz;
			scanf(" %c", &valasz);

			if (valasz == 'I' || valasz == 'i')
			{
				ugyfelek = ugyfelHozzaad(ugyfelek, &uj); /* megerosites utan beillesztjuk a listaba */
				printf("Sikeresen rogzitve!\n");
			}
			else
			{
				printf("Megszakitva.\n");
			}
			break;
		}
		case 2:
		{ // Auto hozzaadasa
			char rendSz[100];
			char model[100];
			char vizsgaErv[50];
			char tulajNev[100];

			printf("auto rendszama: ");
			scanf(" %99[^\n]", rendSz); /* szokozoket is tartalmazo beolvasas biztonsagosan */

			if (autoKeres(autok, rendSz) != NULL)
			{
				printf("HIBA: Ilyen rendszamu auto mar letezik! Nem letezhet megeggyezo rendszamu auto\n");
				break; /* mar letezik, nem engedjuk duplikalni */
			}
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
			strcpy(ujAuto.tulajNev, tulajNev); /* adatok osszegyujtese */

			printf("\nBiztosan hozza akarod adni? (I/N): ");
			char valasz;
			scanf(" %c", &valasz);

			if (valasz == 'I' || valasz == 'i')
			{
				autok = autoHozzaad(autok, &ujAuto); /* megerosites utan beillesztjuk a listaba */
				printf("Sikeresen rogzitve!\n");
			}
			else
			{
				printf("Megszakitva. \n");
			}
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
			strcpy(ujJ.datum, datum); /* adatok osszegyujtese */
			ujJ.ar = ar;

			printf("\nBiztosan hozza akarod adni? (I/N): ");
			char valasz;
			scanf(" %c", &valasz);

			if (valasz == 'I' || valasz == 'i')
			{
				javitasok = javitasHozzaad(javitasok, &ujJ); /* megerosites utan beillesztjuk a listaba */
				printf("Sikeresen rogzitve!\n");
			}
			else
			{
				printf("Megszakitva. \n");
			}
			break;
		}
		case 4:
		{ // Kereses ugyfel neve szerint
			char keresesNev[100];
			printf("keresendo ugyfel neve: ");
			scanf(" %99[^\n]", keresesNev); /* nev beolvasasa, szokozokkel egyutt */

			Ugyfel *talalat = ugyfelKeres(ugyfelek, keresesNev);

			if (talalat == NULL)
			{
				printf("Nincs ilyen nevu ugyfel!\n"); /* nem talaltuk a listaban */
			}
			else
			{
				printf("\nTalalat:\n");
				printf("Nev  : %s\n", talalat->nev);
				printf("Email: %s\n", talalat->email);
				printf("Tel  : %s\n", talalat->telSz);

				printf("\nUgyfel autoi:\n");
				int vanAuto = 0;
				Auto *aktualisAuto = autok;

				while (aktualisAuto != NULL)
				{
					if (strcmp(aktualisAuto->tulajNev, talalat->nev) == 0)
					{ /* megkeressuk az ugyfelhez tartozo autokat a masik listabol */
						printf(" - Rendszam: %s, Tipus: %s\n", aktualisAuto->rendSz, aktualisAuto->model);
						vanAuto = 1; /* rogzitjuk, hogy van legalabb egy autoja */
					}
					aktualisAuto = aktualisAuto->kov;
				}

				if (!vanAuto)
				{
					printf(" Nincs az ugyfel neven rogzitett auto.\n");
				}
				printf("\n\n");
			}
			break;
		}

		case 5:
		{ // Kereses auto rendszam szerint
			char keresesRendSz[50];
			printf("keresendo auto rendszama: ");
			scanf(" %99[^\n]", keresesRendSz); /* keresett rendszam beolvasasa */

			Auto *talalat = autoKeres(autok, keresesRendSz);

			if (talalat == NULL)
			{
				printf("Nincs ilyen rendszamu auto!\n"); /* nem talaltuk a listaban */
			}
			else
			{
				printf("\nTalalat:\n");
				printf("Rendszam  : %s\n", talalat->rendSz);
				printf("Model: %s\n", talalat->model);
				printf("Viszga ervenyessege  : %s\n", talalat->vizsgaErv);
				printf("Tulajdonos neve  : %s\n", talalat->tulajNev);
				printf("\n\n");
			}
			break;
		}
		case 6:
		{ // Auto torlese
			char torlendoRendSz[50];

			printf("Torolni kivant auto rendszama: ");
			scanf(" %49s", torlendoRendSz);

			printf("Biztosan torolni akarod az autot? (I/N): "); /* biztonsagi kerdes, hogy ne toroljunk veletlenul */
			char valasz;
			scanf(" %c", &valasz);
			if (valasz == 'I' || valasz == 'i')
			{

				autoTorles(&autok, torlendoRendSz); /* kitoroljuk az autot a listabol */
				printf("Akarod a hozza tartozo javitasokat is torolni? (I/N): ");
				scanf(" %c", &valasz);
				if (valasz == 'I' || valasz == 'i')
				{
					javitasTorlesRendszamSzerint(&javitasok, torlendoRendSz); /* a konzisztencia erdekeben a kapcsolodo adatokat is toroljuk ha a felhasznalo akarja */
				}
			}
			else
			{
				printf("Megszakitva, nem tortent torles.\n");
			}
			break;
		}

		case 7:
		{ // Auto szerviz tortenet
			char keresettRendSz[50];

			printf("melyik auto szerviz tortenete erdekel (rendszam): ");
			scanf(" %49s", keresettRendSz);

			autoSzervizTortenet(autok, javitasok, keresettRendSz); /* a megadott autohoz tartozo osszes javitas kilistazasa */
			break;
		}

		case 8:
		{ // Lejaro vizsgaju autok listazasa
			char maiInput[100];

			printf("Add meg a mai datumot (YYYY-MM-DD): ");
			scanf(" %99s", maiInput); /* datum beolvasasa */

			int n = strlen(maiInput) + 1;

			char *maiDatum = (char *)malloc(n * sizeof(char));
			if (maiDatum == NULL)
			{
				printf("Memoria foglalasi hiba!\n");
				break;
			}

			strcpy(maiDatum, maiInput); /* atmasoljuk a datumot a dinamikus teruletre */

			lejaroVizsgak(autok, maiDatum); /* lejart vizsgaju autok keresese es kiirasa */

			free(maiDatum); /* lefoglalt memoria felszabaditasa */
			break;
		}
		case 9:
		{ // Kilepes
			printf("Kilepes...\n");

			printf("\nBiztosan ki szeretnel lepni? (I/N): ");
			char valasz;
			scanf(" %c", &valasz);

			if (valasz == 'I' || valasz == 'i')
			{
				mentUgyfelek("data/ugyfelek.txt", ugyfelek);
				mentAutok("data/autok.txt", autok);
				mentJavitasok("data/javitasok.txt", javitasok); /* minden valtozas mentese fajlba a kilepes elott */

				felszabaditUgyfelek(ugyfelek);
				felszabaditAutok(autok);
				felszabaditJavitasok(javitasok); /* dinamikusan foglalt memoria felszabaditasa */
				printf("mentve\n");
				return 0; /*  kilepunk a programbol */
			}
			else
			{
				printf("Megszakitva. \n");
				valasz = 0;
				break; /* ha megsem lepunk ki, visszaterunk a fomenuhoz */
			}
		}

		default:
			printf("Valasztott menu: %d\n", menuVal);
		}
	}

	// felszabaditasok
	felszabaditUgyfelek(ugyfelek);
	felszabaditAutok(autok);
	felszabaditJavitasok(javitasok);

	return 0; /*  kilepunk a programbol */
}
