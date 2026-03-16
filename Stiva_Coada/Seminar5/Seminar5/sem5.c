#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

/*STIVA(LIFO) / COADA(FIFO) facem pe LSI -> to do pt LDI
* fie inseram la sfarsit si stergem de la sfarsit ->to do
* la stiva fie inseram la inceput, si extragere la inceput  -la seminar
* 
* la coada inserez la final si extrag de la inceput    !! to do inserare la inceput si extragele la final
*
*/

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

//inserarea intr-o stiva se numeste push=inserareLaInceput

void push(Nod** varf, Carte c) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c; 
	nou->next = *varf;
	*varf = nou;
}


//prim=cap
void put(Nod** prim, Carte c) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c; 
	nou->next = NULL;
	if ((*prim) == NULL) {
		*prim = nou;
	}
	else {
		Nod* aux = *prim;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = nou;
	}
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


Carte pop(Nod** stiva)
{
	if (*stiva == NULL)
	{
		return initCarte(NULL, 0, 0);
	}
	Carte c = (*stiva)->info;//shallow copy

	// deep copy
	//Carte c=initCarte((*stiva)->info.titlu,(*stiva)->info.nrPagini,....)
	//dupa trebuie dezalocare de mai multe ori

	Nod* copie = *stiva; //salvam nodul din varf
	*stiva = (*stiva)->next; //mutam varful stivei
	free(copie);//adica de vechiul varf

	return c;
}


void conversieDinCoadaInVector(Nod** coada, Carte** vectorCarti, int nrCarti)
{
	*vectorCarti = (Carte*)malloc(sizeof(Carte) * nrCarti);
	int i = 0;
	while (*coada != NULL)
	{
		(*vectorCarti)[i] = pop(coada);
		i++;

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

	//printf("\nTraversare coada:");
	//while (coada != NULL)
	//{ 
	//	c = pop(&coada); //get este pop
	//	afisareCarte(c);
	//	free(c.titlu);

	//}

	printf("\nConversie in vector:");
	Carte* vectorCArti = NULL;
	int nrCarti = 4;
	conversieDinCoadaInVector(&coada, &vectorCArti, nrCarti);
	if (vectorCArti != NULL)
	{

		for (int i = 0;i < nrCarti;i++)
		{
			afisareCarte(vectorCArti[i]);
			free(vectorCArti[i].titlu);
		}
		free(vectorCArti);
	}
	return 0;
}