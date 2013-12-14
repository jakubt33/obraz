#ifndef ODCZYT_H_INCLUDED
#define ODCZYT_H_INCLUDED

#define B_AND_W 49
#define GR_SCALE 50
#define COLOR 51
#define MAGIC_NUMBER 1
#define STOP -1
#define WORK 1
#define WYM_X 0
#define WYM_Y 1

element *push(element *, element *);
void wyswietl(element *);
element * wczytajobraz(element*);
void sprawdz_komentarz(FILE *pFile, element *temp);
int sprawdz_typ(FILE *pFile, element *temp);
int sprawdz_wymiary(FILE *pFile, element *temp);
int sprawdz_odcienie(FILE *pFile, element *temp);
int pobierz_obraz(FILE *pFile, element *temp);
void pobierz_tablice(FILE *pFile, element *temp);
void mallocuj_tablice(element *temp);
void zwolnij_tablice(element *temp);
void nazwa_obrazka(element *temp, int *dzialaj);
void numeruj(element *first);
element * zapisz_bufor(element *glowny, element *temp);

void nazwa_obrazka(element *temp, int *dzialaj)
{
    printf("podaj nazwę obrazka do załadowania do bazy:  ");
    if ( scanf("%19s", temp->nazwa) != 1 )
    {
        error();
        dzialaj = STOP;
    }
}
element * wczytajobraz(element *lista)
{

    element *temp;
    temp=(element*)malloc(sizeof(element));

    int dzialaj = WORK;
    nazwa_obrazka(temp, &dzialaj);
    FILE * pFile;
    pFile=fopen( temp->nazwa, "rt");

    if(pFile==NULL)
    {
        dzialaj = STOP;
        perror("blad otwarcia pliku");
    }
    else
    {
        sprawdz_komentarz(pFile, temp);

        if ( (sprawdz_typ(pFile, temp)) == WORK )
        {
            sprawdz_komentarz(pFile, temp);

            if( sprawdz_wymiary(pFile, temp) == WORK )
            {
                sprawdz_komentarz(pFile, temp);

                dzialaj = pobierz_obraz(pFile, temp);
                temp->czy_zmieniony = NIE;
            }
            else
                dzialaj=STOP; //flaga error
        }
        else
            dzialaj=STOP; //flaga error
        fclose(pFile);
    }
    //free(temp);
    if( dzialaj == WORK )
    {
        temp->next = NULL;
        lista = zapisz_bufor(lista, temp);
        return lista;
    }
    else
        printf("program napotkał błąd przy odczycie danych obrazu\n");
    return lista;
}
element * zapisz_bufor(element *glowny, element *temp)
{
    glowny = push(glowny, temp);
    temp->next = NULL;
    numeruj( glowny );
    return glowny;
}
void numeruj(element *first)
{
    int licznik=0;
    if(first==NULL)
    {
        printf("lista jest pusta\n");
    }
    else
    {
        do
        {
            licznik++;
            first->numer=first->numer=licznik;
            first=first->next; //modyfikuijmy tylko kopie wskaznika!
        }
        while(first!=NULL);
    }
}
void zwolnij_tablice(element *temp)
{
    int licznik=0;
    for(licznik = 0; licznik < temp->wymx; licznik++)
        free(temp->obraz[licznik]);
    free(temp->obraz);
}
int pobierz_obraz(FILE *pFile, element *temp)
{

    switch ( temp->type[MAGIC_NUMBER] )
    {
    case B_AND_W:

        pobierz_tablice(pFile, temp);
        return WORK;
        break;

    case GR_SCALE:

        sprawdz_komentarz(pFile, temp);
        if( sprawdz_odcienie(pFile, temp) )
        {
            sprawdz_komentarz(pFile, temp);
            pobierz_tablice(pFile, temp);
            return WORK;
        }
        else
        {
            return STOP;
        }
        break;

    case COLOR:

        printf("program nie umozliwia jeszcze obsługi kolorowych obrazów\n"); //mozna bedzei dodac funcke jak starczy czasu\
        return STOP;
        break;

    default:
        return STOP;

    }
}
int sprawdz_odcienie(FILE *pFile, element *temp)
{
    char test ;
    do
    {
        test = fgetc(pFile);
    }
    while (test > '0' && test <= '9');
    fseek(pFile, -1, SEEK_CUR);


    if ( fscanf( pFile, "%d", &temp->odcienie) )
    {
        char endline=0;
        while ( endline=fgetc(pFile) != '\n');
        return WORK;
    }
    return STOP;
}
void mallocuj_tablice(element *temp)
{
    int licznik=0;
    temp->obraz = (int**)malloc(temp->wymx * sizeof(int*));

    for(licznik = 0; licznik < temp->wymx; licznik++)
        temp->obraz[licznik] = (int*)malloc(temp->wymy * sizeof(int));
}
void pobierz_tablice(FILE *pFile, element *temp)
{
    mallocuj_tablice(temp);
    int licznik_y=0, licznik_x=0;
    for(licznik_y=0; licznik_y<temp->wymy; licznik_y++)
    {
        for(licznik_x=0; licznik_x<temp->wymx; licznik_x++)
            fscanf(pFile, "%d", &temp->obraz[licznik_x][licznik_y] );
    }

    /*
//po odczycie od razu wyswietla
    for(licznik_y=0; licznik_y<temp->wymiary[WYM_Y]; licznik_y++)
    {
        printf("\n");
        for(licznik_x=0; licznik_x<temp->wymiary[WYM_X]; licznik_x++)
           printf("%d ", temp->obraz[licznik_x][licznik_y]);
    }
    printf("\n");
    */
}
int sprawdz_wymiary(FILE *pFile, element *temp)
{
    char test ;
    do
    {
        test = fgetc(pFile);
    }
    while (test > '0' && test <= '9');
    fseek(pFile, -1, SEEK_CUR);



    if (fscanf(pFile, "%d", &temp->wymx))
    {
        if (fscanf(pFile, "%d", &temp->wymy))
        {
            char endline=0;
            while ( endline=fgetc(pFile) != '\n');
            return WORK;
        }
        else return STOP;
    }
    else return STOP;
}
int sprawdz_typ(FILE *pFile, element *temp)
{
    temp->type[0] = fgetc(pFile);

    if(temp->type[0] == 'P')
    {
        temp->type[MAGIC_NUMBER] = fgetc(pFile);
        if( (temp->type[MAGIC_NUMBER] == B_AND_W) || (temp->type[MAGIC_NUMBER] == GR_SCALE) || (temp->type[MAGIC_NUMBER] == COLOR) )
        {
            temp->type[2] = '\0';
            char endline=0;
            while ( (endline=fgetc(pFile)) != '\n');

            return WORK;
        }
        else return STOP;
    }
    else return STOP;
}
void sprawdz_komentarz(FILE *pFile, element *temp)
{
    char test = 0;
    test = fgetc(pFile);

    fseek(pFile, -1, SEEK_CUR);

    // printf("test = %c\n", test[0]);

    if( test == '#' )
    {
        odczyt_komentarza(pFile, temp);
        sprawdz_komentarz(pFile, temp);
    }
    else if (test == '\n')
    {
        printf("test wykryl 'n'\n");
    }
    else fseek(pFile, -1, SEEK_CUR);

}
int odczyt_komentarza(FILE *pFile, element *temp)
{
    int licznik=0;
    char tempcomment[MAXCOMMENT]={'\0'};
    char znak=0;
    do
    {
        znak=fgetc(pFile);

        if ( licznik < MAXCOMMENT-1)
            tempcomment[licznik] = znak;

        licznik++;

    }
    while ( znak != '\n');
    if ( licznik < MAXCOMMENT-1)
        tempcomment[licznik] = '\0';
    else
        tempcomment[MAXCOMMENT-1] = '\0';

    strcpy(temp->comment, tempcomment/*, sizeof(temp->comment)-strlen(tempcomment)-strlen(temp->comment)-1*/);
    //temp->comment[strlen(temp->comment)] = '\0';
    //printf("\ncomment to :\n%s", temp->comment);
}
element *push(element *first, element *newone)
{
    element *temp=first;
    if(first==NULL)
        return newone;

    while(temp->next!=NULL)
        temp=temp->next;
    temp->next=newone;
    return first;
}
#endif // ODCZYT_H_INCLUDED
