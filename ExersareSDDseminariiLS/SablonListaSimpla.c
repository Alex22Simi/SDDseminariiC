#include<stdio.h>
#include<malloc.h>

typedef struct EchipaFotbal {
	char* nume;
	int nrJucatori;
	float venit;
	char* antrenor;
} EchipaFotbal;

typedef struct NodLS {
	EchipaFotbal info;
	struct NodLS* next;
} NodLS;

NodLS* initializareNodLS(EchipaFotbal echipaFotbal) {
	NodLS* nodNou = (NodLS*)malloc(sizeof(NodLS));
	nodNou->info.nume = (char*)malloc((strlen(echipaFotbal.nume) + 1) * sizeof(char));
	strcpy(nodNou->info.nume, echipaFotbal.nume);
	nodNou->info.nrJucatori = echipaFotbal.nrJucatori;
	nodNou->info.venit = echipaFotbal.venit;
	nodNou->info.antrenor = (char*)malloc((strlen(echipaFotbal.antrenor) + 1) * sizeof(char));
	strcpy(nodNou->info.antrenor, echipaFotbal.antrenor);
	nodNou->next = NULL;
	return nodNou;
}

NodLS* inserareNodLS(NodLS* capLS, EchipaFotbal echipaFotbal) {
	NodLS* nodNou = initializareNodLS(echipaFotbal);

	if (capLS == NULL) {
		capLS = nodNou;
	}
	else {
		NodLS* temp = capLS;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nodNou;
	}
	return capLS;
}

void traversareLS(NodLS* capLS) {
	NodLS* temp = capLS;
	while (temp != NULL) {
		printf("Numele echipei de fotbal: %s\nNumarul de jucatori echipa: %d\nVenituri echipa: %.2f\nAntrenorul echipei: %s\n\n",
			temp->info.nume, temp->info.nrJucatori, temp->info.venit, temp->info.antrenor);
		temp = temp->next;
	}
}

void dezalocareNodLS(NodLS* capLS) {
	NodLS* temp = capLS;
	while (temp != NULL) {
		NodLS* aux = temp->next;
		free(temp->info.nume);
		free(temp->info.antrenor);
		free(temp);
		temp = aux;
	}
}

void adaugareInVectorEchipeCuMultiJucatori(NodLS* capLS, EchipaFotbal* vectorEchipeFotbal, int* nrElemente, float prag) {
	NodLS* temp = capLS;
	while (temp != NULL) {
		if (temp->info.nrJucatori >= prag) {
			vectorEchipeFotbal[*nrElemente].nume = (char*)malloc((strlen(temp->info.nume) + 1) * sizeof(char));
			strcpy(vectorEchipeFotbal[*nrElemente].nume, temp->info.nume);

			vectorEchipeFotbal[*nrElemente].nrJucatori = temp->info.nrJucatori;

			vectorEchipeFotbal[*nrElemente].venit = temp->info.venit;

			vectorEchipeFotbal[*nrElemente].antrenor = (char*)malloc((strlen(temp->info.antrenor) + 1) * sizeof(char));
			strcpy(vectorEchipeFotbal[*nrElemente].antrenor, temp->info.antrenor);

			(*nrElemente)++;
		}
		temp = temp->next;
	}
}

float venitMediuEchipeDeFotbal(NodLS* capLS) {
	int nrEchipe = 0;
	float suma = 0.0f;

	NodLS* temp = capLS;
	while (temp) {
		suma += temp->info.venit;
		nrEchipe++;
		temp = temp->next;
	}
	if (nrEchipe > 0) {
		return suma / nrEchipe;
	}
	else {
		return 0;
	}
}

//sa se afiseze numarul total de jucatori al echipelor care au acelasi antrenor
int numarJucatoriTotalPerAntrenor(NodLS* capLS, const char* numeAntrenor) {
	NodLS* temp = capLS;
	int nrJucatoriTotal = 0;

	while (temp) {
		if (strcmp(temp->info.antrenor, numeAntrenor) == 0) {
			nrJucatoriTotal += temp->info.nrJucatori;
		}
		temp = temp->next;
	}
	if (nrJucatoriTotal == 0) {
		return 0;
	}
	else {
		return nrJucatoriTotal;
	}
}
//afiseaza nr de jucatorii ale celei mai scumpe echipe
void afiseazaNrJucatoriEchipaScumpa(NodLS* capLS) {
	if (capLS == NULL) {
		return;
	}
	NodLS* temp = capLS;
	float venitMax = temp->info.venit;
	EchipaFotbal* echipaScumpa = &temp->info;

	temp = temp->next;
	while (temp) {
		if (temp->info.venit > venitMax) {
			venitMax = temp->info.venit;
			echipaScumpa = &temp->info;
		}
		temp = temp->next;
	}
	printf("\nNumarul de jucatori ale celei mai scumpe echipe  este de %d si are un venit de %.2f", echipaScumpa->nrJucatori,
		echipaScumpa->venit);
}

//afiseaza nume echipa cea mai scumpa
void afisareNumeEchipaCeaMaiScumpa(NodLS* capLS) {
	if (capLS == NULL) {
		return;
	}
	NodLS* temp = capLS;
	float venitMax = temp->info.venit;
	EchipaFotbal* echipaScumpa = &temp->info;

	temp = temp->next;
	while (temp) {
		if (temp->info.venit > venitMax) {
			venitMax = temp->info.venit;
			echipaScumpa = &temp->info;
		}
		temp = temp->next;
	}
	printf("\nNumele celei mai scumpe echipe este %s si are un venit de %.2f", echipaScumpa->nume, echipaScumpa->venit);
}
//stergere echipa dupa nume antrenor
void stergereEchipaDupaAntrenor(NodLS** capLS, const char* numeAntrenor) {
	NodLS* temp = *capLS;
	NodLS* anterior = NULL;

	while (temp != NULL) {
		if (strcmp(temp->info.antrenor, numeAntrenor) == 0) {
			NodLS* deSters = temp;
			if (anterior == NULL) {
				*capLS = temp->next;
				temp = temp->next;
			}
			if (anterior != NULL) {
				anterior->next = temp->next;
				temp = temp->next;
			}
			free(deSters->info.nume);
			free(deSters->info.antrenor);
			free(deSters);
		}
		else {
			anterior = temp;
			temp = temp->next;
		}
	}
	printf("\nNodul a fost sters cu succes!\n");
}

//stergere echipa de fotbal cu cu cei mai multi jucatori
void stergereEchipaNrMareDeFotbalisti(NodLS** capLS) {
	NodLS* temp = *capLS;
	NodLS* anterior = NULL;
	int nrJucatoriMax = temp->info.nrJucatori;

	while (temp != NULL) {
		if (temp->info.nrJucatori > nrJucatoriMax) {
			nrJucatoriMax = temp->info.nrJucatori;
		}
		temp = temp->next;
	}

	temp = (*capLS);

	while (temp != NULL) {
		if (temp->info.nrJucatori == nrJucatoriMax) {
			NodLS* nodDeSters = temp;
			if (anterior == NULL) {
				*capLS = temp->next;
				temp = *capLS;
			}
			else {
				anterior->next = temp->next;
				temp = temp->next;
			}
			free(nodDeSters->info.nume);
			free(nodDeSters->info.antrenor);
			free(nodDeSters);
		}
		else {
			anterior = temp;
			temp = temp->next;
		}
	}
	printf("\nEchipa cu cei mai multi jucatori nu mai are voie sa joace!\n");
}

void main() {
	EchipaFotbal echipaFotbal;
	NodLS* capLS = NULL;
	char buffer[20];
	int nrJucatori;

	FILE* f = fopen("EchipeFotbal.txt", "r");
	fscanf(f, "%d", &nrJucatori);

	for (int i = 0; i < nrJucatori; i++) {
		fscanf(f, "%s", buffer);
		echipaFotbal.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(echipaFotbal.nume, buffer);

		fscanf(f, "%d", &echipaFotbal.nrJucatori);

		fscanf(f, "%f", &echipaFotbal.venit);

		fscanf(f, "%s", buffer);
		echipaFotbal.antrenor = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(echipaFotbal.antrenor, buffer);

		capLS = inserareNodLS(capLS, echipaFotbal);

		free(echipaFotbal.nume);
		free(echipaFotbal.antrenor);
	}
	fclose(f);

	traversareLS(capLS);

	printf("-------------------VECTOR----------------");
	EchipaFotbal* vectorEchipe = (EchipaFotbal*)malloc(nrJucatori * sizeof(EchipaFotbal));
	int nrElemente = 0;
	adaugareInVectorEchipeCuMultiJucatori(capLS, vectorEchipe, &nrElemente, 21);

	for (int i = 0; i < nrElemente; i++) {
		printf("\nNumele echipei: %s\nNumarul de jucatori: %d\nVenitul: %.2f\nAntrenor: %s\n\n",
			vectorEchipe[i].nume, vectorEchipe[i].nrJucatori, vectorEchipe[i].venit, vectorEchipe[i].antrenor);
	}
	for (int i = 0; i < nrElemente; i++) {
		free(vectorEchipe[i].nume);
		free(vectorEchipe[i].antrenor);
	}
	free(vectorEchipe);

	float medie = 0;
	medie = venitMediuEchipeDeFotbal(capLS);
	printf("Venitul mediu al echipelor este de: %.2f EURO.", medie);

	int nrJucPerAntrenor;
	nrJucPerAntrenor = numarJucatoriTotalPerAntrenor(capLS, "Sumudica");
	printf("\nAntrenorul dat are %d jucatori", nrJucPerAntrenor);

	afiseazaNrJucatoriEchipaScumpa(capLS);
	afisareNumeEchipaCeaMaiScumpa(capLS);

	stergereEchipaDupaAntrenor(&capLS, "Charalampous");
	traversareLS(capLS);

	stergereEchipaNrMareDeFotbalisti(&capLS);
	traversareLS(capLS);

	dezalocareNodLS(capLS);
}