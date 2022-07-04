#pragma once
#include "struktura.h"
#include "OpcjeWywolania.h"

void doszarosci(obraz* Obrazek, t_opcje *opcje);
void rozciaganie(obraz* Obrazek, t_opcje *opcje);
void rozmywanie(obraz* Obrazek, t_opcje *opcje);
void konturowanie(obraz* Obrazek, t_opcje *opcje);
void poziomy(obraz* Obrazek, t_opcje *opcje);
void gammma(obraz* Obrazek, t_opcje *opcje);
void progowanie(obraz* Obrazek, t_opcje *opcje);
void negatyw(obraz* Obrazek, t_opcje *opcje);
void konwolucja(obraz* Obrazek, t_opcje *opcje);