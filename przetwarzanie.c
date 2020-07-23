#include "obraz.h"
#include "obsluga_plikow.h"

#define W_OK 0                   /* wartosc oznaczajaca brak bledow */
#define B_NIEPOPRAWNAOPCJA -1    /* kody bledow rozpoznawania opcji */
#define B_BRAKNAZWY   -2
#define B_BRAKWARTOSCI  -3
#define B_BRAKPLIKU   -4

/* strukura do zapamietywania opcji podanych w wywolaniu programu */
typedef struct {
  FILE *plik_we, *plik_wy;        /* uchwyty do pliku wej. i wyj. */
  int negatyw,progowanie,konturowanie,wyswietlenie, std_wejscie,std_wyjscie;      /* opcje */
  int w_progu;              /* wartosc progu dla opcji progowanie */
  char w_kolor;
} w_opcje;

/*******************************************************/
/* Funkcja inicjuje strukture wskazywana przez wybor   */
/* PRE:                                                */
/*      poprawnie zainicjowany argument wybor (!=NULL) */
/* POST:                                               */
/*      "wyzerowana" struktura wybor wybranych opcji   */
/*******************************************************/

void wyzeruj_opcje(w_opcje * wybor) {
  wybor->plik_we=NULL;
  wybor->plik_wy=NULL;
  wybor->negatyw=0;
  wybor->konturowanie=0;
  wybor->progowanie=0;
  wybor->wyswietlenie=0;
  wybor->std_wejscie=0;
  wybor->std_wyjscie=0;
}

/************************************************************************/
/* Funkcja rozpoznaje opcje wywolania programu zapisane w tablicy argv  */
/* i zapisuje je w strukturze wybor                                     */
/* Skladnia opcji wywolania programu                                    */
/*         program {[-i nazwa] [-o nazwa] [-p liczba] [-n] [-r] [-d] }  */
/* Argumenty funkcji:                                                   */
/*         argc  -  liczba argumentow wywolania wraz z nazwa programu   */
/*         argv  -  tablica argumentow wywolania                        */
/*         wybor -  struktura z informacjami o wywolanych opcjach       */
/* PRE:                                                                 */
/*      brak                                                            */
/* POST:                                                                */
/*      funkcja otwiera odpowiednie pliki, zwraca uchwyty do nich       */
/*      w strukturze wybór, do tego ustawia na 1 pola, ktore            */
/*	poprawnie wystapily w linii wywolania programu,                 */
/*	pola opcji nie wystepujacych w wywolaniu ustawione sa na 0;     */
/*	zwraca wartosc W_OK, gdy wywolanie bylo poprawne                */
/*	lub kod bledu zdefiniowany stalymi B_* (<0)                     */
/* UWAGA:                                                               */
/*      funkcja nie sprawdza istnienia i praw dostepu do plikow         */
/*      w takich przypadkach zwracane uchwyty maja wartosc NULL         */
/************************************************************************/

int przetwarzaj_opcje(int argc, char **argv, w_opcje *wybor) {
  int i, prog;
  char *nazwa_pliku_we, *nazwa_pliku_wy;
  char kolor;
  wyzeruj_opcje(wybor);
  wybor->plik_wy=stdout;        /* na wypadek gdy nie podano opcji "-o" */

  for (i=1; i<argc; i++) {
    if (argv[i][0] != '-')  /* blad: to nie jest opcja - brak znaku "-" */
      return B_NIEPOPRAWNAOPCJA;
    switch (argv[i][1]) {
    case 'i': {                 /* opcja z nazwa pliku wejsciowego */
      if (++i<argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
	nazwa_pliku_we=argv[i];
	if (strcmp(nazwa_pliku_we,"-")==0) /* gdy nazwa jest "-"        */
	  {wybor->std_wejscie=1; 
printf("sasasas");
}          
	else                               /* otwieramy wskazany plik   */
	  wybor->plik_we=fopen(nazwa_pliku_we,"r");
      } else
	return B_BRAKNAZWY;                   /* blad: brak nazwy pliku */
      break;
    }
    case 'o': {                 /* opcja z nazwa pliku wyjsciowego */
      if (++i<argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
	nazwa_pliku_wy=argv[i];
	if (strcmp(nazwa_pliku_wy,"-")==0)/* gdy nazwa jest "-"         */
	  wybor->std_wyjscie=1;           /* ustwiamy wyjscie na stdout */
	else                              /* otwieramy wskazany plik    */
	  wybor->plik_wy=fopen(nazwa_pliku_wy,"w");
      } else
	return B_BRAKNAZWY;                   /* blad: brak nazwy pliku */
      break;
    }
    case 'p': {
      if (++i<argc) { /* wczytujemy kolejny argument jako wartosc progu */
	if (sscanf(argv[i],"%d",&prog)==1) {
	  wybor->progowanie=1;
	  wybor->w_progu=prog;
	} else
	  return B_BRAKWARTOSCI;     /* blad: niepoprawna wartosc progu */
      } else
	return B_BRAKWARTOSCI;             /* blad: brak wartosci progu */
      break;
    }
    case 'n': {                 /* mamy wykonac negatyw */
      wybor->negatyw=1;
      break;
    }
    case 'k': {                 /* mamy wykonac konturowanie */
      wybor->konturowanie=1;
      break;
    }
    case 'd': {                 /* mamy wyswietlic obraz */
      wybor->wyswietlenie=1;
      break;
    }
        case 'm': {
    if (++i<argc) {
	if (sscanf(argv[i],"%c",&kolor)==1) {
	  if(kolor =='s' || kolor =='r' || kolor =='g' || kolor =='b')
	  wybor->w_kolor=kolor;
	  else
	  return B_NIEPOPRAWNAOPCJA;

	} else
	  return B_BRAKWARTOSCI;
      } else
	return B_BRAKWARTOSCI;
      break;
    }
    default:
      return B_NIEPOPRAWNAOPCJA;
    } /*koniec switch */
  } /* koniec for */

  if (wybor->plik_we!=NULL || wybor->std_wejscie)     /* ok: wej. strumien danych zainicjowany */
    return W_OK;
  else
    return B_BRAKPLIKU;         /* blad:  nie otwarto pliku wejsciowego  */
}




int main(int argc, char ** argv) {
  w_opcje opcje;
  obraz nowy;
  char nazwa[100];

if(przetwarzaj_opcje(argc,argv,&opcje)==0)
  {

if(opcje.std_wejscie)
{printf("/////////////// %d\n //////////////////////////",opcje.std_wejscie);
  
  printf("Podaj nazwe pliku:\n");
  scanf("%s",nazwa);
  opcje.plik_we=fopen(nazwa,"r");
}

if (opcje.plik_we != NULL) {       // co spowoduje zakomentowanie tego warunku
    czytaj(opcje.plik_we,&nowy);
    fclose(opcje.plik_we);
  }
  else
  {
      fprintf(stderr,"brak pliku");
  }




if(nowy.znak=='3' && opcje.w_kolor=='s')
{
     konwersja(&nowy);
}


if(nowy.znak=='2')
{
    if(opcje.negatyw)
 negatyw(&nowy);
if(opcje.konturowanie)
 konturowanie(&nowy);
if(opcje.progowanie)
 progowanie(&nowy,opcje.w_progu);
}
else
{
if(opcje.negatyw)
 negatyw_kolor(&nowy,opcje.w_kolor);
if(opcje.konturowanie)
 konturowanie_kolor(&nowy,opcje.w_kolor);
if(opcje.progowanie)
 progowanie_kolor(&nowy,opcje.w_progu,opcje.w_kolor);
}

if(opcje.std_wyjscie)
{
     printf("Podaj nazwe pliku:\n");
  scanf("%s",nazwa);
  opcje.plik_wy=fopen(nazwa,"w");
}

zapisz(opcje.plik_wy,&nowy) ;
    fclose(opcje.plik_wy);
}
else
{
    printf("-i [nazwa]/-  odczyt  pliku\n");
    printf("-n   negatyw\n");
    printf("-k   konturowanie\n");
    printf("-p [prog]  progowanie\n");
    printf("-m [kolor]  ustawienie koloru do przetwarzania r,g,b ustawienie opcji s to konwersja z ppm na pgm\n");
    printf("-o [nazwa]/-  zapis \n");

}
  return 0;
}
