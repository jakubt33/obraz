#ifndef EDIT_H_INCLUDED
#define EDIT_H_INCLUDED

void lustrzane_odbicie(element *lista, element *kopie);
void lustro( element *lista);

void lustrzane_odbicie(element *lista, element *kopie)
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
                    //utworz_kopie(lista, kopie);

                    //rob zmiany


                    // lista->kopia = lista;
                    // lista->kopia->next = NULL;
                    // wyswietl( lista->kopia );
                    // lustro ( lista->kopia );
                }
                lista=lista->next; //modyfikuijmy tylko kopie wskaznika!
            }
            while(lista!=NULL);
        }
        if ( znaleziony == NIE)
            printf("nie znaleziono obrazka o takiej nazwie\n");
    }
}

void lustro( element *kopia)
{
    //czy_zmieniony = TAK;
}

#endif // EDIT_H_INCLUDED
