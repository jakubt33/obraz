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
void zapisz1(element *lista);
void zapisz2(element * lista, int polecenie);


void menu(element *lista)
{
    int czy_konczyc = NIE;

    while( czy_konczyc == NIE )
    {
        printf("dostępne funkcje:\n"
               "1 - Dodaj obraz\n"
               "2 - Wyswietl bazę obrazów\n"
               "31 - Odbij poziomo\n"
               "32 - Odbij pionowo\n"
               "33 - Pociemnij\n"
               "34 - Rozjasnij\n"
               "35 - Black&White\n"
               "36 - Znajdz kontury\n"
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

                lista = wczytajobraz(lista);


                //free(temp); wlaczneie tego powoduje nie dopisywanie kolejnych obrazow do listy, tyko lacza sie komentarze
                //kopie = zapisz_bufor(kopie, temp);
                //zwolnij_tablice(temp);
                break;
            }
            case 2:
            {
                wyswietl(lista);
                break;
            }
            case 5:
            {
                printf("zapis zmienionych obrazkow\n");
                zapisz1(lista);
                break;
            }
            case 6:
            {
                printf("kończę działanie programu\n");
                czy_konczyc = TAK;
                break;
            }
            default:
            {
                edycja(lista, komenda);
            }
            }
        }
    }
}
void zapisz1(element *lista)
{
    while(lista!=NULL)
    {
        if ( lista->czy_zmieniony == TAK)
        {
            printf("co zrobic z tym obrazem: %s?\n1 - nadpisz\t2 - zapisz jako\t3 - nie zapisuj\t", lista->nazwa);
            int polecenie=0;
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
                    printf("nadpisuje\n");
                    zapisz2(lista, polecenie);
                    break;
                }
                case 2:
                {
                    printf("zapisjue jako\n");
                    zapisz2(lista, polecenie);
                    break;
                }
                case 3:
                {
                    lista->czy_zmieniony = NIE;
                    printf("nie zapisuje\n");
                    break;
                }
                }
                //printf("\n%d. nazwa obrazu to %s\n", lista->numer, lista->nazwa);
            }
        }
        lista=lista->next;
    }
}
void zapisz2(element * lista, int polecenie)
{

    FILE *pFile;
    int dzialaj = NIE;
    char nazwa[MAXNAZWA];
    if(polecenie == 1)
    {
        strcpy(nazwa, lista->nazwa);
        printf("zapisz");
        dzialaj = TAK;
    }
    else if(polecenie ==2)
    {
        printf("podaj nazwe pod jaką chcesz zapiszać ten obraz: ");
        if ( scanf("%19s", nazwa) != 1 )
            error();
        else dzialaj = TAK;
    }
    if(dzialaj == TAK)
    {
        pFile = fopen( nazwa , "wat");

        if(pFile==NULL)
        {
            perror("blad otwarcia pliku");
        }
        else
        {
            printf("zaczynam zapis...\n");

            fprintf(pFile, "%s\n", lista->type);
            fprintf(pFile, "%s", lista->comment);
            fprintf(pFile, "%d %d\n", lista->wymx, lista->wymy);
            fprintf(pFile, "%d\n", lista->odcienie);

            /*
            printf( "%s\n", lista->type);
            printf( "%d %d\n", lista->wymx, lista->wymy);
            printf( "%d\n", lista->odcienie);
            printf( "%s", lista->comment);

            for(licznik_y=0; licznik_y<lista->wymiary[WYM_Y]; licznik_y++)
            {
                for(licznik_x=0; licznik_x<lista->wymiary[WYM_X]; licznik_x++)
                printf("%d ", lista->obraz[licznik_x][licznik_y]);
            }
            */

            int licznik_x=0, licznik_y=0;
            for(licznik_y=0; licznik_y<lista->wymy; licznik_y++)
            {
                for(licznik_x=0; licznik_x<lista->wymx; licznik_x++)
                    fprintf(pFile, "%d ", lista->obraz[licznik_x][licznik_y]);
            }

            fflush(pFile);
            fclose(pFile);
            lista->czy_zmieniony = NIE;
        }
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
            printf("wymiary to %d na %d\n", first->wymx, first->wymy);
            printf("ilosc odcieni to %d\n", first->odcienie);
            printf("komentarz to:\n%s\n", first->comment);


            /*int licznik_x=0, licznik_y=0;
            for(licznik_y=0; licznik_y<first->wymiary[WYM_Y]; licznik_y++)
            {
                printf("\n");
                for(licznik_x=0; licznik_x<first->wymiary[WYM_X]; licznik_x++)
                    printf("%d ", first->obraz[licznik_x][licznik_y]);
            }
            printf("\n");
            */

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

