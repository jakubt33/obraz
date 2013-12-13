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
                lista = wczytajobraz(lista);
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
            printf("\n%d. nazwa obrazu to %s\n", first->numer, first->nazwa);
            printf("typ obrazu to %s\n", first->type);
            printf("wymiary to %d na %d\n", first->wymiary[0], first->wymiary[1]);
            printf("ilosc odcieni to %d\n", first->odcienie);
            printf("komentarz to:\n%s\n", first->comment);
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
