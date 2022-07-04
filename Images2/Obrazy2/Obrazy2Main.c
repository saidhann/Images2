#include "wyswietlanie.h"
#include "FunkcjePrzerobki.h"
#include "struktura.h"
#include "Deklaracje.h"
#include "OpcjeWywolania.h"

/*
Said Hannoush, Przetwarzanie obrazow 2, 09.01.2022 - 11.01.2022
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*Program Odpowiednio dziala na Linuxie na diablo i panamincie                                                                                                                   *
*Aby program sie skompilowal trzeba podczas wpisywania komendy kompilacji dodac "-lm" na koncu aby wszystkie uzyte biblioteki dzialaly                                          *
*Kazda funkcja posiada opis tego co robi, a wartosci wyrzucane sa zazwyczaj malo wazne, a te przyjmowane sa odpowiednio nazwane dlatego nie ma do nich dodatkowych wyjasniem.   *
*Z gory przepraszam za bledy ortograwiczne jak i przejezyczenia w interfejsie jak i nazwach zmiennych i funkcji                                                                 *
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/**********************************************************************************************************************************************/
/* Program rozpoznaje opcje wywolania                                                                                  
/* Opcje moga byc podane w dowolnej kolejnosci oraz wszyskie kolejne musza byc oddzielone spacja.
/* Beda wykonywane w z gory okreslonej kodem kolejnosci.
/* Nie nalezy uzywac kilku funkcji obrobki obrazu jednoczesnie gdyż wynik może być nieprzewidywalny i niepożadany.
/* 
/* Skladnia opcji wywolania programu:
/* program
/*		||Nazwa programu                                                                                                                ||
/* -i [nazwa pliku] 
/*		||Opcja wczytujaca plik do programu w razie zastapienia nazwy znakiem "-" program wczyta wartosci z domyslnego wejscia.         ||
/* -o [nazwa pliku]
/*		||Opcja zapisujacia plik w danej lokalizacji w pliku o danej nazwie.                                                            ||
/*		||W razie braku podania tej opcji badz wstawieniu w miejsce nazwy pliku znaku "-" program wypisze wartosci na wyjsciu domyslnym.||
/* -d
/*		||Opcja wyswietlajaca obraz.                                                                                                    ||
/*      ||Na linuxie wyswietla w programie dispaly na windowsie tylko na potrzeby testowania przez co nie dziala bez zmiany sciezki do  ||
/*      ||do programu wyswietlajacego. Funkcja podczas wyswietlania twozy plik temp w swojej lokacji ktory nastepnie wyswietla          ||
/*      ||prosze wiec miec na uwadze ze cechy tego miejsca moga miec wplyw na dzialanie wyswietlania, np w razie ograniczonego miejsca. ||
/* -m [r][g][b][s]
/*		||Opcja wybierajaca kolor badz kolory na ktorych program bedzie prowadzil operacje graficzne.                                   ||                                                            
/*		||W razie wybrania podfunkcji "s" program zignoruje mozliwie wczesniej podane argumenty "r", "g" i "b".                         ||
/*      ||Oraz przeprowadzi konwersje obrazu z kolorowego .ppm na czarnobialy .pgm. przed przeprowadzeniem jakichkolwiek innych operacji||
/*      ||!!!Uwaga!!!                                                                                                                   ||
/*      ||Aby przeprowadzi jakiekolwiek operacje na obrazie nalezy wybrac conajmniej 1 opcje.                                           ||
/*      ||W razie wczytania obrazu czarnobialego .pgm dzialac bedzie obrobka tylko na opcji "r",                                        ||
/*      ||poniewaz to w miejscu koloru czerwonego przechowywane sa jasnosci pixeli dla obrazu czarnobialego.                            ||
/*      ||Dla obrazu .pgm argument "s" bedzie probował konwertowac go mimo tego, spowoduje to rozciagniecie histogramu tego obrazu.     ||
/* -n
/*      ||Opcja przeprowadzajaca negatyw dla wybranych kolorow                                                                          ||
/* -p [procent] [odktorej]
/*      ||Opcja przeprowdzajaca polprogowanie na obrazie o zadanym procencie oraz stronie.                                              ||
/*      ||"procent" przyjmuje wartosc procentowa progu progowania                                                                       ||
/*      ||"odktorej" przyjmuje wartosci "1" lub "2", "1" dla progowania od bialego koloru i "2" od czarnego.                            ||
/* -g [wspolczynnik]
/*      ||Opcja przeprowadzajacaca konwersje gamma o podanym wspolczynnku.                                                              ||
/*      ||"wspolczynnik" moze byc dowolna liczba w zapisie dziesietnym z mozliwoscia wartosci po przecinku.                             ||
/* -z [dol] [gora]
/*      ||Opcja przeprowadza na obrazie zmiane poziomow na okreslona wartosc poziomu dolnego i gornego.                                 ||
/*      ||"dol" przyjmuje procentowa wartosc progu dolnego,"gora" przyjmuje procentowa wartosc progu gornego.                           ||
/* -k
/*      ||Opcja przeprowadzajaca konturowanie obrazu.                                                                                   ||
/* -rx [promien]
/*      ||Opcja przeprowadzajaca rozmywanie poziome o zadanym promieniu                                                                 ||
/*      ||"promien" przyjmuje dowolna wartosc i rozmywa obraz o promien o zadanej ilosci pixeli.                                        ||
/*      ||!!!Uwaga!!!                                                                                                                   ||
/*      ||"promien" powinien byc stosunkowo maly w porownaniu do wymiaru obrazu w pixelach, w przeciwnym wypadku program nie zadziala.  ||
/* -ry [promien]
/*      ||Opcja przeprowadzajaca rozmywanie pionowe o zadanym promieniu                                                                 || 
/*      ||Dla szczegolow patrz opcja "-rx"                                                                                              ||
/* -h
/*		||Opcja przeprowadzajaca na obrazie rozciagniecie histogramu.                                                                   ||
/* -s [1.1] [1.2] [1.3] [2.1] [2.2] [2.3] [3.1] [3.2] [3.3] 
/*      ||Opcja prze prowadzajaca splot, konwoluje zadana macieza konwolujcji.                                                          ||
/*      ||Argumenty tej opcji moga byc dowonymi liczbami calkowitymi dodatnimi jak i ujemnymi.                                                          ||
/*      ||Dla komorki "[x.y]" "x" oznacza miejsce w poziomie, a "y" w pionie. Komorka "[1.1]" znajduje sie w lewym gornym rogu maciezy. ||                                                          || 
/**********************************************************************************************************************************************/
/* UWAGA:                                                               */
/*      Program nie sprawdza istnienia i praw dostepu do plikow         */
/*      w takich przypadkach program wyrzuci bład                       */
/************************************************************************/
int pisz(FILE* plik_we, obraz *Obrazek)//Funkcja implementujaca zapis obrazu w formacie .pgm
{            /* zmienna pomocnicza do czytania komentarzy */
	int koniec = 0;            /* czy napotkano koniec danych w pliku */
	int i, j;

	/*Sprawdzenie czy podano prawid�owy uchwyt pliku */

	/* Sprawdzenie "numeru magicznego" - powinien by� P2 */                              /* Nie udalo sie? Koniec danych! */
	if(Obrazek->czykolorowy) fprintf(plik_we, "P3\r\n");
	else fprintf(plik_we, "P2\r\n");
	/* Pobranie wymiarow obrazu i liczby odcieni szarosci */
	fprintf(plik_we, "%d %d\r\n%d\r\n", Obrazek->rozmiarx, Obrazek->rozmiary, Obrazek->MaxWartosc);
	/* Pobranie obrazu i zapisanie w tablicy obraz_pgm*/
	int dlug = 0;
	for (i = 0; i < Obrazek->rozmiary; i++)
	{
		for (j = 0; j < Obrazek->rozmiarx; j++)
		{
			if (Obrazek->czykolorowy)
			{
				dlug += fprintf(plik_we, "%d ", Obrazek->pierwszy[i * Obrazek->rozmiarx + j].czerwony);
				if (dlug > 65)
				{
					fprintf(plik_we, "\r\n");
					dlug = 0;
				}
				dlug += fprintf(plik_we, "%d ", Obrazek->pierwszy[i * Obrazek->rozmiarx + j].zielony);
				if (dlug > 65)
				{
					fprintf(plik_we, "\r\n");
					dlug = 0;
				}
				dlug += fprintf(plik_we, "%d ", Obrazek->pierwszy[i * Obrazek->rozmiarx + j].niebieski);
				if (dlug > 65)
				{
					fprintf(plik_we, "\r\n");
					dlug = 0;
				}
			}
			else
			{
				dlug += fprintf(plik_we, "%d ", Obrazek->pierwszy[i * Obrazek->rozmiarx + j].czerwony);
				if (dlug > 65)
				{
					fprintf(plik_we, "\r\n");
					dlug = 0;
				}
			}
		}
	}
	return Obrazek->rozmiarx * Obrazek->rozmiary;   /* Czytanie zakonczone sukcesem    */
}
int czytaj(FILE* plik_we, obraz *Obrazek)//Funkcja implementujaca wczytywanie obrazu w formacie .pgm
{
	char buf[DL_LINII];      /* bufor pomocniczy do czytania naglowka i komentarzy */
	int znak=0;                /* zmienna pomocnicza do czytania komentarzy */
	int koniec = 0;            /* czy napotkano koniec danych w pliku */
	int i, j;
	Obrazek->rozmiarx = 0, Obrazek->rozmiary = 0, Obrazek->czykolorowy = 0, Obrazek->MaxWartosc=0;
	/*Sprawdzenie czy podano prawid�owy uchwyt pliku */
	if (plik_we == NULL) {
		fprintf(stderr, "Blad: Nie podano uchwytu do pliku\r\n");
		return(0);
	}

	/* Sprawdzenie "numeru magicznego" - powinien by� P2 */
	if (fgets(buf, DL_LINII, plik_we) == NULL)   /* Wczytanie pierwszej linii pliku do bufora */
		koniec = 1;                              /* Nie udalo sie? Koniec danych! */

	if ((buf[0] == 'P') && (buf[1] == '2') || koniec) // sprawdzanie rodzaju pliku
	{  /* Czy jest magiczne "P2"? */
		Obrazek->czykolorowy = 0;
	}
	else
	{
		if ((buf[0] == 'P') && (buf[1] == '3') || koniec)
		{
			Obrazek->czykolorowy = 1;
		}
		else
		{
			fprintf(stderr, "Blad: To nie jest plik PGM\r\n");
			return(0);
		}
	}
	/* Pominiecie komentarzy */
	do {
		if ((znak = fgetc(plik_we)) == '#') {         /* Czy linia rozpoczyna sie od znaku '#'? */
			if (fgets(buf, DL_LINII, plik_we) == NULL)  /* Przeczytaj ja do bufora                */
				koniec = 1;                   /* Zapamietaj ewentualny koniec danych */
		}
		else {
			ungetc(znak, plik_we);                   /* Gdy przeczytany znak z poczatku linii */
		}                                         /* nie jest '#' zwroc go                 */
	} while (znak == '#' && !koniec);   /* Powtarzaj dopoki sa linie komentarza */
									  /* i nie nastapil koniec danych         */

	/* Pobranie wymiarow obrazu i liczby odcieni szarosci */
	if (fscanf(plik_we, "%d %d %d", &Obrazek->rozmiarx, &Obrazek->rozmiary, &Obrazek->MaxWartosc) != 3) {
		fprintf(stderr, "Blad: Brak wymiarow obrazu lub liczby stopni szarosci\r\n");
		return(0);
	}
	/* Pobranie obrazu i zapisanie w tablicy obraz_pgm*/
	if (Obrazek->rozmiarx > MAX || Obrazek->rozmiary > MAX)
	{
		printf("Obraz Za duzy\r\n");
		Obrazek->rozmiarx = 0;
		Obrazek->rozmiary = 0;
	}
	else
	{
		Obrazek->pierwszy = malloc(sizeof(pixel)*Obrazek->rozmiarx * Obrazek->rozmiary);
		for (i = 0; i < Obrazek->rozmiary; i++) {
			for (j = 0; j < Obrazek->rozmiarx; j++)
			{
				if (Obrazek->czykolorowy)
				{
					if (fscanf(plik_we, "%d", &Obrazek->pierwszy[i * Obrazek->rozmiarx + j].czerwony) != 1) {
						fprintf(stderr, "Blad: Niewlasciwe wymiary obrazu\r\n");
						return(0);
					}
					if (fscanf(plik_we, "%d", &Obrazek->pierwszy[i * Obrazek->rozmiarx + j].zielony) != 1) {
						fprintf(stderr, "Blad: Niewlasciwe wymiary obrazu\r\n");
						return(0);
					}
					if (fscanf(plik_we, "%d", &Obrazek->pierwszy[i * Obrazek->rozmiarx + j].niebieski) != 1) {
						fprintf(stderr, "Blad: Niewlasciwe wymiary obrazu\r\n");
						return(0);
					}
				}
				else
				{
					if (fscanf(plik_we, "%d", &Obrazek->pierwszy[i * Obrazek->rozmiarx + j].czerwony) != 1) {
						fprintf(stderr, "Blad: Niewlasciwe wymiary obrazu\r\n");
						return(0);
					}
					Obrazek->pierwszy[i * Obrazek->rozmiarx + j].niebieski = Obrazek->pierwszy[i * Obrazek->rozmiarx + j].czerwony;
					Obrazek->pierwszy[i * Obrazek->rozmiarx + j].zielony = Obrazek->pierwszy[i * Obrazek->rozmiarx + j].czerwony;
				}
			}
		}
	}  /* Czytanie zakonczone sukcesem    */
	return 1;
}
int wyswietlanie(obraz *Obrazek)//Funkcja tworzaca plik tymczsowy .pgm aby wyswietlic obraz
{
	int zapisano = 0;
	FILE* plik;
	plik = fopen("temp", "w");

	if (plik != NULL) {       /* co spowoduje zakomentowanie tego warunku */
		zapisano = pisz(plik, Obrazek);
		fclose(plik);
		if (CZYLINUX) wyswietl("temp");
		else pokaz("temp");
	}

	return 0;
}
int main(int argc, char** argv)
{
	obraz Obrazek;
	t_opcje opcje;
	int kod_bledu;
	wyzeruj_opcje(&opcje);
	kod_bledu = przetwarzaj_opcje(argc, argv, &opcje);
	kod_bledu = 0;
	if (kod_bledu)
	{
		printf("Blad nr %d\n", kod_bledu);
		return kod_bledu;
	}
	else
		printf("Opcje poprawne\n");

	czytaj(opcje.plik_we,&Obrazek);
	if (opcje.czydoszarosci) doszarosci(&Obrazek, &opcje);
	if (opcje.negatyw) negatyw(&Obrazek, &opcje);
	if (opcje.progowanie) progowanie(&Obrazek,&opcje);
	if (opcje.gamma) gammma(&Obrazek, &opcje);
	if (opcje.zmianapoziomow) poziomy(&Obrazek, &opcje);
	if (opcje.konturowanie) konturowanie(&Obrazek, &opcje);
	if (opcje.rozmywanie) rozmywanie(&Obrazek, &opcje);
	if (opcje.rozciaganiehistogramu) rozciaganie(&Obrazek, &opcje);
	if (opcje.splot) konwolucja(&Obrazek, &opcje);
	if (opcje.wyswietlenie) wyswietlanie(&Obrazek);
	pisz(opcje.plik_wy,&Obrazek);
	return kod_bledu;
}
/*
**************************Testy****************************

Test1:
Czy program kompiluje sie poprawnie na diablo i panamincie
Kompilacja
Program poprawnie odpala sie i pokazuje 1 menu na 2 systemach
Program Kompiluje sie poprawnie
Test2:
Czy program wczytuje oraz wyswietla obraz poprawnie
wejscie: obraz .pgm
wyjscie: otwiera sie okno z obrazem
Wczytywanie i wyswietlanie dziala poprawnie
Test3:
Czy program wyrzuca blad przy prubie wczytania blednego formatu
wejscie: obraz o innym rozszezeniu
wyjscie:program nie wczytuje nic ikomunikuje blad
Program poprawnie odpowiada na probe wczytania nie prawidlowego obrazu
Test5:
Czy program wyrzuca blad gdy wczytujemy bledny format zapisu badz obraz o za duzej wielkosci
wejscie: obraz o powyzszych nieprawidlowosciach z .pgm
wyjscie blad + obraz nie zostal wczytany
Program poprawnie wypisuje blad
Test6:
Czy program w razie proby wczytania nieistniejacego pliku wyzuca blad
wejscie: probujemy wczytac nieistniejacy plik
wyjscie: blad+ nic nie zostalo wczytane
Program poprawnie wyrzuca blad przy prubie wczytania nieistniejacych plikow
Test6:
Czy program poprawnie zapisuje wczytany obraz
wejscie: wczytuje poprawny obraz .pgm i nastepnie wybieram opcje zapisu i podaje poprawna lokalizacje zapisu
wyjscie:Program zapisal plik w odpowiednim formacie
program zapisuje poprawnie
Test7:
Sprawdzenie czy program poprawnie wykonuje funkcje negatywu
wejscie:obraz w formacie .pgm
wyjscie:obraz w formacie .pgm o przeprowadzonej operacji negatywu;
Program poprawnie Przeprowadza ta funkcje
Test8:
Sprawdzenie czy wszyskie interaktywne menu dzialaja
wejscie: przeklikiwanie sie pomiedzy meni i funkcjami
wyjscie: program odpowiada poprawnie
Meni w programie dzialaja
Testy 9-24
W tych testach sprawdzalem czy kazda funkcja dziala wprowadzajac obraz do programu wybierajac odpowiednia opcje i nastepnie wysietlajac obraz przerobiony
Wejscie:Obraz ten porownywalem z obrazem przerobionym ta sama funkcja w innym programie graficznym
Wyjscie:Wszyskie funkcje mniejwiecej ukazuja podobny do profesjonalnego programu graficznego efekt
Wszystkie funkcje dzialaja dla przykladowych wprowadzonych obrazow
Test25:
Czy program sie poprawnie zamyka
wejscie: naciskam '5' i nastepnie 'enter'
wyjscie: program zakonczyl dzialanie
Zamykanie programu dziala

Obrabianie Obrazow .pgm okazalo sie latwiejsze niz przypuszczalem,
lecz same ich wczytywanie, zapisywanie i cala opsluga plikow w jezyku c jest trodniejsza niz w c++ z ktorym mialem doswiadczenie.
Najwiecej problemow sprawila proba opanowania funkcji getch() w Linuxie z biblioteki cures.h ,
ktora nie powodowala klopotow na moim linuxie, ale duzo ich sprawila na zdalnym diablo i panamincie.
Niestety zastosowanie funkcji tej zakonczylo sie niepowodzeniem.
*/
