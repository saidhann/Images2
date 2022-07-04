#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DL_LINII 1024
void pokaz(char* n_pliku) //Funkcja wyswietlajaca obraz na Windowsie
{
	char polecenie[DL_LINII];      /* bufor pomocniczy do zestawienia polecenia */

	strcpy(polecenie, "\"\"C:\\Program Files\\IrfanView\\i_view64.exe\" \"");  /* konstrukcja polecenia postaci */
	strcat(polecenie, n_pliku);     /* display "nazwa_pliku" &       */
	strcat(polecenie, "\"\"");
	printf("%s\r\n", polecenie);      /* wydruk kontrolny polecenia */
	system(polecenie);             /* wykonanie polecenia        */
}
void wyswietl(char* n_pliku)//Funkcja wyswietlajaca obraz na Linuxie
{
	char polecenie[DL_LINII];      /* bufor pomocniczy do zestawienia polecenia */

	strcpy(polecenie, "display ");  /* konstrukcja polecenia postaci */
	strcat(polecenie, n_pliku);     /* display "nazwa_pliku" &       */
	strcat(polecenie, " &");
	printf("%s\r\n", polecenie);      /* wydruk kontrolny polecenia */
	system(polecenie);             /* wykonanie polecenia        */
}