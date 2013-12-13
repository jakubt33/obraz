#ifndef EDIT_H_INCLUDED
#define EDIT_H_INCLUDED

void lustrzane_odbicie(element *kopia);
void lustro( element *lista);

void lustrzane_odbicie(element *kopia)
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
        if(kopia==NULL)
        {
            printf("lista jest pusta\n");
        }
        else
        {
            do
            {
                if ( kopia->numer == numer)
                {
                    znaleziony = TAK;
                    printf("znaleziono obraz\n");

                    lustro(kopia);
                }
                kopia=kopia->next; //modyfikuijmy tylko kopie wskaznika!
            }
            while(kopia!=NULL);
        }
        if ( znaleziony == NIE)
            printf("nie znaleziono obrazka o takiej nazwie\n");
    }
}

void lustro( element *kopia)
{
    kopia->czy_zmieniony = TAK;
}

#endif // EDIT_H_INCLUDED
