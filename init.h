#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#define MAXCOMMENT 50

void error();

typedef struct element
{
    struct element *next;
    char type[2+1];
    int odcienie;
    int wymiary[2+1]; // macierz [x,y]
    char comment[MAXCOMMENT];
    int **obraz;
    char nazwa[20];
} element;

void error()
{
    while((getchar()) != '\n');
    printf("zła komenda\n");
}

#endif // INIT_H_INCLUDED
