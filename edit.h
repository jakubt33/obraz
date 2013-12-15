#ifndef EDIT_H_INCLUDED
#define EDIT_H_INCLUDED

void edycja(element *lista, int komenda);
void odbij_poziomo( element *lista);
void odbij_pionowo( element *lista);
void pociemnij( element *lista);
void rozjasnij( element *lista);
void black_white( element *lista);
void kontury( element *lista);
void obrot_90P(element *lista);
void obrot_90L(element *lista);
void kontrast (element *lista);
void przytnij(element *lista);
void rozciagnij(element *lista);


void edycja(element *lista, int komenda)
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
                    switch (komenda)
                    {
                    case 31:
                    {
                        odbij_poziomo( lista );
                        break;
                    }
                    case 32:
                    {
                        odbij_pionowo( lista );
                        break;
                    }
                    case 33:
                    {
                        pociemnij( lista );
                        break;
                    }
                    case 34:
                    {
                        rozjasnij( lista );
                        break;
                    }
                    case 35:
                    {
                        black_white( lista );
                        break;
                    }
                    case 36:
                    {
                        kontury( lista );
                        break;
                    }
                    case 37:
                    {
                        kontrast( lista );
                        break;
                    }
                    case 41:
                    {
                        obrot_90P( lista );
                        break;
                    }
                    case 42:
                    {
                        obrot_90L( lista );
                        break;
                    }
                    case 43:
                    {
                        //obrot_180( lista );
                        break;
                    }
                    case 44:
                    {
                        przytnij( lista );
                        break;
                    }
                    case 45:
                    {
                        rozciagnij( lista ); //naprawic
                        break;
                    }
                    default:
                    {
                        printf("brak takiej opcji\n");
                        break;
                    }
                    }
                }
                lista=lista->next;
            }
            while(lista!=NULL);
        }
        if ( znaleziony == NIE)
            printf("nie znaleziono obrazka o takiej nazwie\n");
    }
}
void przytnij(element *lista)
{
    printf("obrazek ma wymiary %d na %d\n", lista->wymx, lista->wymy);
    printf("podaj o ile piseli przyciąć: \n");
    int od_lewej=0, od_prawej=0 ,od_gory=0 ,od_dolu=0, licznik_x=0, licznik_y=0;

    printf("o strony lewej: \n");
    if ( scanf("%d", &od_lewej) != 1 )
    {
        error();
    }
    else
    {
        printf("o strony prawej: \n");
        if ( scanf("%d", &od_prawej) != 1 )
        {
            error();
        }
        else
        {
            printf("od góry: \n");
            if ( scanf("%d", &od_gory) != 1 )
            {
                error();
            }
            else
            {
                printf("od dolu: \n");
                if ( scanf("%d", &od_dolu) != 1 )
                {
                    error();
                }
                else
                {
                    int n_wymx=0, n_wymy=0, licznik=0;
                    if( (n_wymx=lista->wymx-(od_lewej+od_prawej)) > 0 && od_lewej >=0 && od_prawej >= 0)
                    {
                        if( (n_wymy=lista->wymy-(od_gory+od_dolu)) > 0 && od_gory >= 0 && od_dolu >= 0)
                        {

                            for(licznik_x=od_lewej; licznik_x<lista->wymx; licznik_x++)
                            {
                                for(licznik_y=od_gory; licznik_y<lista->wymy; licznik_y++)
                                {
                                    lista->obraz[licznik_x-od_lewej][licznik_y-od_gory] = lista->obraz[licznik_x][licznik_y];
                                }
                            }

                            lista->obraz = (int**)realloc(lista->obraz, n_wymx * sizeof(int*));
                            for(licznik = 0; licznik < n_wymx; licznik++)
                                lista->obraz[licznik] = (int*)realloc(lista->obraz[licznik], n_wymy * sizeof(int));

                            lista->wymx=n_wymx;
                            lista->wymy=n_wymy;

                            lista->czy_zmieniony = TAK;
                        }
                        else printf("podane wymiary są błędne\n");
                    }
                    else printf ("podane wymiary są błędne\n");
                }
            }
        }
    }
}
void rozciagnij(element *lista)
{
    printf("ile razy poszerzyć obraz w poziomie:  ");
    float wspx=0, wspy=0;
    if ( scanf("%f", &wspx) != 1 )
    {
        error();
    }
    else
    {
        printf("ile razy poszerzyć obraz w pionie:  ");
        if ( scanf("%f", &wspy) != 1 )
        {
            error();
        }
        else
        {
            int licznik=0, licznik_x=0, licznik_y=0, n_wymx=0, n_wymy=0;
            n_wymx = lista->wymx * wspx;
            n_wymy = lista->wymy * wspy;

            int **t;
            t = (int**)malloc( n_wymx * sizeof(int*));
            for(licznik = 0; licznik < n_wymx; licznik++)
                t[licznik] = (int*)malloc( n_wymy * sizeof(int));

            for(licznik_x=0; licznik_x < n_wymx; licznik_x++)
            {
                for(licznik_y=0; licznik_y<n_wymy; licznik_y++)
                {
                    int x = licznik_x/wspx;
                    int y = licznik_y/wspy;
                    t[licznik_x][licznik_y] = lista->obraz[x][y];
                }
            }
            lista->wymx = n_wymx;
            lista->wymy = n_wymy;

            lista->obraz = (int**)realloc(lista->obraz, lista->wymx * sizeof(int*));
            for(licznik = 0; licznik < lista->wymx; licznik++)
                lista->obraz[licznik] = (int*)realloc(lista->obraz[licznik], lista->wymy * sizeof(int));

            for(licznik_x=0; licznik_x < lista->wymx; licznik_x++)
            {
                for(licznik_y=0; licznik_y<lista->wymy; licznik_y++)
                {
                    lista->obraz[licznik_x][licznik_y] = t[licznik_x][licznik_y];
                }
            }
            lista->czy_zmieniony = TAK;

            for(licznik = 0; licznik < lista->wymx; licznik++)
                free(t[licznik]);
            free(t);
        }

    }
}

void kontrast(element *lista)
{
    unsigned long int sumator=0;
    int licznik_x=0, licznik_y=0;
    for(licznik_x=0; licznik_x<lista->wymx; licznik_x++)
    {
        for(licznik_y=0; licznik_y<lista->wymy; licznik_y++)
        {
            sumator += lista->obraz[licznik_x][licznik_y];
        }
    }
    int srednia=((sumator)/((lista->wymx)*(lista->wymy)));
    printf("srednia to %d\n", srednia);
    printf("moc %d - neutralna, większa=większy kontrast\n", srednia);

    int moc = pobierz_moc(lista);
    if(moc != STOP )
    {
        printf("moc to %d\n", moc);
        for(licznik_x=0; licznik_x<lista->wymx; licznik_x++)
        {
            for(licznik_y=0; licznik_y<lista->wymy; licznik_y++)
            {
                float wsp = (moc-srednia)*(srednia-lista->obraz[licznik_x][licznik_y])/(srednia);
                lista->obraz[licznik_x][licznik_y] -=wsp;
                if(lista->obraz[licznik_x][licznik_y]<0) lista->obraz[licznik_x][licznik_y]=0;
                if(lista->obraz[licznik_x][licznik_y]>lista->odcienie) lista->obraz[licznik_x][licznik_y]=lista->odcienie;
            }
        }
        lista->czy_zmieniony=TAK;
    }


}
void obrot_90P(element *lista)
{
    int licznik=0;
    int temp_x=lista->wymx;
    lista->wymx=lista->wymy;
    lista->wymy=temp_x;

    int **t;
    t = (int**)malloc(lista->wymx * sizeof(int*));

    for(licznik = 0; licznik < lista->wymx; licznik++)
        t[licznik] = (int*)malloc(lista->wymy * sizeof(int));


    int licznik_y=0,licznik_x=0;
    for(licznik_y=0; licznik_y<lista->wymy; licznik_y++)
        for(licznik_x=0; licznik_x<lista->wymx; licznik_x++)
            t[licznik_x][licznik_y] = lista->obraz[licznik_y][lista->wymx-1-licznik_x];

    lista->obraz = (int**)realloc(lista->obraz, lista->wymx * sizeof(int*));
    for(licznik = 0; licznik < lista->wymx; licznik++)
        lista->obraz[licznik] = (int*)realloc(lista->obraz[licznik], lista->wymy * sizeof(int));

    for(licznik_y=0; licznik_y<lista->wymy; licznik_y++)
        for(licznik_x=0; licznik_x<lista->wymx; licznik_x++)
            lista->obraz[licznik_x][licznik_y]=t[licznik_x][licznik_y];

    lista->czy_zmieniony = TAK;

    for(licznik = 0; licznik < lista->wymx; licznik++)
        free(t[licznik]);
    free(t);
}
void obrot_90L(element *lista)
{
    int licznik=0;
    int temp_x=lista->wymx;
    lista->wymx=lista->wymy;
    lista->wymy=temp_x;

    int **t;
    t = (int**)malloc(lista->wymx * sizeof(int*));

    for(licznik = 0; licznik < lista->wymx; licznik++)
        t[licznik] = (int*)malloc(lista->wymy * sizeof(int));


    int licznik_y=0,licznik_x=0;
    for(licznik_y=0; licznik_y<lista->wymy; licznik_y++)
        for(licznik_x=0; licznik_x<lista->wymx; licznik_x++)
            t[licznik_x][licznik_y] = lista->obraz[lista->wymy-1-licznik_y][lista->wymx-1-licznik_x];

    lista->obraz = (int**)realloc(lista->obraz, lista->wymx * sizeof(int*));
    for(licznik = 0; licznik < lista->wymx; licznik++)
        lista->obraz[licznik] = (int*)realloc(lista->obraz[licznik], lista->wymy * sizeof(int));

    for(licznik_y=0; licznik_y<lista->wymy; licznik_y++)
        for(licznik_x=0; licznik_x<lista->wymx; licznik_x++)
            lista->obraz[licznik_x][licznik_y]=t[licznik_x][licznik_y];

    lista->czy_zmieniony = TAK;

    for(licznik = 0; licznik < lista->wymx; licznik++)
        free(t[licznik]);
    free(t);
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
            lista->obraz[licznik_x][licznik_y] = lista->obraz[licznik_x][lista->wymy-1-licznik_y];
            lista->obraz[licznik_x][lista->wymy-1-licznik_y] = temp;
        }
    }
    lista->czy_zmieniony = TAK;
}
void odbij_pionowo( element *lista)
{
    int licznik_y=0, licznik_x=0;
    int temp=0;

    for(licznik_y=0; licznik_y<lista->wymy; licznik_y++)
    {
        for(licznik_x=0; licznik_x<lista->wymx/2; licznik_x++)
        {
            temp = lista->obraz[licznik_x][licznik_y];
            lista->obraz[licznik_x][licznik_y] = lista->obraz[lista->wymx-1-licznik_x][licznik_y];
            lista->obraz[lista->wymx-1-licznik_x][licznik_y] = temp;
        }
    }
    lista->czy_zmieniony = TAK;
}
int pobierz_moc(element *lista)
{
    printf("podaj jak moc filtra w sklali 1-%d: ", lista->odcienie);
    int moc=0;
    if ( scanf("%d", &moc) != 1 )
    {
        error();
    }
    else if (moc>lista->odcienie)
    {
        printf("moc poza zakresem\n");
        return STOP;
    }
    else return moc;
}
void pociemnij( element *lista)
{
    int moc=pobierz_moc(lista);
    if(moc != STOP)
    {
        int licznik_y=0, licznik_x=0;
        int temp=0;

        for(licznik_y=0; licznik_y<lista->wymy; licznik_y++)
        {
            for(licznik_x=0; licznik_x<lista->wymx; licznik_x++)
            {
                if (lista->obraz[licznik_x][licznik_y] >= moc )
                    lista->obraz[licznik_x][licznik_y] -= moc ;
                else lista->obraz[licznik_x][licznik_y] = 0;
            }
        }

        lista->czy_zmieniony = TAK;
    }
}
void rozjasnij( element *lista)
{
    int moc=pobierz_moc(lista);
    if(moc != STOP)
    {
        int licznik_y=0, licznik_x=0;
        int temp=0;

        for(licznik_y=0; licznik_y<lista->wymy; licznik_y++)
        {
            for(licznik_x=0; licznik_x<lista->wymx; licznik_x++)
            {
                if (lista->obraz[licznik_x][licznik_y] + moc <= lista->odcienie )
                    lista->obraz[licznik_x][licznik_y] += moc ;
                else lista->obraz[licznik_x][licznik_y] = lista->odcienie;
            }
        }

        lista->czy_zmieniony = TAK;
    }
}
void black_white( element *lista)
{
    int moc=pobierz_moc(lista);
    if(moc != STOP)
    {
        int licznik_y=0, licznik_x=0;
        int temp=0;

        for(licznik_y=0; licznik_y<lista->wymy; licznik_y++)
        {
            for(licznik_x=0; licznik_x<lista->wymx; licznik_x++)
            {
                if (lista->obraz[licznik_x][licznik_y] + moc <= lista->odcienie )
                    lista->obraz[licznik_x][licznik_y] = 0 ;
                else lista->obraz[licznik_x][licznik_y] = lista->odcienie;
            }
        }
        lista->czy_zmieniony = TAK;
    }
}
void kontury( element *lista)
{
    int moc=pobierz_moc(lista);
    if(moc != STOP)
    {
        int licznik_y=0, licznik_x=0;
        int temp=0;

        for(licznik_y=0; licznik_y<lista->wymy; licznik_y++)
        {
            for(licznik_x=0; licznik_x<lista->wymx; licznik_x++)
            {
                if (lista->obraz[licznik_x][licznik_y] + moc <= lista->odcienie )
                    lista->obraz[licznik_x][licznik_y] = 0 ;
                else lista->obraz[licznik_x][licznik_y] = lista->odcienie;
            }
        }

        int licznik=0;
        int **t;
        t = (int**)malloc(lista->wymx * sizeof(int*));

        for(licznik = 0; licznik < lista->wymx; licznik++)
            t[licznik] = (int*)malloc(lista->wymy * sizeof(int));

        int test=0;
        for(licznik_y=1; licznik_y<lista->wymy-1; licznik_y++)
        {
            for(licznik_x=1; licznik_x<lista->wymx-1; licznik_x++)
            {
                if (lista->obraz[licznik_x][licznik_y] != lista->obraz[licznik_x+1][licznik_y] )
                    test++;
                if (lista->obraz[licznik_x][licznik_y] != lista->obraz[licznik_x][licznik_y+1] )
                    test++;
                if (lista->obraz[licznik_x][licznik_y] != lista->obraz[licznik_x-1][licznik_y] )
                    test++;
                if (lista->obraz[licznik_x][licznik_y] != lista->obraz[licznik_x][licznik_y+1] )
                    test++;

                if(test > 0)
                    t[licznik_x][licznik_y] = 0 ;

                else
                    t[licznik_x][licznik_y] = lista->odcienie;
                test=0;
            }
        }
        for(licznik_y=0; licznik_y<lista->wymy; licznik_y++)
        {
            for(licznik_x=0; licznik_x<lista->wymx; licznik_x++)
            {
                lista->obraz[licznik_x][licznik_y]=t[licznik_x][licznik_y];
            }
        }
        for(licznik = 0; licznik < lista->wymx; licznik++)
            free(t[licznik]);
        free(t);

        lista->czy_zmieniony = TAK;
    }
}
#endif // EDIT_H_INCLUDED

