#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct doprinos
{
    char mejl[256];
    int broj_linija;
    char datum[11];
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
    while (fscanf(ulaz, format, red.mejl, &red.broj_linija, red.datum) == 3)
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
void merge(elem *lista)
{
    elem *promenljiva;
    for (elem *prvi = lista; prvi; prvi = prvi->next)
    {
        for (elem *drugi = lista->next; drugi; drugi = drugi->next)
        {
            if (!strcmp(drugi->red.mejl, prvi->red.mejl))
            {
                prvi->red.broj_linija += drugi->red.broj_linija;
                free(drugi);
            }
            promenljiva = drugi;
        }
    }
}
void ispis(elem *lista)
{
    FILE *izlaz = fopen("result.txt", "w+");
    for (; lista; lista = lista->next)
    {
        fprintf(izlaz, "%s %d\n", lista->red.mejl, lista->red.broj_linija);
    }
    fclose(izlaz);
}
int main()
{
    elem *start = ulaz();
    // merge(start);
    ispis(start);
    return 0;
}