#include "auto.h"
#include "debugmalloc.h"
#include "functions.c"
#include "javitas.h"
#include "structs.h"
#include "ugyfel.h"
#include <stdio.h>

int main() {

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
	printf("%d",userInput);
	
  return 0;
}
