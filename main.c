#include <stdio.h>
#include "menu.h"

int main()
{
    element *lista = NULL;

    menu(lista);

    lista = usun(lista);

    return 0;
}
