#include<stdio.h>
#include<malloc.h>

typedef struct Rezervare {
	unsigned int id;//%u
	char* denumireHotel;
	unsigned char nrCamereRezervate;//%hhu
	char* numeClient;
	float suma;
} Rezervare;

typedef struct NodArb {
	int BF;
	Rezervare info;
	struct NodArb* stanga;
	struct NodArb* dreapta;
} NodArb;

NodArb* creareNod(Rezervare rezervare, NodArb* stanga, NodArb* dreapta) {
	NodArb* nou = (NodArb*)malloc(sizeof(NodArb));
	nou->info.id = rezervare.id;
	nou->info.denumireHotel = (char*)malloc((strlen(rezervare.denumireHotel) + 1) * sizeof(char));
	strcpy(nou->info.denumireHotel, rezervare.denumireHotel);
	nou->info.nrCamereRezervate = rezervare.nrCamereRezervate;
	nou->info.numeClient = (char*)malloc((strlen(rezervare.numeClient) + 1) * sizeof(char));
	strcpy(nou->info.numeClient, rezervare.numeClient);
	nou->info.suma = rezervare.suma;
	nou->stanga = stanga;
	nou->dreapta = dreapta;
	return nou;
}

NodArb* inserareNod(NodArb* rad, Rezervare rezervare) {
	if (rad != NULL) {
		if (rezervare.id < rad->info.id) {
			rad->stanga = inserareNod(rad->stanga, rezervare);
			return rad;
		}
		else if (rezervare.id > rad->info.id) {
			rad->dreapta = inserareNod(rad->dreapta, rezervare);
			return rad;
		}
	}
	else {
		return creareNod(rezervare, NULL, NULL);
	}
}

//R S D
NodArb* afisarePreOrdine(NodArb* rad) {
	if (rad != NULL) {
		printf("ID: %u, Nume hotel: %s, Nr. camere rezervare: %hhu, Nume client: %s, Suma: %.2f\n",
			rad->info.id, rad->info.denumireHotel, rad->info.nrCamereRezervate, rad->info.numeClient, rad->info.suma);
		afisarePreOrdine(rad->stanga);
		afisarePreOrdine(rad->dreapta);
	}
}

//S R D
NodArb* afisareInOrdine(NodArb* rad) {
	if (rad != NULL) {
		afisareInOrdine(rad->stanga);
		printf("ID: %u, Nume hotel: %s, Nr. camere rezervare: %hhu, Nume client: %s, Suma: %.2f\n",
			rad->info.id, rad->info.denumireHotel, rad->info.nrCamereRezervate, rad->info.numeClient, rad->info.suma);
		afisareInOrdine(rad->dreapta);
	}
}

//S D R
NodArb* afisarePostOrdine(NodArb* rad) {
	if (rad != NULL) {
		afisarePostOrdine(rad->stanga);
		afisarePostOrdine(rad->dreapta);
		printf("ID: %u, Nume hotel: %s, Nr. camere rezervare: %hhu, Nume client: %s, Suma: %.2f\n",
			rad->info.id, rad->info.denumireHotel, rad->info.nrCamereRezervate, rad->info.numeClient, rad->info.suma);
	}
}

void dezalocare(NodArb* rad) {
	if (rad != NULL) {
		dezalocare(rad->stanga);
		dezalocare(rad->dreapta);
		free(rad->info.denumireHotel);
		free(rad->info.numeClient);
		free(rad);
	}
}

//stergere radacina (suplimentara)
/*NodArb* stergereRad(NodArb* rad) {
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
	free(aux->info.denumireHotel);
	free(aux->info.numeClient);
	free(aux);
	return rad;
}

//transformare in avl(suplimentar)
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

NodArb* rotireDreapta(NodArb* rad) {
	printf("\nRotatie dreapta\n");
	NodArb* nod1 = rad->stanga;
	rad->stanga = nod1->dreapta;
	nod1->dreapta = rad;
	rad = nod1;
	return rad;
}

NodArb* rotireStanga(NodArb* rad) {
	printf("\nRotatie stanga\n");
	NodArb* nod1 = rad->dreapta;
	rad->dreapta = nod1->stanga;
	nod1->stanga = rad;
	rad = nod1;
	return rad;
}

NodArb* rotireStangaDreapta(NodArb* rad) {
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

NodArb* rotireDreaptaStanga(NodArb* rad) {
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
		rad = rotireDreapta(rad);
		calculBF(rad);
	}
	else {
		if (rad->BF >= 2 && fiuDr->BF >= 1) {
			rad = rotireStanga(rad);
			calculBF(rad);
		}
		else {
			if (rad->BF <= -2 && fiuSt->BF >= 1) {
				rad = rotireStangaDreapta(rad);
				calculBF(rad);
			}
			else {
				if (rad->BF >= 2 && fiuDr->BF <= -1) {
					rad = rotireStangaDreapta(rad);
					calculBF(rad);
				}
			}
		}
	}
	return rad;
}*/

//ex2: 
NodArb* afisarePreOrdineEx2(NodArb* rad) {
	if (rad != NULL) {
		printf("ID: %u, Nume client: %s\n",
			rad->info.id, rad->info.numeClient);
		afisarePreOrdineEx2(rad->stanga);
		afisarePreOrdineEx2(rad->dreapta);
	}
}

//ex3:
//val tuturor rez efectuate de catre un client
//specificat ca parametru de intrare al functiei
float getSumaTotalaPlata(NodArb* rad, char* numeClientParam) {
	if (rad == NULL) {
		return 0;
	}

	float suma = 0;

		if (strcmp(rad->info.numeClient, numeClientParam) == 0) {
			suma += rad->info.suma;
		}
		 suma += getSumaTotalaPlata(rad->stanga, numeClientParam);
		 suma += getSumaTotalaPlata(rad->dreapta, numeClientParam);
		 return suma;
}

//ex4:
//sterge nodul cu cheia minima 
//afisare in preordine
NodArb* stergeNodCheieMin(NodArb* rad) {
	if (rad == NULL) {
		return NULL;
	}
	//daca nu are nimic pe stanga inseamna ca e cel mai mic
	if (rad->stanga == NULL) {
		NodArb* temp = rad->dreapta;
		free(rad->info.denumireHotel);
		free(rad->info.numeClient);
		free(rad);
		return temp;
	}

	//altfel continuam pana la ultimul sub arbore stanga
	rad->stanga = stergeNodCheieMin(rad->stanga);
	return rad;
}

//ex 5
//vector ce contine nr de noduri plasate pe fiecare nivel 
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

void numaraPeNivel(NodArb* rad, int nivel, int* frecventa) {
	if (rad != NULL) {
		frecventa[nivel]++;
		numaraPeNivel(rad->stanga, nivel + 1, frecventa);
		numaraPeNivel(rad->dreapta, nivel + 1, frecventa);
	}
}

int* getVectorNoduriPeNivel(NodArb* rad, int* inaltime) {
	*inaltime = inaltimeArb(rad);
	int* vector = (int*)malloc(*inaltime * sizeof(int));

	// Inițializare manuală (echivalent cu calloc)
	for (int i = 0; i < *inaltime; i++) {
		vector[i] = 0;
	}

	numaraPeNivel(rad, 0, vector);
	return vector;
}



void main() {
	NodArb* rad = NULL;
	Rezervare rezervare;
	char buffer[50];
	int nrRezervari;

	FILE* f = fopen("fisier.txt", "r");

	fscanf(f, "%d", &nrRezervari);
	for (int i = 0; i< nrRezervari; i++) {
		fscanf(f, "%u", &rezervare.id);

		fscanf(f, "%s", buffer);
		rezervare.denumireHotel = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(rezervare.denumireHotel, buffer);

		fscanf(f, "%hhu", &rezervare.nrCamereRezervate);

		fscanf(f, "%s", buffer);
		rezervare.numeClient = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(rezervare.numeClient, buffer);

		fscanf(f, "%f", &rezervare.suma);

		rad = inserareNod(rad, rezervare);
		free(rezervare.denumireHotel);
		free(rezervare.numeClient);

		//rad = reechilibrare(rad);
	}
	fclose(f);

	printf("-------------------------------PREORDINE---------------------\n");
	afisarePreOrdine(rad);
	printf("-------------------------------INORDINE---------------------\n");
	afisareInOrdine(rad);
	printf("-------------------------------POSTORDINE---------------------\n");
	afisarePostOrdine(rad);

	/*printf("-------------------------------PREORDINE---------------------\n");
	afisarePreOrdine(rad);
	printf("-------------------------------DUPA STERGERE RAD---------------------\n");
	rad = stergereRad(rad);
	afisarePreOrdine(rad);*/
	printf("-------------------------------Ex2: ---------------------\n");
	afisarePreOrdineEx2(rad);

	printf("-------------------------------Ex3: ---------------------\n");
	float sumaS = getSumaTotalaPlata(rad, "Simionescu");
	printf("Suma clientului dat ca parametru este: %.2f\n", sumaS);


	printf("-------------------------------Ex4:  ---------------------\n");
	rad = stergeNodCheieMin(rad);
	afisarePreOrdineEx2(rad);

	printf("-------------------------------Ex5: ---------------------\n");
	int h = 0;
	int* vector = getVectorNoduriPeNivel(rad, &h);
	printf("Vector nivele: ");
	for (int i = 0; i < h; i++) {
		printf("%d", vector[i]);
		if (i < h - 1) {
			printf(", ");
		}
	}
	printf("\n");
	free(vector);



	dezalocare(rad);
}