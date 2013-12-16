#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED


#define MAXCOMMENT 10000
#define MAXNAZWA 20


typedef struct element
{
    struct element *next;
    int numer; //numer kazdego obrazka w liscie
    int czy_zmieniony;
    char type[2+1];
    int odcienie;
    int wymx;
    int wymy;
    char comment[MAXCOMMENT];
    int **obraz;
    char nazwa[MAXNAZWA];
} element;

#endif // INIT_H_INCLUDED
