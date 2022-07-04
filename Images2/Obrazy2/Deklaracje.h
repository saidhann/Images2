#pragma once
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
//Deklaracje funcji jak i innych wartosci pozwalajacych na dzialanie programu na Windowsie i Linuxie
#ifdef _WIN32
#include <conio.h>
#define CLS system("cls")
#define CZYLINUX 0
#else
#define CZYLINUX 1
#define CLS printf("\x1b\x63")
#endif
#define MAX 512 // Zmienna Globalna Okreslajaca maksymalna wielkosc tablicy
#define DL_LINII 1024