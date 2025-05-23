#include <stdio.h>
#include <stdlib.h>

struct Nod {
    int valoare;
    struct Nod* anterior;
    struct Nod* urmator;
};

typedef struct Nod Nod;

Nod* creare_nod(int valoare) {
    Nod* nod_nou = (Nod*)malloc(sizeof(Nod));
    nod_nou->valoare = valoare;
    nod_nou->anterior = NULL;
    nod_nou->urmator = NULL;
    return nod_nou;
}

void adauga_inceput(Nod** cap, int valoare) {
    Nod* nod_nou = creare_nod(valoare);
    if (*cap != NULL) {
        nod_nou->urmator = *cap;
        (*cap)->anterior = nod_nou;
    }
    *cap = nod_nou;
}

void afisare_lista(Nod* cap) {
    Nod* curent = cap;
    while (curent != NULL) {
        printf("%d ", curent->valoare);
        curent = curent->urmator;
    }
    printf("\n");
}

void adauga_sfarsit(Nod** cap, int valoare) {
    Nod* nod_nou = creare_nod(valoare);
    if (*cap == NULL) {
        *cap = nod_nou;
        return;
    }
    Nod* curent = *cap;
    while (curent->urmator != NULL) {
        curent = curent->urmator;
    }
    curent->urmator = nod_nou;
    nod_nou->anterior = curent;
}

void sterge_nod(Nod** cap, int valoare) {
    Nod* curent = *cap;
    while (curent != NULL && curent->valoare != valoare) {
        curent = curent->urmator;
    }
    if (curent == NULL) return;
    if (curent->anterior != NULL) {
        curent->anterior->urmator = curent->urmator;
    }
    else {
        *cap = curent->urmator;
    }
    if (curent->urmator != NULL) {
        curent->urmator->anterior = curent->anterior;
    }
    free(curent);
}

int main() {
    Nod* lista = NULL;
    adauga_inceput(&lista, 3);
    adauga_inceput(&lista, 2);
    adauga_inceput(&lista, 1);
    afisare_lista(lista);
    adauga_sfarsit(&lista, 4);
    adauga_sfarsit(&lista, 5);
    afisare_lista(lista);
    sterge_nod(&lista, 3);
    afisare_lista(lista);
    return 0;
}