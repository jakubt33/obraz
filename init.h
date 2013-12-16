#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#define MAXCOMMENT 1000
#define MAXNAZWA 20

void error();

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


void error()
{
    while((getchar()) != '\n');
    printf("zła komenda\n");
}

#endif // INIT_H_INCLUDED
