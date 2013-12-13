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
void nazwa_obrazka(char *nazwa);

void nazwa_obrazka(char *nazwa)
{
    printf("podaj nazwę obrazka do załadowania do bazy:  ");
    scanf("%19s", nazwa);
}
element * wczytajobraz(element *lista)
{
    int dzialaj = WORK;

    element *temp;
    temp=(element*)malloc(sizeof(element));

    char nazwa[20];
    nazwa_obrazka(nazwa);
    FILE * pFile;
    pFile=fopen( nazwa, "rt");

    if(pFile==NULL)
    {
        perror("blad otwarcia pliku\n");
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
            }
            else
                dzialaj=STOP; //flaga error
        }
        else
            dzialaj=STOP; //flaga error

        if( dzialaj == WORK )
        {
            temp->next=NULL;
            lista=push(lista, temp);
            //zwolnij_tablice(temp);
            printf("dodano obraz\n");
        }
        else if ( dzialaj == STOP )
            printf("program napotkał błąd przy odczycie danych obrazu\n");

        fclose(pFile);
    }

    free(temp);

    return lista;
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
    temp->obraz = (int**)malloc(temp->wymiary[WYM_X] * sizeof(int*));

    for(licznik = 0; licznik < temp->wymiary[WYM_X]; licznik++)
        temp->obraz[licznik] = (int*)malloc(temp->wymiary[WYM_Y] * sizeof(int));
}
void pobierz_tablice(FILE *pFile, element *temp)
{
    mallocuj_tablice(temp);
    int licznik_y=0, licznik_x=0;
    for(licznik_y=0; licznik_y<temp->wymiary[WYM_Y]; licznik_y++)
    {
        for(licznik_x=0; licznik_x<temp->wymiary[WYM_X]; licznik_x++)
            fscanf(pFile, "%d", &temp->obraz[licznik_x][licznik_y] );
    }
    /*
    for(licznik_y=0; licznik_y<temp->wymiary[WYM_Y]; licznik_y++)
    {
        printf("\n");
        for(licznik_x=0; licznik_x<temp->wymiary[WYM_X]; licznik_x++)
           printf("%d ", temp->obraz[licznik_x][licznik_y]);
    }
    printf("\n");
    */ //po odczycie od razu wyswietla

}
int sprawdz_wymiary(FILE *pFile, element *temp)
{
    if (fscanf(pFile, "%d", &temp->wymiary[0]))
    {
        if (fscanf(pFile, "%d", &temp->wymiary[1]))
        {
            temp->wymiary[2] = '\0';
            char endline=0;
            while ( endline=fgetc(pFile) != '\n');
            return WORK; //or no // dopisac
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
    char test[2];
    test[0] = fgetc(pFile);
    fseek(pFile, -1, SEEK_CUR);

   // printf("test = %c\n", test[0]);

    if( test[0] == '#' )
    {
        odczyt_komentarza(pFile, temp); //zrobic zeby laczylo koment w jeden max 50 znakow
        sprawdz_komentarz(pFile, temp);
    }
    else fseek(pFile, -1, SEEK_CUR);

}
int odczyt_komentarza(FILE *pFile, element *temp)
{
    int licznik=0;
    char tempcomment[MAXCOMMENT-1];
    char znak=0;
    do
    {
        znak=fgetc(pFile);
        tempcomment[licznik] = znak;
        licznik++;
    } while ( znak != '\n');
    tempcomment[licznik] = '\0';
    strncat(temp->comment, tempcomment, sizeof(temp->comment)-strlen(tempcomment)- 1);
    temp->comment[MAXCOMMENT-1] = '\0';
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
