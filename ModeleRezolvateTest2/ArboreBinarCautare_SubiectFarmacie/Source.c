#include<stdio.h>
#include<malloc.h>

typedef struct Farmacie {
	unsigned short int id;//hu //unsigned -> doar valori pozitive, shor-> tip de date întreg, mai mic decât int
	char* denumire;
	float cifraAfaceri;
	char* numeFarmacistSef;
	unsigned char nrAngajati;//hhu
	char* localitate;
} Farmacie;

typedef struct NodArb {
	Farmacie info;
	struct NodArb* stanga;
	struct NodArb* dreapta;
} NodArb;

typedef struct NodListaSimpla {
	unsigned short int id;
	struct NodLista* next;
} NodListaSimpla;

NodArb* creareNod(Farmacie farmacie, NodArb* stanga, NodArb* dreapta) {
	NodArb* nou = (NodArb*)malloc(sizeof(NodArb));
	nou->info.id = farmacie.id;
	nou->info.denumire = (char*)malloc((strlen(farmacie.denumire) + 1) * sizeof(char));
	strcpy(nou->info.denumire, farmacie.denumire);
	nou->info.cifraAfaceri = farmacie.cifraAfaceri;
	nou->info.numeFarmacistSef = (char*)malloc((strlen(farmacie.numeFarmacistSef) + 1) * sizeof(char));
	strcpy(nou->info.numeFarmacistSef, farmacie.numeFarmacistSef);
	nou->info.nrAngajati = farmacie.nrAngajati;
	nou->info.localitate = (char*)malloc((strlen(farmacie.localitate) + 1) * sizeof(char));
	strcpy(nou->info.localitate, farmacie.localitate);
	nou->stanga = stanga;
	nou->dreapta = dreapta;
	return nou;
}

NodArb* inserareNod(NodArb* rad, Farmacie farmacie) {
	if (rad != NULL) {
		if (farmacie.id < rad->info.id) {
			rad->stanga = inserareNod(rad->stanga, farmacie);
			return rad;
		}
		else if (farmacie.id > rad->info.id) {
			rad->dreapta = inserareNod(rad->dreapta, farmacie);
			return rad;
		}
		else {
			return rad;
		}
	}
	else {
		return creareNod(farmacie, NULL, NULL);
	}
}
//afisare preOrdine -> radacina stanga dreapta
void afisarePreordine(NodArb* rad) {
	if (rad != NULL) {
		printf(" Id: %hu\n Denumire: %s\n Cifra afaceri: %2.5f\n Nume farmacist sef: %s\n Nr. angajati: %hhu\n Localitate: %s\n\n",
			rad->info.id, rad->info.denumire, rad->info.cifraAfaceri, rad->info.numeFarmacistSef, rad->info.nrAngajati, rad->info.localitate);
		afisarePreordine(rad->stanga);
		afisarePreordine(rad->dreapta);
	}
}

//afisare inOrdine -> stanga radacina dreapta
void afisareInordine(NodArb* rad) {
	if (rad != NULL) {
		afisareInordine(rad->stanga);
		printf(" Id: %hu\n Denumire: %s\n Cifra afaceri: %2.5f\n Nume farmacist sef: %s\n Nr. angajati: %hhu\n Localitate: %s\n\n",
			rad->info.id, rad->info.denumire, rad->info.cifraAfaceri, rad->info.numeFarmacistSef, rad->info.nrAngajati, rad->info.localitate);
		afisareInordine(rad->dreapta);
	}
}

//afisare postOrdine-> stanga dreapta radacina
void afisarePostordine(NodArb* rad) {
	if (rad != NULL) {
		afisarePostordine(rad->stanga);
		afisarePostordine(rad->dreapta);
		printf(" Id: %hu\n Denumire: %s\n Cifra afaceri: %2.5f\n Nume farmacist sef: %s\n Nr. angajati: %hhu\n Localitate: %s\n\n",
			rad->info.id, rad->info.denumire, rad->info.cifraAfaceri, rad->info.numeFarmacistSef, rad->info.nrAngajati, rad->info.localitate);
	}
}

void dezalocare(NodArb* rad) {
	if (rad != NULL) {
		dezalocare(rad->stanga);
		dezalocare(rad->dreapta);
		free(rad->info.denumire);
		free(rad->info.numeFarmacistSef);
		free(rad->info.localitate);
		free(rad);
	}
}

//ex2-> nr total de angajati la farmacia dintr-o
//anumita localitate data ca param

void sumaNrAngajati(NodArb* rad, unsigned char *nrAngajatiLocalitate, const char* localitateParam) {
	if (rad != NULL) {
		if (strcmp(rad->info.localitate, localitateParam) == 0) {
			*nrAngajatiLocalitate += rad->info.nrAngajati;
		}
		sumaNrAngajati(rad->stanga, nrAngajatiLocalitate, localitateParam);
		sumaNrAngajati(rad->dreapta, nrAngajatiLocalitate, localitateParam);
	}
}

//ex3-> cifra de afaceri medie lunara pt o farmacie
//specificata prin id in param functiei
float cifraAfaceriLunara(NodArb* rad, unsigned short int idParam) {;
	if (rad != NULL) {
		if (rad->info.id == idParam) {
			return  rad->info.cifraAfaceri / 12;
		}
		float st = cifraAfaceriLunara(rad->stanga, idParam);
		if (st > 0) {
			return st;
		}
		float dr = cifraAfaceriLunara(rad->dreapta, idParam);
		if (dr > 0) {
			return dr;
		}
	}
	return 0;
}

//ex 4
//stergere noduri frunza din structura arborescenta
//plsate pe un nivel specificat ca parametru al functiei
//afisare in ordine

NodArb* stergereFrunzeNivel(NodArb* rad, int nivelCurent, int nivelSpec) {
	if (rad == NULL) {
		return NULL;
	}
	if (nivelCurent == nivelSpec && rad->stanga == NULL && rad->dreapta == NULL) {
		//se afla pe nivelul specificat si este frunza
		free(rad->info.denumire);
		free(rad->info.numeFarmacistSef);
		free(rad->info.localitate);
		free(rad);
		return NULL;
	}
	rad->stanga = stergereFrunzeNivel(rad->stanga, nivelCurent + 1, nivelSpec);
	rad->dreapta = stergereFrunzeNivel(rad->dreapta, nivelCurent + 1, nivelSpec);
	return rad;
}

//ex 5
//salvare arbore intr o lista simpla
//toate valorile de tip id farmacie plasate pe un nivel specificat
//in param functiei
NodListaSimpla* initializareNodLS(unsigned short int id) {
	NodListaSimpla* nou = (NodListaSimpla*)malloc(sizeof(NodListaSimpla));
	nou->id = id;
	nou->next = NULL;
	return nou;
}

NodListaSimpla* inserareNodLS(NodListaSimpla* capLS, unsigned short int id) {
	NodListaSimpla* nou = initializareNodLS(id);
	if (capLS == NULL) {
		return nou;
	}
	else {
		NodListaSimpla* temp = capLS;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nou;
		return capLS;
	}
}

void salvareIdNivel(NodArb* rad, int nivelCurent, int nivelSpecificat, NodListaSimpla** capLS) {
	if (rad != NULL) {
		if (nivelCurent == nivelSpecificat) {
			*capLS = inserareNodLS(*capLS, rad->info.id);
		}
		salvareIdNivel(rad->stanga, nivelCurent + 1, nivelSpecificat, capLS);
		salvareIdNivel(rad->dreapta, nivelCurent + 1, nivelSpecificat, capLS);
	}
}

void traversareLista(NodListaSimpla* capLS) {
	NodListaSimpla* temp = capLS;
	while (temp != NULL) {
		printf("Id = %hu\n", temp->id);
		temp = temp->next;
	}
}


void dezalocareLista(NodListaSimpla* capLS) {
	NodListaSimpla* temp = capLS;
	while (temp != NULL) {
		NodListaSimpla* aux = temp->next;
		free(temp);
		temp = aux;
	}
}



void main() {
	NodArb* rad = NULL;
	Farmacie farmacie;
	char buffer[50];
	int nrFarmacii;
	FILE* f = fopen("farmacie.txt", "r");

	fscanf(f, "%d", &nrFarmacii);

	for (int i = 0; i < nrFarmacii; i++) {
		fscanf(f, "%hu", &farmacie.id);
		fscanf(f, "%s", buffer);
		farmacie.denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(farmacie.denumire, buffer);
		fscanf(f, "%f", &farmacie.cifraAfaceri);
		fscanf(f, "%s", buffer);
		farmacie.numeFarmacistSef = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(farmacie.numeFarmacistSef, buffer);
		fscanf(f, "%hhu", &farmacie.nrAngajati);
		fscanf(f, "%s", buffer);
		farmacie.localitate = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(farmacie.localitate, buffer);

		rad = inserareNod(rad, farmacie);
		free(farmacie.denumire);
		free(farmacie.numeFarmacistSef);
		free(farmacie.localitate);
	}
	fclose(f);

	printf("-----------------------PREORDINE-----------------\n");
	afisarePreordine(rad);
	printf("-----------------------INORDINE-----------------\n");
	afisareInordine(rad);
	printf("-----------------------POSTORDINE-----------------\n");
	afisarePostordine(rad);

	printf("-----------------------EX 2:-----------------\n");
	unsigned char nrAng = 0;
	sumaNrAngajati(rad, &nrAng, "Bucuresti");
	printf("Nr. de angajati din localitatea data este: %hhu\n", nrAng);

	printf("-----------------------EX 3:-----------------\n");
	float ca = 0;
	ca = cifraAfaceriLunara(rad, 10);
	printf("CA: %f\n", ca);

	printf("-----------------------EX 4:-----------------\n");
	int nivel = 2;
	rad = stergereFrunzeNivel(rad, 0, nivel);
	printf("Dupa stergere: \n");
	afisareInordine(rad);

	printf("-----------------------EX 5:-----------------\n");
	int nivelCautat = 1;
	NodListaSimpla* capLS = NULL;
	salvareIdNivel(rad, 0, nivelCautat, &capLS);

	printf("Farmacii pe nivelul %d:\n", nivelCautat);
	traversareLista(capLS);

	dezalocareLista(capLS);

	dezalocare(rad);
}