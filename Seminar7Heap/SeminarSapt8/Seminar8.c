/*
//heap-> arbore binar implementat sub forma de vector
//heap = coada de prioritati
#include<stdio.h>
#include<malloc.h>

typedef struct {
	int prioritate;
	char* descriere;
	float durata;
} task;

typedef struct {
	task* vect;
	int nrElem;
} heap;

typedef struct nodStiva {
	task info;
	struct nodStiva* next;
} nodStiva;





//h.vect[indexSt].prioritate < -> din < => ca avem min heap
//h.vect[indexSt].prioritate > -> din > => ca avem max heap
void filtrare(heap h, int index) {
	int indexRad = index;
	int indexSt = 2 * index + 1;
	int indexDr = 2 * index + 2;
	if (indexSt < h.nrElem && h.vect[indexSt].prioritate <
		h.vect[indexRad].prioritate) {
		indexRad = indexSt;
	}
	if (indexDr < h.nrElem && h.vect[indexDr].prioritate <
		h.vect[indexRad].prioritate) {
		indexRad = indexDr;
	}
	if (index != indexRad) {
		task aux = h.vect[index];
		h.vect[index] = h.vect[indexRad];
		h.vect[indexRad] = aux;

		filtrare(h, indexRad);
	}
}

heap inserare(heap h, task nou) {
	task* vectNou = (task*)malloc((h.nrElem + 1) * sizeof(task));
	for (int i = 0; i < h.nrElem; i++) {
		vectNou[i] = h.vect[i];
	}
	h.nrElem++;
	vectNou[h.nrElem - 1] = nou;
	free(h.vect);
	h.vect = vectNou;
	for (int i = (h.nrElem - 1) / 2; i >= 0; i--) {
		filtrare(h, i);
	}
	return h;
}

heap extragere(heap h, task* extras) {
	task* vectNou = (task*)malloc((h.nrElem - 1) * sizeof(task));
	task aux = h.vect[0];
	h.vect[0] = h.vect[h.nrElem - 1];
	h.vect[h.nrElem - 1] = aux;
	*extras = h.vect[h.nrElem - 1];
	h.nrElem--;
	for (int i = 0; i < h.nrElem; i++) {
		vectNou[i] = h.vect[i];
	}
	free(h.vect);
	h.vect = vectNou;
	for (int i = (h.nrElem - 1) / 2; i >= 0; i--) {
		filtrare(h, i);
	}
	return h;
}

void afisareHeap(heap h) {
	for (int i = 0; i < h.nrElem; i++) {
		printf("\nPrioritate = %d, Descriere = %s, Durata = %5.2f",
			h.vect[i].prioritate, h.vect[i].descriere, h.vect[i].durata);
	}
}

void dezalocare(heap h) {
	for (int i = 0; i < h.nrElem; i++) {
		free(h.vect[i].descriere);
	}
	free(h.vect);
}

//sa se salveze elementele din heapul nostru intr-o stiva
void push(nodStiva** varf, task t) {
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));

	nou->info.prioritate = t.prioritate;
	nou->info.durata = t.durata;
	nou->info.descriere = (char*)malloc((strlen(t.descriere) + 1) * sizeof(char));
	strcpy(nou->info.descriere, t.descriere);

	nou->next = NULL;

	if (*varf == NULL) {
		*varf = nou;
	}
	else {
		nou->next = *varf;
		*varf = nou;
	}
}

nodStiva* conversieHeapInStiva(heap* h) {
	nodStiva* varf = NULL;
	task extras;

	while (h->nrElem > 0) {
		*h = extragere(*h, &extras);
		push(&varf, extras);
	}

	return varf;
}

void afisareStiva(nodStiva* varf) {
	nodStiva* p = varf;
	while (p) {
		printf("\nPrioritate = %d, Descriere = %s, Durata = %5.2f",
			p->info.prioritate, p->info.descriere, p->info.durata);
		p = p->next;
	}
}





void main() {
	heap h;
	char buffer[50];
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &h.nrElem);
	h.vect = (task*)malloc(h.nrElem * sizeof(task));
	for (int i = 0; i < h.nrElem; i++) {
		fscanf(f, "%d", &h.vect[i].prioritate);
		fscanf(f, "%s", buffer);
		h.vect[i].descriere = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(h.vect[i].descriere, buffer);
		fscanf(f, "%f", &h.vect[i].durata);
	}
	fclose(f);
	for (int i = (h.nrElem - 1) / 2; i >= 0; i--) {
		filtrare(h, i);
	}
	afisareHeap(h);

	printf("\n----------------------------------\n");
	task nou;
	printf("Prioritate = ");
	scanf("%d", &nou.prioritate);
	printf("Descriere = ");
	scanf("%s", buffer);
	nou.descriere = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(nou.descriere, buffer);
	printf("Durata = ");
	scanf("%f", &nou.durata);

	h = inserare(h, nou);
	afisareHeap(h);

	printf("\n----------------------------------\n");
	task extras;
	h = extragere(h, &extras);
	afisareHeap(h);
	printf("\nExtras-> Prioritate = %d, Descriere = %s, Durata = %5.2f",
		extras.prioritate, extras.descriere, extras.durata);

	printf("\n----------------------------------\n");
	task* vectSortat = (task*)malloc(h.nrElem * sizeof(task));
	/*int nr = h.nrElem;
	for (int i = 0; i < nr; i++) {
		h = extragere(h, &extras);
		vectSortat[i] = extras;
	}
	for (int i = 0; i < nr; i++) {
		printf("\nPrioritate = %d, Descriere = %s, Durata = %5.2f",
			vectSortat[i].prioritate, vectSortat[i].descriere, vectSortat[i].durata);
	}
	for (int i = 0; i < nr; i++) {
		free(vectSortat[i].descriere);
	}
	free(vectSortat);

	//avem dezalocarea facuta inainte si de asta
	//dezalocare(h);

	printf("\n----------------------------------\n");
	printf("Salvam heapul intr-o stiva:\n");

	nodStiva* varf = conversieHeapInStiva(&h); 

	printf("\nElementele din stiva sunt:\n");
	afisareStiva(varf); 





}*/


#include<stdio.h>
#include<malloc.h>

typedef struct
{
	int prioritate;
	char* descriere;
	float durata;
} task;

typedef struct
{
	task* vect;
	int nrElem;
} heap;

void filtrare(heap h, int index)
{
	int indexRad = index;
	int indexSt = 2 * index + 1;
	int indexDr = 2 * index + 2;

	if (indexSt < h.nrElem && h.vect[indexSt].prioritate <
		h.vect[indexRad].prioritate)
		indexRad = indexSt;
	if (indexDr < h.nrElem && h.vect[indexDr].prioritate <
		h.vect[indexRad].prioritate)
		indexRad = indexDr;

	if (index != indexRad)
	{
		task aux = h.vect[index];
		h.vect[index] = h.vect[indexRad];
		h.vect[indexRad] = aux;

		filtrare(h, indexRad);
	}
}

heap inserare(heap h, task nou)
{
	task* vectNou = (task*)malloc((h.nrElem + 1) * sizeof(task));
	for (int i = 0; i < h.nrElem; i++)
		vectNou[i] = h.vect[i];
	h.nrElem++;
	vectNou[h.nrElem - 1] = nou;
	free(h.vect);
	h.vect = vectNou;
	for (int i = (h.nrElem - 1) / 2; i >= 0; i--)
		filtrare(h, i);
	return h;
}

heap extragere(heap h, task* extras)
{
	task* vectNou = (task*)malloc((h.nrElem - 1) * sizeof(task));
	task aux = h.vect[0];
	h.vect[0] = h.vect[h.nrElem - 1];
	h.vect[h.nrElem - 1] = aux;
	*extras = h.vect[h.nrElem - 1];
	h.nrElem--;
	for (int i = 0; i < h.nrElem; i++)
		vectNou[i] = h.vect[i];
	free(h.vect);
	h.vect = vectNou;
	for (int i = (h.nrElem - 1) / 2; i >= 0; i--)
		filtrare(h, i);
	return h;
}

void afisareHeap(heap h)
{
	for (int i = 0; i < h.nrElem; i++)
		printf("\nPrioritate = %d, Descriere = %s, Durata = %5.2f",
			h.vect[i].prioritate, h.vect[i].descriere,
			h.vect[i].durata);
}

void dezalocareHeap(heap h)
{
	for (int i = 0; i < h.nrElem; i++)
		free(h.vect[i].descriere);
	free(h.vect);
}

void main()
{
	heap h;
	char buffer[50];
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &h.nrElem);
	h.vect = (task*)malloc(h.nrElem * sizeof(task));
	for (int i = 0; i < h.nrElem; i++)
	{
		fscanf(f, "%d", &h.vect[i].prioritate);
		fscanf(f, "%s", buffer);
		h.vect[i].descriere = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(h.vect[i].descriere, buffer);
		fscanf(f, "%f", &h.vect[i].durata);
	}
	fclose(f);
	for (int i = (h.nrElem - 1) / 2; i >= 0; i--)
		filtrare(h, i);

	afisareHeap(h);

	printf("\n--------------------------\n");

	task nou;
	printf("Prioritate = ");
	scanf("%d", &nou.prioritate);
	printf("Descriere = ");
	scanf("%s", buffer);
	nou.descriere = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(nou.descriere, buffer);
	printf("Durata = ");
	scanf("%f", &nou.durata);

	h = inserare(h, nou);

	afisareHeap(h);

	printf("\n--------------------------\n");

	task extras;
	h = extragere(h, &extras);

	afisareHeap(h);

	printf("\nExtras -> Prioritate = %d, Descriere = %s, Durata = %5.2f",
		extras.prioritate, extras.descriere, extras.durata);

	printf("\n--------------------------\n");

	task* vectSortat = (task*)malloc(h.nrElem * sizeof(task));
	int nr = h.nrElem;
	for (int i = 0; i < nr; i++)
	{
		h = extragere(h, &extras);
		vectSortat[i] = extras;
	}

	for (int i = 0; i < nr; i++)
		printf("\nPrioritate = %d, Descriere = %s, Durata = %5.2f",
			vectSortat[i].prioritate, vectSortat[i].descriere,
			vectSortat[i].durata);
	for (int i = 0; i < nr; i++)
		free(vectSortat[i].descriere);
	free(vectSortat);

	//dezalocareHeap(h);
}
