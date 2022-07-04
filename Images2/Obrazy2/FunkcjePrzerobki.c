#include "Deklaracje.h"
#include "struktura.h"
#include "OpcjeWywolania.h"
void rozciaganie(obraz *Obrazek, t_opcje *opcje) // Funkcja rozciagajaca obraz z tablicy
{
	printf("Rozpoczynanie Rozciagania Histogramu\r\n");
	int JasMax = 0, JasMin = Obrazek->MaxWartosc;
	if (opcje->kolor[0] || Obrazek->czykolorowy == 0)
	{
		for (int i = 0; i < Obrazek->rozmiary; i++)
		{
			for (int j = 0; j < Obrazek->rozmiarx; j++)
			{
				if (Obrazek->pierwszy[i * Obrazek->rozmiarx + j].czerwony > JasMax) JasMax = Obrazek->pierwszy[i * Obrazek->rozmiarx + j].czerwony;
				if (Obrazek->pierwszy[i * Obrazek->rozmiarx + j].czerwony < JasMin) JasMin = Obrazek->pierwszy[i * Obrazek->rozmiarx + j].czerwony;
			}
		}
		for (int i = 0; i < Obrazek->rozmiary; i++)
		{
			for (int j = 0; j < Obrazek->rozmiarx; j++)
			{
				Obrazek->pierwszy[i * Obrazek->rozmiarx + j].czerwony = (Obrazek->pierwszy[i * Obrazek->rozmiarx + j].czerwony - JasMin) * Obrazek->MaxWartosc / (JasMax - JasMin);
			}
		}
	}
	JasMax = 0; JasMin = Obrazek->MaxWartosc;
	if (opcje->kolor[1] || Obrazek->czykolorowy == 0)
	{
		for (int i = 0; i < Obrazek->rozmiary; i++)
		{
			for (int j = 0; j < Obrazek->rozmiarx; j++)
			{
				if (Obrazek->pierwszy[i * Obrazek->rozmiarx + j].zielony > JasMax) JasMax = Obrazek->pierwszy[i * Obrazek->rozmiarx + j].zielony;
				if (Obrazek->pierwszy[i * Obrazek->rozmiarx + j].zielony < JasMin) JasMin = Obrazek->pierwszy[i * Obrazek->rozmiarx + j].zielony;
			}
		}
		for (int i = 0; i < Obrazek->rozmiary; i++)
		{
			for (int j = 0; j < Obrazek->rozmiarx; j++)
			{
				Obrazek->pierwszy[i * Obrazek->rozmiarx + j].zielony = (Obrazek->pierwszy[i * Obrazek->rozmiarx + j].zielony - JasMin) * Obrazek->MaxWartosc / (JasMax - JasMin);
			}
		}
	}
	JasMax = 0; JasMin = Obrazek->MaxWartosc;
	if (opcje->kolor[2] || Obrazek->czykolorowy == 0)
	{
		for (int i = 0; i < Obrazek->rozmiary; i++)
		{
			for (int j = 0; j < Obrazek->rozmiarx; j++)
			{
				if (Obrazek->pierwszy[i * Obrazek->rozmiarx + j].niebieski > JasMax) JasMax = Obrazek->pierwszy[i * Obrazek->rozmiarx + j].niebieski;
				if (Obrazek->pierwszy[i * Obrazek->rozmiarx + j].niebieski < JasMin) JasMin = Obrazek->pierwszy[i * Obrazek->rozmiarx + j].niebieski;
			}
		}
		for (int i = 0; i < Obrazek->rozmiary; i++)
		{
			for (int j = 0; j < Obrazek->rozmiarx; j++)
			{
				Obrazek->pierwszy[i * Obrazek->rozmiarx + j].niebieski = (Obrazek->pierwszy[i * Obrazek->rozmiarx + j].niebieski - JasMin) * Obrazek->MaxWartosc / (JasMax - JasMin);
			}
		}
	}
	printf("Rozciaganie Histogramu Zakonczone\r\n");
}
void rozmywanie(obraz *Obrazek, t_opcje *opcje) // Funkcja rozmywajaca obraz
{
	printf("Rozpoczynanie Rozmywania\r\n");
	pixel *Tymczasowy;
	Tymczasowy = malloc(sizeof(pixel) * Obrazek->rozmiarx * Obrazek->rozmiary);
	int Kierunek=0;
		if (opcje->czypoziome) Kierunek = 2;
		else Kierunek = 1;
	int Promien = opcje->wartoscrozmywania;
	if (opcje->kolor[0] || Obrazek->czykolorowy == 0) {
		if (Kierunek == 1)
		{
			for (int i = Promien; i + Promien < Obrazek->rozmiary; i++)
			{
				for (int j = 0; j < Obrazek->rozmiarx; j++)
				{
					Tymczasowy[i * Obrazek->rozmiarx + j].czerwony = (Obrazek->pierwszy[(i - Promien) * Obrazek->rozmiarx + j].czerwony + Obrazek->pierwszy[i * Obrazek->rozmiarx + j].czerwony + Obrazek->pierwszy[(i + Promien) * Obrazek->rozmiarx + j].czerwony) / 3;
				}
			}
		}
		else
		{
			for (int i = 0; i < Obrazek->rozmiary; i++)
			{
				for (int j = Promien; j + Promien < Obrazek->rozmiarx; j++)
				{
					Tymczasowy[i * Obrazek->rozmiarx + j].czerwony = (Obrazek->pierwszy[i * Obrazek->rozmiarx + j - Promien].czerwony + Obrazek->pierwszy[i * Obrazek->rozmiarx + j].czerwony + Obrazek->pierwszy[i * Obrazek->rozmiarx + j + Promien].czerwony) / 3;
				}
			}
		}
		for (int i = 0; i < Obrazek->rozmiary; i++)
		{
			for (int j = 0; j < Obrazek->rozmiarx; j++)
			{
				Obrazek->pierwszy[i * Obrazek->rozmiarx + j].czerwony = Tymczasowy[i * Obrazek->rozmiarx + j].czerwony;
			}
		}
	}
	if (opcje->kolor[1]) {
		if (Kierunek == 1)
		{
			for (int i = Promien; i + Promien < Obrazek->rozmiary; i++)
			{
				for (int j = 0; j < Obrazek->rozmiarx; j++)
				{
					Tymczasowy[i * Obrazek->rozmiarx + j].zielony = (Obrazek->pierwszy[(i - Promien) * Obrazek->rozmiarx + j].zielony + Obrazek->pierwszy[i * Obrazek->rozmiarx + j].zielony + Obrazek->pierwszy[(i + Promien) * Obrazek->rozmiarx + j].zielony) / 3;
				}
			}
		}
		else
		{
			for (int i = 0; i < Obrazek->rozmiary; i++)
			{
				for (int j = Promien; j + Promien < Obrazek->rozmiarx; j++)
				{
					Tymczasowy[i * Obrazek->rozmiarx + j].zielony = (Obrazek->pierwszy[i * Obrazek->rozmiarx + j - Promien].zielony + Obrazek->pierwszy[i * Obrazek->rozmiarx + j].zielony + Obrazek->pierwszy[i * Obrazek->rozmiarx + j + Promien].zielony) / 3;
				}
			}
		}
		for (int i = 0; i < Obrazek->rozmiary; i++)
		{
			for (int j = 0; j < Obrazek->rozmiarx; j++)
			{
				Obrazek->pierwszy[i * Obrazek->rozmiarx + j].zielony = Tymczasowy[i * Obrazek->rozmiarx + j].zielony;
			}
		}
	}
	if (opcje->kolor[2]) {
		if (Kierunek == 1)
		{
			for (int i = Promien; i + Promien < Obrazek->rozmiary; i++)
			{
				for (int j = 0; j < Obrazek->rozmiarx; j++)
				{
					Tymczasowy[i * Obrazek->rozmiarx + j].niebieski = (Obrazek->pierwszy[(i - Promien) * Obrazek->rozmiarx + j].niebieski + Obrazek->pierwszy[i * Obrazek->rozmiarx + j].niebieski + Obrazek->pierwszy[(i + Promien) * Obrazek->rozmiarx + j].niebieski) / 3;
				}
			}
		}
		else
		{
			for (int i = 0; i < Obrazek->rozmiary; i++)
			{
				for (int j = Promien; j + Promien < Obrazek->rozmiarx; j++)
				{
					Tymczasowy[i * Obrazek->rozmiarx + j].niebieski = (Obrazek->pierwszy[i * Obrazek->rozmiarx + j - Promien].niebieski + Obrazek->pierwszy[i * Obrazek->rozmiarx + j].niebieski + Obrazek->pierwszy[i * Obrazek->rozmiarx + j + Promien].niebieski) / 3;
				}
			}
		}
		for (int i = 0; i < Obrazek->rozmiary; i++)
		{
			for (int j = 0; j < Obrazek->rozmiarx; j++)
			{
				Obrazek->pierwszy[i * Obrazek->rozmiarx + j].niebieski = Tymczasowy[i * Obrazek->rozmiarx + j].niebieski;
			}
		}
	}
	printf("Rozmywanie Zakonczone\r\n");
}
void konturowanie(obraz *Obrazek, t_opcje *opcje) // Funkcja przeprowadzajaca konturowanie obrazu
{
	printf("Rozpoczynanie Konturowania\r\n");
	if (opcje->kolor[0] || Obrazek->czykolorowy == 0)
	{
		for (int i = 0; i+1 < Obrazek->rozmiary; i++)
		{
			for (int j = 0; j+1 < Obrazek->rozmiarx; j++)
			{
				Obrazek->pierwszy[i * Obrazek->rozmiarx + j].czerwony = abs(Obrazek->pierwszy[(i + 1) * Obrazek->rozmiarx + j].czerwony - Obrazek->pierwszy[i * Obrazek->rozmiarx + j].czerwony) + abs(Obrazek->pierwszy[i * Obrazek->rozmiarx + j + 1].czerwony - Obrazek->pierwszy[i * Obrazek->rozmiarx + j].czerwony);
				if (i == Obrazek->rozmiary - 1 || j == Obrazek->rozmiarx - 1) Obrazek->pierwszy[i * Obrazek->rozmiarx + j].czerwony = 0;
			}
		}
	}
	if (opcje->kolor[1])
	{
		for (int i = 0; i+1 < Obrazek->rozmiary; i++)
		{
			for (int j = 0; j+1 < Obrazek->rozmiarx; j++)
			{
				Obrazek->pierwszy[i * Obrazek->rozmiarx + j].zielony = abs(Obrazek->pierwszy[(i + 1) * Obrazek->rozmiarx + j].zielony - Obrazek->pierwszy[i * Obrazek->rozmiarx + j].zielony) + abs(Obrazek->pierwszy[i * Obrazek->rozmiarx + j + 1].zielony - Obrazek->pierwszy[i * Obrazek->rozmiarx + j].zielony);
				if (i == Obrazek->rozmiary - 1 || j == Obrazek->rozmiarx - 1) Obrazek->pierwszy[i * Obrazek->rozmiarx + j].zielony = 0;
			}
		}
	}
	if (opcje->kolor[2])
	{
		for (int i = 0; i+1 < Obrazek->rozmiary; i++)
		{
			for (int j = 0; j+1 < Obrazek->rozmiarx; j++)
			{
				Obrazek->pierwszy[i * Obrazek->rozmiarx + j].niebieski = abs(Obrazek->pierwszy[(i + 1) * Obrazek->rozmiarx + j].niebieski - Obrazek->pierwszy[i * Obrazek->rozmiarx + j].niebieski) + abs(Obrazek->pierwszy[i * Obrazek->rozmiarx + j + 1].niebieski - Obrazek->pierwszy[i * Obrazek->rozmiarx + j].niebieski);
				if (i == Obrazek->rozmiary - 1 || j == Obrazek->rozmiarx - 1) Obrazek->pierwszy[i * Obrazek->rozmiarx + j].niebieski = 0;
			}
		}
	}
	printf("Konturowanie Zakonczone\r\n");
}
void poziomy(obraz *Obrazek, t_opcje *opcje) // Funkcja poziomujaca obraz
{
	printf("Rozpoczynanie Zmiany Poziomow\r\n");
	int Czern = opcje->poziomdolny, Biel = opcje->poziomgorny;
	Czern = Czern * Obrazek->MaxWartosc / 100;
	Biel = Biel * Obrazek->MaxWartosc / 100;
	if (opcje->kolor[0] || Obrazek->czykolorowy == 0) {
		for (int i = 0; i < Obrazek->rozmiary; i++)
		{
			for (int j = 0; j < Obrazek->rozmiarx; j++)
			{
				if (Obrazek->pierwszy[i * Obrazek->rozmiarx + j].czerwony <= Czern) Obrazek->pierwszy[i * Obrazek->rozmiarx + j].czerwony = 0;
				else
				{
					if (Obrazek->pierwszy[i * Obrazek->rozmiarx + j].czerwony >= Biel) Obrazek->pierwszy[i * Obrazek->rozmiarx + j].czerwony = Obrazek->MaxWartosc;
					else Obrazek->pierwszy[i * Obrazek->rozmiarx + j].czerwony = (Obrazek->pierwszy[i * Obrazek->rozmiarx + j].czerwony - Czern) * Obrazek->MaxWartosc / (Biel - Czern);
				}
			}
		}
	}
	if (opcje->kolor[1]) {
		for (int i = 0; i < Obrazek->rozmiary; i++)
		{
			for (int j = 0; j < Obrazek->rozmiarx; j++)
			{
				if (Obrazek->pierwszy[i * Obrazek->rozmiarx + j].zielony <= Czern) Obrazek->pierwszy[i * Obrazek->rozmiarx + j].zielony = 0;
				else
				{
					if (Obrazek->pierwszy[i * Obrazek->rozmiarx + j].zielony >= Biel) Obrazek->pierwszy[i * Obrazek->rozmiarx + j].zielony = Obrazek->MaxWartosc;
					else Obrazek->pierwszy[i * Obrazek->rozmiarx + j].zielony = (Obrazek->pierwszy[i * Obrazek->rozmiarx + j].zielony - Czern) * Obrazek->MaxWartosc / (Biel - Czern);
				}
			}
		}
	}
	if (opcje->kolor[2]) {
		for (int i = 0; i < Obrazek->rozmiary; i++)
		{
			for (int j = 0; j < Obrazek->rozmiarx; j++)
			{
				if (Obrazek->pierwszy[i * Obrazek->rozmiarx + j].niebieski <= Czern) Obrazek->pierwszy[i * Obrazek->rozmiarx + j].niebieski = 0;
				else
				{
					if (Obrazek->pierwszy[i * Obrazek->rozmiarx + j].niebieski >= Biel) Obrazek->pierwszy[i * Obrazek->rozmiarx + j].niebieski = Obrazek->MaxWartosc;
					else Obrazek->pierwszy[i * Obrazek->rozmiarx + j].niebieski = (Obrazek->pierwszy[i * Obrazek->rozmiarx + j].niebieski - Czern) * Obrazek->MaxWartosc / (Biel - Czern);
				}
			}
		}
	}
	printf("Zmiana Poziomow Zakonczona\r\n");
}
void gammma(obraz *Obrazek, t_opcje *opcje)// Funkcja przeprowadzajaca korekcje gamma
{
	double Parametr = opcje->wspolczynnikgamma;
	if (opcje->kolor[0] || Obrazek->czykolorowy == 0) {
		for (int i = 0; i < Obrazek->rozmiary; i++)
		{
			for (int j = 0; j < Obrazek->rozmiarx; j++)
			{
				Obrazek->pierwszy[i * Obrazek->rozmiarx + j].czerwony = (int)round(pow(Obrazek->pierwszy[i * Obrazek->rozmiarx + j].czerwony / (double)Obrazek->MaxWartosc, (1.0 / Parametr)) * Obrazek->MaxWartosc);
			}
		}
	}
	if (opcje->kolor[1]) {
		for (int i = 0; i < Obrazek->rozmiary; i++)
		{
			for (int j = 0; j < Obrazek->rozmiarx; j++)
			{
				Obrazek->pierwszy[i * Obrazek->rozmiarx + j].zielony = (int)round(pow(Obrazek->pierwszy[i * Obrazek->rozmiarx + j].zielony / (double)Obrazek->MaxWartosc, (1.0 / Parametr)) * Obrazek->MaxWartosc);
			}
		}
	}
	if (opcje->kolor[2]) {
		for (int i = 0; i < Obrazek->rozmiary; i++)
		{
			for (int j = 0; j < Obrazek->rozmiarx; j++)
			{
				Obrazek->pierwszy[i * Obrazek->rozmiarx + j].niebieski = (int)round(pow(Obrazek->pierwszy[i * Obrazek->rozmiarx + j].niebieski / (double)Obrazek->MaxWartosc, (1.0 / Parametr)) * Obrazek->MaxWartosc);
			}
		}
	}
	printf("Korekcja Gamma Zakonczona\r\n");
}
void progowanie(obraz *Obrazek, t_opcje *opcje)// Funkcja przeprowadzajaca progowanie
{
	printf("Rozpoczynanie Progowania\r\n");
	int Progowanie = opcje->odktorejprog;
	int ProcentProgowania = opcje->w_progu;
	if (opcje->kolor[0] || Obrazek->czykolorowy == 0) {
		for (int i = 0; i < Obrazek->rozmiary; i++)
		{
			for (int j = 0; j < Obrazek->rozmiarx; j++)
			{
				if (Progowanie == 2) {
					if (Obrazek->pierwszy[i * Obrazek->rozmiarx + j].czerwony <= Obrazek->MaxWartosc * ProcentProgowania / 100) Obrazek->pierwszy[i * Obrazek->rozmiarx + j].czerwony = 0;
				}
				else if (Progowanie == 1) {
					if (Obrazek->pierwszy[i * Obrazek->rozmiarx + j].czerwony > Obrazek->MaxWartosc * ProcentProgowania / 100) Obrazek->pierwszy[i * Obrazek->rozmiarx + j].czerwony = Obrazek->MaxWartosc;
				}
			}
		}
	}
	if (opcje->kolor[1]) {
		for (int i = 0; i < Obrazek->rozmiary; i++)
		{
			for (int j = 0; j < Obrazek->rozmiarx; j++)
			{
				if (Progowanie == 2) {
					if (Obrazek->pierwszy[i * Obrazek->rozmiarx + j].zielony <= Obrazek->MaxWartosc * ProcentProgowania / 100) Obrazek->pierwszy[i * Obrazek->rozmiarx + j].zielony = 0;
				}
				else if (Progowanie == 1) {
					if (Obrazek->pierwszy[i * Obrazek->rozmiarx + j].zielony > Obrazek->MaxWartosc * ProcentProgowania / 100) Obrazek->pierwszy[i * Obrazek->rozmiarx + j].zielony = Obrazek->MaxWartosc;
				}
			}
		}
	}
	if (opcje->kolor[2]) {
		for (int i = 0; i < Obrazek->rozmiary; i++)
		{
			for (int j = 0; j < Obrazek->rozmiarx; j++)
			{
				if (Progowanie == 2) {
					if (Obrazek->pierwszy[i * Obrazek->rozmiarx + j].niebieski <= Obrazek->MaxWartosc * ProcentProgowania / 100) Obrazek->pierwszy[i * Obrazek->rozmiarx + j].niebieski = 0;
				}
				else if (Progowanie == 1) {
					if (Obrazek->pierwszy[i * Obrazek->rozmiarx + j].niebieski > Obrazek->MaxWartosc * ProcentProgowania / 100) Obrazek->pierwszy[i * Obrazek->rozmiarx + j].niebieski = Obrazek->MaxWartosc;
				}
			}
		}
	}
	printf("Progowanie Zakonczone\r\n\r\n");
}
void negatyw(obraz *Obrazek, t_opcje *opcje)// Funkcja tworzaca negatyw obrazu
{
	printf("Rozpoczynanie Tworzenia Negatywu\r\n");
	if (opcje->kolor[0] || Obrazek->czykolorowy == 0) {
		for (int i = 0; i < Obrazek->rozmiary; i++)
		{
			for (int j = 0; j < Obrazek->rozmiarx; j++)
			{
				Obrazek->pierwszy[i * Obrazek->rozmiarx + j].czerwony = Obrazek->MaxWartosc - Obrazek->pierwszy[i * Obrazek->rozmiarx + j].czerwony;
			}
		}
	}
	if (opcje->kolor[1]) {
		for (int i = 0; i < Obrazek->rozmiary; i++)
		{
			for (int j = 0; j < Obrazek->rozmiarx; j++)
			{
				Obrazek->pierwszy[i * Obrazek->rozmiarx + j].zielony = Obrazek->MaxWartosc - Obrazek->pierwszy[i * Obrazek->rozmiarx + j].zielony;
			}
		}
	}
	if (opcje->kolor[2]) {
		for (int i = 0; i < Obrazek->rozmiary; i++)
		{
			for (int j = 0; j < Obrazek->rozmiarx; j++)
			{
				Obrazek->pierwszy[i * Obrazek->rozmiarx + j].niebieski = Obrazek->MaxWartosc - Obrazek->pierwszy[i * Obrazek->rozmiarx + j].niebieski;
			}
		}
	}
	printf("Tworzenie Negatywu Zakonczone\r\n\r\n");
}
void konwolucja(obraz *Obrazek, t_opcje *opcje) //Funkcja przeprowadzajaca filtrowanie za pomoca podanej macierzy konwolucji
{
	printf("Rozpoczynam Konwolucje:\r\n");
	pixel* Tymczasowy;
	Tymczasowy = malloc(sizeof(pixel) * Obrazek->rozmiarx * Obrazek->rozmiary);
	if (opcje->kolor[0] || Obrazek->czykolorowy == 0) {
		for (int i = 0; i < Obrazek->rozmiary; i++) for (int j = 0; j < Obrazek->rozmiarx; j++) Tymczasowy[i * Obrazek->rozmiarx + j].czerwony = 0;
		for (int i = 1; i < Obrazek->rozmiary - 1; i++)
		{
			for (int j = 1; j < Obrazek->rozmiarx - 1; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					for (int l = 0; l < 3; l++)
					{
						Tymczasowy[i * Obrazek->rozmiarx + j].czerwony = Tymczasowy[i * Obrazek->rozmiarx + j].czerwony + Obrazek->pierwszy[(i + k - 1) * Obrazek->rozmiarx + j + l - 1].czerwony * opcje->maciez[k][l];
					}
				}
			}
		}
		int LMax = 0, LMin = Tymczasowy[1].czerwony;
		for (int i = 1; i < Obrazek->rozmiary - 1; i++)
		{
			for (int j = 1; j < Obrazek->rozmiarx - 1; j++)
			{
				if (LMax < Tymczasowy[i * Obrazek->rozmiarx + j].czerwony) LMax = Tymczasowy[i * Obrazek->rozmiarx + j].czerwony;
				if (LMin > Tymczasowy[i * Obrazek->rozmiarx + j].czerwony) LMin = Tymczasowy[i * Obrazek->rozmiarx + j].czerwony;
			}
		}
		if (LMin == LMax)
		{
			int Suma = 0;
			for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) Suma = Suma + opcje->maciez[i][j];
			if (Suma == 0)
			{
				printf("Tablica Pusta\r\n");
				for (int i = 1; i < Obrazek->rozmiary - 1; i++) for (int j = 1; j < Obrazek->rozmiarx - 1; j++) Tymczasowy[i * Obrazek->rozmiarx + j].czerwony = 0;
			}
			else
			{
				for (int i = 1; i < Obrazek->rozmiary - 1; i++) for (int j = 1; j < Obrazek->rozmiarx - 1; j++) Tymczasowy[i * Obrazek->rozmiarx + j].czerwony = Tymczasowy[i * Obrazek->rozmiarx + j].czerwony / Suma;
				printf("Tablica 1 kolorowa\r\n");
			}
		}
		else
		{
			for (int i = 1; i < Obrazek->rozmiary - 1; i++) for (int j = 1; j < Obrazek->rozmiarx - 1; j++) Tymczasowy[i * Obrazek->rozmiarx + j].czerwony = (Tymczasowy[i * Obrazek->rozmiarx + j].czerwony - LMin) * Obrazek->MaxWartosc / (LMax - LMin);
		}
		for (int i = 1; i < Obrazek->rozmiary - 1; i++) for (int j = 1; j < Obrazek->rozmiarx - 1; j++) Obrazek->pierwszy[i * Obrazek->rozmiarx + j].czerwony = Tymczasowy[i * Obrazek->rozmiarx + j].czerwony;
	}
	if (opcje->kolor[1]) {
		for (int i = 0; i < Obrazek->rozmiary; i++) for (int j = 0; j < Obrazek->rozmiarx; j++) Tymczasowy[i * Obrazek->rozmiarx + j].zielony = 0;
		for (int i = 1; i < Obrazek->rozmiary - 1; i++)
		{
			for (int j = 1; j < Obrazek->rozmiarx - 1; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					for (int l = 0; l < 3; l++)
					{
						Tymczasowy[i * Obrazek->rozmiarx + j].zielony = Tymczasowy[i * Obrazek->rozmiarx + j].zielony + Obrazek->pierwszy[(i + k - 1) * Obrazek->rozmiarx + j + l - 1].zielony * opcje->maciez[k][l];
					}
				}
			}
		}
		int LMax = 0, LMin = Tymczasowy[1].zielony;
		for (int i = 1; i < Obrazek->rozmiary - 1; i++)
		{
			for (int j = 1; j < Obrazek->rozmiarx - 1; j++)
			{
				if (LMax < Tymczasowy[i * Obrazek->rozmiarx + j].zielony) LMax = Tymczasowy[i * Obrazek->rozmiarx + j].zielony;
				if (LMin > Tymczasowy[i * Obrazek->rozmiarx + j].zielony) LMin = Tymczasowy[i * Obrazek->rozmiarx + j].zielony;
			}
		}
		if (LMin == LMax)
		{
			int Suma = 0;
			for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) Suma = Suma + opcje->maciez[i][j];
			if (Suma == 0)
			{
				printf("Tablica Pusta\r\n");
				for (int i = 1; i < Obrazek->rozmiary - 1; i++) for (int j = 1; j < Obrazek->rozmiarx - 1; j++) Tymczasowy[i * Obrazek->rozmiarx + j].zielony = 0;
			}
			else
			{
				for (int i = 1; i < Obrazek->rozmiary - 1; i++) for (int j = 1; j < Obrazek->rozmiarx - 1; j++) Tymczasowy[i * Obrazek->rozmiarx + j].zielony = Tymczasowy[i * Obrazek->rozmiarx + j].zielony / Suma;
				printf("Tablica 1 kolorowa\r\n");
			}
		}
		else
		{
			for (int i = 1; i < Obrazek->rozmiary - 1; i++) for (int j = 1; j < Obrazek->rozmiarx - 1; j++) Tymczasowy[i * Obrazek->rozmiarx + j].zielony = (Tymczasowy[i * Obrazek->rozmiarx + j].zielony - LMin) * Obrazek->MaxWartosc / (LMax - LMin);
		}
		for (int i = 1; i < Obrazek->rozmiary - 1; i++) for (int j = 1; j < Obrazek->rozmiarx - 1; j++) Obrazek->pierwszy[i * Obrazek->rozmiarx + j].zielony = Tymczasowy[i * Obrazek->rozmiarx + j].zielony;

	}
	if (opcje->kolor[2]) {
		for (int i = 0; i < Obrazek->rozmiary; i++) for (int j = 0; j < Obrazek->rozmiarx; j++) Tymczasowy[i * Obrazek->rozmiarx + j].niebieski = 0;
		for (int i = 1; i < Obrazek->rozmiary - 1; i++)
		{
			for (int j = 1; j < Obrazek->rozmiarx - 1; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					for (int l = 0; l < 3; l++)
					{
						Tymczasowy[i * Obrazek->rozmiarx + j].niebieski = Tymczasowy[i * Obrazek->rozmiarx + j].niebieski + Obrazek->pierwszy[(i + k - 1) * Obrazek->rozmiarx + j + l - 1].niebieski * opcje->maciez[k][l];
					}
				}
			}
		}
		int LMax = 0, LMin = Tymczasowy[1].niebieski;
		for (int i = 1; i < Obrazek->rozmiary - 1; i++)
		{
			for (int j = 1; j < Obrazek->rozmiarx - 1; j++)
			{
				if (LMax < Tymczasowy[i * Obrazek->rozmiarx + j].niebieski) LMax = Tymczasowy[i * Obrazek->rozmiarx + j].niebieski;
				if (LMin > Tymczasowy[i * Obrazek->rozmiarx + j].niebieski) LMin = Tymczasowy[i * Obrazek->rozmiarx + j].niebieski;
			}
		}
		if (LMin == LMax)
		{
			int Suma = 0;
			for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) Suma = Suma + opcje->maciez[i][j];
			if (Suma == 0)
			{
				printf("Tablica Pusta\r\n");
				for (int i = 1; i < Obrazek->rozmiary - 1; i++) for (int j = 1; j < Obrazek->rozmiarx - 1; j++) Tymczasowy[i * Obrazek->rozmiarx + j].niebieski = 0;
			}
			else
			{
				for (int i = 1; i < Obrazek->rozmiary - 1; i++) for (int j = 1; j < Obrazek->rozmiarx - 1; j++) Tymczasowy[i * Obrazek->rozmiarx + j].niebieski = Tymczasowy[i * Obrazek->rozmiarx + j].niebieski / Suma;
				printf("Tablica 1 kolorowa\r\n");
			}
		}
		else
		{
			for (int i = 1; i < Obrazek->rozmiary - 1; i++) for (int j = 1; j < Obrazek->rozmiarx - 1; j++) Tymczasowy[i * Obrazek->rozmiarx + j].niebieski = (Tymczasowy[i * Obrazek->rozmiarx + j].niebieski - LMin) * Obrazek->MaxWartosc / (LMax - LMin);
		}
		for (int i = 1; i < Obrazek->rozmiary - 1; i++) for (int j = 1; j < Obrazek->rozmiarx - 1; j++) Obrazek->pierwszy[i * Obrazek->rozmiarx + j].niebieski = Tymczasowy[i * Obrazek->rozmiarx + j].niebieski;

	}
	printf("Kowolucja Zakonczona\r\n");
}
void doszarosci(obraz* Obrazek, t_opcje *opcje) { // Funkcja konwertujaca obraz kolorowy .ppm do obrazu czarnobialego .pgm
	printf("Rozpoczynanie Konwersji do szarosci\r\n");
	for (int i = 0; i < Obrazek->rozmiary; i++)
	{
		for (int j = 0; j < Obrazek->rozmiarx; j++)
		{
			Obrazek->pierwszy[i * Obrazek->rozmiarx + j].czerwony = (Obrazek->pierwszy[i * Obrazek->rozmiarx + j].czerwony + Obrazek->pierwszy[i * Obrazek->rozmiarx + j].zielony + Obrazek->pierwszy[i * Obrazek->rozmiarx + j].niebieski) / 3;
			Obrazek->pierwszy[i * Obrazek->rozmiarx + j].zielony = 0;
			Obrazek->pierwszy[i * Obrazek->rozmiarx + j].niebieski = 0;
		}
	}
	Obrazek->czykolorowy = 0;
	printf("Konwersja do szarosci Zakonczona\r\n");
}