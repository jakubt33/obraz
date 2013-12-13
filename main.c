#include <stdio.h>
#include "menu.h"

int main()
{
    element *lista = NULL;
    element *kopie = NULL;

    menu(lista, kopie);

    lista = usun(lista);
    kopie = usun(kopie);

    return 0;
}
