#include<stdio.h>
#include<malloc.h>

typedef struct
{
	int cod;
	char* marca;
	float pret;
} masina;

typedef struct
{
	masina** vect;
	int nrElem;
} hashT;

int functieHash(hashT tabela, int cheie)
{
	return cheie % tabela.nrElem;
}

void inserareHash(hashT tabela, masina* m)
{
	int poz = functieHash(tabela, (*m).cod);
	if (tabela.vect[poz] == NULL)
		tabela.vect[poz] = m; //shallow copy intre 2 pointeri
	else
	{
		int index = 1;
		while (poz + index < tabela.nrElem)
		{
			if (tabela.vect[poz + index] == NULL)
			{
				poz += index;
				tabela.vect[poz] = m;
				break;
			}
			else
				index++;
		}
	}
}

void traversareHash(hashT tabela)
{
	for (int i = 0; i < tabela.nrElem; i++)
		if (tabela.vect[i] != NULL)
		{
			printf("\nPozitie=%d", i);
			printf("\nCod=%d, Marca=%s, Pret=%5.2f",
				tabela.vect[i]->cod, tabela.vect[i]->marca,
				tabela.vect[i]->pret);
		}
}

void dezalocareHash(hashT tabela)
{
	for (int i = 0; i < tabela.nrElem; i++)
		if (tabela.vect[i] != NULL)
		{
			free(tabela.vect[i]->marca);
			free(tabela.vect[i]);
		}
	free(tabela.vect);
}

int stergereHash(hashT tabela, int codCautat)
{
	int poz = functieHash(tabela, codCautat);
	if (tabela.vect[poz] == NULL)
		return -1;
	else
		if (tabela.vect[poz]->cod == codCautat)
		{
			free(tabela.vect[poz]->marca);
			free(tabela.vect[poz]);
			tabela.vect[poz] = NULL;
		}
		else
		{
			int index = 1;
			while (poz + index < tabela.nrElem)
			{
				if (tabela.vect[poz + index]->cod == codCautat)
				{
					poz += index;
					free(tabela.vect[poz]->marca);
					free(tabela.vect[poz]);
					tabela.vect[poz] = NULL;
					break;
				}
				else
					index++;
			}
		}
	return poz;
}

void main()
{
	hashT tabela;
	tabela.nrElem = 23;
	tabela.vect = (masina**)malloc(tabela.nrElem * sizeof(masina*));
	for (int i = 0; i < tabela.nrElem; i++)
		tabela.vect[i] = NULL;

	int nrMasini;
	masina* m;
	char buffer[20];
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrMasini);
	for (int i = 0; i < nrMasini; i++)
	{
		m = (masina*)malloc(sizeof(masina));
		fscanf(f, "%d", &m->cod);
		fscanf(f, "%s", buffer);
		m->marca = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(m->marca, buffer);
		fscanf(f, "%f", &m->pret);
		inserareHash(tabela, m);
	}
	fclose(f);

	traversareHash(tabela);

	printf("\n------------------------------\n");

	stergereHash(tabela, 47);

	traversareHash(tabela);

	dezalocareHash(tabela);
}

















/*#include<stdio.h>
#include<malloc.h>

typedef struct {
	int cod;
	char* marca;
	float pret;
} Masina;

typedef struct {
	Masina** vect;
	int nrElem;
} hashT;

int functieHash(hashT tabela, int cheie) {
	return cheie % tabela.nrElem;
}

void inserareHash(hashT tabela, Masina* m) {
	int poz = functieHash(tabela, (*m).cod);
	if (tabela.vect[poz] == NULL) {
		tabela.vect[poz] = m; //shallow copy intre 2 pointeri
	}
	else {
		int index = 1;
		while (poz + index < tabela.nrElem) {
			if (tabela.vect[poz + index] == NULL) {
				poz += index;
				tabela.vect[poz] = m;
				break;
			}
			else {
				index++;
			}
		}
	}
}

void traversareHash(hashT tabela) {
	for (int i = 0; i < tabela.nrElem; i++) {
		if (tabela.vect[i] != NULL) {
			printf("\nPozitie = %d", i);
			printf("\nCod = %d, Marca = %s, Pret = %5.2f",
				tabela.vect[i]->cod, tabela.vect[i]->marca, tabela.vect[i]->pret);
		}
	}
}

void dezalocareHash(hashT tabela) {
	for (int i = 0; i < tabela.nrElem; i++) {
		if (tabela.vect[i] != NULL) {
			free(tabela.vect[i]->marca);
			free(tabela.vect[i]);
		}
	}
	free(tabela.vect);
}

int stergereHash(hashT tabela, int codCautat) {
	int poz = functieHash(tabela, codCautat);
	if (tabela.vect[poz] == NULL) {
		return -1;
	}
	else 
		if (tabela.vect[poz]->cod == codCautat) {
		free(tabela.vect[poz]->marca);
		free(tabela.vect[poz]);
		tabela.vect[poz] = NULL;
	}
	else {
			int index = 1;
			while (poz + index < tabela.nrElem) {
				if (tabela.vect[poz + index]->cod == codCautat) {
					poz += index;
					free(tabela.vect[poz]->marca);
					free(tabela.vect[poz]);
					tabela.vect[poz] = NULL;
					break;
				}
				else {
					index++;
				}
			}
	}
	return poz;
}

//functie pentru deteterminarea din tabela de dispersie a masinilor cu pretul intre 15000 si 50000
//unde cele doua praguri sunt date in main la apel
Masina** filtrareMasini(hashT tabela, float pragMin, float pragMax, int* nrGasite) {
	Masina** rezultat = (Masina**)malloc(tabela.nrElem * sizeof(Masina*));
	*nrGasite = 0;

	for (int i = 0; i < tabela.nrElem; i++) {
		if (tabela.vect[i] != NULL) {
			if (tabela.vect[i]->pret >= pragMin && tabela.vect[i]->pret <= pragMax) {
				Masina* copie = (Masina*)malloc(sizeof(Masina));
				copie->cod = tabela.vect[i]->cod;
				copie->marca = (char*)malloc(strlen(tabela.vect[i]->marca) + 1);
				strcpy(copie->marca, tabela.vect[i]->marca);
				copie->pret = tabela.vect[i]->pret;

				rezultat[*nrGasite] = copie;
				(*nrGasite)++;
			}
		}
	}
	return rezultat;
}


void main() {
	hashT tabela;
	tabela.nrElem = 23;
	tabela.vect = (Masina**)malloc(tabela.nrElem * sizeof(Masina*));
	for (int i = 0; i < tabela.nrElem; i++) {
		tabela.vect[i] = NULL;
	}
	int nrMasini;
	Masina* m;
	char buffer[20];
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrMasini);
	for (int i = 0; i < nrMasini; i++) {
		m = (Masina*)malloc(sizeof(Masina));
		fscanf(f, "%d", &m->cod);
		fscanf(f, "%s", buffer);
		m->marca = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(m->marca, buffer);
		fscanf(f, "%f", &m->pret);
		inserareHash(tabela, m);
	}
	fclose(f);

	traversareHash(tabela);
	printf("\n-----------------------------------------\n");
	stergereHash(tabela, 47);

	traversareHash(tabela);


	printf("\n-----------------------------\n");
	int nrGasite;
	float pragMin = 15000, pragMax = 50000;
	Masina** vectorRezultat = filtrareMasini(tabela, pragMin, pragMax, &nrGasite);

	
	printf("\nMasini in intervalul [%.2f - %.2f]:\n", pragMin, pragMax);
	for (int i = 0; i < nrGasite; i++) {
		printf("Cod = %d, Marca = %s, Pret = %.2f\n",
			vectorRezultat[i]->cod, vectorRezultat[i]->marca, vectorRezultat[i]->pret);
	}

	for (int i = 0; i < nrGasite; i++) {
		free(vectorRezultat[i]->marca);
		free(vectorRezultat[i]);
	}
	free(vectorRezultat);


	dezalocareHash(tabela);
}*/