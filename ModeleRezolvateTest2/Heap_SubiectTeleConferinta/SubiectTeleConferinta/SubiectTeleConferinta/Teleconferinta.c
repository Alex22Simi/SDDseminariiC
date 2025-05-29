#include<stdio.h>
#include<malloc.h>

typedef struct Platforma {
	int pretLicenta;
	char* nume;
	int nrLicente;
	int* nrOameniCareAuLucratLaLicenta;
	int id;
} Platforma;

typedef struct Heap {
	Platforma* vect;
	int nrElem;
} Heap;

void filtrare(Heap heap, int index) {
	int indexRad = index;
	int indexSt = 2 * index + 1;
	int indexDr = 2 * index + 2;

	if (indexSt < heap.nrElem && heap.vect[indexSt].pretLicenta < heap.vect[indexRad].pretLicenta) {
		indexRad = indexSt;
	} 
	if (indexDr < heap.nrElem && heap.vect[indexDr].pretLicenta < heap.vect[indexRad].pretLicenta) {
		indexRad = indexDr;
	} 
	if (indexRad != index) {
		Platforma aux = heap.vect[index];
		heap.vect[index] = heap.vect[indexRad];
		heap.vect[indexRad] = aux;

		filtrare(heap, indexRad);
	}
}

Heap inserare(Heap heap, Platforma platforma) {
	Platforma* vectNou = (Platforma*)malloc((heap.nrElem + 1) * sizeof(Platforma));
	for (int i = 0; i < heap.nrElem; i++) {
		vectNou[i] = heap.vect[i];
	}
	heap.nrElem++;
	vectNou[heap.nrElem - 1] = platforma;
	free(heap.vect);
	heap.vect = vectNou;

	for (int i = (heap.nrElem - 1) / 2; i >= 0; i--) {
		filtrare(heap, i);
	}
	return heap;
}

Heap extragere(Heap heap, Platforma* extrasa) {
	Platforma* vectNou = (Platforma*)malloc((heap.nrElem - 1) * sizeof(Platforma));
	Platforma aux = heap.vect[0];
	heap.vect[0] = heap.vect[heap.nrElem - 1];
	heap.vect[heap.nrElem - 1] = aux;

	*extrasa = heap.vect[heap.nrElem - 1];

	heap.nrElem--;

	for (int i = 0; i < heap.nrElem; i++) {
		vectNou[i] = heap.vect[i];
	}

	free(heap.vect);
	heap.vect = vectNou;

	for (int i = (heap.nrElem - 1)/2; i >= 0; i--) {
		filtrare(heap, i);
	}

	return heap;
}

void afisare(Heap heap) {
	for (int i = 0; i < heap.nrElem; i++) {
		printf("Pret: %d, Nume: %s, Nr licente: %d, Oameni/licitenta: ",
			heap.vect[i].pretLicenta, heap.vect[i].nume, heap.vect[i].nrLicente);
		for (int j = 0; j < heap.vect[i].nrLicente; j++) {
			printf("%d ", heap.vect[i].nrOameniCareAuLucratLaLicenta[j]);
		}
		printf("Id: %d\n", heap.vect[i].id);
	}
}

void dezalocare(Heap heap) {
	for (int i = 0; i < heap.nrElem; i++) {
		free(heap.vect[i].nume);
		free(heap.vect[i].nrOameniCareAuLucratLaLicenta);
	}
	free(heap.vect);
}

void main() {
	Heap heap;
	char buffer[50];

	FILE* f = fopen("platforma.txt", "r");

	fscanf(f, "%d", &heap.nrElem);
	heap.vect = (Platforma*)malloc(heap.nrElem * sizeof(Platforma));

	for (int i = 0; i < heap.nrElem; i++) {
		fscanf(f, "%d", &heap.vect[i].pretLicenta);

		fscanf(f, "%s", buffer);
		heap.vect[i].nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(heap.vect[i].nume, buffer);

		fscanf(f, "%d", &heap.vect[i].nrLicente);

		heap.vect[i].nrOameniCareAuLucratLaLicenta = (int*)malloc(heap.vect[i].nrLicente * sizeof(int));


		for (int j = 0; j < heap.vect[i].nrLicente; j++) {
			fscanf(f, "%d", &heap.vect[i].nrOameniCareAuLucratLaLicenta[j]);
		}
		fscanf(f, "%d", &heap.vect[i].id);
	}
	fclose(f);

	for (int i = (heap.nrElem - 1) / 2; i >= 0; i--) {
		filtrare(heap, i);
	}

	afisare(heap);
}