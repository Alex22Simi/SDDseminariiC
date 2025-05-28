#include<stdio.h>
#include<malloc.h>

typedef struct Curs {
	unsigned int cod; // %u
	char* denumireDisciplina; //%s
	char* numeProfesor;
	char* dataSustinere;
	unsigned int nrCredite; // %u
} Curs;

typedef struct NodArb {
	int BF;
	Curs info;
	struct NodArb* stanga;
	struct NodArb* dreapta;
} NodArb;

NodArb* creareNodArb(Curs curs, NodArb* stanga, NodArb* dreapta) {
	NodArb* nou = (NodArb*)malloc(sizeof(NodArb));
	nou->info.cod = curs.cod;

	nou->info.denumireDisciplina = (char*)malloc((strlen(curs.denumireDisciplina) + 1) * sizeof(char));
	strcpy(nou->info.denumireDisciplina, curs.denumireDisciplina);

	nou->info.numeProfesor = (char*)malloc((strlen(curs.numeProfesor) + 1) * sizeof(char));
	strcpy(nou->info.numeProfesor, curs.numeProfesor);

	nou->info.dataSustinere = (char*)malloc((strlen(curs.dataSustinere) + 1) * sizeof(char));
	strcpy(nou->info.dataSustinere, curs.dataSustinere);

	nou->info.nrCredite = curs.nrCredite;

	nou->stanga = stanga;

	nou->dreapta = dreapta;
	return nou;
}

NodArb* inserareNodArb(NodArb* rad, Curs curs) {
	if (rad != NULL) {
		if (curs.cod < rad->info.cod) {
			rad->stanga = inserareNodArb(rad->stanga, curs);
			return rad;
		}
		else if (curs.cod > rad->info.cod) {
			rad->dreapta = inserareNodArb(rad->dreapta, curs);
			return rad;
		}
		else {
			return rad;
		}
	}
	else {
		return creareNodArb(curs, NULL, NULL);
	}
}

void afisarePreOrdine(NodArb* rad) {
	if (rad != NULL) {
		printf("Cod: %u, Denumire disciplina: %s, Profesor: %s, Data examen: %s, Credite: %u\n",
			rad->info.cod, rad->info.denumireDisciplina, rad->info.numeProfesor,
			rad->info.dataSustinere, rad->info.nrCredite);
		afisarePreOrdine(rad->stanga);
		afisarePreOrdine(rad->dreapta);
	}
}

void afisareInOrdine(NodArb* rad) {
	if (rad != NULL) {
		afisareInOrdine(rad->stanga);
		printf("Cod: %u, Denumire disciplina: %s, Profesor: %s, Data examen: %s, Credite: %u\n",
			rad->info.cod, rad->info.denumireDisciplina, rad->info.numeProfesor,
			rad->info.dataSustinere, rad->info.nrCredite);
		afisareInOrdine(rad->dreapta);
	}
}

void afisarePostOrdine(NodArb* rad) {
	if (rad != NULL) {
		afisarePostOrdine(rad->stanga);
		afisarePostOrdine(rad->dreapta);
		printf("Cod: %u, Denumire disciplina: %s, Profesor: %s, Data examen: %s, Credite: %u\n",
			rad->info.cod, rad->info.denumireDisciplina, rad->info.numeProfesor,
			rad->info.dataSustinere, rad->info.nrCredite);
	}
}

void dezalocareArb(NodArb* rad) {
	if (rad != NULL) {
		dezalocareArb(rad->stanga);
		dezalocareArb(rad->dreapta);
		printf("Dezaloc: Cod: %u, Denumire disciplina: %s, Profesor: %s, Data examen: %s, Credite: %u\n",
			rad->info.cod, rad->info.denumireDisciplina, rad->info.numeProfesor,
			rad->info.dataSustinere, rad->info.nrCredite);
		free(rad->info.denumireDisciplina);
		free(rad->info.numeProfesor);
		free(rad->info.dataSustinere);
		free(rad);
	}
}

//ex2.
//actualizare data sustinere curs al carui cod
//este dat ca param, noua data de sustinere tot in param este data
void actualizareData(NodArb* rad, unsigned int codParam, const char* dataParam) {
	if (rad != NULL) {
		if (rad->info.cod == codParam) {
			free(rad->info.dataSustinere);
			rad->info.dataSustinere = (char*)malloc((strlen(dataParam) + 1) * sizeof(char));
			strcpy(rad->info.dataSustinere, dataParam);

			printf("Cod: %u, Denumire disciplina: %s, Profesor: %s, Data examen: %s, Credite: %u\n",
				rad->info.cod, rad->info.denumireDisciplina, rad->info.numeProfesor,
				rad->info.dataSustinere, rad->info.nrCredite);
		}
		else if (codParam < rad->info.cod) {
			actualizareData(rad->stanga, codParam, dataParam);
		}
		else {
			actualizareData(rad->dreapta, codParam, dataParam);
		}
	}
}

//ex 3
//salvare in vector a codurilor care au data mai mare decat
//o data specificata in param
void getVector(NodArb* rad, unsigned int* vect, int* dimensiuneVect, const char* dataParam) {
	if (rad != NULL) {
		getVector(rad->stanga, vect, dimensiuneVect, dataParam);

		if (strcmp(rad->info.dataSustinere, dataParam) > 0) {
			vect[*dimensiuneVect] = rad->info.cod;
			(*dimensiuneVect)++;
		}
		getVector(rad->dreapta, vect, dimensiuneVect, dataParam);
	}
}

/*int maxim(int a, int b) {
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
	return nod2;
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
			if (rad->BF >= 2 && fiuDr->BF <= -1) {
				rad = rotatieDreaptaStanga(rad);
				calculBF(rad);
			}
			else {
				if (rad->BF <= -2 && fiuSt->BF >= 1) {
					rad = rotatieStangaDreapta(rad);
					calculBF(rad);
				}
			}
		}
	}
	return rad;
}*/

void main() {
	NodArb* rad = NULL;
	Curs curs;
	int nrCursuri;
	char buffer[50];

	FILE* f = fopen("cursuri.txt", "r");

	fscanf(f, "%d", &nrCursuri);

	for (int i = 0; i < nrCursuri; i++) {
		fscanf(f, "%u", &curs.cod);

		fscanf(f, "%s", buffer);
		curs.denumireDisciplina = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(curs.denumireDisciplina, buffer);

		fscanf(f, "%s", buffer);
		curs.numeProfesor = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(curs.numeProfesor, buffer);

		fscanf(f, "%s", buffer);
		curs.dataSustinere = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(curs.dataSustinere, buffer);

		fscanf(f, "%u", &curs.nrCredite);

		rad = inserareNodArb(rad, curs);

		free(curs.denumireDisciplina);
		free(curs.numeProfesor);
		free(curs.dataSustinere);

		//rad = reechilibrare(rad);
	}
	fclose(f);

	printf("----------------PREORDINE----------------\n");
	afisarePreOrdine(rad);
	printf("----------------INORDINE----------------\n");
	afisareInOrdine(rad);
	printf("----------------POSTORDINE----------------\n");
	afisarePostOrdine(rad);

	printf("----------------Ex. 2:----------------\n");
	actualizareData(rad, 5, "22.06.2025");
	printf("----------------PREORDINE - AFISARE DUPA MODIFICARE DATA----------------\n");
	afisarePreOrdine(rad);

	printf("----------------Ex. 3:----------------\n");
	unsigned int vect[100];
	int dimensiuneVect = 0;
	getVector(rad, vect, &dimensiuneVect, "11.06.2025");
	for (int i = 0; i < dimensiuneVect; i++) {
		printf("Cod: %u\n", vect[i]);
	}

	dezalocareArb(rad);
}