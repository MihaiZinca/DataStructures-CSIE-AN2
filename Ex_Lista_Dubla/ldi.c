#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct Carte
{
	char* titlu;
	int nrPagini;
	float pret;
}Carte;

typedef struct Nod Nod;
struct Nod {
	Carte info;
	Nod* next;
	Nod* prev;
};

void inserareLaInceput(Nod** cap, Nod** coada, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = *cap;
	nou->prev = NULL;
	if (*cap == NULL)
	{
		*cap = *coada = nou;
	}
	else
	{
		(*cap)->prev = nou;
		*cap = nou;
	}
}

void inserareLaSfarsit(Nod** cap, Nod** coada, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = NULL;
	nou->prev = *coada;
	if ((*cap) == NULL)
	{
		*cap = *coada = nou;
	}
	else
	{
		(*coada)->next = nou;
		*coada = nou;
	}

}

void inserareIntre(Nod* aux, Nod** coada, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	if (aux->next == NULL)
	{
		aux->next = nou;
		aux->prev = nou;
		nou->next = NULL;
		
		*coada = nou;
	}
	else //inserare intre doua nod
	{
		nou->next = aux->next;
		nou->prev = aux;

		aux->next->prev = nou;
		aux->next = nou;
	}
}

void insereareDupaPret(Nod** cap, Nod** coada, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = NULL;
	nou->prev = NULL;
	if ((*cap) == NULL)
	{
		*cap = *coada = nou;
	}
	else if (c.pret < (*cap)->info.pret) //inserare la inceput
	{
		nou->next = *cap;
		(*cap)->prev = nou;
		*cap = nou;
	}
	else if (c.pret >= (*coada)->info.pret)//inserare la sfarsit
	{
		nou->prev = *coada;
		(*coada)->next = nou;
		*coada = nou;
	}
	else //inserare intre ele
	{
		Nod* aux = *cap;
		while (aux->next != NULL && aux->next->info.pret < c.pret)
			aux = aux->next;

		nou->next = aux->next; //nou pointeaza la nodul urmator
		nou->prev = aux;//nou pointeaza inapoi la nodul precedent

		aux->next->prev = nou; //nodul urmator trb sa stie ca inaintea lui vine nou
		aux->next = nou; //nodul precedent pointeaza catre nou
	}

}

void inseareInceputCircular(Nod** cap, Nod** coada, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	if ((*cap) == NULL)
	{
		nou->next = nou;
		nou->prev = nou;
		*cap = *coada = nou;
	}
	else
	{
		nou->next = *cap;
		nou->prev = *coada;

		(*cap)->prev = nou;
		(*coada)->next = nou;
		*cap = nou;
	}
}

void inserareSfarsitCircular(Nod** cap, Nod** coada, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	if ((*cap) = NULL)
	{
		nou->next = nou;
		nou->prev = nou;
		*cap = *coada = nou;
	}
	else
	{
		nou->next = *cap;
		nou->prev = *coada;

		(*coada)->next = nou;
		(*cap)->prev = nou;

		*coada = nou;
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
	printf("Titlu: %s, nrPagini: %d, pret: %.2f. \n", carte.titlu, carte.nrPagini, carte.pret);
}

//de la st la dr
void afisareListaCarti(Nod* cap)
{
	while (cap != NULL)
	{
		afisareCarte(cap->info);
		cap = cap->next;
	}
}

//de la dr la st
void afisareInversaListaCarti(Nod* coada)
{
	while (coada != NULL)
	{
		afisareCarte(coada->info);
		coada = coada->prev;
	}
}

void afisareListaCirculara(Nod* cap)
{
	if (!cap)
		return;

	Nod* aux = cap;
	do
	{
		afisareCarte(cap->info);
		cap = cap->next;
	} while (cap != aux);
}


void dezalocare(Nod** cap, Nod** coada)
{
	while ((*cap) != NULL)
	{
		free((*cap)->info.titlu);
		Nod* aux = *cap;
		*cap = (*cap)->next;
		free(aux);
	}
	*coada = NULL;
}

void dezalocareCirculara(Nod** cap, Nod** coada)
{
	(*cap)->prev = NULL;
	(*coada)->next = NULL;
	
	while ((*cap) != NULL)
	{
		free((*cap)->info.titlu);
		Nod* aux = *cap;
		*cap = (*cap)->next;
		free(aux);
	}
	*coada = NULL;

}

float pretMediuCarte(Nod* coada)
{
	int nrCarti = 0;
	float sumaPreturi = 0;
	while (coada != NULL)
	{
		sumaPreturi += coada->info.pret;
		nrCarti++;
		coada = coada->prev;
	}
	if (nrCarti != 0)return sumaPreturi / nrCarti;
	else return 0;
}

//CONVERSIE VECTOR->LSI
Nod* vectorTOLSI(Carte v[], int n)
{
	Nod* cap = NULL;
	for (int i = n - 1; i >= 0; i--)
	{
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = v[i];
		nou->next = cap;
		cap = nou;
	}
	return cap;
}
//CONVERSIE LSI->VECTOR
int lsiToVector(Nod* cap, Carte v[])
{
	int n = 0;
	while (cap != NULL)
	{
		v[n++] = cap->info;
		cap = cap->next;
	}
	return n;
}

//conversie LSI->LDI
void lsiTOldi(Nod* lsi, Nod** cap, Nod** coada)
{
	*cap = *coada = NULL;

	while (lsi != NULL)
	{
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = lsi->info;
		nou->next = NULL;
		nou->prev = *coada;

		if ((*coada) != NULL)
		{
			(*coada)->next = nou;
		}
		else
			*cap = nou;
		
		*coada = nou;
		lsi = lsi->next;
	}
}

//conversie LDI->LSI

Nod* ldiTOlsi(Nod* cap)
{
	Nod* h = NULL; //capul LSI
	Nod* t = NULL; //pt sfarsit

	while (cap != NULL)
	{
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = cap->info;
		nou->next = NULL;

		if (t != NULL) 
			t->next = nou; 
		else
			h = nou;

		t = nou;
		cap = cap->next;
	}
	return h;
}
int main()
{
	Nod* cap = NULL;
	Nod* coada = NULL;

	Carte c1 = initCarte("Ion", 300, 45.5);
	Carte c2 = initCarte("Morometii", 250, 39.9);
	Carte c3 = initCarte("Baltagul", 200, 29.5);
	Carte c4 = initCarte("Enigma Otiliei", 350, 55.0);
	Carte c5 = initCarte("Amintiri din copilarie", 150, 20.0);

	inserareLaInceput(&cap, &coada, c1);
	inserareLaSfarsit(&cap, &coada, c2);
	inserareLaSfarsit(&cap, &coada, c3);
	inserareLaSfarsit(&cap, &coada, c4);

	afisareListaCarti(cap);
	printf("\n");

	afisareInversaListaCarti(coada);
	printf("\n");

	insereareDupaPret(&cap, &coada, c5);

	afisareListaCarti(cap);
	printf("\n");

	printf("Pret mediu: %.2f\n", pretMediuCarte(coada));

	Carte vector[10];
	int n = lsiToVector(cap, vector);

	for (int i = 0; i < n; i++)
	{
		afisareCarte(vector[i]);
	}

	Nod* capLSI = vectorTOLSI(vector, n);
	printf("\n");

	afisareListaCarti(capLSI);

	Nod* capLDI = NULL;
	Nod* coadaLDI = NULL;

	lsiTOldi(capLSI, &capLDI, &coadaLDI);
	printf("\n");

	afisareListaCarti(capLDI);

	Nod* listaSimpla = ldiTOlsi(capLDI);
	printf("\n");

	afisareListaCarti(listaSimpla);

	dezalocare(&cap, &coada);
	dezalocare(&capLDI, &coadaLDI);

	return 0;
}
