#pragma once

#include<stdio.h>
#include<string.h>
#define W_OK 0                  
#define B_NIEPOPRAWNAOPCJA -1    
#define B_BRAKNAZWY   -2
#define B_BRAKWARTOSCI  -3
#define B_BRAKPLIKU   -4

/* strukura do zapamietywania opcji podanych w wywolaniu programu */

/*******************************************************/
/* Funkcja inicjuje strukture wskazywana przez wybor   */
/* PRE:                                                */
/*      poprawnie zainicjowany argument wybor (!=NULL) */
/* POST:                                               */
/*      "wyzerowana" struktura wybor wybranych opcji   */
/*******************************************************/

typedef struct {
    FILE* plik_we, * plik_wy;        /* uchwyty do pliku wej. i wyj. */
    int wyswietlenie;
    int kolor[3]; // kolor przetwazania 1-czerwony 2-zielony 3-niebieski
    int czydoszarosci; // czy konwertowac do szarosci
    int negatyw; //negatyw
    int progowanie, w_progu, odktorejprog; /* progowanie */
    int gamma;
    double wspolczynnikgamma;
    int zmianapoziomow, poziomdolny, poziomgorny;
    int konturowanie;      //konturowanie
    int rozmywanie, czypoziome, wartoscrozmywania;
    int rozciaganiehistogramu;
    int splot, maciez[3][3];
} t_opcje;
// Funkcja zerujaca Opcje wyboru
void wyzeruj_opcje(t_opcje* wybor);
// Funkcja przypisujaca argumenty wywolania do struktury przechowujacej opcje programu
int przetwarzaj_opcje(int argc, char** argv, t_opcje* wybor);