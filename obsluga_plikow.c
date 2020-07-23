#include "obsluga_plikow.h"


int czytaj(FILE *plik_we,obraz *obr) {
  char buf[DL_LINII];      /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;                /* zmienna pomocnicza do czytania komentarzy */
  int koniec=0;            /* czy napotkano koniec danych w pliku */
  int i,j,k;

  /*Sprawdzenie czy podano prawid³owy uchwyt pliku */
  if (plik_we==NULL) {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    return(0);
  }

  /* Sprawdzenie "numeru magicznego" - powinien byæ P2 */
  if (fgets(buf,DL_LINII,plik_we)==NULL)   /* Wczytanie pierwszej linii pliku do bufora */
    koniec=1;                              /* Nie udalo sie? Koniec danych! */

  if ( (buf[0]!='P') || (buf[1]!='2' && buf[1]!='3') || koniec) {  /* Czy jest magiczne "P2"? */
    fprintf(stderr,"Blad: To nie jest plik PGM\n");
    return(0);
  }

  obr->znak=buf[1];

  /* Pominiecie komentarzy */
  do {
    if ((znak=fgetc(plik_we))=='#') {         /* Czy linia rozpoczyna sie od znaku '#'? */
      if (fgets(buf,DL_LINII,plik_we)==NULL)  /* Przeczytaj ja do bufora                */
	koniec=1;                   /* Zapamietaj ewentualny koniec danych */
    }  else {
      ungetc(znak,plik_we);                   /* Gdy przeczytany znak z poczatku linii */
    }                                         /* nie jest '#' zwroc go                 */
  } while (znak=='#' && !koniec);   /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil koniec danych         */

  /* Pobranie wymiarow obrazu i liczby odcieni obr->odcieni */
  if (fscanf(plik_we,"%d %d %d",&obr->wymx,&obr->wymy,&obr->odcienie)!=3) {
    fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni obr->odcieni\n");
    return(0);
  }

  if(obr->znak=='2')
  {
  obr->obraz=malloc(obr->wymy*sizeof(int*));
  for (i=0;i<obr->wymy;i++)
    obr->obraz[i]=malloc(obr->wymx*sizeof(int));

  for (i=0;i<obr->wymy;i++) {
    for (j=0;j<obr->wymx;j++) {
      if (fscanf(plik_we,"%d",&(obr->obraz[i][j]))!=1) {
	fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
	return(0);
      }
    }
  }
  }


  if(obr->znak=='3')
  {
  obr->obraz_kolorowy=malloc(obr->wymy*sizeof(int**));

  for (i=0;i<obr->wymy;i++)
    obr->obraz_kolorowy[i]=malloc(obr->wymx*sizeof(int*));

      for (i=0;i<obr->wymy;i++)
        for (j=0;j<obr->wymx;j++)
          obr->obraz_kolorowy[i][j]=malloc(3*sizeof(int));

  for (i=0;i<obr->wymy;i++) {
    for (j=0;j<obr->wymx;j++) {
        for (k=0;k<3;k++) {
      if (fscanf(plik_we,"%d",&(obr->obraz_kolorowy[i][j][k]))!=1) {
	fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
	return(0);
      }
     }
    }
  }
  }

  return obr->wymx*obr->wymy;   /* Czytanie zakonczone sukcesem    */
}                       /* Zwroc liczbe wczytanych pikseli */

void wyswietl(char *n_pliku) {
  char polecenie[DL_LINII];      /* bufor pomocniczy do zestawienia polecenia */

  strcpy(polecenie,"display ");  /* konstrukcja polecenia postaci */
  strcat(polecenie,n_pliku);     /* display "nazwa_pliku" &       */
  strcat(polecenie," &");
  printf("%s\n",polecenie);      /* wydruk kontrolny polecenia */
  system(polecenie);             /* wykonanie polecenia        */
}

int zapisz(FILE*plik, obraz *obr)
{
    int i,j,k;
    fprintf(plik,"P%c\n",obr->znak);
    fprintf(plik,"%d %d\n", obr->wymx,obr->wymy);


    if(obr->znak=='2')
    {
    fprintf(plik,"%d\n",obr->odcienie);
         for (i=0; i<obr->wymy; i++) {
         for (j=0; j<obr->wymx; j++) {
                fprintf(plik,"%d ",obr->obraz[i][j]);
    }
    fprintf(plik,"\n");
    }
    }
        if(obr->znak=='3')
    {
    fprintf(plik,"%d\n",obr->odcienie);
         for (i=0; i<obr->wymy; i++) 
         {
         for (j=0; j<obr->wymx; j++) 
         {
         for (k=0; k<3; k++) 
                 {
                fprintf(plik,"%d ",obr->obraz_kolorowy[i][j][k]);
                }
          }
          }
    }
}
