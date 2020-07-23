#ifndef OBSLUGA_PLIKOW_H
#define OBSLUGA_PLIKOW_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"struktura.h"

#define DL_LINII 1024

int czytaj(FILE *plik_we,obraz *obr);

void wyswietl(char *n_pliku);

int zapisz(FILE*plik, obraz *obr);

#endif
