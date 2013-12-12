#ifndef NAGLOWKI_H_INCLUDED
#define NAGLOWKI_H_INCLUDED

#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAXCOMMENT 100
#define B_AND_W 1
#define GR_SCALE 2
#define COLOR 3
#define MAGIC_NUMBER 1
#define BAD_FILE_TYPE -1
#define TYPE_OK 1
#define DIM_OK 1


typedef struct element
{
    struct element *next;
    char type[2+1];
    int data;
    char wymiary[2+1]; // macierz [x,y]
    char comment[MAXCOMMENT];
} element;

element *push(element *, element *);
void wyswietl(element *);
element * usun(element *);
element * wczytajobraz(element*);
void sprawdz_komentarz(FILE *pFile);
int sprawdz_typ(FILE *pFile, element *temp);
int sprawdz_wymiary(FILE *pFile, element *temp);


element * wczytajobraz(element *lista)
{
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
        sprawdz_komentarz(pFile);

        if ( (sprawdz_typ(pFile, temp)) == TYPE_OK ) //odczytany typ
        {
            sprawdz_komentarz(pFile);

            if( sprawdz_wymiary(pFile, temp) == DIM_OK )
            {
                sprawdz_komentarz(pFile);
                //to fajnie, mozna przejsc do pobierania danych do tablicy
            }
            else ;//flaga error

        } //odczytrany typ i magic number, flaga ze mamy typ i magic number

        else ;//flaga error

        temp->next=NULL;
        lista=push(lista, temp);
        printf("dodano obraz\n");

    }

    free(temp);
    fclose(pFile);

    return lista;
}
int sprawdz_wymiary(FILE *pFile, element *temp)
{
    fscanf(pFile, "%d", &temp->wymiary[0]);
    fscanf(pFile, "%d", &temp->wymiary[1]);
    temp->wymiary[2] = '\0';
    return DIM_OK; //or no // dopisac
}
int sprawdz_typ(FILE *pFile, element *temp)
{
    temp->type[0] = fgetc(pFile);

    if(temp->type[0] == 'P')
    {
        temp->type[MAGIC_NUMBER] = fgetc(pFile);
        if( (temp->type[MAGIC_NUMBER] == '1') || (temp->type[MAGIC_NUMBER] == '2') || (temp->type[MAGIC_NUMBER] == '3') )
        {
            temp->type[2] = '\0';
            return TYPE_OK;
        }
        else return BAD_FILE_TYPE;
    }
    else return BAD_FILE_TYPE;
}
void sprawdz_komentarz(FILE *pFile)
{
    char test;
    if( (test = fgetc(pFile)) == '#')
    {
        // zspisuje linie komentarza()
        sprawdz_komentarz(pFile);
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
            printf("\ntyp obrazu to %s\nwymiary to %d na %d\n", first->type, first->wymiary[0], first->wymiary[1]);
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
