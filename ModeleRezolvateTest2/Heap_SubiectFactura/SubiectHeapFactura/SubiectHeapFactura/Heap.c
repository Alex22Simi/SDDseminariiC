#include<stdio.h>
#include<malloc.h>

typedef struct Factura {
	int nrZileScandenta;
	char* platitor;
	char* adresaPlatitor;
	int nrPersoaneGospodarie;
	float suma;
} Factura;

typedef struct Heap {
	Factura* vect;
	int nrElem;
} Heap;

typedef struct NodArb {
	int BF;
	Factura info;
	struct NodArb* stanga;
	struct NodArb* dreapta;
}NodArb;

typedef struct NodLS {
	Factura info;
	struct NodLS* next;
} NodLS;

//min heap
void filtrare(Heap h, int index) {
	int indexRad = index;
	int indexSt = 2 * index + 1;
	int indexDr = 2 * index + 2;

	if (indexSt < h.nrElem && h.vect[indexSt].nrZileScandenta < h.vect[indexRad].nrZileScandenta) {
		indexRad = indexSt;
	}
	if (indexDr < h.nrElem && h.vect[indexDr].nrZileScandenta < h.vect[indexRad].nrZileScandenta) {
		indexRad = indexDr;
	}
	if (indexRad != index) {
		Factura aux = h.vect[index];
		h.vect[index] = h.vect[indexRad];
		h.vect[indexRad] = aux;

		filtrare(h, indexRad);
	}
}

Heap inserare(Heap h, Factura factura) {
	Factura* vectNou = (Factura*)malloc((h.nrElem + 1) * sizeof(Factura));
	for (int i = 0; i < h.nrElem; i++) {
		vectNou[i] = h.vect[i];
	}
	h.nrElem++;
	vectNou[h.nrElem - 1] = factura;
	free(h.vect);
	h.vect = vectNou;
	for (int i = (h.nrElem - 1) / 2; i >= 0; i--) {
		filtrare(h, i);
	}
	return h;
}
//suplimentar
/*Heap extragere(Heap h, Factura* extrasa) {
	Factura* vectNou = (Factura*)malloc((h.nrElem - 1) * sizeof(Factura));
	Factura aux = h.vect[0];
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
}*/

void afisare(Heap h) {
	for (int i = 0; i < h.nrElem; i++) {
		printf("Zile scandenta: %d, Platitor: %s, Adresa platitor: %s, Nr. pers. gospodarie: %d, Suma: %5.2f\n",
			h.vect[i].nrZileScandenta, h.vect[i].platitor, h.vect[i].adresaPlatitor, h.vect[i].nrPersoaneGospodarie, h.vect[i].suma);
	}
}

void dezalocare(Heap h) {
	for (int i = 0; i < h.nrElem; i++) {
		free(h.vect[i].platitor);
		free(h.vect[i].adresaPlatitor);
	}
	free(h.vect);
}

//ex 2
//eliminare din heap facturi cu 
//termen mai putin de trei zile pana
//la scadenta

Heap stergeFacturi(Heap h) {
	Heap rezultat;
	rezultat.nrElem = 0;
	rezultat.vect = NULL;
	for (int i = 0; i < h.nrElem; i++) {
		if (h.vect[i].nrZileScandenta >= 3) {
			Factura f;
			f.nrZileScandenta = h.vect[i].nrZileScandenta;
			f.platitor = (char*)malloc(strlen(h.vect[i].platitor) + 1);
			strcpy(f.platitor, h.vect[i].platitor);
			f.adresaPlatitor = (char*)malloc(strlen(h.vect[i].adresaPlatitor) + 1);
			strcpy(f.adresaPlatitor, h.vect[i].adresaPlatitor);
			f.nrPersoaneGospodarie = h.vect[i].nrPersoaneGospodarie;
			f.suma = h.vect[i].suma;

			rezultat = inserare(rezultat, f);
		}
		else {
			// daca e sub 3 zile, eliberam memoria
			free(h.vect[i].platitor);
			free(h.vect[i].adresaPlatitor);
		}
	}
	free(h.vect); 
	return rezultat;
}

//ex3
//de copiat din heap in abc
NodArb* creareNodArb(Factura factura, NodArb* stanga, NodArb* dreapta) {
	NodArb* nou = (NodArb*)malloc(sizeof(NodArb));
	nou->info.nrZileScandenta = factura.nrZileScandenta;

	nou->info.platitor = (char*)malloc((strlen(factura.platitor) + 1) * sizeof(char));
	strcpy(nou->info.platitor, factura.platitor);

	nou->info.adresaPlatitor = (char*)malloc((strlen(factura.adresaPlatitor) + 1) * sizeof(char));
	strcpy(nou->info.adresaPlatitor, factura.adresaPlatitor);

	nou->info.nrPersoaneGospodarie = factura.nrPersoaneGospodarie;

	nou->info.suma = factura.suma;

	nou->stanga = stanga;

	nou->dreapta = dreapta;

	return nou;
}

NodArb* inserareArb(NodArb* rad, Factura factura) {
	if (rad != NULL) {
		if (factura.nrPersoaneGospodarie < rad->info.nrPersoaneGospodarie) {
			rad->stanga = inserareArb(rad->stanga, factura);
			return rad;
		}
		else if (factura.nrPersoaneGospodarie > rad->info.nrPersoaneGospodarie) {
			rad->dreapta = inserareArb(rad->dreapta, factura);
			return rad;
		}
		else {
			return rad;
		}
	}
	else {
		return creareNodArb(factura, NULL, NULL);
	}
}

//R S D
void afisarePreOrdine(NodArb* rad) {
	if (rad != NULL) {
		printf("Zile scandenta: %d, Platitor: %s, Adresa platitor: %s, Nr. pers. gospodarie: %d, Suma: %5.2f\n",
			rad->info.nrZileScandenta, rad->info.platitor, rad->info.adresaPlatitor, rad->info.nrPersoaneGospodarie,
			rad->info.suma);
		afisarePreOrdine(rad->stanga);
		afisarePreOrdine(rad->dreapta);
	}
}

void dezalocareArb(NodArb* rad) {
	if (rad != NULL) {
		dezalocareArb(rad->stanga);
		dezalocareArb(rad->dreapta);
		free(rad->info.platitor);
		free(rad->info.adresaPlatitor);
		free(rad);
	}
}
//suplimentare creare AVL
int maxim(int a, int b) {
	int max = a;
	if (max < b) {
		max = b;
	}
	return max;
}

int inaltimeArb(NodArb* rad) {
	if (rad != NULL) {
		return 1 + maxim(inaltimeArb(rad->stanga), inaltimeArb(rad->dreapta));
	}
	else {
		return 0;
	}
}

void calculBF(NodArb* rad) {
	if (rad != NULL) {
		rad->BF = inaltimeArb(rad->dreapta) - inaltimeArb(rad->stanga);
		calculBF(rad->stanga);
		calculBF(rad->dreapta);
	}
}

NodArb* rotatieDreapta(NodArb* rad) {
	printf("\nRotatie dreapta\n");
	NodArb* nod1 = rad->stanga;
	rad->stanga = nod1->dreapta;
	nod1->dreapta = rad;
	rad = nod1;
	return rad;
}

NodArb* rotatieStanga(NodArb* rad) {
	printf("\nRotatie stanga\n");
	NodArb* nod1 = rad->dreapta;
	rad->dreapta = nod1->stanga;
	nod1->stanga = rad;
	rad = nod1;
	return rad;
}

NodArb* rotatieStangaDreapta(NodArb* rad) {
	printf("\nRotatie stanga-dreapta\n");
	NodArb* nod1 = rad->stanga;
	NodArb* nod2 = nod1->dreapta;
	nod1->dreapta = nod2->stanga;
	nod2->stanga = nod1;
	rad->stanga = nod2->dreapta;
	nod2->dreapta = rad;
	rad = nod2;
	return rad;
}

NodArb* rotatieDreaptaStanga(NodArb* rad) {
	printf("\nRotatie dreapta-stanga\n");
	NodArb* nod1 = rad->dreapta;
	NodArb* nod2 = nod1->stanga;
	nod1->stanga = nod2->dreapta;
	nod2->dreapta = nod1;
	rad->dreapta = nod2->stanga;
	nod2->stanga = rad;
	rad = nod2;
	return rad;
}

NodArb* reechilibrare(NodArb* rad) {
	calculBF(rad);
	NodArb* fiuSt = rad->stanga;
	NodArb* fiuDr = rad->dreapta;
	if (rad->BF <= -2 && fiuSt->BF <= -1) {
		rad = rotatieDreapta(rad);
		calculBF(rad);
	}
	else {
		if (rad->BF >= 2 && fiuDr->BF >= 1) {
			rad = rotatieStanga(rad);
			calculBF(rad);
		}
		else {
			if (rad->BF <= -2 && fiuSt->BF >= 1) {
				rad = rotatieStangaDreapta(rad);
				calculBF(rad);
			}
			else {
				if (rad->BF >= 2 && fiuDr->BF <= -1) {
					rad = rotatieDreaptaStanga(rad);
					calculBF(rad);
				}
			}
		}
	}
	return rad;
}

NodArb* convertesteHeapInABC(Heap h) {
	NodArb* rad = NULL;
	for (int i = 0; i < h.nrElem; i++) {
		//copiere facturi suma > 500
		if(h.vect[i].suma > 500) {
			rad = inserareArb(rad, h.vect[i]);
		}
	}
	return reechilibrare(rad);
}

//ex 4
NodLS* creareNodLS(Factura f) {
	NodLS* nod = (NodLS*)malloc(sizeof(NodLS));
	nod->info.nrZileScandenta = f.nrZileScandenta;

	nod->info.platitor = (char*)malloc(strlen(f.platitor) + 1);
	strcpy(nod->info.platitor, f.platitor);

	nod->info.adresaPlatitor = (char*)malloc(strlen(f.adresaPlatitor) + 1);
	strcpy(nod->info.adresaPlatitor, f.adresaPlatitor);

	nod->info.nrPersoaneGospodarie = f.nrPersoaneGospodarie;
	nod->info.suma = f.suma;

	nod->next = NULL;
	return nod;
}

void inserareLaFinal(NodLS** cap, Factura f) {
	NodLS* nou = creareNodLS(f);
	if (*cap == NULL)
		*cap = nou;
	else {
		NodLS* temp = *cap;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = nou;
	}
}

int salvarePanaLaNod(NodArb* rad, int cheie, NodLS** cap) {
	if (rad == NULL)
		return 0;

	inserareLaFinal(cap, rad->info);

	if (cheie == rad->info.nrPersoaneGospodarie)
		return 1;  // l-am găsit, ne oprim

	if (cheie < rad->info.nrPersoaneGospodarie)
		return salvarePanaLaNod(rad->stanga, cheie, cap);
	else
		return salvarePanaLaNod(rad->dreapta, cheie, cap);

}



void afisareLista(NodLS* cap) {
	while (cap != NULL) {
		printf("Zile scandenta: %d, Platitor: %s, Adresa: %s, Pers: %d, Suma: %5.2f\n",
			cap->info.nrZileScandenta, cap->info.platitor, cap->info.adresaPlatitor,
			cap->info.nrPersoaneGospodarie, cap->info.suma);
		cap = cap->next;
	}
}

void dezalocareLista(NodLS* cap) {
	while (cap != NULL) {
		NodLS* temp = cap;
		cap = cap->next;
		free(temp->info.platitor);
		free(temp->info.adresaPlatitor);
		free(temp);
	}
}




void main() {
	NodLS* lista = NULL;
	NodArb* rad = NULL;
	Heap h;
	char buffer[50];

	FILE* f = fopen("facturi.txt", "r");

	fscanf(f, "%d", &h.nrElem);
	h.vect = (Factura*)malloc((h.nrElem) * sizeof(Factura));

	for (int i = 0; i < h.nrElem; i++) {
		fscanf(f, "%d", &h.vect[i].nrZileScandenta);

		fscanf(f, "%s", buffer);
		h.vect[i].platitor = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(h.vect[i].platitor, buffer);

		fscanf(f, "%s", buffer);
		h.vect[i].adresaPlatitor = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(h.vect[i].adresaPlatitor, buffer);

		fscanf(f, "%d", &h.vect[i].nrPersoaneGospodarie);

		fscanf(f, "%f", &h.vect[i].suma);
	}
	fclose(f);

	for (int i = (h.nrElem - 1) / 2; i >= 0; i--) {
		filtrare(h, i);
	}

	afisare(h);

	printf("--------------------------INSERARE-------------------\n");
	Factura noua;
	printf("Nr zile scadenta: ");
	scanf("%d", &noua.nrZileScandenta);
	printf("Platitor: ");
	scanf("%s", buffer);
	noua.platitor = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(noua.platitor, buffer);
	printf("Adresa: ");
	scanf("%s", buffer);
	noua.adresaPlatitor = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(noua.adresaPlatitor, buffer);
	printf("Nr pers: ");
	scanf("%d", &noua.nrPersoaneGospodarie);
	printf("Suma: ");
	scanf("%f", &noua.suma);

	h = inserare(h, noua);

	afisare(h);
	/*printf("--------------------------Extragere: -------------------\n");
	Factura extrasa;
	h = extragere(h, &extrasa);
	afisare(h);
	printf("Extrasa->Zile scandenta: %d, Platitor: %s, Adresa platitor: %s, Nr. pers. gospodarie: %d, Suma: %5.2f\n",
		extrasa.nrZileScandenta, extrasa.platitor, extrasa.adresaPlatitor, extrasa.nrPersoaneGospodarie, extrasa.suma);

	free(extrasa.platitor);
	free(extrasa.adresaPlatitor);*/

	printf("--------------------------EX2:-------------------\n");
	printf("--------------------------INAINTE DE STERGERE:-------------------\n");
	afisare(h);
	h = stergeFacturi(h);
	printf("--------------------------DUPA STERGERE:-------------------\n");
	afisare(h);

	printf("--------------------------EX3: COPIERE IN ARBORE -------------------\n");
	rad = convertesteHeapInABC(h);
	afisarePreOrdine(rad);
	printf("--------------------------EX4: -------------------\n");
	int cheieCautata;
	printf("Introduceti cheia de cautare (nrPersoaneGospodarie): ");
	scanf("%d", &cheieCautata);

	salvarePanaLaNod(rad, cheieCautata, &lista);


	printf("---------- Lista cu nodurile de la radacina pana la cheia %d ----------\n", cheieCautata);
	afisareLista(lista);


	dezalocareLista(lista);
	dezalocareArb(rad);
	dezalocare(h);
}