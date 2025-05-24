#include<stdio.h>
#include<malloc.h>

typedef struct Produs {
	unsigned short int idProdus; //%hu
	char* denumireProdus;
	unsigned short int stoc;//%hu
	unsigned char nrClienti;//%hhu
	unsigned short int* stocuriClienti;//%hu
} Produs;

typedef struct NodArb {
	int BF;
	Produs info;
	struct NodArb* stanga;
	struct NodArb* dreapta;
} NodArb;

typedef struct NodLS {
	unsigned short int idProdus;
	struct NodLS* next;
} NodLS;

NodArb* creareNod(Produs produs, NodArb* stanga, NodArb* dreapta) {
	NodArb* nou = (NodArb*)malloc(sizeof(NodArb));
	nou->info.idProdus = produs.idProdus;

	nou->info.denumireProdus = (char*)malloc((strlen(produs.denumireProdus) + 1) * sizeof(char));
	strcpy(nou->info.denumireProdus, produs.denumireProdus);

	nou->info.stoc = produs.stoc;

	nou->info.nrClienti = produs.nrClienti;

	nou->info.stocuriClienti = (unsigned short int*)malloc(produs.nrClienti * sizeof(unsigned short int));
	for (int i = 0; i < produs.nrClienti; i++) {
		nou->info.stocuriClienti[i] = produs.stocuriClienti[i];
	}

	nou->stanga = stanga;
	nou->dreapta = dreapta;
		
	return nou;
}

NodArb* inserareNod(NodArb* rad, Produs produs) {
	if (rad != NULL) {
		if (produs.idProdus < rad->info.idProdus) {
			rad->stanga = inserareNod(rad->stanga, produs);
			return rad;
		}
		else if (produs.idProdus > rad->info.idProdus) {
			rad->dreapta = inserareNod(rad->dreapta, produs);
			return rad;
		}
		else {
			return rad;
		}
	}
	else {
		return creareNod(produs, NULL, NULL);
	}
}

//R S D
NodArb* afisarePreOrdine(NodArb* rad) {
	if (rad != NULL) {
		printf("Id: %hu, Denumire: %s, Stoc: %hu, Nr. clienti: %hhu, Stocuri clienti: \n",
			rad->info.idProdus, rad->info.denumireProdus, rad->info.stoc, rad->info.nrClienti);

		for (int i = 0; i < rad->info.nrClienti; i++) {
			printf("%hu ", rad->info.stocuriClienti[i]);
		}
		printf("\n");

		afisarePreOrdine(rad->stanga);
		afisarePreOrdine(rad->dreapta);
	}
}

//S R D
NodArb* afisareInOrdine(NodArb* rad) {
	if (rad != NULL) {
		afisareInOrdine(rad->stanga);
		printf("Id: %hu, Denumire: %s, Stoc: %hu, Nr. clienti: %hhu, Stocuri clienti: \n",
			rad->info.idProdus, rad->info.denumireProdus, rad->info.stoc, rad->info.nrClienti);
		for (int i = 0; i < rad->info.nrClienti; i++) {
			printf("%hu ", rad->info.stocuriClienti[i]);
		}
		printf("\n");
		afisareInOrdine(rad->dreapta);
	}
}

//S D R
NodArb* afisarePostOrdine(NodArb* rad) {
	if (rad != NULL) {
		afisarePostOrdine(rad->stanga);
		afisarePostOrdine(rad->dreapta);
		printf("Id: %hu, Denumire: %s, Stoc: %hu, Nr. clienti: %hhu, Stocuri clienti: \n",
			rad->info.idProdus, rad->info.denumireProdus, rad->info.stoc, rad->info.nrClienti);
		for (int i = 0; i < rad->info.nrClienti; i++) {
			printf("%hu ", rad->info.stocuriClienti[i]);
		}
		printf("\n");
	}
}

void dezalocare(NodArb* rad) {
	if (rad != NULL) {
		dezalocare(rad->stanga);
		dezalocare(rad->dreapta);
		free(rad->info.denumireProdus);
		free(rad->info.stocuriClienti);
		free(rad);
	}
}

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
	NodArb* nod2 = rad->dreapta;
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
	else 
	{
		if (rad->BF >= 2 && fiuDr->BF >= 1) {
			rad = rotatieStanga(rad);
			calculBF(rad);
		}
		else {
			if (rad->BF <= -2 && fiuSt->BF >= 1)
			{
				rad = rotatieStangaDreapta(rad);
				calculBF(rad);
			}
			else {
				if (rad->BF >= 2 && fiuDr->BF <= -1)
				{
					rad = rotatieDreaptaStanga(rad);
					calculBF(rad);
				}
			}
		}
	}
	
	return rad;
}
//ex 2:
//nr de prod cu stoc mai mare decat un prag specificat in param
int numaraProdStocMare(NodArb* rad, unsigned short int stocPrag) {
	if (rad != NULL) {
		int contor = 0;
		if (rad->info.stoc > stocPrag) {
			contor = 1;
		}
		contor += numaraProdStocMare(rad->stanga, stocPrag);
		contor += numaraProdStocMare(rad->dreapta, stocPrag);

		return contor;

	}
	else {
		return 0;
	}	
}

//ex. 3:
//val stoc mediu la clienti pt un produs specificat
//prin id in param functiei
unsigned short int getValMedie(NodArb* rad, unsigned short int idProdusParam) {
	if (rad != NULL) {
		if (rad->info.idProdus == idProdusParam) {
			unsigned short int sumaStocuri = 0;
			for (int i = 0; i < rad->info.nrClienti; i++) {
				sumaStocuri += rad->info.stocuriClienti[i];
			}
			if (rad->info.nrClienti > 0) {
				return sumaStocuri / rad->info.nrClienti;
			}
			else {
				return 0;
			}
		}
		else {
			unsigned short int stanga = getValMedie(rad->stanga, idProdusParam);
			if (stanga != 0) return stanga;
			return getValMedie(rad->dreapta, idProdusParam);
		}
		
	}
	return 0;
}

//ex4
//sterge nodul radacina, apelare inordine
NodArb* stergereRad(NodArb* rad) {
	NodArb* aux = rad;
	if (aux->dreapta != NULL) {
		rad = aux->dreapta;
		if (aux->stanga != NULL) {
			NodArb* temp = aux->dreapta;
			while (temp->stanga != NULL) {
				temp = temp->stanga;
			}
			temp->stanga = aux->stanga;
		}
	}
	else if (aux->stanga != NULL) {
		rad = aux->stanga;
	}
	else {
		rad = NULL;
	}
	free(aux->info.denumireProdus);
	free(aux->info.stocuriClienti);
	free(aux);
	return reechilibrare(rad);
}

//ex5 
//salvare in ls toate val de tip id prod, plasate pe 
//drumul de la radacina catre nodul cu cheia id maxima
void inserareSfarsit(NodLS** cap, unsigned short int id) {
	NodLS* nou = (NodLS*)malloc(sizeof(NodLS));
	nou->idProdus = id;
	nou->next = NULL;
	if (*cap == NULL) {
		*cap = nou;
	}
	else {
		NodLS* temp = *cap;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nou;
	}
}

void salvareDrumMax(NodArb* rad, NodLS** cap) {
	NodArb* temp = rad;
	while (temp != NULL) {
		inserareSfarsit(cap, temp->info.idProdus);
		temp = temp->dreapta;
	}
}

void afisareLista(NodLS* cap) {
	NodLS* temp = cap;
	printf("Drumul de la radacina pana la nodul cu id maxim:\n");
	while (temp != NULL) {
		printf("%hu -> ", temp->idProdus);
		temp = temp->next;
	}
	printf("NULL\n");
}

void dezalocareLista(NodLS** cap) {
	while (*cap) {
		NodLS* temp = *cap;
		*cap = (*cap)->next;
		free(temp);
	}
}

void main() {
	NodArb* rad = NULL;
	Produs produs;
	char buffer[50];
	int nrProduse;

	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrProduse);

	for (int i = 0; i < nrProduse; i++) {
		fscanf(f, "%hu", &produs.idProdus);

		fscanf(f, "%s", buffer);
		produs.denumireProdus = (char*)malloc((strlen(buffer) + 1));
		strcpy(produs.denumireProdus, buffer);

		fscanf(f, "%hu", &produs.stoc);

		fscanf(f, "%hhu", &produs.nrClienti);
		produs.stocuriClienti = (unsigned short int*)malloc(produs.nrClienti * sizeof(unsigned short int));
		for (int j = 0; j < produs.nrClienti; j++) {
			fscanf(f, "%hu", &produs.stocuriClienti[j]);
		}

		rad = inserareNod(rad, produs);
		free(produs.denumireProdus);
		free(produs.stocuriClienti);
	}
	fclose(f);

	printf("-------------------------------PREORDINE---------------------\n");
	afisarePreOrdine(rad);
	printf("-------------------------------INORDINE---------------------\n");
	afisareInOrdine(rad);
	printf("-------------------------------POSTORDINE---------------------\n");
	afisarePostOrdine(rad);

	printf("-------------------------------EX. 2: ---------------------\n");
	unsigned short int prag = 50;
	int rezultat = numaraProdStocMare(rad, prag);
	printf("Exista %d produse cu stocul mai mare decat %hu.\n", rezultat, prag);

	printf("-------------------------------EX. 3: ---------------------\n");
	unsigned short int medie = getValMedie(rad, 10);
	printf("Produsul cu id-ul specificat are val stocurilor de %hu.\n", medie);

	printf("-------------------------------EX. 4: ---------------------\n");
	afisareInOrdine(rad);
	rad = stergereRad(rad);
	printf("----------------DUPA STERGERE RAD-----------\n");
	afisareInOrdine(rad);

	printf("-------------------------------EX. 5: ---------------------\n");
	NodLS* listaIduri = NULL;
	salvareDrumMax(rad, &listaIduri);
	afisareLista(listaIduri);
	dezalocareLista(&listaIduri);

	dezalocare(rad);
}