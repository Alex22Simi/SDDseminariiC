#include<stdio.h>
#include<malloc.h>

typedef struct Proiect {
	unsigned int codProiect;//%u
	char* titluProiect;
	char* beneficiar;
	unsigned short int durataZile; //%hu
	float bugetAlocat;
} Proiect;

typedef struct NodArb {
	Proiect info;
	struct NodArb* stanga;
	struct NodArb* dreapta;
} NodArb;

NodArb* creareNod(Proiect proiect, NodArb* stanga, NodArb* dreapta) {
	NodArb* nou = (NodArb*)malloc(sizeof(NodArb));

	nou->info.codProiect = proiect.codProiect;

	nou->info.titluProiect = (char*)malloc((strlen(proiect.titluProiect) + 1) * sizeof(char));
	strcpy(nou->info.titluProiect, proiect.titluProiect);

	nou->info.beneficiar = (char*)malloc((strlen(proiect.beneficiar) + 1) * sizeof(char));
	strcpy(nou->info.beneficiar, proiect.beneficiar);

	nou->info.durataZile = proiect.durataZile;

	nou->info.bugetAlocat = proiect.bugetAlocat;

	nou->stanga = stanga;

	nou->dreapta = dreapta;
	return nou;
}

NodArb* inserareNod(NodArb* rad, Proiect proiect) {
	if (rad != NULL) {
		if (proiect.codProiect < rad->info.codProiect) {
			rad->stanga = inserareNod(rad->stanga, proiect);
			return rad;
		}
		else if (proiect.codProiect > rad->info.codProiect) {
			rad->dreapta = inserareNod(rad->dreapta, proiect);
			return rad;
		}
		else {
			return rad;
		}
	}
	else {
		return creareNod(proiect, NULL, NULL);
	}
}

void afisarePreOrdine(NodArb* rad) {
	if (rad != NULL) {
		printf("Cod: %u, Titlu: %s, Beneficiar: %s, Durata: %hu, Buget: %5.2f\n",
			rad->info.codProiect, rad->info.titluProiect, rad->info.beneficiar, rad->info.durataZile, rad->info.bugetAlocat);
		afisarePreOrdine(rad->stanga);
		afisarePreOrdine(rad->dreapta);
	}
}

void afisareInOrdine(NodArb* rad) {
	if (rad != NULL) {
		afisareInOrdine(rad->stanga);
		printf("Cod: %u, Titlu: %s, Beneficiar: %s, Durata: %hu, Buget: %5.2f\n",
			rad->info.codProiect, rad->info.titluProiect, rad->info.beneficiar, rad->info.durataZile, rad->info.bugetAlocat);
		afisareInOrdine(rad->dreapta);
	}
}

void afisarePostOrdine(NodArb* rad) {
	if (rad != NULL) {
		afisarePostOrdine(rad->stanga);
		afisarePostOrdine(rad->dreapta);
		printf("Cod: %u, Titlu: %s, Beneficiar: %s, Durata: %hu, Buget: %5.2f\n",
			rad->info.codProiect, rad->info.titluProiect, rad->info.beneficiar, rad->info.durataZile, rad->info.bugetAlocat);
	}
}

void dezalocareArb(NodArb* rad) {
	if (rad != NULL) {
		dezalocareArb(rad->stanga);
		dezalocareArb(rad->dreapta);
		free(rad->info.titluProiect);
		free(rad->info.beneficiar);
		free(rad);
	}
}

//ex 2
//det nr de proiecte care au acelasi beneficiar
//beneficiarul este dat ca param
int getNrProiectBeneficiar(NodArb* rad, const char* beneficiarParam) {
	if (rad == NULL) {
		return 0;
	}
	int contor = 0;
	if (strcmp(rad->info.beneficiar, beneficiarParam) == 0) {
		contor = 1;
	}
	contor +=  getNrProiectBeneficiar(rad->stanga, beneficiarParam);
	contor += getNrProiectBeneficiar(rad->dreapta, beneficiarParam);
	return contor;
}

//ex 3
//modifica bugetul unui proiect specificat
//prin cod proiect in parametrii
//noua val se determina pe baza unui procent/coeficient specificat
//in lista de param
//cautarea proiectului pe baza de cod 
void modificaPret(NodArb* rad, unsigned int codProiectParam, float procentParam) {
	if (rad != NULL) {
		if (rad->info.codProiect == codProiectParam) {
			rad->info.bugetAlocat *= procentParam;
			printf("Proiectul modificat:\n");
			printf("Cod: %u, Titlu: %s, Beneficiar: %s, Durata: %hu, Buget: %5.2f\n",
				rad->info.codProiect, rad->info.titluProiect, rad->info.beneficiar,
				rad->info.durataZile, rad->info.bugetAlocat);
			return;
		}

		if (codProiectParam < rad->info.codProiect) {
			modificaPret(rad->stanga, codProiectParam, procentParam);
		}
		else {
			modificaPret(rad->dreapta, codProiectParam, procentParam);
		}
		
	}
	
}
//ex 4
//det nr de noduri frunza 
int detNrNoduriFrunza(NodArb* rad) {
	if (rad == NULL) {
		return 0;
	}
	if (rad->stanga == NULL && rad->dreapta == NULL) {
		return 1;
	}
	return detNrNoduriFrunza(rad->stanga) + detNrNoduriFrunza(rad->dreapta);
}

//ex 5
//return vect proiecte cu durata mai mare decat o valoare data in param
void getVect(NodArb* rad, Proiect* vectProiecte, int* dimensiune, unsigned short int durataZileParam) {
	if (rad != NULL) {
		if (rad->info.durataZile > durataZileParam) {
			vectProiecte[*dimensiune].codProiect = rad->info.codProiect;

			vectProiecte[*dimensiune].titluProiect = (char*)malloc((strlen(rad->info.titluProiect) + 1) * sizeof(char));
			strcpy(vectProiecte[*dimensiune].titluProiect, rad->info.titluProiect);

			vectProiecte[*dimensiune].beneficiar = (char*)malloc((strlen(rad->info.beneficiar) + 1) * sizeof(char));
			strcpy(vectProiecte[*dimensiune].beneficiar, rad->info.beneficiar);

			vectProiecte[*dimensiune].durataZile = rad->info.durataZile;

			vectProiecte[*dimensiune].bugetAlocat = rad->info.bugetAlocat;

			(*dimensiune)++;
		}
		getVect(rad->stanga, vectProiecte, dimensiune, durataZileParam);
		getVect(rad->dreapta, vectProiecte, dimensiune, durataZileParam);
	}
}
	


void main() {
	NodArb* rad = NULL;
	Proiect proiect;
	char buffer[50];
	int nrProiecte;

	FILE* f = fopen("proiecte.txt", "r");
	fscanf(f, "%d", &nrProiecte);

	for (int i = 0; i < nrProiecte; i++) {
		fscanf(f, "%u", &proiect.codProiect);

		fscanf(f, "%s", buffer);
		proiect.titluProiect = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(proiect.titluProiect, buffer);

		fscanf(f, "%s", buffer);
		proiect.beneficiar = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(proiect.beneficiar, buffer);

		fscanf(f, "%hu", &proiect.durataZile);

		fscanf(f, "%f", &proiect.bugetAlocat);

		rad = inserareNod(rad, proiect);

		free(proiect.titluProiect);
		free(proiect.beneficiar);
	}
	fclose(f);

	printf("------------------------------PREORDINE-------------------------\n");
	afisarePreOrdine(rad);
	printf("------------------------------INORDINE-------------------------\n");
	afisareInOrdine(rad);
	printf("------------------------------POSTORDINE-------------------------\n");
	afisarePostOrdine(rad);

	printf("------------------------------Ex2: -------------------------\n");
	int nrProiecteBeneficiar = getNrProiectBeneficiar(rad, "Simionescu");
	printf("Numarul de proiecte al beneficiarului dat este: %d\n", nrProiecteBeneficiar);

	printf("------------------------------Ex3: -------------------------\n");
	modificaPret(rad, 22, 1.1);

	printf("------------------------------Ex4: -------------------------\n");
	int nrFrunze = 0;
	nrFrunze = detNrNoduriFrunza(rad);
	printf("Sunt: %d noduri frunza.\n", nrFrunze);

	printf("------------------------------Ex5: -------------------------\n");
	Proiect* vect;
	vect = (Proiect*)malloc(nrProiecte * sizeof(Proiect));
	int dimensiune = 0;
	getVect(rad, vect, &dimensiune, 200);
	printf("Proiectele cu durata mai mare de 200 zile:\n");
	for (int i = 0; i < dimensiune; i++) {
		printf("Cod: %u, Titlu: %s, Beneficiar: %s, Durata: %hu, Buget: %.2f\n",
			vect[i].codProiect,
			vect[i].titluProiect,
			vect[i].beneficiar,
			vect[i].durataZile,
			vect[i].bugetAlocat);
	}
	for (int i = 0; i < dimensiune; i++) {
		free(vect[i].titluProiect);
		free(vect[i].beneficiar);
	}
	free(vect);



	dezalocareArb(rad);
}