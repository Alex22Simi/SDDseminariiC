#include <stdio.h>
#include <malloc.h>

typedef struct Rezervare {
	unsigned int nrRezervare;//%u
	char* denumireHotel;
	unsigned char nrCamereRezervate; 
	char* numeClient;
	char* dataRezervare;

} Rezervare;

typedef struct NodArb {
	Rezervare info;
	struct NodArb* stanga;
	struct NodArb* dreapta;
} NodArb;

NodArb* creareNod(Rezervare rezervare, NodArb* stanga, NodArb* dreapta) {
	NodArb* nou = (NodArb*)malloc(sizeof(NodArb));
	nou->info.nrRezervare = rezervare.nrRezervare;
	nou->info.denumireHotel = (char*)malloc((strlen(rezervare.denumireHotel) + 1) * sizeof(char));
	strcpy(nou->info.denumireHotel, rezervare.denumireHotel);
	nou->info.nrCamereRezervate = rezervare.nrCamereRezervate;
	nou->info.numeClient = (char*)malloc((strlen(rezervare.numeClient) + 1) * sizeof(char));
	strcpy(nou->info.numeClient, rezervare.numeClient);
	nou->info.dataRezervare = (char*)malloc((strlen(rezervare.dataRezervare) + 1) * sizeof(char));
	strcpy(nou->info.dataRezervare, rezervare.dataRezervare);
	nou->stanga = NULL;
	nou->dreapta = NULL;
	return nou;
}

NodArb* inserareNod(NodArb* rad, Rezervare rezervare) {
	if (rad != NULL) {
		if (rezervare.nrRezervare < rad->info.nrRezervare) {
			rad->stanga = inserareNod(rad->stanga, rezervare);
			return rad;
		}
		else if (rezervare.nrRezervare > rad->info.nrRezervare) {
			rad->dreapta = inserareNod(rad->dreapta, rezervare);
			return rad;
		}
		else {
			return rad;
		}
	}
	else {
		return creareNod(rezervare, NULL, NULL);
	}
}

//R S D
void afisarePreOrdine(NodArb* rad) {
	if (rad != NULL) {
		printf("NrRezervare: %u, Denumire hotel: %s, NrCamereRezervate: %hhu, Nume client: %s, Data rezervare: %s\n",
			rad->info.nrRezervare, rad->info.denumireHotel, rad->info.nrCamereRezervate, rad->info.numeClient, rad->info.dataRezervare);
		afisarePreOrdine(rad->stanga);
		afisarePreOrdine(rad->dreapta);
	}
}

//S R D
void afisareInOrdine(NodArb* rad) {
	if (rad != NULL) {
		afisareInOrdine(rad->stanga);
		printf("NrRezervare: %u, Denumire hotel: %s, NrCamereRezervate: %hhu, Nume client: %s, Data rezervare: %s\n",
			rad->info.nrRezervare, rad->info.denumireHotel, rad->info.nrCamereRezervate, rad->info.numeClient, rad->info.dataRezervare);
		afisareInOrdine(rad->dreapta);
	}
}

//S D R
void afisarePostOrdine(NodArb* rad) {
	if (rad != NULL) {
		afisarePostOrdine(rad->stanga);
		afisarePostOrdine(rad->dreapta);
		printf("NrRezervare: %u, Denumire hotel: %s, NrCamereRezervate: %hhu, Nume client: %s, Data rezervare: %s\n",
			rad->info.nrRezervare, rad->info.denumireHotel, rad->info.nrCamereRezervate, rad->info.numeClient, rad->info.dataRezervare);
	}
}

void dezalocareArb(NodArb* rad) {
	if (rad != NULL) {
		dezalocareArb(rad->stanga);
		dezalocareArb(rad->dreapta);
		free(rad->info.denumireHotel);
		free(rad->info.numeClient);
		free(rad->info.dataRezervare);
		free(rad);
	}
}

//ex2
//rezervarea cu nr max de camere
//se intoarce prima aparitie a rezervarii cu nr max de camere
Rezervare* rezervareCuMaxCamere(NodArb* rad, Rezervare* currentMax) {
	if (rad != NULL) {
		if (currentMax == NULL || rad->info.nrCamereRezervate > currentMax->nrCamereRezervate) {
			currentMax = &(rad->info);
		}
		currentMax = rezervareCuMaxCamere(rad->stanga, currentMax);
		currentMax = rezervareCuMaxCamere(rad->dreapta, currentMax);
	}
	return currentMax;
}

//ex3
//modifica nr de camere ale unei rez specificata prin nr rezervare
//in lista de param
//noua valoare este de asemenea pusa in param
void modificaRezervare(NodArb* rad, unsigned int nrRezervareParam, unsigned char nrCamereRezervateParam) {
	if (rad != NULL) {
		if (rad->info.nrRezervare == nrRezervareParam) {
			rad->info.nrCamereRezervate = nrCamereRezervateParam;
			return;
		}
		modificaRezervare(rad->stanga, nrRezervareParam, nrCamereRezervateParam);
		modificaRezervare(rad->dreapta, nrRezervareParam, nrCamereRezervateParam);
	}
}

void cautaRezervareDupaNr(NodArb* rad, unsigned int nrRezervareParam) {
	if (rad != NULL) {
		if (rad->info.nrRezervare == nrRezervareParam) {
			printf("NrRezervare: %u, Denumire hotel: %s, NrCamereRezervate: %hhu, Nume client: %s, Data rezervare: %s\n",
				rad->info.nrRezervare, rad->info.denumireHotel, rad->info.nrCamereRezervate, rad->info.numeClient, rad->info.dataRezervare);
		}
		cautaRezervareDupaNr(rad->stanga, nrRezervareParam);
		cautaRezervareDupaNr(rad->dreapta, nrRezervareParam);
	}
}
//ex4
//det nr de noduri
int detNrNoduri(NodArb* rad) {
	if (rad == NULL) {
		return 0;
	}
	else {
		return 1 + detNrNoduri(rad->stanga) + detNrNoduri(rad->dreapta);
	}
}

//ex5
//transformare arbore in vector de rezervari plasate pe drumul de la nodul radacinii
//pana la un anumit nod specificat prin nr de rezervare
//in lista de parametri ai functiei
int getDrum(NodArb* rad, unsigned int nrCautat, Rezervare** drum, int nivel) {
	if (rad == NULL) {
		return 0;
	}

	drum[nivel] = &rad->info;//adaugare rezervare curent in drum;

	if (rad->info.nrRezervare == nrCautat) {
		return 1;
	} 
	if (getDrum(rad->stanga, nrCautat, drum, nivel + 1)) {
		return 1;
	}
	if (getDrum(rad->dreapta, nrCautat, drum, nivel + 1)) {
		return 1;
	}
	//daca nu gasim in niciun a=subarbore eliminam ultimul adaugat
	drum[nivel] = NULL;
	return 0;

}


void main() {
	NodArb* rad = NULL;
	Rezervare rezervare;
	int nrRezervari;

	char buffer[50];
	FILE* f = fopen("rezervari.txt", "r");

	fscanf(f, "%d", &nrRezervari);
	for (int i = 0; i < nrRezervari; i++) {
		fscanf(f, "%u", &rezervare.nrRezervare);

		fscanf(f, "%s", buffer);
		rezervare.denumireHotel = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(rezervare.denumireHotel, buffer);

		fscanf(f, "%hhu", &rezervare.nrCamereRezervate);

		fscanf(f, "%s", buffer);
		rezervare.numeClient = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(rezervare.numeClient, buffer);

		fscanf(f, "%s", buffer);
		rezervare.dataRezervare = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(rezervare.dataRezervare, buffer);

		rad = inserareNod(rad, rezervare);
	}
	fclose(f);

	printf("-----------------------AFISARE PREORDINE-----------------------\n");
	afisarePreOrdine(rad);
	printf("-----------------------AFISARE INORDINE-----------------------\n");
	afisareInOrdine(rad);
	printf("-----------------------AFISARE POSTORDINE-----------------------\n");
	afisarePostOrdine(rad);

	printf("-----------------------EX. 2:-----------------------\n");
	Rezervare* maxRez = rezervareCuMaxCamere(rad, NULL);
	if (maxRez != NULL) {
		printf("Rezervarea cu cele mai multe camere: %u, %s, %hhu, %s, %s\n",
			maxRez->nrRezervare, maxRez->denumireHotel, maxRez->nrCamereRezervate,
			maxRez->numeClient, maxRez->dataRezervare);
	}

	printf("-----------------------EX. 3:-----------------------\n");
	modificaRezervare(rad, 12, 2);
	cautaRezervareDupaNr(rad, 12);

	printf("-----------------------EX. 4:-----------------------\n");
	int nrNoduri = detNrNoduri(rad);
	printf("Numarul de radacini total din arbore: %d\n", nrNoduri);

	printf("-----------------------EX. 5:-----------------------\n");
	Rezervare* drum[100] = { NULL };
	unsigned int nrCautat = 12;

	if (getDrum(rad, nrCautat, drum, 0)) {
		printf("Drumul de la radacina pana la rezervarea cu nr %u este:\n", nrCautat);
		for (int i = 0; drum[i] != NULL; i++) {
			printf("-> %u, %s, %hhu, %s, %s\n",
				drum[i]->nrRezervare,
				drum[i]->denumireHotel,
				drum[i]->nrCamereRezervate,
				drum[i]->numeClient,
				drum[i]->dataRezervare);
		}
	}
	else {
		printf("Rezervarea cu nr %u nu a fost gasita in arbore.\n", nrCautat);
	}

	dezalocareArb(rad);
}