#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

struct nod {
	
	Masina info;
	struct nod* next;

};
typedef struct nod nod;

//creare structura pentru un nod dintr-o lista simplu inlantuita

//creare structura pentru tabela de dispersie
// aceasta este un vector de liste
struct HashTable {
	
	nod** vector; // vector pointeri
	int dim;

};
typedef struct HashTable HashTable;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareListaMasini(nod* lista) {
	
	nod* p = lista;
	
	while (p)
	{
		afisareMasina(p->info);
		p = p->next;
	}
	
}

void adaugaMasinaInLista(nod** lista, Masina masinaNoua) {

	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = masinaNoua;
	nou->next = NULL;
	
	if (*lista)
	{
		nod* p = *lista;
		while (p->next)
		{
			p = p->next;

		}
		p->next = nou;
	}
	else
	{
		*lista = nou;
	}
	
}


HashTable initializareHashTable(int dimensiune) {
	
	HashTable ht;
	
	ht.vector = (nod**)malloc(sizeof(nod*)*dimensiune);
	ht.dim = dimensiune;
	
	for (int i = 0; i < dimensiune; i++)
	{
		ht.vector[i] = NULL;
	}

	return ht;
}

int calculeazaHash(char key, int dimensiune) {

	int hash;
	
	if (dimensiune)
	{
		hash = key % dimensiune;
		return hash;
	}
	else
	{
		return 0;
	}

}

void inserareMasinaInTabela(HashTable hash, Masina masina) {
	
	int pozitieVector = calculeazaHash(masina.serie, hash.dim);
	
	if (pozitieVector< hash.dim)
	{
			if (hash.vector[pozitieVector] != NULL)
			{
				//avem coliziune
				adaugaMasinaInLista(&(hash.vector[pozitieVector]), masina);
			}
			else
			{
				//nu avem coliziune
				hash.vector[pozitieVector] = (nod*)malloc(sizeof(nod));
				hash.vector[pozitieVector]->info = masina;
				hash.vector[pozitieVector]->next = NULL;
			}
	}
}

HashTable citireMasiniDinFisier(const char* numeFisier, int dimensiune) {
	
	FILE* f = fopen(numeFisier, "r");
	HashTable TabelaHash = initializareHashTable(dimensiune);
	
	while (!feof(f))
	{
		Masina m = citireMasinaDinFisier(f);
		inserareMasinaInTabela(TabelaHash, m);
	}
	
	fclose(f);
	return TabelaHash;
}

void afisareTabelaDeMasini(HashTable ht) {

	for (int i = 0; i < ht.dim; i++)
	{
		printf("\nSuntem pe pozitia %d\n", i);
		afisareListaMasini(ht.vector[i]);
	}
}

void dezalocareTabelaDeMasini(HashTable *ht) {
	//sunt dezalocate toate masinile din tabela de dispersie
}

float* calculeazaPreturiMediiPerClustere(HashTable ht, int* nrClustere) {
	//calculeaza pretul mediu al masinilor din fiecare cluster.
	//trebuie sa returnam un vector cu valorile medii per cluster.
	//lungimea vectorului este data de numarul de clustere care contin masini
	return NULL;
}

Masina getMasinaDupaCheie(HashTable ht, char key) {
	Masina m;
	m.id = -1;
	int pozitie = calculeazaHash(serie, ht.dim);
	ht.vector[pozitie];
		if (ht.vector[pozitie] != NULL)
		{
			nod* p = ht.vector[pozitie];
			while (p && p->info.serie != serie)
			{
				p = p->next;
			}
			if (p)
			{
				m = p->info;
				m.model = (char*)malloc(strlen(p->info.model) + 1);
				strcpy(m.model, p->info.model);
				m.numeSofer = (char*)malloc(strlen(p->info.numeSofer) + 1);
				strcpy(m.numeSofer, p->info.numeSofer);

			}
		}
	return m;
}

int main() {
	
	HashTable tabelaHash;
	tabelaHash = citireMasiniDinFisier("masini.txt", 7);
	afisareTabelaDeMasini(tabelaHash);
	Masina m;
	m = getMasinaDupaCheie(tabelaHash, "A");
	printf("\nMasina cu seria: A\n");
	afisareMasina(m);
	free(m.model);
	free(m.numeSofer);
	


	return 0;
}