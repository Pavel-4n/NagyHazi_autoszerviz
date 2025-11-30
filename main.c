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
		printf("Autoszerviz V1.17\n");
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
		
		while(getchar() != '\n');
		
		switch (menuVal)
		{
		case 1:
		{ // Ugyfel hozzadasa
			char nev[100];
			char email[100];
			char telSz[50];

			printf("ugyfel neve: ");
			scanf(" %99[^\n]", nev);
			
			if (ugyfelKeres(ugyfelek, nev) != NULL) {
					printf("HIBA: Ilyen nevu ugyfel mar letezik! Ellenorizd a nevet vagy adj hozza megkulombozo karaktert\n");
					break;
			}

			printf("ugyfel email-cime: ");
			scanf(" %99s", email);

			printf("ugyfel telefonszama: ");
			scanf(" %49s", telSz);

			Ugyfel uj;

			strcpy(uj.nev, nev);
			strcpy(uj.email, email);
			strcpy(uj.telSz, telSz);

			uj.kov = NULL;
			
			printf("\nBiztosan hozza akarod adni? (I/N): ");

			char valasz;
			scanf(" %c", &valasz);

			if (valasz == 'I' || valasz == 'i') {
				ugyfelek = ugyfelHozzaad(ugyfelek, &uj);
				printf("Sikeresen rogzitve!\n");
			} else {
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
			scanf(" %99[^\n]", rendSz);

			if (autoKeres(autok, rendSz) != NULL) {
					printf("HIBA: Ilyen rendszamu auto mar letezik! Nem letezhet megeggyezo rendszamu auto\n");
					break;
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
			strcpy(ujAuto.tulajNev, tulajNev);

			printf("\nBiztosan hozza akarod adni? (I/N): ");
			char valasz;
			scanf(" %c", &valasz);

			if (valasz == 'I' || valasz == 'i') {
				autok = autoHozzaad(autok, &ujAuto);
				printf("Sikeresen rogzitve!\n");
			} else {
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
			strcpy(ujJ.datum, datum);
			ujJ.ar = ar;

			printf("\nBiztosan hozza akarod adni? (I/N): ");
			char valasz;
			scanf(" %c", &valasz);

			if (valasz == 'I' || valasz == 'i') {
				javitasok = javitasHozzaad(javitasok, &ujJ);
				printf("Sikeresen rogzitve!\n");
			} else {
				printf("Megszakitva. \n");
			}
			break;
		}
		case 4:
		{ // Kereses ugyfel neve szerint
			char keresesNev[100];
			printf("keresendo ugyfel neve: ");
			scanf(" %99[^\n]", keresesNev);

						
			Ugyfel *talalat = ugyfelKeres(ugyfelek, keresesNev);

			if (talalat == NULL) 
			{
				printf("Nincs ilyen nevu ugyfel!\n");
			}
			else
			{
								
				printf("\nTalalat:\n");
				printf("Nev  : %s\n", talalat->nev);
				printf("Email: %s\n", talalat->email);
				printf("Tel  : %s\n", talalat->telSz);
				printf("\n\n");
			}
			break;

		}

		case 5:
		{ // Kereses auto rendszam szerint
			char keresesRendSz[50];
			printf("keresendo auto rendszama: ");
			scanf(" %99[^\n]", keresesRendSz);

			Auto *talalat = autoKeres(autok, keresesRendSz);

			if (talalat == NULL)
			{
				printf("Nincs ilyen rendszamu auto!\n");
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
			case 6: { // Auto torlese
					char torlendoRendSz[50];

					printf("Torolni kivant auto rendszama: ");
					scanf(" %49s", torlendoRendSz);

					int torolveVolt = autoTorles(&autok, torlendoRendSz);

					if (torolveVolt) {
							char valasz;

							printf("Akarod a hozza tartozo javitasokat is torolni? (I/N): ");
							scanf(" %c", &valasz);

							if (valasz == 'I' || valasz == 'i') {
									javitasTorlesRendszamSzerint(&javitasok, torlendoRendSz);
							}
					}

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
		case 9: { // Kilepes
				printf("Kilepes...\n");

				printf("\nBiztosan ki szeretnel lepni? (I/N): ");
				char valasz;
				scanf(" %c", &valasz);

				if (valasz == 'I' || valasz == 'i') {
					mentUgyfelek("data/ugyfelek.txt", ugyfelek);
					mentAutok("data/autok.txt", autok);
					mentJavitasok("data/javitasok.txt", javitasok);

					felszabaditUgyfelek(ugyfelek);
					felszabaditAutok(autok);
					felszabaditJavitasok(javitasok);						
					printf("mentve\n");
					return 0;
				} else {
					printf("Megszakitva. \n");
					valasz = 0;
					break;
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

	return 0;
}
