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
void rozmycie (element *lista);
void sukces();
int pobierz_moc(element *lista);


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
                        sukces();
                        break;
                    }
                    case 32:
                    {
                        odbij_pionowo( lista );
                        sukces();
                        break;
                    }
                    case 33:
                    {
                        pociemnij( lista );
                        sukces();
                        break;
                    }
                    case 34:
                    {
                        rozjasnij( lista );
                        sukces();
                        break;
                    }
                    case 35:
                    {
                        black_white( lista );
                        sukces();
                        break;
                    }
                    case 36:
                    {
                        kontury( lista );
                        sukces();
                        break;
                    }
                    case 37:
                    {
                        kontrast( lista );
                        sukces();
                        break;
                    }
                    case 38:
                    {
                        rozmycie( lista );
                        sukces();
                        break;
                    }
                    case 41:
                    {
                        obrot_90P( lista );
                        sukces();
                        break;
                    }
                    case 42:
                    {
                        obrot_90L( lista );
                        sukces();
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
                        sukces();
                        break;
                    }
                    case 45:
                    {
                        rozciagnij( lista );
                        sukces();
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
            printf("nie znaleziono takiego obrazka w bazie\n");
    }
}
void sukces()
{
    printf("edycja zakończona sukcesem!\n");
}
void rozmycie (element *lista)
{
    int licznik_x=0, licznik_y=0, licznik=0, **temp;

    printf("podaj moc filtra, standardowo 1-5\n");
    int moc=0;
    if ( scanf("%d", &moc) != 1 )
    {
        error();
    }
    else if (moc>0 && lista->wymx>2*moc && lista->wymy>2*moc)
    {
        temp = (int**)malloc(lista->wymx * sizeof(int*));
        for(licznik = 0; licznik < lista->wymx; licznik++)
            temp[licznik] = (int*)malloc(lista->wymy * sizeof(int));

        int sumator=0, i=0, j=0;
        for(licznik_x=moc; licznik_x<lista->wymx-moc; licznik_x++)
        {
            for(licznik_y=moc; licznik_y<lista->wymy-moc; licznik_y++)
            {
                sumator=0, i=0, j=0;

                for(i=-moc; i<=moc; i++)
                    for(j=-moc; j<=moc; j++)
                        sumator+= lista->obraz[licznik_x+i][licznik_y+j] ;

                temp[licznik_x][licznik_y] = sumator/(((2*moc) + 1)*((2*moc)+1));
            }
        }
        moc--;
        while(moc>0)
        {
            int k=0;
            for(k=0; k<2; k++)//musi sie wykonać 2 razy, dla storny lewej i prawej
            {
                int ty=moc;
                for(licznik_x=ty; licznik_x<lista->wymx-ty; licznik_x++)
                {
                    sumator=0, i=0, j=0;
                    for(i=-moc; i<=moc; i++)
                        for(j=-moc; j<=moc; j++)
                            sumator+= lista->obraz[licznik_x+i][ty+j] ;

                    temp[licznik_x][moc] = sumator/((2*moc + 1)*(2*moc+1));
                }
                ty = lista->wymy-moc;
            }
            for(k=0; k<2; k++) //musi sie wykonać 2 razy, dla storny lewej i prawej
            {
                int tx=moc;
                for(licznik_y=moc; licznik_y<lista->wymy-moc; licznik_y++)
                {
                    sumator=0, i=0, j=0;

                    for(i=-moc; i<=moc; i++)
                        for(j=-moc; j<=moc; j++)
                            sumator+= lista->obraz[tx+i][licznik_y+j] ;

                    temp[moc][licznik_y] = sumator/((2*moc + 1)*(2*moc+1));
                }
                tx = lista->wymx-moc;
            }
            moc--;
        }

        for(licznik_x=moc; licznik_x<lista->wymx-moc; licznik_x++)
        {
            for(licznik_y=moc; licznik_y<lista->wymy-moc; licznik_y++)
            {
                lista->obraz[licznik_x][licznik_y] = temp[licznik_x][licznik_y];
            }
        }

        for(licznik = 0; licznik < lista->wymx; licznik++)
            free(temp[licznik]);
        free(temp);

        lista->czy_zmieniony = TAK;
    }
}
void przytnij(element *lista)
{
    printf("obrazek ma wymiary %d na %d\n", lista->wymx, lista->wymy);
    printf("podaj o ile pikseli przyciąć: \n");
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
        else if (wspy>0 && wspx>0)
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
        else
            printf("wybrano złe współczynniki\n");

    }
}
void kontrast(element *lista)
{
    unsigned long int sumator=0; //zrobic zabezpieczenie przed max rozmiarem
    int licznik_x=0, licznik_y=0;
    for(licznik_x=0; licznik_x<lista->wymx; licznik_x++)
    {
        for(licznik_y=0; licznik_y<lista->wymy; licznik_y++)
        {
            sumator += lista->obraz[licznik_x][licznik_y];
        }
    }
    int srednia=((sumator)/((lista->wymx)*(lista->wymy)));
    printf("moc %d - neutralna, większa=większy kontrast\n", srednia);

    int moc = pobierz_moc(lista);
    if(moc != STOP )
    {
        printf("wybrana moc to %d\n", moc);
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
    return moc;

}
void pociemnij( element *lista)
{
    int moc=pobierz_moc(lista);
    if(moc != STOP)
    {
        int licznik_y=0, licznik_x=0;

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
    printf("standardowa moc to ok %d\n", lista->odcienie/2);
    int moc=pobierz_moc(lista);
    if(moc != STOP)
    {
        int licznik_y=0, licznik_x=0;

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






