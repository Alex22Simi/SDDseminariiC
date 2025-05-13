#include<stdio.h>
#include<malloc.h>

typedef struct Fotografie {
	unsigned int idFotografie;
	char* orasulLocatie;
	char* dataRealizarii;
	float rezolutie;
} Fotografie;

typedef struct NodArb {
	Fotografie info;
	struct NodArb* stanga;
	struct NodArb* dreapta;
} NodArb;

NodArb* creareNod(Fotografie fotografie, NodArb* stanga, NodArb* dreapta) {
	NodArb* nou = (NodArb*)malloc(sizeof(NodArb));
	nou->info.idFotografie = fotografie.idFotografie;
	nou->info.orasulLocatie = (char*)malloc((strlen(fotografie.orasulLocatie) + 1) * sizeof(char));
	strcpy(nou->info.orasulLocatie, fotografie.orasulLocatie);
	nou->info.dataRealizarii = (char*)malloc((strlen(fotografie.dataRealizarii) + 1) * sizeof(char));
	strcpy(nou->info.dataRealizarii, fotografie.dataRealizarii);
	nou->info.rezolutie = fotografie.rezolutie;
	nou->stanga = stanga;
	nou->dreapta = dreapta;
	return nou;
}

NodArb* inserareNod(NodArb* rad, Fotografie fotografie) {
	if (rad != NULL) {
		if (fotografie.idFotografie < rad->info.idFotografie) {
			rad->stanga = inserareNod(rad->stanga, fotografie);
			return rad;
		}
		else if (fotografie.idFotografie > rad->info.idFotografie) {
			rad->dreapta = inserareNod(rad->dreapta, fotografie);
			return rad;
		}
		else {
			return rad;
		}
	}
	else {
		return creareNod(fotografie, NULL, NULL);
	}
}

//radacina stanga dreapta
void afisarePreOrdine(NodArb* rad) {
	if (rad != NULL) {
		printf("Id: %d, Oras: %s, Data: %s, Rezolutie: %5.2f\n",
			rad->info.idFotografie, rad->info.orasulLocatie, rad->info.dataRealizarii, rad->info.rezolutie);
		afisarePreOrdine(rad->stanga);
		afisarePreOrdine(rad->dreapta);
	}
}

//stanga dreapta radacina
void afisareInOrdine(NodArb* rad) {
	if (rad != NULL) {
		afisareInOrdine(rad->stanga);
		printf("Id: %d, Oras: %s, Data: %s, Rezolutie: %5.2f\n",
			rad->info.idFotografie, rad->info.orasulLocatie, rad->info.dataRealizarii, rad->info.rezolutie);
		afisareInOrdine(rad->dreapta);
	}
}

//stanga dreapta radacina
void afisarePostOrdine(NodArb* rad) {
	if (rad != NULL) {
		afisarePostOrdine(rad->stanga);
		afisarePostOrdine(rad->dreapta);
		printf("Id: %d, Oras: %s, Data: %s, Rezolutie: %5.2f\n",
			rad->info.idFotografie, rad->info.orasulLocatie, rad->info.dataRealizarii, rad->info.rezolutie);
	}
}

void dezalocareArb(NodArb* rad) {
	if (rad != NULL) {
		dezalocareArb(rad->stanga);
		dezalocareArb(rad->dreapta);
		free(rad->info.orasulLocatie);
		free(rad->info.dataRealizarii);
		free(rad);
	}
}

//ex2 -> det nr de foto realizate in acelasi oras
//numele orasului se da ca param
/*int afisareNrFoto(NodArb* rad, const char* orasParam) {
	int nrFoto = 1;
	if (rad != NULL) {
		if (strcmp(rad->info.orasulLocatie, orasParam) == 0) {
			nrFoto++;
		}
		else {
			nrFoto = 0;
		}
		afisareNrFoto(rad->stanga, orasParam);
		afisareNrFoto(rad->dreapta, orasParam);
	}
	return nrFoto;
}*/

int afisareNrFoto(NodArb* rad, const char* orasParam) {
	if (rad == NULL) {
		return 0;
	}
	int nrFoto = 0;
		if (strcmp(rad->info.orasulLocatie, orasParam) == 0) {
			nrFoto = 1;
		}
		return nrFoto + afisareNrFoto(rad->stanga, orasParam) + afisareNrFoto(rad->dreapta, orasParam);
}

//ex3-> functia care modifica data realizarii unei foto
//data prin id in lista de parametrii
//nou data este  specificata in lista de parametrii
//afisare in ordine
void modificaData(NodArb* rad, unsigned int idParam, const char* nouaData) {
	if (rad != NULL) {
		if (rad->info.idFotografie == idParam) {
			free(rad->info.dataRealizarii);

			rad->info.dataRealizarii = (char*)malloc((strlen(nouaData) + 1) * sizeof(char));
			strcpy(rad->info.dataRealizarii, nouaData);
			return;
		}
		modificaData(rad->stanga, idParam, nouaData);
		modificaData(rad->dreapta, idParam, nouaData);
	}
}

//ex4 -> stergere nod radacina
//traversare in ordine a struturii
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
	else {
		if (aux->stanga != NULL) {
			rad = aux->stanga;
		}
		else {
			rad = NULL;
		}
	}
	free(aux->info.orasulLocatie);
	free(aux->info.dataRealizarii);
	free(aux);
	return rad;
}

//ex 5
//returneaza un vector de foto care au o rezolutie
//primita ca param de intrare al functiei
//datele sunt preluate din strutura arborescenta si nu sunt 
//partajate zone de memorie heap intre cele doua structuri (arbore si vector)
int numaraFotoCuRez(NodArb* rad, float rezolutieCautata) {
	if (rad == NULL) {
		return 0;
	}
	int nrFoto = 0;
	if (rad->info.rezolutie == rezolutieCautata) {
		nrFoto = 1;
	}
	return nrFoto + numaraFotoCuRez(rad->stanga, rezolutieCautata) + numaraFotoCuRez(rad->dreapta, rezolutieCautata);
}

void addFotoInVector(NodArb* rad, float rezolutieCautata, Fotografie* vector, int* index) { 
		if (rad != NULL) {
			if (rad->info.rezolutie == rezolutieCautata) {
				vector[*index].idFotografie = rad->info.idFotografie;

				vector[*index].orasulLocatie = (char*)malloc((strlen(rad->info.orasulLocatie) + 1) * sizeof(char));
				strcpy(vector[*index].orasulLocatie, rad->info.orasulLocatie);

				vector[*index].dataRealizarii = (char*)malloc((strlen(rad->info.dataRealizarii) + 1) * sizeof(char));
				strcpy(vector[*index].dataRealizarii, rad->info.dataRealizarii);

				vector[*index].rezolutie = rad->info.rezolutie;
				(*index)++;
			}
			addFotoInVector(rad->stanga, rezolutieCautata, vector, index);
			addFotoInVector(rad->dreapta, rezolutieCautata, vector, index);
		}
}

void afisareVector(Fotografie* vector, int dim) {
	for (int i = 0; i < dim; i++) {
		printf("Id: %d, Oras: %s, Data: %s, Rezolutie: %5.2f\n",
			vector[i].idFotografie,
			vector[i].orasulLocatie,
			vector[i].dataRealizarii,
			vector[i].rezolutie);
	}
}

void dezalocareVector(Fotografie* vector, int dim) {
	for (int i = 0; i < dim; i++) {
		free(vector[i].orasulLocatie);
		free(vector[i].dataRealizarii);
	}
	free(vector);
}


void main() {
	NodArb* rad = NULL;
	Fotografie fotografie;
	int nrFotografii;
	char buffer[50];

	FILE* f = fopen("fotografii.txt", "r");
	fscanf(f, "%d", &nrFotografii);

	for (int i = 0; i < nrFotografii; i++) {
		fscanf(f, "%d", &fotografie.idFotografie);
		fscanf(f, "%s", buffer);
		fotografie.orasulLocatie = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(fotografie.orasulLocatie, buffer);
		fscanf(f, "%s", buffer);
		fotografie.dataRealizarii = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(fotografie.dataRealizarii, buffer);
		fscanf(f, "%f", &fotografie.rezolutie);

		rad = inserareNod(rad, fotografie);

		free(fotografie.orasulLocatie);
		free(fotografie.dataRealizarii);
	}
	fclose(f);

	printf("----------------PREORDINE----------------\n");
	afisarePreOrdine(rad);
	printf("----------------INORDINE----------------\n");
	afisareInOrdine(rad);
	printf("----------------POSTORDINE----------------\n");
	afisarePostOrdine(rad);

	printf("----------------CERINTA 2:----------------\n");
	int foto = afisareNrFoto(rad, "Calimanesti");
	printf("Numarul total de foto din orasul dat ca parametru este %d.\n", foto);


	printf("----------------CERINTA 3:----------------\n");
	modificaData(rad, 22, "02.02.2002");
	afisareInOrdine(rad);

	printf("----------------CERINTA 4:----------------\n");
	rad = stergereRad(rad);
	afisareInOrdine(rad);

	printf("----------------CERINTA 5:----------------\n");
	float rezolutieCautata = 188.2;
	int fotoCuRez = numaraFotoCuRez(rad, rezolutieCautata);

	if (fotoCuRez > 0) {
		Fotografie* vect = (Fotografie*)malloc(fotoCuRez * sizeof(Fotografie));
		int index = 0;

		addFotoInVector(rad, rezolutieCautata, vect, &index);
		afisareVector(vect, fotoCuRez);
		dezalocareVector(vect, fotoCuRez);
	}
	else {
		printf("Nu exista fotografii cu rezolutia cautat: %5.2f", rezolutieCautata);
	}


	dezalocareArb(rad);
}