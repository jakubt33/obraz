#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#define NIE 0
#define TAK 1

#include <stdlib.h>
#include "init.h"
#include "odczyt.h"
#include "edit.h"


void menu(element *lista);
void wyswietl(element *);
element * usun(element *);
void zapisz(element *lista);
void nadpisz(element * lista);


void menu(element *lista)
{
    int czy_konczyc = NIE;

    while( czy_konczyc == NIE )
    {
        printf("dostępne funkcje:\n"
               "1 - Dodaj obraz\n"
               "2 - Wyswietl bazę obrazów\n"
               "31 - Lustrzane odbicie\n"
               "32 - Rozjaśnij\n"
               "33 - Przyciemnij\n"
               "34 - Kafelki\n"
               "35 - Rozmycie Gaussa\n"
               "41 - Obrót w prawo\n"
               "42 - Obrót w lewo\n"
               "43 - Obrót o 180\n"
               "44 - Zmniejsz obraz\n"
               "5 - Zapisz zmienione obrazy\n"
               "6 - Wyjdź\n");
        int komenda = 0 ;
        if( scanf("%19d", &komenda) != 1)
        {
            error();
        }
        else
        {
            switch (komenda)
            {
            case 1:
            {

                element *temp;
                temp=(element*)malloc(sizeof(element));


                temp = wczytajobraz(temp);

                lista = zapisz_bufor(lista, temp);
                //kopie = zapisz_bufor(kopie, temp);
                //zwolnij_tablice(temp);
                break;
            }
            case 2:
            {
                wyswietl(lista);
                break;
            }
            case 31:
            {
                lustrzane_odbicie( lista );
                break;
            }
            case 5:
            {
                printf("zapis zmienionych obrazkow\n");
                zapisz(lista);
                break;
            }
            case 6:
            {
                printf("kończę działanie programu\n");
                czy_konczyc = TAK;
                break;
            }
            }
        }
    }
}
void zapisz(element *lista)
{
    while(lista!=NULL)
    {
        if ( lista->czy_zmieniony == TAK)
        {
            printf("co zrobic z tym obrazem: %s?\n1 - nadpisz\t2 - zapisz jako\t3 - nie zapisuj\t", lista->nazwa);
            char polecenie=0;
            if ( scanf("%d", &polecenie) != 1 )
            {
                error();
            }
            else
            {
                switch (polecenie)
                {
                    case 1:
                    {
                        //nadpisanie kopii na liste
                        printf("nadpisuje\n");
                        nadpisz(lista);

                        lista->czy_zmieniony = NIE;


                        break;
                    }
                    case 2:
                    {
                        printf("zapisjue jako\n");
                        break;
                    }
                    case 3:
                    {
                        printf("nie zapisuje\n");
                        break;
                    }
                }
                printf("\n%d. nazwa obrazu to %s\n", lista->numer, lista->nazwa);
            }
        }
        lista=lista->next;
    }
}
void nadpisz(element * lista)
{
    FILE *pFile;
    pFile = fopen( lista->nazwa , "wat");

    if(pFile==NULL)
    {
        perror("blad otwarcia pliku");
    }
    else
    {
        printf("zaczynam nadpisywac\n");
        fprintf(pFile, "%s\n", lista->type);
        fprintf(pFile, "%s", lista->comment);
        fprintf(pFile, "%d %d\n", lista->wymiary[WYM_X], lista->wymiary[WYM_Y]);
        fprintf(pFile, "%d\n", lista->odcienie);

        int licznik_x=0, licznik_y=0;
        for(licznik_y=0; licznik_y<lista->wymiary[WYM_Y]; licznik_y++)
        {
            for(licznik_x=0; licznik_x<lista->wymiary[WYM_X]; licznik_x++)
            printf("%d ", lista->obraz[licznik_x][licznik_y]);
        }

        for(licznik_y=0; licznik_y<lista->wymiary[WYM_Y]; licznik_y++)
        {
            for(licznik_x=0; licznik_x<lista->wymiary[WYM_X]; licznik_x++)
            fprintf(pFile, "%d ", lista->obraz[licznik_x][licznik_y]);
       }
        fflush(pFile);
        fclose(pFile);
    }
}
void wyswietl(element *first)
{
    if(first==NULL)
    {
        printf("lista jest pusta\n");
    }
    else
    {
        do
        {
            printf("\n%d. nazwa obrazu to %s", first->numer, first->nazwa);
            if(first->czy_zmieniony == TAK) printf("\nobrazek jest zmienieniony\n");
            else printf("\nobrazek jest niezmienieniony\n");
            printf("typ obrazu to %s\n", first->type);
            printf("wymiary to %d na %d\n", first->wymiary[0], first->wymiary[1]);
            printf("ilosc odcieni to %d\n", first->odcienie);
            printf("komentarz to:\n%s\n", first->comment);

            int licznik_x=0, licznik_y=0;
            for(licznik_y=0; licznik_y<first->wymiary[WYM_Y]; licznik_y++)
            {
                printf("\n");
                for(licznik_x=0; licznik_x<first->wymiary[WYM_X]; licznik_x++)
                    printf("%d ", first->obraz[licznik_x][licznik_y]);
            }
            printf("\n");

            first=first->next; //modyfikuijmy tylko kopie wskaznika!

        }
        while(first!=NULL);
    }
}
element * usun(element *first)
{
    if(first==NULL)
    {
        printf("\nlista juz jest pusta\n");
        return NULL;
    }
    usun(first->next);
    free(first);
    return NULL;
}

#endif // MENU_H_INCLUDED

