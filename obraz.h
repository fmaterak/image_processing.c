#ifndef OBRAZ_H
#define OBRAZ_H
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"struktura.h"

void konwersja(obraz *obr);

void negatyw(obraz *obr);

void konturowanie(obraz *obr);

void progowanie(obraz *obr, int prog);

void negatyw_kolor(obraz *obr,char kolor);

void konturowanie_kolor(obraz *obr,char kolor);

void progowanie_kolor(obraz *obr, int prog,char kolor);

#endif
