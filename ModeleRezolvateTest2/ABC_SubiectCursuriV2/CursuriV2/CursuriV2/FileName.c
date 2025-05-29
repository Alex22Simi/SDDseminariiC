#include<stdio.h>
#include<malloc.h>
 

typedef struct Curs {
	unsigned int cod;
	char* denumireDisciplina;
	char* numeProfesor;
	char* dataSustinere;
	unsigned int nrCredite;
} Curs;

typedef struct NodArb {
	Curs info;
	struct NodArb* stanga;
	struct NodArb* dreapta;
} NodArb;

NodArb* creareNod(Curs curs, NodArb* stanga, NodArb* dreapta) {
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

NodArb* inserareNod(NodArb* rad, Curs curs) {
	if (rad != NULL) {
		if (curs.cod < rad->info.cod) {
			rad->stanga = inserareNod(rad->stanga, curs);
			return rad;
		}
		else if (curs.cod > rad->info.cod) {
			rad->dreapta = inserareNod(rad->dreapta, curs);
			return rad;
		}
		else {
			return rad;
		}
	}

	else {
		return creareNod(curs, NULL, NULL);
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
		free(rad->info.denumireDisciplina);
		free(rad->info.numeProfesor);
		free(rad->info.dataSustinere);
	}
}

//ex2
//actualizare data pentru un curs al carui cod
//este dat in param, noua data este in param
void actualizeazaData(NodArb* rad, unsigned int codParam, const char* dataParam) {
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
			actualizeazaData(rad->stanga, codParam, dataParam);
		}
		else {
			actualizeazaData(rad->dreapta, codParam, dataParam);
		}
	}
}

//ex3
//salvare intr-un vector a codurilor
//care au data mai mare decat o data specificata in param
void getVect(NodArb* rad, unsigned int* vect, int* dimensiune, const char* dataParam) {
	if (rad != NULL) {
		getVect(rad->stanga, vect, dimensiune, dataParam);
		if (strcmp(rad->info.dataSustinere, dataParam) > 0) {
			vect[*dimensiune] = rad->info.cod;
			(*dimensiune)++;
		}
		getVect(rad->dreapta, vect, dimensiune, dataParam);
	}
}


void main() {
	NodArb* rad = NULL;
	Curs curs;
	int nrElem;
	char buffer[50];

	FILE* f = fopen("cursuri.txt", "r");
	fscanf(f, "%d", &nrElem);

	for (int i = 0; i < nrElem; i++) {
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

		rad = inserareNod(rad, curs);

		free(curs.denumireDisciplina);
		free(curs.numeProfesor);
		free(curs.dataSustinere);
	}
	fclose(f);

	printf("----------------PREORDINE----------------\n");
	afisarePreOrdine(rad);
	printf("----------------INORDINE----------------\n");
	afisareInOrdine(rad);
	printf("----------------POSTORDINE----------------\n");
	afisarePostOrdine(rad);

	printf("----------------Ex. 2:----------------\n");
	actualizeazaData(rad, 22, "22.02.2022");

	printf("----------------Ex. 3:----------------\n");
	unsigned int vect[100];
	int dimVect = 0;
	getVect(rad, vect, &dimVect, "15.06.2024");

	for (int i = 0; i < dimVect; i++) {
		printf("Cod: %u\n", vect[i]);
	}




	dezalocareArb(rad);
}