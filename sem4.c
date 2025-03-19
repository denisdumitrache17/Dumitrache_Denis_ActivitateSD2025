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

//creare structura pentru un nod dintr-o lista dublu inlantuita

struct nod
{
	Masina info;
	struct nod* next;
};
typedef struct nod n;

//creare structura pentru Lista Dubla 

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

void afisareListaMasini(n* nod) {

	while (nod)
	{
		afisareMasina(nod->info);
		nod = nod->next;
	}
	 
}

void adaugaMasinaInLista(n** lista, Masina masinaNoua) {

	n* nodNou;
	nodNou = (n*)malloc(sizeof(n));
	nodNou->info = masinaNoua;
	nodNou->next = NULL;

	if ((*lista) == NULL)
	{
		(*lista) = nodNou;
	}
	else
	{
		n* aux=(*lista);
		while (aux->next)
		{
			aux = aux->next;
		}
		aux->next = nodNou;
	}

	//adauga la final in lista primita o noua masina pe care o primim ca parametru
}

void adaugaLaInceputInLista(/*lista dubla de masini*/ Masina masinaNoua) {
	//adauga la inceputul listei dublu inlantuite o noua masina pe care o primim ca parametru
}

n* citireLDMasiniDinFisier(const char* numeFisier) {
	
	FILE* f = fopen(numeFisier, "r");
	n* lista = NULL;
	
	while (!feof(f))
	{
		Masina masinaNoua;
		masinaNoua=citireMasinaDinFisier(f);
		adaugaMasinaInLista(&lista, masinaNoua);
	}
	fclose(f);

	return lista;

}

void dezalocareLDMasini(n** lista) {

	while ((*lista))
	{
		n* p = (*lista);
		free(p->info.model);
		free(p->info.numeSofer);
		(*lista) = (*lista)->next;
		free(p);
	}
	//sunt dezalocate toate masinile si lista dublu inlantuita de elemente
}

float calculeazaPretMediu(n* lista) {
	
	float suma = 0;
	int contor = 0;
	while (lista)
	{
		suma = suma+lista->info.pret;
		contor++;
	}

	if (contor == 0)
		return 0;
	else
		return suma / contor;
}

void stergeMasinaDupaID(/*lista masini*/ int id) {
	//sterge masina cu id-ul primit.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
}

float calculeazaPretulMasinilorUnuiSofer(n* lista, const char* numeSofer) {
	
	float suma = 0;
	while (lista)
	{
		if (strcmp(lista->info.numeSofer, numeSofer) == 0)
			suma = suma + lista->info.pret;
	lista = lista->next;
	}
	return suma;
}

int getNrUsiMasinaScumpa(n* lista)
{
	if (lista)
	{
		float pretMaxim = lista->info.pret;
		int nrUsi = lista->info.nrUsi;
		lista = lista->next;
		while (lista)
		{
			if (lista->info.pret > pretMaxim)
			{
				nrUsi = lista->info.nrUsi;
				pretMaxim = lista->info.pret;
			}
			lista = lista->next;
		}
		return nrUsi;
	}
	return 0;
}

int main() {
	n* nod;
	nod = citireLDMasiniDinFisier("masini.txt");
	afisareListaMasini(nod);
	dezalocareLDMasini(&nod);
	float medie;
	medie=calculeazaPretMediu(nod);
	printf("Media este: %.2f", medie);

	float suma;
	suma = calculeazaPretulMasinilorUnuiSofer(nod, "Ionescu");
	dezalocareLDMasini(&nod);

	int nrUsi;
	nrUsi=getNrUsiMasinaScumpa(nod);
	return 0;
}