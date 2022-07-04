#pragma once
// Struktura przechowujaca cechy obrazu:

// Obiekt pixel przechowuje 3 wartosci dla kazdego z kolorow, w razie obrazu czarno-bialego wartosci sa takie same dla wszystkich kolorow
typedef struct
{
	int czerwony;
	int niebieski;
	int zielony;
}pixel;
// Obiekt obraz przechowuje informacje o tym czy obraz jest kolorowy, rozmiary obrazu, jego ilosc odcieni oraz wskaznik na na pierwszy pixel obrazu
typedef struct
{
	int czykolorowy;
	int rozmiarx;
	int rozmiary;
	int MaxWartosc;
	pixel* pierwszy;
}obraz;
// Podczas inicjowania obiektu na poczatku jest lokowana odpowiednia ilosc pamieci.
// Nastepnie kazemy wskaznikowi pierwszy wskazywac na to miejsce,
// twozac w danym miejscu w pamieci tablice obiektow pixel gdzie kazdy jeden przechowuje 3 wartosci dla kazdego z 3 kolorow.
// Jest to inicjowane podczas wczytywania pliku w funkcji pisz() w pliku Obrazy2Main.c