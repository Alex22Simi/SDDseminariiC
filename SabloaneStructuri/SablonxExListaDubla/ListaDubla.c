#include<malloc.h>
#include<stdio.h>

typedef struct Masina {
	int id;
	int nrUsi;
	float pret;
	char* model;
} Masina;

typedef struct NodLD {
	Masina info;
	struct NodLD* next;
	struct NodLD* prev;
} NodLD;

NodLD* initializareNodLD(Masina masina) {
	NodLD* nodNou = (NodLD*)malloc(sizeof(NodLD));
	nodNou->info.id = masina.id;
	nodNou->info.nrUsi = masina.nrUsi;
	nodNou->info.pret = masina.pret;
	nodNou->info.model = (char*)malloc((strlen(masina.model) + 1) * sizeof(char));
	strcpy(nodNou->info.model, masina.model);
	nodNou->next = NULL;
	nodNou->prev = NULL;
	return nodNou;
}

NodLD* inserareNodLD(NodLD* capLD, NodLD** coadaLD, Masina masina) {
	NodLD* nodNou = initializareNodLD(masina);
	if (capLD == NULL) {
		capLD = nodNou;
		*coadaLD = nodNou;
	}
	else {
		(*coadaLD)->next = nodNou;
		nodNou->prev = (*coadaLD);
		(*coadaLD) = nodNou;
	}
	return capLD;
}

void traversareNodLD(NodLD* capLD) {
	NodLD* temp = capLD;
	while (temp != NULL) {
		printf("\nId-ul masinii: %d\nNumarul de usi: %d\nPretul: %.2f\nModelul: %s\n\n",
			temp->info.id, temp->info.nrUsi, temp->info.pret, temp->info.model);
		temp = temp->next;
	}
}

void traversareInversaLD(NodLD* coadaLD) {
	NodLD* temp = coadaLD;
	while (temp != NULL) {
		printf("\nId-ul masinii: %d\nNumarul de usi: %d\nPretul: %.2f\nModelul: %s\n\n",
			temp->info.id, temp->info.nrUsi, temp->info.pret, temp->info.model);
		temp = temp->prev;
	}
}

void dezalocare(NodLD* capLD) {
	NodLD* temp = capLD;
	while (temp != NULL) {
		NodLD* aux = temp->next;
		free(temp->info.model);
		free(temp);
		temp = aux;
	}
}

void salvareMasiniInVectorCuPretMare(NodLD* capLD, Masina* vectMasini, int* nrElem, float prag) {
	NodLD* temp = capLD;
	while (temp != NULL) {
		if (temp->info.pret > prag) {
			vectMasini[*nrElem].id = temp->info.id;
			vectMasini[*nrElem].nrUsi = temp->info.nrUsi;
			vectMasini[*nrElem].pret = temp->info.pret;
			vectMasini[*nrElem].model = (char*)malloc((strlen(temp->info.model) + 1) * sizeof(char));
			strcpy(vectMasini[*nrElem].model, temp->info.model);
			(*nrElem)++;
		}
		temp = temp->next;
	}
}

//adaugare Masina la sfarsit
NodLD* adaugaMasinaLaSfarsit(NodLD* capLD, NodLD** coadaLD, int id, int nrUsi, float pret, const char* model) {
	Masina masina;

	masina.id = id;
	masina.nrUsi = nrUsi;
	masina.pret = pret;
	masina.model = (char*)malloc((strlen(model) + 1) * sizeof(char));
	strcpy(masina.model, model);

	NodLD* nodNou = initializareNodLD(masina);
	if (capLD == NULL) {
		capLD = nodNou;
		(*coadaLD) = nodNou;
	}
	else {
		(*coadaLD)->next = nodNou;
		nodNou->prev = (*coadaLD);
		(*coadaLD) = nodNou;
	}
	free(masina.model);
	return capLD;
}

//adaugare Masina la inceput
NodLD* adaugaMasinaInceput(NodLD* capLD, NodLD** coadLD, int id, int nrUsi, float pret, const char* model) {
	Masina masina;

	masina.id = id;
	masina.nrUsi = nrUsi;
	masina.pret = pret;
	masina.model = (char*)malloc((strlen(model) + 1) * sizeof(char));
	strcpy(masina.model, model);

	NodLD* nodNou = initializareNodLD(masina);

	nodNou->prev = NULL;
	nodNou->next = capLD;

	if (capLD != NULL) {
		capLD->prev = nodNou;
	}
	else {
		(*coadLD) = nodNou;
	}
	free(masina.model);
	capLD = nodNou;
	return capLD;
}

//sa se se faca media usilor masinilor
float mediaUsiMasini(NodLD* capLD) {
	int valoare = 0;
	int contor = 0;

	NodLD* temp = capLD;
	while (temp != NULL) {
		valoare += temp->info.nrUsi;
		contor++;
		temp = temp->next;
	}
	if (valoare > 0) {
		return valoare / contor;
	}
	else {
		return 0;
	}
}

//sa se afiseze numele modelului cel mai scump
char* afiseazaNumeModelScump(NodLD* capLD) {
	float pretMax = 0.0;
	char* numeModel = NULL;
	NodLD* temp = capLD;
	while (temp != NULL) {
		if (temp->info.pret > pretMax) {
			numeModel = temp->info.model;
			pretMax = temp->info.pret;
		}
		temp = temp->next;
	}
	if (pretMax > 0) {
		return numeModel;
	}
	else {
		return "Nu exista masini.";
	}
}

//stergere masina dupa nume
void stergereMasinaDupaNume(NodLD** capLD, NodLD** coadaLD, const char* modelMasina) {
	if (strcmp((*capLD)->info.model, modelMasina) == 0) {
		NodLD* deSters = (*capLD);
		(*capLD) = (*capLD)->next;
		if ((*capLD) != NULL) {
			(*capLD)->prev = NULL;
		}
		free(deSters->info.model);
		free(deSters);
		return;
	}
	else {
		NodLD* deSters = (*coadaLD);
		if (strcmp((*coadaLD)->info.model, modelMasina) == 0) {
			(*coadaLD) = (*coadaLD)->prev;
			if ((*coadaLD) != NULL) {
				(*coadaLD)->next = NULL;
			}
			free(deSters->info.model);
			free(deSters);
			return;
		}
		else {
			NodLD* deSters = (*capLD);
			while (deSters != NULL) {
				if (strcmp(deSters->info.model, modelMasina) == 0) {
					NodLD* anterior = deSters->prev;
					NodLD* urmator = deSters->next;
					anterior->next = urmator;
					urmator->prev = anterior;
					free(deSters->info.model);
					free(deSters);
					return;
				}
				else {
					deSters = deSters->next;
				}
			}
		}
	}
}

void main() {
	NodLD* capLD = NULL;
	NodLD* coadaLD = NULL;
	Masina masina;
	int nrElementeFisier;
	char buffer[20];

	FILE* f = fopen("masini.txt", "r");
	fscanf(f, "%d", &nrElementeFisier);
	for (int i = 0; i < nrElementeFisier; i++) {
		fscanf(f, "%d", &masina.id);
		fscanf(f, "%d", &masina.nrUsi);
		fscanf(f, "%f", &masina.pret);
		fscanf(f, "%s", buffer);
		masina.model = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(masina.model, buffer);
		capLD = inserareNodLD(capLD, &coadaLD, masina);
		free(masina.model);
	}
	fclose(f);

	traversareNodLD(capLD);
	printf("-------------------TRANVERSARE INVERSA------------------\n");
	traversareInversaLD(coadaLD);

	printf("----------------------VECTOR----------------");
	Masina* vectMasini = (Masina*)malloc(nrElementeFisier * sizeof(Masina));
	int nrElementeVect = 0;
	salvareMasiniInVectorCuPretMare(capLD, vectMasini, &nrElementeVect, 10000);
	for (int i = 0; i < nrElementeVect; i++) {
		printf("\nId-ul masinii: %d\nNumarul de usi: %d\nPretul: %.2f\nModelul: %s\n\n",
			vectMasini[i].id, vectMasini[i].nrUsi, vectMasini[i].pret, vectMasini[i].model);
	}
	for (int i = 0; i < nrElementeVect; i++) {
		free(vectMasini[i].model);
	}
	free(vectMasini);

	printf("\n-----------------ADAUGARE SFARSIT----------------------\n");
	capLD = adaugaMasinaLaSfarsit(capLD, &coadaLD, 222, 2, 1010, "Cielo");
	traversareNodLD(capLD);

	printf("\n------------------ADAUGARE INCEPUT---------------------\n");
	capLD = adaugaMasinaInceput(capLD, &coadaLD, 9900, 3, 56767, "Duster");
	traversareNodLD(capLD);

	float medie;
	medie = mediaUsiMasini(capLD);
	printf("Media usilor este %.2f\n", medie);

	char* nume;
	nume = afiseazaNumeModelScump(capLD);
	printf("Modelul cel mai scump este: %s", nume);

	printf("\n-----------------------------STERGERE MASINA DUPA NUME-------------------------\n");
	stergereMasinaDupaNume(&capLD, &coadaLD, "Logan");
	traversareNodLD(capLD);

	dezalocare(capLD);
}