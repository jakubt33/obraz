#include <stdio.h>
#include "menu.h"

int main()
{
    element *lista = NULL;

    menu(lista);

    lista = usun(lista);
    podpis();
    return 0;
}
//negatyw
//laplace
//instrukcja
//czyszczenie pamieci!!!
//ustawienie voidow w jakiejs kolejnosci
