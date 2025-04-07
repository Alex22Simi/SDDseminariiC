/*#include<stdio.h>
#include<malloc.h>

typedef struct EchipaNationala {
	char* nume;
	int mondialeCastigate;
	int europeneCastigate;
} EchipaNationala;

typedef struct NodLD {
	EchipaNationala info;
	struct NodLD* next;
	struct NodLD* prev;
} NodLD;

NodLD* initializareNodLD(EchipaNationala echipa) {
	NodLD* nodNou = (NodLD*)malloc(sizeof(NodLD));
	nodNou->info.nume = (char*)malloc((strlen(echipa.nume) + 1) * sizeof(char));
	strcpy(nodNou->info.nume, echipa.nume);
	nodNou->info.mondialeCastigate = echipa.mondialeCastigate;
	nodNou->info.europeneCastigate = echipa.europeneCastigate;
	nodNou->next = nodNou;
	nodNou->prev = nodNou;
	return nodNou;
}

NodLD* inserareLD(NodLD* capLD,NodLD** coadaLD, EchipaNationala echipa) {
	NodLD* nodNou = initializareNodLD(echipa);
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

void transversareInceput(NodLD* capLD) {
	NodLD* temp = capLD;
	while (temp->next != capLD) {
		printf("\nNumele echipei: %s\nMondiale castigate: %d\nEuropene castigate: %d\n",
			temp->info.nume, temp->info.mondialeCastigate, temp->info.europeneCastigate);
		temp = temp->next;
	}
	printf("\nNumele echipei: %s\nMondiale castigate: %d\nEuropene castigate: %d\n",
		temp->info.nume, temp->info.mondialeCastigate, temp->info.europeneCastigate);
}

void transversareInversa(NodLD* coadaLD) {
	NodLD* temp = coadaLD;
	while (temp->prev != coadaLD) {
		printf("\nNumele echipei: %s\nMondiale castigate: %d\nEuropene castigate: %d\n",
			temp->info.nume, temp->info.mondialeCastigate, temp->info.europeneCastigate);
		temp = temp->prev;
	}
	printf("\nNumele echipei: %s\nMondiale castigate: %d\nEuropene castigate: %d\n",
		temp->info.nume, temp->info.mondialeCastigate, temp->info.europeneCastigate);
}

void dezalocareLD(NodLD* capLD) {
	NodLD* temp = capLD;
	while (temp-> next != capLD) {
		NodLD* aux = temp->next;
		free(temp->info.nume);
		free(temp);
		temp = aux;
	}
	free(temp->info.nume);
	free(temp);
}

//stergere echipa dupa Nume
void stergereEchipaDupaNume(NodLD** capLD, NodLD** coadaLD, const char* numeEchipa) {
	if (strcmp((*capLD)->info.nume, numeEchipa) == 0) {
		NodLD* temp = (*capLD);
		(*capLD) = (*capLD)->next;
		(*capLD)->prev = (*coadaLD);
		(*coadaLD)->next = (*capLD);
		free(temp->info.nume);
		free(temp);
		return;
	}
	else {
		if (strcmp((*coadaLD)->info.nume, numeEchipa) == 0) {
			NodLD* temp = (*coadaLD);
			(*coadaLD) = (*coadaLD)->prev;
			(*coadaLD)->next = (*capLD);
			(*capLD)->prev = (*coadaLD);
			free(temp->info.nume);
			free(temp);
			return;
		}
		else {
			NodLD* temp = *capLD;
			while (temp != NULL) {
				if (strcmp(temp->info.nume, numeEchipa) == 0) {
					NodLD* anterior = temp->prev;
					NodLD* urmator = temp->next;
					anterior->next = urmator;
					urmator->prev = anterior;
					free(temp->info.nume);
					free(temp);
					return;
				}
				else {
					temp = temp->next;
				}
			}
		}
	}
}


void main() {
	NodLD* capLD = NULL;
	NodLD* coadaLD = NULL;

	EchipaNationala echipa;
	int nrEchipe;
	char buffer[20];

	FILE* f = fopen("EchipeNationale.txt", "r");
	fscanf(f, "%d", &nrEchipe);
	for (int i = 0; i < nrEchipe; i++) {
		fscanf(f, "%s", buffer);
		echipa.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(echipa.nume, buffer);

		fscanf(f, "%d", &echipa.mondialeCastigate);

		fscanf(f, "%d", &echipa.europeneCastigate);


		capLD = inserareLD(capLD, &coadaLD, echipa);

		free(echipa.nume);
	}
	fclose(f);
	printf("\n-------------------TRANSVERSARE INCEPUT-------------\n");
	transversareInceput(capLD);

	printf("\n-------------------TRANSVERSARE SFARSIT-------------\n");
	transversareInversa(coadaLD);

	printf("\n-----------------STERGERE-------------\n");
	stergereEchipaDupaNume(&capLD, &coadaLD, "RomaniaU21");
	transversareInceput(capLD);

	dezalocareLD(capLD);
}*/


/*#include<stdio.h>
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
}*/

#include<stdio.h>
#include<malloc.h>

typedef struct CampionatMondial{
	char* numeNationala;
	int golaveraj;
	unsigned char grupa;
} CampionatMondial;

typedef struct NodLD {
	CampionatMondial info;
	struct NodLD* next;
	struct NodLD* prev;
} NodLD;

NodLD* initializareNodLD(CampionatMondial campionat) {
	NodLD* nodNou = (NodLD*)malloc((sizeof(NodLD)));
	nodNou->info.numeNationala = (char*)malloc((strlen(campionat.numeNationala) + 1) * sizeof(char));
	strcpy(nodNou->info.numeNationala, campionat.numeNationala);
	nodNou->info.golaveraj = campionat.golaveraj;
	nodNou->info.grupa = campionat.grupa;
	nodNou->next = nodNou;
	nodNou->prev = nodNou;
	return nodNou;
}

NodLD* inserareNodLD(NodLD* capLD, NodLD** coadaLD, CampionatMondial campionat) {
	NodLD* nodNou = initializareNodLD(campionat);
	if (capLD == NULL) {
		capLD = nodNou;
		(*coadaLD = nodNou);
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

void transversareInceput(NodLD* capLD) {
	NodLD* temp = capLD;
	while (temp->next != capLD) {
		printf("\nNumele nationalei: %s\nGolaveraj: %d\nGrupa: %c\n\n",
			temp->info.numeNationala, temp->info.golaveraj, temp->info.grupa);
		temp = temp->next;
	}
	printf("\nNumele nationalei: %s\nGolaveraj: %d\nGrupa: %c\n\n",
		temp->info.numeNationala, temp->info.golaveraj, temp->info.grupa);
}

void transversareFinal(NodLD* coadaLD) {
	NodLD* temp = coadaLD;
	while (temp->prev != coadaLD) {
		printf("\nNumele nationalei: %s\nGolaveraj: %d\nGrupa: %c\n\n",
			temp->info.numeNationala, temp->info.golaveraj, temp->info.grupa);
		temp = temp->prev;
	}
	printf("\nNumele nationalei: %s\nGolaveraj: %d\nGrupa: %c\n\n",
		temp->info.numeNationala, temp->info.golaveraj, temp->info.grupa);
}

void dezalocareLD(NodLD* capLD) {
	NodLD* temp = capLD;
	while (temp->next != capLD) {
		NodLD* aux = temp->next;
		free(temp->info.numeNationala);
		free(temp);
		temp = aux;
	}
	free(temp->info.numeNationala);
	free(temp);
}

void stergereEchipaDupaNume(NodLD** capLD, NodLD** coadaLD, const char* numeEchipa) {
	if (strcmp((*capLD)->info.numeNationala, numeEchipa) == 0) {
		NodLD* temp = (*capLD);
		(*capLD) = (*capLD)->next;
		(*capLD)->prev = (*coadaLD);
		(*coadaLD)->next = (*capLD);
		free(temp->info.numeNationala);
		free(temp);
		return;
	}
	else if (strcmp((*coadaLD)->info.numeNationala, numeEchipa) == 0) {
		NodLD* temp = (*coadaLD);
		(*coadaLD) = (*coadaLD)->prev;
		(*coadaLD)->next = (*capLD);
		(*capLD)->prev = (*coadaLD);
		free(temp->info.numeNationala);
		free(temp);
		return;
	}
	else {
		NodLD* temp = (*capLD);
		while (temp != NULL) {
			if (strcmp(temp->info.numeNationala, numeEchipa) == 0) {
				NodLD* anterior = temp->prev;
				NodLD* urmator = temp->next;
				anterior->next = urmator;
				urmator->prev = anterior;
				free(temp->info.numeNationala);
				free(temp);
				return;
			}
			else {
				temp = temp->next;
			}
		}
	}

}

void main() {
	NodLD* capLD = NULL;
	NodLD* coadaLD = NULL;
	CampionatMondial campionat;
	int nrEchipe;
	char buffer[20];

	FILE* f = fopen("CampionatMondial.txt", "r");
	fscanf(f, "%d", &nrEchipe);
	for (int i = 0; i < nrEchipe; i++) {
		fscanf(f, "%s", buffer);
		campionat.numeNationala = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(campionat.numeNationala, buffer);

		fscanf(f, "%d", &campionat.golaveraj);

		fscanf(f, " %c", &campionat.grupa);

		capLD = inserareNodLD(capLD, &coadaLD, campionat);
		free(campionat.numeNationala);
	}
	fclose(f);

	printf("\n-----------------------TRANSVERSARE DE LA INCEPUT------------------------\n");
	transversareInceput(capLD);

	printf("\n-----------------------TRANSVERSARE DE LA FINAL------------------------\n");
	transversareFinal(coadaLD);

	printf("\n-------------------STERGERE-------------\n");
	stergereEchipaDupaNume(&capLD, &coadaLD, "Romania");
	transversareInceput(capLD);

	dezalocareLD(capLD);
}