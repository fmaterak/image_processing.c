#include "obraz.h"



void negatyw(obraz *obr)
{
    int i,j;
    for (i=0; i<obr->wymy; i++)
    {
        for (j=0; j<obr->wymx; j++)
        {
            obr->obraz[i][j]=obr->odcienie-obr->obraz[i][j];
        }
    }
}

void konturowanie(obraz *obr)
{
    int i,j;
    for(i=0; i<obr->wymy-1; i++)
    {
        for(j=0; j<obr->wymx-1; j++)
        {
            obr->obraz[i][j]=abs(obr->obraz[i+1][j]-obr->obraz[i][j])+abs(obr->obraz[i][j+1]-obr->obraz[i][j]);
        }
    }
}

void progowanie(obraz *obr, int prog)
{
    int i,j;
    for(i=0; i<obr->wymy; i++)
    {
        for(j=0; j<obr->wymx; j++)
        {
            if(obr->obraz[i][j]<=(prog*obr->odcienie/100))
                obr->obraz[i][j]=0;
            else
                obr->obraz[i][j]=obr->odcienie;
        }
    }
}

void konwersja(obraz *obr)
{
    int i,j,k;
    int suma=0;
    obr->znak='2';
    obr->obraz=malloc(obr->wymy*sizeof(int*));
    for (i=0; i<obr->wymy; i++)
        obr->obraz[i]=malloc(obr->wymx*sizeof(int));


    for(i=0; i<obr->wymy; i++)
    {
        for(j=0; j<obr->wymx; j++)
        {
            for(k=0; k<3; k++)
                suma+=obr->obraz_kolorowy[i][j][k];

            obr->obraz[i][j]=suma/3.0;
            suma=0;
        }

       
    }


}
    void negatyw_kolor(obraz *obr,char kolor)
    {
        
        int i,j;
        for (i=0; i<obr->wymy; i++)
        {
            for (j=0; j<obr->wymx; j++)
            {
                if(kolor == 'r')
                    obr->obraz_kolorowy[i][j][0]=obr->odcienie- obr->obraz_kolorowy[i][j][0];
                else if(kolor == 'g')
                    obr->obraz_kolorowy[i][j][1]=obr->odcienie-obr->obraz_kolorowy[i][j][1];
                else if(kolor == 'b')
                    obr->obraz_kolorowy[i][j][2]=obr->odcienie-obr->obraz_kolorowy[i][j][2];
            }
        }

    }

    void konturowanie_kolor(obraz *obr,char kolor)
    {
        int i,j;
        for(i=0; i<obr->wymy-1; i++)
        {
            for(j=0; j<obr->wymx-1; j++)
            {
                if(kolor == 'r')
                    obr->obraz_kolorowy[i][j][0]=abs(obr->obraz_kolorowy[i+1][j][0]-obr->obraz_kolorowy[i][j][0])+abs(obr->obraz_kolorowy[i][j+1][0]-obr->obraz_kolorowy[i][j][0]);
                    else if(kolor == 'g')
                    obr->obraz_kolorowy[i][j][1]=abs(obr->obraz_kolorowy[i+1][j][1]-obr->obraz_kolorowy[i][j][1])+abs(obr->obraz_kolorowy[i][j+1][1]-obr->obraz_kolorowy[i][j][1]);
                        else if(kolor == 'b')
                        obr->obraz_kolorowy[i][j][2]=abs(obr->obraz_kolorowy[i+1][j][2]-obr->obraz_kolorowy[i][j][2])+abs(obr->obraz_kolorowy[i][j+1][2]-obr->obraz_kolorowy[i][j][2]);
                        }
        }

    }

    void progowanie_kolor(obraz *obr, int prog,char kolor)
    {

            int i,j;
    for(i=0; i<obr->wymy; i++)
    {
        for(j=0; j<obr->wymx; j++)
        {
            if(kolor== 'r')
            {
                            if(obr->obraz_kolorowy[i][j][0]<=(prog*obr->odcienie/100))
                obr->obraz_kolorowy[i][j][0]=0;
            else
                obr->obraz_kolorowy[i][j][0]=obr->odcienie;
            }
                        if(kolor== 'g')
            {
                            if(obr->obraz_kolorowy[i][j][1]<=(prog*obr->odcienie/100))
                obr->obraz_kolorowy[i][j][1]=0;
            else
                obr->obraz_kolorowy[i][j][1]=obr->odcienie;
            }
                        if(kolor== 'b')
            {
                            if(obr->obraz_kolorowy[i][j][2]<=(prog*obr->odcienie/100))
                obr->obraz_kolorowy[i][j][2]=0;
            else
                obr->obraz_kolorowy[i][j][2]=obr->odcienie;
            }

        }
    }

    }

