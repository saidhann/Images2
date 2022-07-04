// Cytuje zapozyczenie fragmentu programu:
/********************************************************************/
/*                                                                  */
/* ALTERNATYWNA DO PRZEDSTAWIONEJ NA WYKLADZIE WERSJA OPRACOWANIA   */
/* PARAMETROW WYWOLANIA PROGRAMU UWZGLEDNIAJACA OPCJE Z PARAMETRAMI */
/* Z ODPOWIEDNIO ZAPROPONOWANYMI STRUKTURAMI DANYCH PRZEKAZUJACYMI  */
/* WCZYTANE USTAWIENIA                                              */
/*                                    COPYRIGHT (c) 2007-2020 KCiR  */
/*                                                                  */
/* Autorzy udzielaja kazdemu prawa do kopiowania tego programu      */
/* w calosci lub czesci i wykorzystania go w dowolnym celu, pod     */
/* warunkiem zacytowania zrodla                                     */
/*                                                                  */
/********************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "OpcjeWywolania.h"
#define W_OK 0                   /* wartosc oznaczajaca brak bledow */
#define B_NIEPOPRAWNAOPCJA -1    /* kody bledow rozpoznawania opcji */
#define B_BRAKNAZWY   -2
#define B_BRAKWARTOSCI  -3
#define B_BRAKPLIKU   -4


// zerowanie opcji
void wyzeruj_opcje(t_opcje* wybor) {
    assert(wybor != NULL);
    wybor->plik_we = NULL;
    wybor->plik_wy = NULL;
    wybor->negatyw = 0;
    wybor->konturowanie = 0;
    wybor->progowanie = 0;
    wybor->wyswietlenie = 0;
    wybor->czydoszarosci = 0;
    wybor->kolor[0] = 0;
    wybor->kolor[1] = 0;
    wybor->kolor[2] = 0;
    wybor->czydoszarosci = 0; // czy konwertowac do szarosci
    wybor->negatyw = 0; //negatyw
    wybor->progowanie = 0;
    wybor->w_progu = 0;
    wybor->odktorejprog = 0; /* progowanie */
    wybor->gamma = 0;
    wybor->wspolczynnikgamma = 0;
    wybor->zmianapoziomow = 0;
    wybor->poziomdolny = 0;
    wybor->poziomgorny = 0;
    wybor->konturowanie = 0;      //konturowanie
    wybor->rozmywanie = 0;
    wybor->czypoziome = 0;
    wybor->wartoscrozmywania = 0;
    wybor->rozciaganiehistogramu = 0;
    wybor->splot = 0;
    for(int i = 0; i < 3;i++) for(int j = 0; j < 3; j++) wybor->maciez[i][j]=0;
}


// Funkcja przypisujaca argumenty wywolania do struktury przechowujacej opcje programu
int przetwarzaj_opcje(int argc, char** argv, t_opcje* wybor) {
    assert(argc != 0);
    assert(argv != NULL);
    assert(wybor != NULL);
    int i, prog,odktorej;
    char* nazwa_pliku_we, * nazwa_pliku_wy;

    wyzeruj_opcje(wybor);
    wybor->plik_wy = stdout;        /* na wypadek gdy nie podano opcji "-o" */
    int czywybranykolor = 0;
    for (i = 1; i < argc; i++) {
        if (argv[i][0] != '-')  /* blad: to nie jest opcja - brak znaku "-" */
            return B_NIEPOPRAWNAOPCJA;
        switch (argv[i][1]) {
        case 'i': {                 /* opcja z nazwa pliku wejsciowego */
            if (++i < argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
                nazwa_pliku_we = argv[i];
                if (strcmp(nazwa_pliku_we, "-") == 0) /* gdy nazwa jest "-"        */
                    wybor->plik_we = stdin;            /* ustwiamy wejscie na stdin */
                else                               /* otwieramy wskazany plik   */
                    wybor->plik_we = fopen(nazwa_pliku_we, "r");
            }
            else
                return B_BRAKNAZWY;                   /* blad: brak nazwy pliku */
            break;
        }
        case 'o': {                 /* opcja z nazwa pliku wyjsciowego */
            if (++i < argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
                nazwa_pliku_wy = argv[i];
                if (strcmp(nazwa_pliku_wy, "-") == 0)/* gdy nazwa jest "-"         */
                    wybor->plik_wy = stdout;          /* ustwiamy wyjscie na stdout */
                else                              /* otwieramy wskazany plik    */
                    wybor->plik_wy = fopen(nazwa_pliku_wy, "w");
            }
            else
                return B_BRAKNAZWY;                   /* blad: brak nazwy pliku */
            break;
        }
        case 'd': {                 /* mamy wyswietlic obraz */
            wybor->wyswietlenie = 1;
            break;
        }
        case 'm': {
            if (argc > i++)
            {
                for (int j = 0; j < strlen(argv[i]); j++)
                {
                    if (argv[i][j] == 's') wybor->czydoszarosci = 1;
                    if (argv[i][j] == 'r') wybor->kolor[0] = 1;
                    if (argv[i][j] == 'g') wybor->kolor[1] = 1;
                    if (argv[i][j] == 'b') wybor->kolor[2] = 1;
                }
                if (wybor->czydoszarosci)
                {
                    wybor->kolor[0] = 0;
                    wybor->kolor[1] = 0;
                    wybor->kolor[2] = 0;
                    wybor->rozciaganiehistogramu=1;
                }
                else
                {
                    if (wybor->kolor[1] == 1 || wybor->kolor[2] == 1 || wybor->kolor[0] == 1);
                    else return B_NIEPOPRAWNAOPCJA;
                }
            }
            else return B_NIEPOPRAWNAOPCJA;
            czywybranykolor = 1;
            break;
        }
        case 'n': {                 /* mamy wykonac negatyw */
            if (czywybranykolor);
            else return B_NIEPOPRAWNAOPCJA;
            wybor->negatyw = 1;
            break;
        }
        case 'p': {
            if (czywybranykolor);
            else return B_NIEPOPRAWNAOPCJA;
            if (++i < argc) { /* wczytujemy kolejny argument jako wartosc progu */
                if (sscanf(argv[i], "%d", &prog) == 1) {
                    wybor->w_progu = prog;
                    if (++i < argc) { /* wczytujemy od ktorej strony ma byc prog */
                        if (sscanf(argv[i], "%d", &odktorej) == 1) {
                            wybor->progowanie = 1;
                            wybor->odktorejprog = odktorej;
                        }
                        else
                            return B_BRAKWARTOSCI;     /* blad: niepoprawna wartosc progu */
                    }
                    else
                        return B_BRAKWARTOSCI;             /* blad: brak wartosci progu */
                }
                else
                    return B_BRAKWARTOSCI;     /* blad: niepoprawna wartosc progu */
            }
            else
                return B_BRAKWARTOSCI;             /* blad: brak wartosci progu */
            break;
        }
        case 'g': {
            if (czywybranykolor);
            else return B_NIEPOPRAWNAOPCJA;
            if (++i < argc) { /* wczytujemy kolejny argument jako wartosc wsp. gamma */
                double gamma = 0;
                if (sscanf(argv[i], "%le", &gamma) == 1) {
                    wybor->wspolczynnikgamma = gamma;
                    wybor->gamma = 1;
                }
                else
                    return B_BRAKWARTOSCI;     /* blad: niepoprawna wartosc wsp gamma */
            }
            else
                return B_BRAKWARTOSCI;             /* blad: brak wartosci wsp gamma */
            break;
        }
        case 'z': {
            if (czywybranykolor);
            else return B_NIEPOPRAWNAOPCJA;
            int dol = 0, gora = 0;
            if (++i < argc) { /* wczytujemy kolejny argument jako wartosc progu */
                if (sscanf(argv[i], "%d", &dol) == 1) {

                    if (++i < argc) { /* wczytujemy od ktorej strony ma byc prog */
                        if (sscanf(argv[i], "%d", &gora) == 1) {
                            wybor->zmianapoziomow = 1;
                            wybor->poziomgorny = gora;
                            wybor->poziomdolny = dol;
                        }
                        else
                            return B_BRAKWARTOSCI;     /* blad: niepoprawna wartosc progu */
                    }
                    else
                        return B_BRAKWARTOSCI;             /* blad: brak wartosci progu */
                }
                else
                    return B_BRAKWARTOSCI;     /* blad: niepoprawna wartosc progu */
            }
            break;
        }
        case 'k': {                 /* mamy wykonac konturowanie */
            if (czywybranykolor);
            else return B_NIEPOPRAWNAOPCJA;
            wybor->konturowanie = 1;
            break;
        }
        case 'r': {
            if (czywybranykolor);
            else return B_NIEPOPRAWNAOPCJA;
            if(strlen(argv[i])!=3) return B_NIEPOPRAWNAOPCJA;
            if (argv[i][2] == 'x')
            {
                int wartosc;
                if (++i < argc) { /* wczytujemy od ktorej strony ma byc prog */
                    if (sscanf(argv[i], "%d", &wartosc) == 1) {
                        wybor->wartoscrozmywania = wartosc;
                        wybor->rozmywanie = 1;
                        wybor->czypoziome = 1;
                    }
                    else
                        return B_BRAKWARTOSCI;     /* blad: niepoprawna wartosc progu */
                }
                else
                    return B_BRAKWARTOSCI;             /* blad: brak wartosci progu */

            }
            else
            {
                if (argv[i][2] == 'y')
                {
                    int wartosc;
                    if (++i < argc) { /* wczytujemy od ktorej strony ma byc prog */
                        if (sscanf(argv[i], "%d", &wartosc) == 1) {
                            wybor->wartoscrozmywania = wartosc;
                            wybor->rozmywanie = 1;
                            wybor->czypoziome = 0;
                        }
                        else
                            return B_BRAKWARTOSCI;     /* blad: niepoprawna wartosc progu */
                    }
                    else
                        return B_BRAKWARTOSCI;             /* blad: brak wartosci progu */
                }
                else return B_NIEPOPRAWNAOPCJA;
            }
            break;
        }
        case 'h': {
            if (czywybranykolor);
            else return B_NIEPOPRAWNAOPCJA;
            wybor->rozciaganiehistogramu=1;
            break;
        }
        case 's': {
            if (czywybranykolor);
            else return B_NIEPOPRAWNAOPCJA;
            if (argc > i + 9)
            {
                i++;
                for (int j = 0; j < 3; j++)
                {
                    for (int k = 0; k < 3; i++,k++)
                    {
                        wybor->maciez[j][k]=atoi(argv[i]);
                    }
                }
                wybor->splot = 1;
            }
            else return B_NIEPOPRAWNAOPCJA;
            break;
        }
        default:                    /* nierozpoznana opcja */
            return B_NIEPOPRAWNAOPCJA;
        } /* koniec switch */
    } /* koniec for */
    if (wybor->plik_we != NULL)     /* ok: wej. strumien danych zainicjowany */
        return W_OK;
    else
        return B_BRAKPLIKU;         /* blad:  nie otwarto pliku wejsciowego  */
}
