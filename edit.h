#ifndef EDIT_H_INCLUDED
#define EDIT_H_INCLUDED

void lustrzane_odbicie(element *lista);
void lustro( element *lista);
void odbij_poziomo( element *lista);

void lustrzane_odbicie(element *lista)
{
    int znaleziony = NIE;
    printf("podaj numer obrazka który chcesz edytować: ");

    int numer=0;
    if ( scanf("%d", &numer) != 1 )
    {
        error();
    }
    else
    {
        printf("%d <- to jest numer ktory wybrales\n", numer);
        if(lista==NULL)
        {
            printf("lista jest pusta\n");
        }
        else
        {
            do
            {
                if ( lista->numer == numer)
                {
                    znaleziony = TAK;
                    printf("znaleziono obraz\n");

                    odbij_poziomo(lista);
                }
                lista=lista->next;
            }
            while(lista!=NULL);
        }
        if ( znaleziony == NIE)
            printf("nie znaleziono obrazka o takiej nazwie\n");
    }
}

void odbij_poziomo( element *lista)
{
    int licznik_y=0, licznik_x=0;
    int temp=0;
    for(licznik_x=0; licznik_x<lista->wymx; licznik_x++)
    {
        for(licznik_y=0; licznik_y<lista->wymy/2; licznik_y++)
        {
            temp= lista->obraz[licznik_x][licznik_y];
            lista->obraz[licznik_x][licznik_y] = lista->obraz[licznik_x][lista->wymy-licznik_y];
            lista->obraz[licznik_x][lista->wymy-licznik_y] = temp;
        }
    }
    lista->czy_zmieniony = TAK;
}
void odbij_pionowo( element *lista)
{
    int licznik_y=0, licznik_x=0;
    int temp=0;
    for(licznik_x=0; licznik_x<lista->wymx; licznik_x++)
    {
        for(licznik_y=0; licznik_y<lista->wymy/2; licznik_y++)
        {
            temp= lista->obraz[licznik_x][licznik_y];
            lista->obraz[licznik_x][licznik_y] = lista->obraz[licznik_x][lista->wymy-licznik_y];
            lista->obraz[licznik_x][lista->wymy-licznik_y] = temp;
        }
    }
    lista->czy_zmieniony = TAK;
}

#endif // EDIT_H_INCLUDED
