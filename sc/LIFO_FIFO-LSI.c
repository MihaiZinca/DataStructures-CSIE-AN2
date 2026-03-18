#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include <string.h>


//STIVA(LIFO) / COADA(FIFO) LSI 
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
};

//INSERARE LA  szINCEPUT
void push(Nod** varf, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = *varf;
	*varf = nou;
}

//INSERARE SFARSIT
void put(Nod** prim, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = NULL;
	if ((*prim) == NULL)
	{
		*prim = nou;
	}
	else
	{
		Nod* aux = *prim;
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = nou;
	}
}
//TRAVERSARE/EXTRAGERE INCEPUT
Carte pop(Nod** stiva)
{
	if (*stiva == NULL)
		return initCarte(NULL, 0, 0);
	
	//shallow copy
	Carte c = (*stiva)->info;
	//deep copy
	//Carte c = initCarte((*stiva)->info.titlu, (*stiva)->info.nrPagini, ..);

	Nod* copie = *stiva;
	*stiva = (*stiva)->next;
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

void CoadaInVector(Nod** coada, Carte** vectorCarti,int nrCarti)
{
	*vectorCarti = (Carte*)malloc(sizeof(Carte) * nrCarti);
	int i = 0;
	while (*coada != NULL)
	{
		(*vectorCarti)[i] = pop(coada);
		i++;
	}
}

void StivaInCoada(Nod** stiva,Nod** coada)
{
	Nod* aux = NULL;
	while (*stiva != NULL)
	{
		Carte c = pop(stiva);
		push(&aux, c);
	}
	while (aux != NULL)
	{
		Carte c = pop(&aux);
		put(coada, c);
	}
}

void CoadaInStiva(Nod** coada, Nod** stiva)
{
	while (*coada != NULL)
	{
		Carte c = pop(coada);
		push(stiva, c);
	}
}

int main() {
	Nod* stiva = NULL;
	push(&stiva, initCarte("Carte1", 240, 45));
	push(&stiva, initCarte("Carte2", 320, 62.5));
	push(&stiva, initCarte("Carte3", 170, 50));
	push(&stiva, initCarte("Carte4", 225, 61));

	printf("\nTraversare stiva:");
	Carte c;
	while (stiva != NULL)
	{
		c = pop(&stiva);
		afisareCarte(c);
		free(c.titlu);

	}


	Nod* coada = NULL;
	put(&coada, initCarte("Carte1", 240, 45));
	put(&coada, initCarte("Carte2", 320, 62.5));
	put(&coada, initCarte("Carte3", 170, 50));
	put(&coada, initCarte("Carte4", 225, 61));

	printf("\nTraversare coada:");
	while (coada != NULL)
	{
		c = pop(&coada); //get este pop
		afisareCarte(c);
		free(c.titlu);

	}

	printf("\nCoada dupa conversie din stiva:");
	while (coada != NULL)
	{
		Carte c = pop(&coada);
		afisareCarte(c);
		free(c.titlu);
	}
	

	return 0;
}