#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#define NIE 0
#define TAK 1

#include <stdlib.h>
#include <string.h>
#include "init.h"
#include "odczyt.h"
#include "edit.h"


void menu(element *lista);
void wyswietl(element *);
element * usun(element *);
void zapisz1(element *lista);
void zapisz2(element * lista, int polecenie);
void podpis();


void menu(element *lista)
{
    int komendy[] = {31,32,33,34,35,36,37,38,39,41,42,43,44,45}; //14
    int czy_konczyc = NIE;
    while( czy_konczyc == NIE )
    {
        printf("\n-------------------\n"
               "dostępne funkcje:\n"
               "1 - Dodaj obraz\n"
               "2 - Wyswietl bazę obrazów\n"
               "-------------------\n"
               "31 - Odbij poziomo\n"
               "32 - Odbij pionowo\n"
               "33 - Pociemnij\n"
               "34 - Rozjasnij\n"
               "35 - Black&White\n"
               "36 - Znajdz kontury\n"
               "37 - Zmień kontrast\n"
               "38 - Rozmycie\n"
               "39 - Negatyw\n" //dorobic
               "-------------------\n"
               "41 - Obrót w prawo o 90 stopni\n"
               "42 - Obrót w lewo o 90 stopni\n"
               "43 - Obrót o 180\n"
               "44 - Przytnij obraz\n"
               "45 - Rozciągnij\n"
               "-------------------\n"
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
                int licznik=0, czy_znaleziono = NIE;
                for(licznik=0;licznik<14;licznik++)
                {
                    if(komendy[licznik] == komenda)
                        czy_znaleziono = TAK;
                }
                if(czy_znaleziono == TAK)
                    edycja(lista, komenda);
                else printf("nie ma takiej opcji\n");

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
                    printf("nadpisuję...\n");
                    zapisz2(lista, polecenie);
                    break;
                }
                case 2:
                {
                    printf("zapisuję jako...\n");
                    zapisz2(lista, polecenie);
                    break;
                }
                case 3:
                {
                    lista->czy_zmieniony = NIE;
                    printf("nie zapisuję\n");
                    break;
                }
                }
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
        dzialaj = TAK;
    }
    else if(polecenie ==2)
    {
        printf("podaj nazwe pod jaką chcesz zapisać ten obraz: ");
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
            printf("\n%d. nazwa obrazu: %s\t", first->numer, first->nazwa);
            printf("typ obrazu to %s\n", first->type);
            if(first->czy_zmieniony == TAK) printf("obrazek jest zmienieniony\n");
            else printf("obrazek jest niezmienieniony\n");
            printf("komentarz to:\n%s\n", first->comment);

            first=first->next;
        }
        while(first!=NULL);
        printf("\n[enter] aby porwóić do widoku menu\n");
        getchar();
        getchar();
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
void podpis()
{
    printf("\n--------------------\n"
           "JAKUB TRZYNA 205687\n"
           "programowanie w C\n"
           "--------------------\n");
}
#endif // MENU_H_INCLUDED

