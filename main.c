#include <stdio.h>
#include <stdlib.h>

#include "naglowki.h"


int main()
{
    element *lista=NULL;
    element *temp;

    lista = wczytajobraz(lista);

    wyswietl(lista);


 /*   int i;
    for(i=0;i<10;i++)
    {
        temp=(element*)malloc(sizeof(element));
        temp->next=NULL;
        temp->data=i;
        lista=push(lista, temp);
    }
    wyswietl(lista);
    lista=usun(lista);
    wyswietl(lista);
*/

    return 0;
}
