/*#include<stdio.h>
#include<malloc.h>

typedef struct Task{
	int prioritate;
	char* descriere;
	float durata;
} Task;

typedef struct Heap {
	Task* vect;
	int nrElemente;
} Heap;

void filtrare(Heap h, int index) {
	int indexRad = index;
	int indexSt = 2 * index + 1;
	int indexDr = 2 * index + 2;

	if (indexSt < h.nrElemente && h.vect[indexSt].prioritate
	> h.vect[indexRad].prioritate) {
		indexRad = indexSt;
	}
	if (indexDr < h.nrElemente && h.vect[indexDr].prioritate >
		h.vect[indexRad].prioritate) {
		indexRad = indexDr;
	}
	if (index != indexRad) {
		Task aux = h.vect[index];
		h.vect[index] = h.vect[indexRad];
		h.vect[indexRad] = aux;

		filtrare(h, indexRad);
	}
}

Heap inserare(Heap h, Task taskNou) {
	Task* vectNou = (Task*)malloc((h.nrElemente + 1) * sizeof(Task));
	for (int i = 0; i < h.nrElemente; i++) {
		vectNou[i] = h.vect[i];
	}
	h.nrElemente++;
	vectNou[h.nrElemente - 1] = taskNou;
	free(h.vect);
	h.vect = vectNou;
	for (int index = (h.nrElemente - 1) / 2; index >= 0; index--) {
		filtrare(h, index);
	}
	return h;
}

Heap extragere(Heap h, Task* extras) {
	Task* vectNou = (Task*)malloc((h.nrElemente - 1) * sizeof(Task));
	Task aux = h.vect[0];
	h.vect[0] = h.vect[h.nrElemente - 1];
	h.vect[h.nrElemente - 1] = aux;
	*extras = h.vect[h.nrElemente - 1];
	h.nrElemente--;
	for (int i = 0; i < h.nrElemente; i++) {
		vectNou[i] = h.vect[i];
	}
	free(h.vect);
	h.vect = vectNou;
	for (int index = (h.nrElemente - 1) / 2; index >= 0; index--) {
		filtrare(h, index);
	}
	return h;
}

void afisareHeap(Heap h) {
	for (int i = 0; i < h.nrElemente; i++) {
		printf("\nPrioritate = %d, Descriere = %s, Durata = %5.2f",
			h.vect[i].prioritate, h.vect[i].descriere,
			h.vect[i].durata);
	}
}

void dezalocareHeap(Heap h) {
	for (int i = 0; i < h.nrElemente; i++) {
		free(h.vect[i].descriere);
	}
	free(h.vect);
}

//de trsnaformat din arbore in stiva

void main() {
	Heap h;
	char buffer[50];
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &h.nrElemente);

	h.vect = (Task*)malloc(h.nrElemente * sizeof(Task));

	for (int i = 0; i < h.nrElemente; i++) {
		fscanf(f, "%d", &h.vect[i].prioritate);
		fscanf(f, "%s", buffer);
		h.vect[i].descriere = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(h.vect[i].descriere, buffer);
		fscanf(f, "%f", &h.vect[i].durata);
	}
	fclose(f);

	for (int index = (h.nrElemente - 1) / 2; index >= 0; index--) {
		filtrare(h, index);
	}

	afisareHeap(h);

	printf("\--------------------------\n");

	Task nou;
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

	printf("\n---------------------\n");
	Task extras;
	h = extragere(h, &extras);
	afisareHeap(h);

	printf("\nExtras -> Prioritate = %d, Descriere = %s, Durata = %5.2f",
		extras.prioritate, extras.descriere, extras.durata);

	printf("\n--------------------------\n");
	Task* vectSortat = (Task*)malloc(h.nrElemente * sizeof(Task));
	int nr = h.nrElemente;

	for (int i = 0; i < nr; i++) {
		h = extragere(h, &extras);
		vectSortat[i] = extras;
	}

	for (int i = 0; i < nr; i++) {
		printf("\nPrioritate = %d, Descriere = %s, Durata = %5.2f",
			vectSortat[i].prioritate, vectSortat[i].descriere,
			vectSortat[i].durata);
	}
	for (int i = 0; i < nr; i++) {
		free(vectSortat[i].descriere);
	}
	free(vectSortat);

	//dezalocareHeap(h);
}*/

/*#include<stdio.h>
#include<malloc.h>

typedef struct Examen {
	int nrCredite;
	char* numeMaterie;
} Examen;

typedef struct Heap {
	Examen* vect;
	int nrElemente;
} Heap;

//max heap
void filtrare(Heap h, int index) {
	int indexRad = index;
	int indexSt = 2 * index + 1;
	int indexDr = 2 * index + 2;

	if (indexSt < h.nrElemente && h.vect[indexSt].nrCredite > h.vect[indexRad].nrCredite) {
		indexRad = indexSt;
	}
	if (indexDr < h.nrElemente && h.vect[indexDr].nrCredite > h.vect[indexRad].nrCredite) {
		indexRad = indexDr;
	} 
	if (index != indexRad) {
		Examen aux = h.vect[index];
		h.vect[index] = h.vect[indexRad];
		h.vect[indexRad] = aux;

		filtrare(h, indexRad);
	}
}

Heap inserare(Heap h, Examen examen) {
	Examen* vectNou = (Examen*)malloc((h.nrElemente + 1) * sizeof(Examen));
	for (int i = 0; i < h.nrElemente; i++) {
		vectNou[i] = h.vect[i];
	}
	h.nrElemente++;
	vectNou[h.nrElemente - 1] = examen;
	free(h.vect);
	h.vect = vectNou;
	for (int index = (h.nrElemente - 1) / 2; index >= 0; index--) {
		filtrare(h, index);
	}
	return h;
}

Heap extragere(Heap h, Examen* extras) {
	Examen* vectNou = (Examen*)malloc((h.nrElemente - 1) * sizeof(Examen));
	Examen aux = h.vect[0];
	h.vect[0] = h.vect[h.nrElemente - 1];
	h.vect[h.nrElemente - 1] = aux;
	*extras = h.vect[h.nrElemente - 1];
	h.nrElemente--;
	for (int i = 0; i < h.nrElemente; i++) {
		vectNou[i] = h.vect[i];
	}
	free(h.vect);
	h.vect = vectNou;
	for (int index = (h.nrElemente - 1) / 2; index >= 0; index--) {
		filtrare(h, index);
	}
	return h;
}

void afisareHeap(Heap h) {
	for (int i = 0; i < h.nrElemente; i++) {
		printf("\nNr credite = %d, Nume materie = %s",
			h.vect[i].nrCredite, h.vect[i].numeMaterie);
	}
}

void dezalocareHeap(Heap h) {
	for (int i = 0; i < h.nrElemente; i++) {
		free(h.vect[i].numeMaterie);
	}
	free(h.vect);
}

void main() {
	Heap h;
	char buffer[50];
	FILE* f = fopen("examen.txt", "r");

	fscanf(f, "%d", &h.nrElemente);
	h.vect = (Examen*)malloc(h.nrElemente * sizeof(Examen));

	for (int i = 0; i < h.nrElemente; i++) {
		fscanf(f, "%d", &h.vect[i].nrCredite);

		fscanf(f, "%s", buffer);
		h.vect[i].numeMaterie = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(h.vect[i].numeMaterie, buffer);
	}
	fclose(f);

	for(int index = (h.nrElemente - 1) / 2; index >= 0; index--) {
		filtrare(h, index);
	}
	printf("Citire din fisier: \n");
	afisareHeap(h);

	printf("\n-------------------------------\n");
	printf("\n-------------------------------\n");

	Examen examNou;
	printf("Nr credite= ");
	scanf("%d", &examNou.nrCredite);

	printf("Nume materie= ");
	scanf("%s", buffer);
	examNou.numeMaterie = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(examNou.numeMaterie, buffer);

	h = inserare(h, examNou);
	afisareHeap(h);

	printf("\n-------------------------------\n");
	printf("\n-------------------------------\n");

	Examen extras;
	h = extragere(h, &extras);

	afisareHeap(h);
	printf("\nExtras -> Nr credite = %d, Nume materie = %s",
		extras.nrCredite, extras.numeMaterie);

	printf("\n--------------------------\n");

	Examen* vectSortat = (Examen*)malloc(h.nrElemente * sizeof(Examen));
	int nr = h.nrElemente;
	for (int i = 0; i < nr; i++) {
		h = extragere(h, &extras);
		vectSortat[i] = extras;
	}
	for (int i = 0; i < nr; i++) {
		printf("\nNr credite = %d, Nume materie = %s",
			vectSortat[i].nrCredite, vectSortat[i].numeMaterie);
	}
	for (int i = 0; i < nr; i++) {
		free(vectSortat[i].numeMaterie);
	}
	free(vectSortat);

	//dezalocareHeap(h);
}*/

#include<stdio.h>
#include<malloc.h>

typedef struct Echipa{
	int cod;
	char* nume;
} Echipa;

typedef struct Heap {
	Echipa* vect;
	int nrElemente;
} Heap;

void filtrare(Heap h, int index) {
	int indexRad = index;
	int indexSt = 2 * index + 1;
	int indexDr = 2 * index + 2;

	if (indexSt < h.nrElemente && h.vect[indexSt].cod > h.vect[indexRad].cod) {
		indexRad = indexSt;
	}
	if (indexDr < h.nrElemente && h.vect[indexDr].cod > h.vect[indexRad].cod) {
		indexRad = indexDr;
	}
	if (index != indexRad) {
		Echipa aux = h.vect[index];
		h.vect[index] = h.vect[indexRad];
		h.vect[indexRad] = aux;

		filtrare(h, indexRad);
	}
}

Heap inserare(Heap h, Echipa echipa) {
	Echipa* vectNou = (Echipa*)malloc((h.nrElemente + 1) * sizeof(Echipa));
	for (int i = 0; i < h.nrElemente; i++) {
		vectNou[i] = h.vect[i];
	}
	h.nrElemente++;
	vectNou[h.nrElemente - 1] = echipa;
	free(h.vect);
	h.vect = vectNou;
	for (int index = (h.nrElemente - 1) / 2; index >= 0; index--) {
		filtrare(h, index);
	}
	return h;
}

Heap extragere(Heap h, Echipa* extrasa) {
	Echipa* vectNou = (Echipa*)malloc((h.nrElemente - 1) * sizeof(Echipa));
	Echipa aux = h.vect[0];
	h.vect[0] = h.vect[h.nrElemente - 1];
	h.vect[h.nrElemente - 1] = aux;

	*extrasa = h.vect[h.nrElemente - 1];
	h.nrElemente--;

	for (int i = 0; i < h.nrElemente; i++) {
		vectNou[i] = h.vect[i];
	}
	free(h.vect);
	h.vect = vectNou;
	for (int index = (h.nrElemente - 1) / 2; index >= 0; index--) {
		filtrare(h, index);
	}
	return h;
}

void afisareHeap(Heap h) {
	for (int i = 0; i < h.nrElemente; i++) {
		printf("Cod: %d, Nume: %s\n", h.vect[i].cod, h.vect[i].nume);
	}
}
void dezalocareHeap(Heap h) {
	for (int i = 0; i < h.nrElemente; i++) {
		free(h.vect[i].nume);
	}
	free(h.vect);
}

void main() {
	Heap h;
	char buffer[50];
	FILE* f = fopen("Echipe.txt", "r");
	fscanf(f, "%d", &h.nrElemente);
	h.vect  = (Echipa*)malloc(h.nrElemente * sizeof(Echipa));

	for (int i = 0; i < h.nrElemente; i++) {
		fscanf(f, "%d", &h.vect[i].cod);
		fscanf(f, "%s", buffer);
		h.vect[i].nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(h.vect[i].nume, buffer);
	}
	fclose(f);
	for (int index = (h.nrElemente - 1) / 2; index >= 0; index--) {
		filtrare(h, index);
	}
	printf("-------------AFISARE HEAP------------------------\n");
	afisareHeap(h);

	Echipa noua;
	printf("-------------INSERARE------------------------\n");
	printf("Cod: ");
	scanf("%d", &noua.cod);
	printf("Nume: ");
	scanf("%s", buffer);
	noua.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(noua.nume, buffer);

	h = inserare(h, noua);
	afisareHeap(h);

	printf("-------------EXTRAGERE------------------------\n");
	Echipa extrasa;
	h = extragere(h, &extrasa);
	afisareHeap(h);

	printf("-------------ECHIPA EXTRASA------------------------\n");
	printf("Cod: %d, Nume: %s\n",
		extrasa.cod, extrasa.nume);

	printf("-------------VECTOR SORTAT------------------------\n");
	Echipa* vectSortat = (Echipa*)malloc(h.nrElemente * sizeof(Echipa));
	int nr = h.nrElemente;

	for(int i = 0; i < nr; i++) {
		h = extragere(h, &extrasa);
		vectSortat[i] = extrasa;
	}

	for(int i = 0; i < nr; i++) {
		printf("Cod: %d, Nume: %s\n", vectSortat[i].cod,
			vectSortat[i].nume);
	}

	for (int i = 0; i < nr; i++) {
		free(vectSortat[i].nume);
	}
	free(vectSortat);


	//dezalocareHeap(h);
}