#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <stdlib.h>
#include "init.h"
#include "odczyt.h"

#define NIE 0
#define TAK 1

void menu(element *lista);
void wyswietl(element *);
element * usun(element *);

void menu(element *lista)
{
    int czy_konczyc = NIE;

    while( czy_konczyc == NIE )
    {
        printf("dostępne funkcje:\n"
               "1 - Dodaj obraz\n"
               "2 - Wyswietl obraz\n"
               "31 - Inwersja\n"
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
        int komenda=0;
        scanf("%20d", &komenda);

        switch (komenda)
        {
        case 1:
        {
            element *nowy_obraz;
            lista = wczytajobraz(nowy_obraz);
            break;
        }
        case 2:
        {
            wyswietl(lista);
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
    lista=usun(lista);

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
            printf("\ntyp obrazu to %s\n", first->type);
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
void zwolnij_tablice(element *temp)
{
    int licznik=0;
    for(licznik = 0; licznik < temp->wymiary[WYM_X]; licznik++)
        free(temp->obraz[licznik]);
    free(temp->obraz);
}
#endif // MENU_H_INCLUDED
