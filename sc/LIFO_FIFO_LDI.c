#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include <string.h>


//STIVA(LIFO) / COADA(FIFO) LDI
//LIFO -INSERARE LA INCEPUT,EXTRAGERE INCEPUT
//FIFO - INSERARE FINAL, EXTRAGERE INCEPUT


typedef struct Nod Nod;

typedef struct Carte {
	char* titlu;
	int nrPagini;
	float pret;
} Carte;

struct Nod {
	Carte info;
	Nod* next;
	Nod* prev;
};

//inserare la inceput
void push(Nod** varf,Nod**sfarsit, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = *varf;
	nou->prev = NULL;
	if ((*varf) == NULL)
	{
		*varf = *sfarsit = nou;
	}
	else
	{
		(*varf)->prev = nou;
		*varf = nou;
	}
}

//inseare final
void put(Nod** prim, Nod** sfarsit, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = NULL;
	nou->prev = *sfarsit;
	if ((*prim) == NULL)
	{
		*prim = *sfarsit = nou;
	}
	else
	{
		(*sfarsit)->next = nou;
		*sfarsit = nou;
	}
}

//EXTRAGERE/TRAVERSARE INCEPUT
Carte pop(Nod** varf, Nod** sfarsit)
{
	if (*varf == NULL)
		return initCarte(NULL, 0, 0);

	Carte c = (*varf)->info;
	Nod* copie = *varf;
	*varf = (*varf)->next;
	if (*varf != NULL)
		(*varf)->prev = NULL;
	else
		*sfarsit = NULL;
	free(copie);
	return c;
}

Carte initCarte(const char* titlu, int nrPagini, float pret)
{
	Carte c;
	c.nrPagini = nrPagini;
	c.pret = pret;
	c.titlu = (char*)malloc(sizeof(char) * (strlen(titlu) + 1));
	strcpy(c.titlu, titlu);
	return c;
}

void afisareCarte(Carte carte) {
	printf("\nTitlu: %s, nrPagini: %d, pret: %.2f.", carte.titlu, carte.nrPagini, carte.pret);
}

void StivaInCoada(Nod** stiva, Nod** coada)
{
	Nod* aux_v = NULL;
	Nod* aux_s = NULL;
	while (*stiva != NULL)
	{
		Carte c = pop(stiva,coada);
		push(&aux_v,&aux_s,c);
	}
	while (aux_v != NULL)
	{
		Carte c = pop(&aux_v,&aux_s);
		push(stiva,coada, c);
	}
}

void CoadaInStiva(Nod** coada, Nod** stiva)
{
	Nod* aux_s = NULL;
	Nod* aux_c = NULL;
	while (*coada != NULL)
	{
		Carte c = pop(coada,stiva);
		push(&aux_s,&aux_c, c);
	}
}

int main() {
	// ---------- STIVA (LIFO) ----------
	Nod* varf = NULL;
	Nod* sfarsit = NULL;

	push(&varf, &sfarsit, initCarte("Carte A", 100, 10));
	push(&varf, &sfarsit, initCarte("Carte B", 200, 20));
	push(&varf, &sfarsit, initCarte("Carte C", 150, 15));

	printf("Traversare Stiva (LIFO):\n");
	while (varf != NULL) {
		Carte c = pop(&varf, &sfarsit);
		afisareCarte(c);
		free(c.titlu);
	}

	// ---------- COADA (FIFO) ----------
	Nod* cap = NULL;
	Nod* coada = NULL;

	put(&cap, &coada, initCarte("Carte X", 120, 12));
	put(&cap, &coada, initCarte("Carte Y", 220, 22));
	put(&cap, &coada, initCarte("Carte Z", 180, 18));

	printf("\nTraversare Coada (FIFO):\n");
	while (cap != NULL) {
		Carte c = pop(&cap, &coada); // extragere de la început
		afisareCarte(c);
		free(c.titlu);
	}

	return 0;
}