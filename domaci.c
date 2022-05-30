#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct doprinos
{
    char mejl[256];
    int broj_linija;
    int ukupno_linija;
    char *datum[11];
} doprinos;
typedef struct elem
{
    doprinos red;
    struct elem *next;
    // struct elem *prev;
} elem;
elem *ulaz()
{
    FILE *ulaz = fopen("contribution.txt", "r");
    if (!ulaz)
    {
        printf("DAT_GRESKA");
        exit(0);
    }
    elem *vugla = NULL, *rep = vugla, *tmp;
    doprinos red;
    char *format = "%s %d %s";
    while (fscanf(ulaz, format, red.mejl, red.broj_linija, red.datum) == 3)
    {
        tmp = malloc(sizeof(elem));
        tmp->red = red;
        if (vugla == 0)
        {
            rep = tmp;
            vugla = rep;
        }
        else
        {
            rep->next = tmp;
            rep = rep->next;
        }
    }
    rep->next = 0;
    fclose(ulaz);
    return vugla;
}
elem *merge(elem *lista)
{
}
int main()
{
    elem *start = ulaz();
    FILE *izlaz = fopen("result.txt", "w+");
    fclose(izlaz);
    return 0;
}