#include<stdio.h>
#include<malloc.h>
typedef struct CursaFeroviara {
	unsigned int nrCursa;//%u
	char* dataCursa;
	unsigned char nrDeVagoane;//%hhu
	unsigned short int clasaBilete[2]; // [0] -> nr bilete clasa 1, [1] -> nr bilete clasa 2 %hu
	float preturi[2]; //pret bilete: [0] = pret pt clasa 1, [1] = pret pt clasa 2 %hu
} CursaFeroviara;

typedef struct NodArb {
	int BF;
	CursaFeroviara info;
	struct NodArb* stanga;
	struct NodArb* dreapta;
} NodArb;

NodArb* creareNod(CursaFeroviara cursa, NodArb* stanga, NodArb* dreapta) {
	NodArb* nou = (NodArb*)malloc(sizeof(NodArb));
	nou->info.nrCursa = cursa.nrCursa;

	nou->info.dataCursa = (char*)malloc((strlen(cursa.dataCursa) + 1) * sizeof(char));
	strcpy(nou->info.dataCursa, cursa.dataCursa);

	nou->info.nrDeVagoane = cursa.nrDeVagoane;

	nou->info.clasaBilete[0] = cursa.clasaBilete[0];
	nou->info.clasaBilete[1] = cursa.clasaBilete[1];

	nou->info.preturi[0] = cursa.preturi[0];
	nou->info.preturi[1] = cursa.preturi[1];

	nou->stanga = stanga;
	nou->dreapta = dreapta;
	return nou;
}

NodArb* inserareNod(NodArb* rad, CursaFeroviara cursa) {
	if (rad != NULL) {
		if (cursa.nrCursa < rad->info.nrCursa) {
			rad->stanga = inserareNod(rad->stanga, cursa);
			return rad;
		}
		else {
			if (cursa.nrCursa > rad->info.nrCursa) {
				rad->dreapta = inserareNod(rad->dreapta, cursa);
				return rad;
			}
			else {
				return rad;
			}
		}
	}
	else {
		return creareNod(cursa, NULL, NULL);
	}
}

void afisarePreOrdine(NodArb* rad) {
	if (rad != NULL) {
		printf(" Nr cursa: %u\n Data cursa: %s\n Nr. de vagoane: %hhu\n Nr. de bilete la clasa 1: %hu\n Nr. de bilete la clasa 2: %hu\n Pret bilet clasa 1: %5.2f\n Pret bilet clasa 2: %5.2f\n\n",
			rad->info.nrCursa, rad->info.dataCursa, rad->info.nrDeVagoane, rad->info.clasaBilete[0], 
			rad->info.clasaBilete[1], rad->info.preturi[0], rad->info.preturi[1]);
		afisarePreOrdine(rad->stanga);
		afisarePreOrdine(rad->dreapta);
	}
}

void afisareInOrdine(NodArb* rad) {
	if (rad != NULL) {
		afisareInOrdine(rad->stanga);
		printf(" Nr cursa: %u\n Data cursa: %s\n Nr. de vagoane: %hhu\n Nr. de bilete la clasa 1: %hu\n Nr. de bilete la clasa 2: %hu\n Pret bilet clasa 1: %5.2f\n Pret bilet clasa 2: %5.2f\n\n",
			rad->info.nrCursa, rad->info.dataCursa, rad->info.nrDeVagoane, rad->info.clasaBilete[0],
			rad->info.clasaBilete[1], rad->info.preturi[0], rad->info.preturi[1]);
		afisareInOrdine(rad->dreapta);
	}
}

void afisarePostOrdine(NodArb* rad) {
	if (rad != NULL) {
		afisarePostOrdine(rad->stanga);
		afisarePostOrdine(rad->dreapta);
		printf(" Nr cursa: %u\n Data cursa: %s\n Nr. de vagoane: %hhu\n Nr. de bilete la clasa 1: %hu\n Nr. de bilete la clasa 2: %hu\n Pret bilet clasa 1: %5.2f\n Pret bilet clasa 2: %5.2f\n\n",
			rad->info.nrCursa, rad->info.dataCursa, rad->info.nrDeVagoane, rad->info.clasaBilete[0],
			rad->info.clasaBilete[1], rad->info.preturi[0], rad->info.preturi[1]);
	}
}

void dezalocareArb(NodArb* rad) {
	if (rad != NULL) {
		dezalocareArb(rad->stanga);
		dezalocareArb(rad->dreapta);
		free(rad->info.dataCursa);
		free(rad);
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

void calculeazaBF(NodArb* rad) {
	if (rad != NULL) {
		rad->BF = inaltimeArb(rad->dreapta) - inaltimeArb(rad->stanga);
		calculeazaBF(rad->stanga);
		calculeazaBF(rad->dreapta);
	}
}

NodArb* rotireDreapta(NodArb* rad) {
	printf("Rotatie dreapta\n");
	NodArb* nod1 = rad->stanga;
	rad->stanga = nod1->dreapta;
	nod1->dreapta = rad;
	rad = nod1;
	return rad;
}

NodArb* rotireStanga(NodArb* rad) {
	printf("Rotatie stanga\n");
	NodArb* nod1 = rad->dreapta;
	rad->dreapta = nod1->stanga;
	nod1->stanga = rad;
	rad = nod1;
	return rad;
}

NodArb* rotireStangaDreapta(NodArb* rad) {
	printf("Rotatie stanga-dreapta\n");
	NodArb* nod1 = rad->stanga;
	NodArb* nod2 = nod1->dreapta;
	nod1->dreapta = nod2->stanga;
	nod2->stanga = nod1;
	rad->stanga = nod2->dreapta;
	nod2->dreapta = rad;
	rad = nod2;
	return rad;
}

NodArb* rotireDreaptaStanga(NodArb* rad) {
	printf("Rotatie dreapta-stanga\n");
	NodArb* nod1 = rad->dreapta;
	NodArb* nod2 = nod1->stanga;
	nod1->stanga = nod2->dreapta;
	nod2->dreapta = nod1;
	rad->dreapta = nod2->stanga;
	nod2->stanga = rad;
	rad = nod2;
	return rad;
}

NodArb* reechilibreaza(NodArb* rad) {
	calculeazaBF(rad);
	NodArb* fiuSt = rad->stanga;
	NodArb* fiuDr = rad->dreapta;

	if (rad->BF <= -2 && fiuSt->BF <= -1) {
		rad = rotireDreapta(rad);
		calculeazaBF(rad);
	}
	else {
		if (rad->BF >= 2 && fiuDr->BF >= -1) {
			rad = rotireStanga(rad);
			calculeazaBF(rad);
		}
		else {
			if (rad->BF <= -2 && fiuSt->BF >= 1) {
				rad = rotireStangaDreapta(rad);
				calculeazaBF(rad);
			}
			else {
				if (rad->BF >= 2 && fiuDr->BF <= -1) {
					rad = rotireDreaptaStanga(rad);
					calculeazaBF(rad);
				}
			}
		}
	}
	return rad;
}*/

//Ex. 2
//nr de bilete cumparate la clasa a2 a 
 int getNrBileteClasa2(NodArb* rad) {
	int contor = 0;
	if (rad == NULL) {
		return 0;
	}
	contor += rad->info.clasaBilete[1];
	contor += getNrBileteClasa2(rad->stanga);
	contor += getNrBileteClasa2(rad->dreapta);
	
	return contor;
}

 //Ex. 3
 //modifica pretul biletelor la clasa 1 
 //pentru cursele feroviare programate la o anumita
 //data, data cursei si procentul de modificare a pretului se vor
 //afisa in lista de param
 //afisare in inordine
void modificaPretBiletClasa1(NodArb* rad, const char* dataParam, float procentModificarePret) {
	 if (rad != NULL) {
		 modificaPretBiletClasa1(rad->stanga, dataParam, procentModificarePret);
		 if (strcmp(rad->info.dataCursa, dataParam) == 0) {
			 rad->info.preturi[0] *= procentModificarePret;
		 }
		modificaPretBiletClasa1(rad->dreapta, dataParam, procentModificarePret);
	 }
 }

//Ex4. 
//returnare cursa feroviara cu incasari maxime
//in cazul in care doua curse au acelasi nr max de incasari
//functia intoarce o singura cursa, la alegere
void getCursaFerIncasariMaxime(NodArb* rad, CursaFeroviara* cursaMax, float* incasariMax) {
	if (rad != NULL) {
		float incasari = rad->info.clasaBilete[0] * rad->info.preturi[0] +
			rad->info.clasaBilete[1] * rad->info.preturi[1];

		if (incasari > *incasariMax) {
			*incasariMax = incasari;
			*cursaMax = rad->info;
		}
		getCursaFerIncasariMaxime(rad->stanga, cursaMax, incasariMax);
		getCursaFerIncasariMaxime(rad->dreapta, cursaMax, incasariMax);
	}
}

//ex. 5
//return vector cu nr curselor feroviare stocate in nodurile 
//frunza
/*void getFrunza(NodArb* rad, unsigned int** vect, int* dimensiuneVect) {
	if (rad != NULL) {
		if (rad->stanga == NULL && rad->dreapta == NULL) {
			*vect = (unsigned int*)malloc(*dimensiuneVect * sizeof(unsigned int));
			(*vect)[*dimensiuneVect] = rad->info.nrCursa;
			(*dimensiuneVect)++;
		}
		getFrunza(rad->stanga, vect, dimensiuneVect);
		getFrunza(rad->dreapta, vect, dimensiuneVect);
	}
}*/
int numaraFrunze(NodArb* rad) {
	if (rad == NULL) {
		return 0;
	}
	if (rad->stanga == NULL && rad->dreapta == NULL) {
		return 1;
	}
	return numaraFrunze(rad->stanga) + numaraFrunze(rad->dreapta);
}

void getFrunze(NodArb* rad, unsigned int* vect, int* index) {
	if (rad != NULL) {
		if (rad->stanga == NULL && rad->dreapta == NULL) {
			vect[*index] = rad->info.nrCursa;
			(*index)++;
		}
		getFrunze(rad->stanga, vect, index);
		getFrunze(rad->dreapta, vect, index);
	}
}



void main() {
	NodArb* rad = NULL;
	CursaFeroviara cursa;
	int nrCurse;
	char buffer[50];
	FILE* f = fopen("curse.txt", "r");

	fscanf(f, "%d", &nrCurse);
	for (int i = 0; i < nrCurse; i++) {
		fscanf(f, "%u", &cursa.nrCursa);

		fscanf(f, "%s", buffer);
		cursa.dataCursa = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(cursa.dataCursa, buffer);

		fscanf(f, "%hhu", &cursa.nrDeVagoane);

		fscanf(f, "%hu", &cursa.clasaBilete[0]);
		fscanf(f, "%hu", &cursa.clasaBilete[1]);

		fscanf(f, "%f", &cursa.preturi[0]);
		fscanf(f, "%f", &cursa.preturi[1]);

		rad = inserareNod(rad, cursa);
		//free(cursa.dataCursa);

		//rad = reechilibreaza(rad);
	}
	fclose(f);

	printf("------------------------------PREORDINE-------------------------\n");
	afisarePreOrdine(rad);
	printf("------------------------------INORDINE-------------------------\n");
	afisareInOrdine(rad);
	printf("------------------------------POSTORDINE-------------------------\n");
	afisarePostOrdine(rad);

	printf("------------------------------Nr. 2:-------------------------\n");
	int nrBilete2 = getNrBileteClasa2(rad);
	printf("Nr bilete clasa 2: %d\n", nrBilete2);

	printf("------------------------------Nr. 3:-------------------------\n");
	modificaPretBiletClasa1(rad, "09.09.2019", 1.1);
	afisareInOrdine(rad);

	printf("------------------------------Nr. 4:-------------------------\n");
	CursaFeroviara cursaMax;
	float incasariMax = 0;
	getCursaFerIncasariMaxime(rad, &cursaMax, &incasariMax);
	printf("Cursa cu incasari maxime %5.2f:\n", incasariMax);
	printf(" Nr cursa: %u\n Data cursa: %s\n Nr. de vagoane: %hhu\n Nr. de bilete la clasa 1: %hu\n Nr. de bilete la clasa 2: %hu\n Pret bilet clasa 1: %5.2f\n Pret bilet clasa 2: %5.2f\n\n",
		cursaMax.nrCursa, cursaMax.dataCursa, cursaMax.nrDeVagoane,
		cursaMax.clasaBilete[0], cursaMax.clasaBilete[1],
		cursaMax.preturi[0], cursaMax.preturi[1]);


	printf("------------------------------Nr. 5:-------------------------\n");
	int nrFrunze = numaraFrunze(rad);
	unsigned int* frunze = (unsigned int*)malloc(nrFrunze * sizeof(unsigned int));

	int index = 0;
	getFrunze(rad, frunze, &index);

	printf("Numerele curselor din noduri frunza sunt: ");
	for (int i = 0; i < nrFrunze; i++) {
		printf("%u ", frunze[i]);
	}
	printf("\n");

	free(frunze);

	dezalocareArb(rad);
}