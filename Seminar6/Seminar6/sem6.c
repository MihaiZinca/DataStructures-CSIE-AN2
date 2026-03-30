#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

//HashTable(Chaining)

//coliziune -inserare mai multe elemente pe aceeasi pozitie
//chaining - toate elementele se pun intr o lista simpla,
//initial,vectorul este full null, apoi se retine in vector adresa capului listei
//elementele vectorului= adresele capetelor listelor -liste in liste gen



typedef struct Nod Nod;

typedef struct HashTable HashTable;

typedef struct Carte {
	char* titlu;
	int nrPagini;
	float pret;
} Carte;

struct Nod {
	Carte info;
	Nod* next;
};


struct HashTable
{
	Nod** vector; //implementarea este un vector de liste
	int size;
};


void inserareLaSfarsit(Nod** cap, Carte c) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c; //shallow copy util
	nou->next = NULL;
	if ((*cap) == NULL) {
		*cap = nou;
	}
	else {
		Nod* aux = *cap;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = nou;
	}
}

Carte initCarte(const char* titlu, int nrPagini, float pret) {
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

void afisareListaCarti(Nod* cap) {
	while (cap != NULL) {
		afisareCarte(cap->info);
		cap = cap->next;
	}
}

void dezalocare(Nod** cap) {
	while ((*cap) != NULL) {
		free((*cap)->info.titlu);
		Nod* aux = *cap;
		*cap = (*cap)->next;
		free(aux);
	}
}

//initializare tabela cu null
HashTable initTable(int dim)
{
	HashTable tabela;
	tabela.size = dim;
	tabela.vector = (Nod**)malloc(dim * sizeof(Nod*));
	for (int i = 0;i < dim;i++)
	{
		tabela.vector[i] = NULL;
	}

	return tabela; 
}

int hash(int nrPagini, int size)
{
	return nrPagini % size; //ne va da o valoarae intre 0 si size-1
}

//mecanismul de tratare a coliziunii este chaining -la test asta ,alte metode si la examen
void inserareInTabela(HashTable table,Carte c) //transmitem prin valoare hashtable pentru ca nu modific
{
	if (table.size > 0)
	{
		int pozitie = hash(c.nrPagini, table.size);
		if (pozitie >= 0 && pozitie < table.size)
		{
			inserareLaSfarsit(&(table.vector[pozitie]), c); //tabela.vector este de tip nod*
		}
	}

}

void parcurgereTabela(HashTable tabela)
{
	for (int i = 0;i < tabela.size;i++)
	{
		printf("Pozitie: %d\n", i);
		afisareListaCarti(tabela.vector[i]);
	}
}

void dezalocareTabela(HashTable tabela)
{
	for (int i = 0;i < tabela.size;i++)
	{
		dezalocare(&(tabela.vector[i]));
	}
	free(tabela.vector);
}

//pretul mediu pt o carte, pt toate cartile care au dat un nr de pagini dat ca parametru --daca avem cheia facem functia hash!!
float calculPretMediu(HashTable tabela, int nrPagini)
{
	int poz = hash(nrPagini, tabela.size);
	Nod* cap = tabela.vector[poz]; //extrag din vector nodul de la pozitia poz

	float s = 0;
	int nr = 0;
	while (cap != NULL)
	{
		if (cap->info.nrPagini == nrPagini)
		{
			s += cap->info.pret;
			nr++;
		}
		cap = cap->next;
	}

	if (nr > 0)
		return s / nr;
	else
		return 0;
}


int main() {

	//2 abordari de salvare declar o structura si salevez datele vect

	HashTable tabela = initTable(6);
	inserareInTabela(tabela,initCarte("MiculPrint", 132, 35.2)); //132%6=0
	inserareInTabela(tabela, initCarte("Nuntasii", 122, 46.9)); // 122 % 6 = 2
	inserareInTabela(tabela, initCarte("Nuntasii2", 122, 71.5));
	inserareInTabela(tabela, initCarte("Confess", 126, 34.3)); //126%6=0
	//prima si ultima care coliziune poz 0

	parcurgereTabela(tabela);
	//dezalocareTabela(tabela);

	//functia hash modulo(%) dim -returneaza pozitia pe care se va insera elementul, cuprinsa intre [0,dim)
	//ex nostru :nrPagini% dim , pret%dim, pret/100  , strlen(titlu) , cod ASCII

	int nrPagini = 122;
	printf("\n Pretul mediu pentru o carte cu %d nr pagini este: %.2f lei!", nrPagini, calculPretMediu(tabela, nrPagini));



	//Pana aici intra la test!!!  test pe 20!
	//nota 4-- sa stiu sa citesc informatii utila din fisier,sa folosesc functia de initCarte -ce am fct in sapt3 
	//--sa stiu sa fac insert in structura pe care o primesc
	//--sa stiu sa afisez/traversez
	//--intra tot ce am discutat, vector,lsi,ldi,lista circulara, coada ,stiva, hashtable
	//+ CONVERSIE INTRE STRUCTURI(toate intre ele gen)
	//-timp 35 de min

	return 0;
}