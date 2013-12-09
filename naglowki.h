#ifndef NAGLOWKI_H_INCLUDED
#define NAGLOWKI_H_INCLUDED

#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAXCOMMENT 10

typedef struct element
{
    struct element *next;
    int type;
    int data;
    // int x, y;
    //char comment[MAXCOMMENT];
}element;

element *push(element *, element *);
void wyswietl(element *);
element * usun(element *);
element * wczytajobraz(element*);


element * wczytajobraz(element *lista)
{
    element *temp;
    temp=(element*)malloc(sizeof(element));

    FILE * pFile;
    pFile=fopen("pic.pgm", "rt");
    if(pFile==NULL)
    {
        perror("blad otwarcia pliku");
    }
    else
    {

        if( ( temp->type = fgetc(pFile))!='P')
            printf("zły typ obrazka\n");

        else
        {
            fscanf(pFile, "%d", &temp->type);
            printf("typ obrazka to P%d\n", temp->type);
            temp->next=NULL;
            lista=push(lista, temp);
            printf("dodano obraz\n");
        }
    }
    free(temp);
    fclose(pFile);

    return lista;
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
    //printf("%d", first->data);
    if(first==NULL)
    {
        printf("lista jest pusta\n");
    }
    else
    {
        do
        {
            printf("typ obrazu to P%d", first->type);
            first=first->next;      //modyfikuijmy tylko kopie wskaznika!
        }while(first!=NULL);
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
