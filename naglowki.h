#ifndef NAGLOWKI_H_INCLUDED
#define NAGLOWKI_H_INCLUDED

#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAXCOMMENT 100
#define B_AND_W 49
#define GR_SCALE 50
#define COLOR 51
#define MAGIC_NUMBER 1
#define BAD_FILE_TYPE -1
#define TYPE_OK 1
#define DIM_OK 1
#define DIM_FAIL -1
#define STOP -1
#define WORK 1

typedef struct element
{
    struct element *next;
    char type[2+1];
    int odcienie;
    char wymiary[2+1]; // macierz [x,y]
    char comment[MAXCOMMENT];
} element;

element *push(element *, element *);
void wyswietl(element *);
element * usun(element *);
element * wczytajobraz(element*);
void sprawdz_komentarz(FILE *pFile, element *temp);
int sprawdz_typ(FILE *pFile, element *temp);
int sprawdz_wymiary(FILE *pFile, element *temp);
int sprawdz_odcienie(FILE *pFile, element *temp);
int pobierz_obraz(FILE *pFile, element *temp);
void pobierz_tablice(FILE *pFile, element *temp);


element * wczytajobraz(element *lista)
{
    int dzialaj = WORK;
    element *temp;
    temp=(element*)malloc(sizeof(element));

    FILE * pFile;
    pFile=fopen("test.pgm", "rt");

    if(pFile==NULL)
    {
        perror("blad otwarcia pliku");
    }
    else
    {
        sprawdz_komentarz(pFile, temp);

        if ( (sprawdz_typ(pFile, temp)) == TYPE_OK )
        {
            sprawdz_komentarz(pFile, temp);

            if( sprawdz_wymiary(pFile, temp) == DIM_OK )
            {
                sprawdz_komentarz(pFile, temp);

                dzialaj = pobierz_obraz(pFile, temp);
                //to fajnie, mozna przejsc do pobierania danych do tablicy
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
            printf("dodano obraz\n");
        }
        else if ( dzialaj == STOP )
            printf("program napotkał błąd przy odczycie danych obrazu\n");


    }

    free(temp);
    fclose(pFile);

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
        return WORK;
    }
    return STOP;
}
void pobierz_tablice(FILE *pFile, element *temp)
{

}
int sprawdz_wymiary(FILE *pFile, element *temp)
{
    if (fscanf(pFile, "%d", &temp->wymiary[0]))
    {
        if (fscanf(pFile, "%d", &temp->wymiary[1]))
        {
            temp->wymiary[2] = '\0';
            return DIM_OK; //or no // dopisac
        }
        else return DIM_FAIL;
    }
    else return DIM_FAIL;
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
            return TYPE_OK;
        }
        else return BAD_FILE_TYPE;
    }
    else return BAD_FILE_TYPE;
}
void sprawdz_komentarz(FILE *pFile, element *temp)
{
    char test;
    if( (test = fgetc(pFile)) == '#')
    {
        // zspisuje linie komentarza()
        sprawdz_komentarz(pFile, temp);
    }
    else
    {
        fseek(pFile, -1, SEEK_CUR);
    }
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
void wyswietl(element *first)
{
    if(first==NULL)
    {
        printf("lista jest pusta\n");
    }
    else
    {
        do
        {
            printf("\ntyp obrazu to %s\nwymiary to %d na %d\nilosc odcieni to %d\n", first->type, first->wymiary[0], first->wymiary[1], first->odcienie);
            first=first->next;      //modyfikuijmy tylko kopie wskaznika!
        }
        while(first!=NULL);
    }
}
element * usun(element *first)
{
    if(first==NULL)
    {
        printf("\nlista juz jest pusta\n");
        return NULL;
    }
    usun(first->next);
    free(first);
    return NULL;
}

#endif // NAGLOWKI_H_INCLUDED
