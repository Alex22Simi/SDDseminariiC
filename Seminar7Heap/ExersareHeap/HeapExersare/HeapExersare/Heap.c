/*#include<stdio.h>
#include<malloc.h>

//heap -> arbore binar implementat sub forma de vector
//heap = coada de prioritati

typedef struct Activitate {
	int prioritate;
	char* denumire;
	float durata;
} Activitate;

typedef struct Heap {
	Activitate* vect;
	int nrElem;
} Heap;

void filtrare(Heap h, int index) {
	int indexRad = index;
	int indexSt = 2 * index + 1;
	int indexDr = 2 * index + 2;

	if (indexSt < h.nrElem && h.vect[indexSt].prioritate > h.vect[indexRad].prioritate) {
		indexRad = indexSt;
	}
	if (indexDr < h.nrElem && h.vect[indexDr].prioritate > h.vect[indexRad].prioritate) {
		indexRad = indexDr;
	}
	if (index != indexRad) {
		Activitate aux = h.vect[index];
		h.vect[index] = h.vect[indexRad];
		h.vect[indexRad] = aux;

		filtrare(h, indexRad);
	}
}

Heap inserare(Heap h, Activitate activitate) {
	Activitate* vectNou = (Activitate*)malloc((h.nrElem + 1) * sizeof(Activitate));
	for (int i = 0; i < h.nrElem; i++) {
		vectNou[i] = h.vect[i];
	}
	h.nrElem++;
	vectNou[h.nrElem - 1] = activitate;
	free(h.vect);
	h.vect = vectNou;
	for (int i = (h.nrElem - 1) / 2; i >= 0; i--) {
		filtrare(h, i);
	}
	return h;
}

Heap extragere(Heap h, Activitate* extrasa) {
	Activitate* vectNou = (Activitate*)malloc((h.nrElem - 1) * sizeof(Activitate));
	Activitate aux = h.vect[0];
	h.vect[0] = h.vect[h.nrElem - 1];
	h.vect[h.nrElem - 1] = aux;

	*extrasa = h.vect[h.nrElem - 1];
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

void afisare(Heap h) {
	for (int i = 0; i < h.nrElem; i++) {
		printf("Prioritate = %d, Denumire = %s, Durata = %5.2f\n",
			h.vect[i].prioritate, h.vect[i].denumire, h.vect[i].durata);
	}
}

void dezalocare(Heap h) {
	for (int i = 0; i < h.nrElem; i++) {
		free(h.vect[i].denumire);
	}
	free(h.vect);
}

void main() {
	Heap h;
	char buffer[20];

	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &h.nrElem);
	h.vect = (Activitate*)malloc((h.nrElem) * sizeof(Activitate));
	for (int i = 0; i < h.nrElem; i++) {
		fscanf(f, "%d", &h.vect[i].prioritate);

		fscanf(f, "%s", buffer);
		h.vect[i].denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(h.vect[i].denumire, buffer);

		fscanf(f, "%f", &h.vect[i].durata);
	}
	fclose(f);

	for (int i = (h.nrElem - 1) / 2; i >= 0; i--) {
		filtrare(h, i);
	}
	afisare(h);

	Activitate noua;
	printf("Prioritate = ");
	scanf("%d", &noua.prioritate);
	printf("Denumire = ");
	scanf("%s", buffer);
	noua.denumire = (char*)malloc((strlen(buffer)+1)*sizeof(char));
	strcpy(noua.denumire, buffer);
	printf("Durata = ");
	scanf("%f", &noua.durata);
	printf("\n-------------------------------\n");

	h = inserare(h, noua);

	afisare(h);
	printf("\n-------------------------------\n");

	Activitate extrasa;
	h = extragere(h, &extrasa);

	afisare(h);

	printf("\nExtrasa -> Prioritate = %d, Denumire = %s, Durata = %5.2f",
		extrasa.prioritate, extrasa.denumire, extrasa.durata);

	dezalocare(h);
}*/

#include<stdio.h>
#include<malloc.h>

typedef struct Task {
	int prioritate;
	char* descriere;
	float durata;
} Task;

typedef struct Heap {
	Task* vect;
	int nrElem;
} Heap;

void filtrare(Heap h, int index) {
	int indexRad = index;
	int indexSt = 2 * index + 1;
	int indexDr = 2 * index + 2;

	if (indexSt < h.nrElem && h.vect[indexSt].prioritate > h.vect[indexRad].prioritate) {
		indexRad = indexSt;
	}
	if (indexDr < h.nrElem && h.vect[indexDr].prioritate > h.vect[indexRad].prioritate) {
		indexRad = indexDr;
	}
	if (index != indexRad) {
		Task aux = h.vect[index];
		h.vect[index] = h.vect[indexRad];
		h.vect[indexRad] = aux;

		filtrare(h, indexRad);
	}
}

Heap inserare(Heap h, Task task) {
	Task* vectNou = (Task*)malloc((h.nrElem + 1) * sizeof(Task));
	for (int i = 0; i < h.nrElem; i++) {
		vectNou[i] = h.vect[i];
	}
	h.nrElem++;
	vectNou[h.nrElem - 1] = task;
	free(h.vect);
	h.vect = vectNou;
	for (int i = (h.nrElem - 1) / 2; i >= 0; i--) {
		filtrare(h, i);
	}
	return h;
}

Heap extragere(Heap h, Task* extras) {
	Task* vectNou = (Task*)malloc((h.nrElem - 1) * sizeof(Task));
	Task aux = h.vect[0];
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

void afisare(Heap h) {
	for (int i = 0; i < h.nrElem; i++) {
		printf("Prioritate = %d Descriere = %s Durata = %5.2f\n",
			h.vect[i].prioritate, h.vect[i].descriere, h.vect[i].durata);
	}
}

void dezalocare(Heap h) {
	for (int i = 0; i < h.nrElem; i++) {
		free(h.vect[i].descriere);
	}
	free(h.vect);
}

void main() {
	Heap h;
	char buffer[50];

	FILE* f = fopen("taskuri.txt", "r");

	fscanf(f, "%d", &h.nrElem);
	h.vect = (Task*)malloc(h.nrElem * sizeof(Task));
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

	afisare(h);
	printf("------------------------------\n");
	Task nou;
	printf("Prioritate: ");
	scanf("%d", &nou.prioritate);
	printf("Descriere: ");
	scanf("%s", buffer);
	nou.descriere = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(nou.descriere, buffer);
	printf("Durata: ");
	scanf("%f", &nou.durata);
	h = inserare(h,nou);
	afisare(h);
	printf("------------------------------\n");
	Task extras;
	h = extragere(h, &extras);

	afisare(h);

	printf("Extras->Prioritate = %d Descriere = %s Durata = %5.2f\n",
		extras.prioritate, extras.descriere, extras.durata);

	dezalocare(h);
}


