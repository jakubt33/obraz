#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#define NIE 0
#define TAK 1

#include <stdlib.h>
#include "init.h"
#include "odczyt.h"
#include "edit.h"


void menu(element *lista, element *kopie);
void wyswietl(element *);
element * usun(element *);
void zapisz(element *lista, element *kopie);


void menu(element *lista, element *kopie)
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
                kopie = zapisz_bufor(kopie, temp);

                zwolnij_tablice(temp);
                break;
            }
            case 2:
            {
                wyswietl(kopie);
                break;
            }
            case 31:
            {
                lustrzane_odbicie( kopie );
                break;
            }
            case 5:
            {
                printf("zapis zmienionych obrazkow\n");
                zapisz(lista, kopie);
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
void zapisz(element *lista, element *kopia)
{
    while(kopia!=NULL)
    {
        if ( kopia->czy_zmieniony == TAK)
        {
            printf("co zrobic z tym obrazem: %s?\n1 - nadpisz\t2 - zapisz jako\t3 - nie zapisuj\t", kopia->nazwa);
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
                        kopia->czy_zmieniony = NIE;

                        printf("nadpisuje\n");
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
                printf("\n%d. nazwa obrazu to %s", first->numer, first->nazwa);
            }
        }
        kopia=kopia->next; //modyfikuijmy tylko kopie wskaznika!
        lista=lista->next;
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

