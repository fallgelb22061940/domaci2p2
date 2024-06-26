#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct doprinos // originalna struktura
{
    char mejl[256];
    int broj_linija;
    char datum[11];
} doprinos;
typedef struct elem // ulančana lista
{
    doprinos red;
    struct elem *next;
} elem;
// otvaranje fajla i smeštanje podataka u ulančanu listu
elem *ulaz()
{
    FILE *ulaz = fopen("contribution.txt", "r");
    if (!ulaz) // ispiši grešku ako fajl ne postoji
    {
        printf("DAT_GRESKA");
        exit(0);
    }
    elem *glava = NULL, *rep = glava, *tmp;
    doprinos red;
    char *format = "%s %d %s";
    while (fscanf(ulaz, format, red.mejl, &red.broj_linija, red.datum) == 3) // fscanf vraća broj pročitanih podataka, tako da čita dok ima šta da se čita
    {
        tmp = malloc(sizeof(elem));
        tmp->red = red;
        if (glava == 0)
        {
            rep = tmp;
            glava = rep; // dodela vrednosti na početku
        }
        else
        {
            rep->next = tmp;
            rep = rep->next; //čitaj dalje dok ima šta da se čita
        }
    }
    rep->next = 0;
    fclose(ulaz);
    return glava;
}
// Sortiranje leksikografski kako bi bila lakša obrada, plus jedan od zahteva je da je to sekundarno sortiranje
void sort1(elem *lista)
{
    for (elem *prvi = lista; prvi; prvi = prvi->next)
    {
        for (elem *drugi = lista; drugi; drugi = drugi->next)
        {
            if (strcmp(prvi->red.mejl, drugi->red.mejl) <= 0) // strcmp vraća manje od 0 ukoliko bi u rečniku prvi bio ispred drugog
            {
                doprinos tmp = prvi->red;
                prvi->red = drugi->red;
                drugi->red = tmp;
            }
        }
    }
}
// Spajanje doprinosa sa istim mejlom
void merge(elem *lista)
{
    while (lista->next)
    {
        elem *sled = lista->next;

        if (strcmp(lista->red.mejl, sled->red.mejl) == 0) // ako se poklapaju mejlovi
        {
            lista->red.broj_linija += sled->red.broj_linija; // sabiranje broja linija u slučaju da je uslov ispunjen
            lista->next = sled->next;                        // izbacivanje člana iz liste
            free(sled);                                      // brisanje izbačenog člana
        }
        else
        {
            lista = lista->next; // ako se ne poklapaju mejlovi ide dalje
        }
    }
}
// sortiranje po učinku
void sort2(elem *lista)
{
    for (elem *prvi = lista; prvi; prvi = prvi->next)
    {
        for (elem *drugi = lista; drugi; drugi = drugi->next)
        {
            if (prvi->red.broj_linija > drugi->red.broj_linija)
            {
                doprinos tmp = prvi->red;
                prvi->red = drugi->red;
                drugi->red = tmp;
            }
        }
    }
}
// Ispis u zadati fajl
void ispis(elem *lista)
{
    FILE *izlaz = fopen("result.txt", "w+");
    for (; lista; lista = lista->next) // dok se nalazi u listi da ponavlja ispis
    {
        fprintf(izlaz, "%s %d", lista->red.mejl, lista->red.broj_linija); // ispis samo potrebnih podataka, datum nije potreban
        if (lista->next)
        {
            fprintf(izlaz, "\n"); // da ne ispiše novi red u zadnjem redu
        }
    }
    fclose(izlaz);
}
// Čišćenje memorije posle izvršenog programa
void pocisti(elem *lista)
{
    while (lista) // vrti petlju po listi i čisti svaki član
    {
        elem *sled = lista->next;
        free(lista);
        lista = sled;
    }
}
// U main samo pozivi funkcija
int main()
{
    elem *start = ulaz();
    sort1(start);
    merge(start);
    sort2(start);
    ispis(start);
    pocisti(start);
    return 0;
}