#include<stdio.h>
#include<malloc.h>

typedef struct CampionatFotbal {
	char* numeCampionat;
	int nrEchipe;
	float valoarePremiu;
} CampionatFotbal;

typedef struct NodLD {
	CampionatFotbal info;
	struct NodLD* next;
	struct NodLD* prev;
} NodLD;

NodLD* initializareNodLD(CampionatFotbal campionat) {
	NodLD* nodNou = (NodLD*)malloc(sizeof(NodLD));
	nodNou->info.numeCampionat = (char*)malloc((strlen(campionat.numeCampionat) + 1) * sizeof(char));
	strcpy(nodNou->info.numeCampionat, campionat.numeCampionat);
	nodNou->info.nrEchipe = campionat.nrEchipe;
	nodNou->info.valoarePremiu = campionat.valoarePremiu;
	nodNou->next = nodNou;
	nodNou->prev = nodNou;
	return nodNou;
}

NodLD* inserareNodLD(NodLD* capLD, NodLD** coadaLD, CampionatFotbal campionat) {
	NodLD* nodNou = initializareNodLD(campionat);
	if (capLD == NULL) {
		capLD = nodNou;
		(*coadaLD) = nodNou;
	}
	else {
		(*coadaLD)->next = nodNou;
		nodNou->prev = (*coadaLD);
		(*coadaLD) = nodNou;
		(*coadaLD)->next = capLD;
		capLD->prev = (*coadaLD);
	}
	return capLD;
}

void traversareInceputLD(NodLD* capLD) {
	NodLD* temp = capLD;
	while (temp->next != capLD) {
		printf("\nNume campionat: %s\nNumar de echipe: %d\nValoare premiu: %2.f\n\n",
			temp->info.numeCampionat, temp->info.nrEchipe, temp->info.valoarePremiu);
		temp = temp->next;
	}
	printf("\nNume campionat: %s\nNumar de echipe: %d\nValoare premiu: %2.f\n\n",
		temp->info.numeCampionat, temp->info.nrEchipe, temp->info.valoarePremiu);
}

void traversareInversaLD(NodLD* coadaLD) {
	NodLD* temp = coadaLD;
	while (temp->prev != coadaLD) {
		printf("\nNume campionat: %s\nNumar de echipe: %d\nValoare premiu: %.2f\n\n",
			temp->info.numeCampionat, temp->info.nrEchipe, temp->info.valoarePremiu);
		temp = temp->prev;
	}
	printf("\nNume campionat: %s\nNumar de echipe: %d\nValoare premiu: %.2f\n\n",
		temp->info.numeCampionat, temp->info.nrEchipe, temp->info.valoarePremiu);
}

void dezalocareLD(NodLD* capLD) {
	NodLD* temp = capLD;
	while (temp->next != capLD) {
		NodLD* aux = temp->next;
		free(temp->info.numeCampionat);
		free(temp);
		temp = aux;
	}
	free(temp->info.numeCampionat);
	free(temp);
}

void stergereCampionatDupaNume(NodLD** capLD, NodLD** coadaLD, const char* numeCampionat) {
	if (strcmp((*capLD)->info.numeCampionat, numeCampionat) == 0) {
		NodLD* temp = (*capLD);
		(*capLD) = (*capLD)->next;
		(*capLD)->prev = (*coadaLD);
		(*coadaLD)->next = (*capLD);
		free(temp->info.numeCampionat);
		free(temp);
		return;
	}
	else if (strcmp((*coadaLD)->info.numeCampionat, numeCampionat) == 0) {
		NodLD* temp = (*coadaLD);
		(*coadaLD) = (*coadaLD)->prev;
		(*coadaLD)->next = (*capLD);
		(*capLD)->prev = (*coadaLD);
		free(temp->info.numeCampionat);
		free(temp);
		return;
	}
	else {
		NodLD* temp = (*capLD);
		while (temp != NULL) {
			if (strcmp(temp->info.numeCampionat, numeCampionat) == 0) {
				NodLD* anterior = temp->prev;
				NodLD* urmator = temp->next;
				anterior->next = urmator;
				urmator->prev = anterior;
				free(temp->info.numeCampionat);
				free(temp);
				return;
			}
			temp = temp->next;
		}
	}

}

void main() {
	NodLD* capLD = NULL;
	NodLD* coadaLD = NULL;
	CampionatFotbal campionat;
	char buffer[20];
	int nrCampionate;

	FILE* f = fopen("CampionateFotbal.txt", "r");
	fscanf(f, "%d", &nrCampionate);
	for (int i = 0; i < nrCampionate; i++) {
		fscanf(f, "%s", buffer);
		campionat.numeCampionat = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(campionat.numeCampionat, buffer);

		fscanf(f, "%d", &campionat.nrEchipe);

		fscanf(f, "%f", &campionat.valoarePremiu);

		capLD = inserareNodLD(capLD, &coadaLD, campionat);
		free(campionat.numeCampionat);
	}
	printf("\n---------------------TRANSVERSARE INCEPUT-----------------\n");
	traversareInceputLD(capLD);

	printf("\n---------------------TRANSVERSARE SFARSIT-----------------\n");
	traversareInversaLD(coadaLD);

	printf("\n----------------STERGERE----------------\n");
	stergereCampionatDupaNume(&capLD, &coadaLD, "Bundesliga");
	traversareInceputLD(capLD);

	dezalocareLD(capLD);
}