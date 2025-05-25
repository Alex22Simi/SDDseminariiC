/*#include<stdio.h>
#include<malloc.h>

typedef struct Data {
	int zi;
	int luna;
	int an;
} Data;

typedef struct Zbor {
	int cod;
	char* companie;
	float pret;
	Data dataZbor;
} Zbor;

typedef struct NodArb {
	int BF;
	Zbor info;
	struct NodArb* stanga;
	struct NodArb* dreapta;
} NodArb;

NodArb* creareNod(Zbor zbor, NodArb* stanga, NodArb* dreapta) {
	NodArb* nou = (NodArb*)malloc(sizeof(NodArb));
	nou->info.cod = zbor.cod;
	nou->info.companie = (char*)malloc((strlen(zbor.companie) + 1) * sizeof(char));
	strcpy(nou->info.companie, zbor.companie);
	nou->info.pret = zbor.pret;
	nou->info.dataZbor.zi = zbor.dataZbor.zi;
	nou->info.dataZbor.luna = zbor.dataZbor.luna;
	nou->info.dataZbor.an = zbor.dataZbor.an;
	nou->stanga = stanga;
	nou->dreapta = dreapta;
	return nou;
}

NodArb* inserareNod(NodArb* rad, Zbor zbor) {
	if (rad != NULL) {
		if (zbor.cod < rad->info.cod) {
			rad->stanga = inserareNod(rad->stanga, zbor);
			return rad;
		}
		else if (zbor.cod > rad->info.cod) {
			rad->dreapta = inserareNod(rad->dreapta, zbor);
			return rad;
		}
		else {
			return rad;
		}
	}
	else {
		return creareNod(zbor, NULL, NULL);
	}
}

//RSD
void preordine(NodArb* rad)
{
	if (rad != NULL)
	{
		printf("\nCod=%d, Companie=%s, Pret=%5.2f, Data=%d/%d/%d",
			rad->info.cod, rad->info.companie, rad->info.pret,
			rad->info.dataZbor.zi, rad->info.dataZbor.luna, rad->info.dataZbor.an);
		preordine(rad->stanga);
		preordine(rad->dreapta);
	}
}

//SRD
void inordine(NodArb* rad)
{
	if (rad != NULL)
	{
		inordine(rad->stanga);
		printf("\nCod=%d, Companie=%s, Pret=%5.2f, Data=%d/%d/%d",
			rad->info.cod, rad->info.companie, rad->info.pret,
			rad->info.dataZbor.zi, rad->info.dataZbor.luna, rad->info.dataZbor.an);
		inordine(rad->dreapta);
	}
}

//SDR
void postordine(NodArb* rad)
{
	if (rad != NULL)
	{
		postordine(rad->stanga);
		postordine(rad->dreapta);
		printf("\nCod=%d, Companie=%s, Pret=%5.2f, Data=%d/%d/%d",
			rad->info.cod, rad->info.companie, rad->info.pret,
			rad->info.dataZbor.zi, rad->info.dataZbor.luna, rad->info.dataZbor.an);
	}
}

void dezalocare(NodArb* rad) {
	if (rad != NULL) {
		dezalocare(rad->stanga);
		dezalocare(rad->dreapta);
		free(rad->info.companie);
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
	else
	{
		return 0;
	}
}

int calculBF(NodArb* rad) {
	if (rad != NULL) {
		rad->BF = inaltimeArb(rad->dreapta) - inaltimeArb(rad->stanga);
		calculBF(rad->stanga);
		calculBF(rad->dreapta);
	}
}

NodArb* rotatieDreapta(NodArb* rad) {
	printf("Rotatie dreapta\n");
	NodArb* nod1 = rad->stanga;
	rad->stanga = nod1->dreapta;
	nod1->dreapta = rad;
	rad = nod1;
	return rad;
}

NodArb* rotatieStanga(NodArb* rad) {
	printf("Rotatie stanga\n");
	NodArb* nod1 = rad->dreapta;
	rad->dreapta = nod1->stanga;
	nod1->stanga = rad;
	rad = nod1;
	return rad;
}

NodArb* rotatieStangaDreapta(NodArb* rad) {
	printf("Rotatie stanga dreapta\n");
	NodArb* nod1 = rad->stanga;
	NodArb* nod2 = nod1->dreapta;
	nod1->dreapta = nod2->stanga;
	nod2->stanga = nod1;
	rad->stanga = nod2->dreapta;
	nod2 -> dreapta = rad;
	rad = nod2;
	return rad;
}

NodArb* rotatieDreaptaStanga(NodArb* rad) {
	printf("Rotatie dreapta stanga\n");
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
	else
	{
		if (rad->BF >= 2 && fiuDr >= 1) {
			rad = rotatieStanga(rad);
			calculBF(rad);
		}
		else {
			if (rad->BF <= -2 && fiuSt->BF >= 1) {
				rad = rotatieStangaDreapta(rad);
				calculBF(rad);
			}
			else {
				if (rad->BF >= 2 && fiuDr->BF <= 1) {
					rad = rotatieDreaptaStanga(rad);
					calculBF(rad);
				}
			}
		}
	}
	return rad;
}

int maxim(int a, int b) {
	int max = a;
	if (max < b) {
		max = b;
	}
	return max;
}

int inaltimeArbore(NodArb* rad) {
	if (rad != NULL) {
		return 1 + maxim(inaltimeArbore(rad->stanga), inaltimeArbore(rad->dreapta));
	}
	else {
		return 0;
	}
}

void calculBF(NodArb* rad) {
	if (rad != NULL) {
		rad->BF = inaltimeArbore(rad->dreapta) - inaltimeArbore(rad->stanga);
		calculBF(rad->stanga);
		calculBF(rad->dreapta);
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
	printf("Rotatie stanga dreapta\n");
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
	printf("Rotatie dreapta stanga\n");
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
		rad = rotireDreapta(rad);
		calculBF(rad);
	}
	else
	{
		if (rad->BF >= 2 && fiuDr->BF >= 1) {
			rad = rotireStanga(rad);
			calculBF(rad);
		}
		else {
			if (rad->BF <= -2 && fiuSt->BF >= 1) {
				rad = rotireStangaDreapta(rad);
				calculBF(rad);
			}
			else {
				if (rad->BF >= 2 && fiuDr->BF <= -1) {
					rad = rotireDreaptaStanga(rad);
					calculBF(rad);
				}
			}
		}
	}
	return rad;
}

void main() {
	NodArb* rad = NULL;
	Zbor zbor;
	char buffer[50];
	int nrZboruri;

	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrZboruri);
	for (int i = 0; i < nrZboruri; i++) {
		fscanf(f, "%d", &zbor.cod);

		fscanf(f, "%s", buffer);

		zbor.companie = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(zbor.companie, buffer);

		fscanf(f, "%f", &zbor.pret);

		fscanf(f, "%d", &zbor.dataZbor.zi);

		fscanf(f, "%d", &zbor.dataZbor.luna);

		fscanf(f, "%d", &zbor.dataZbor.an);
		
		rad = inserareNod(rad, zbor);

		free(zbor.companie);

		rad = reechilibrare(rad);
	}
	fclose(f);

	printf("-----------------PREORDINE-----------\n");
	preordine(rad);
}*/

#include<stdio.h>
#include<malloc.h>

typedef struct Carte {
	int cod;
	char* titlu;
	int nrAutori;
	float pret;
} Carte;

typedef struct NodArb {
	int BF;
	Carte info;
	struct NodArb* stanga;
	struct NodArb* dreapta;
} NodArb;

NodArb* creareNod(Carte carte, NodArb* stanga, NodArb* dreapta) {
	NodArb* nou = (NodArb*)malloc(sizeof(NodArb));
	nou->info.cod = carte.cod;
	nou->info.titlu = (char*)malloc((strlen(carte.titlu) + 1) * sizeof(char));
	strcpy(nou->info.titlu, carte.titlu);
	nou->info.nrAutori = carte.nrAutori;
	nou->info.pret = carte.pret;
	nou->stanga = stanga;
	nou->dreapta = dreapta;
	return nou;
}

NodArb* inserareNod(NodArb* rad, Carte carte) {
	if (rad != NULL) {
		if (carte.cod < rad->info.cod) {
			rad->stanga = inserareNod(rad->stanga, carte);
			return rad;
		}
		else if (carte.cod > rad->info.cod) {
			rad->dreapta = inserareNod(rad->dreapta, carte);
			return rad;
		}
		else {
			return rad;
		}
	}
	else {
		return creareNod(carte, NULL, NULL);
	}
}

//R S D
void afisarePreOrdine(NodArb* rad) {
	if (rad != NULL)
	{
		printf("\nCod=%d, Titlu=%s, Nr. autori=%d, Pret=%5.2f",
			rad->info.cod, rad->info.titlu, rad->info.nrAutori, rad->info.pret);
		afisarePreOrdine(rad->stanga);
		afisarePreOrdine(rad->dreapta);
	}
}

//S R D
void afisareInOrdine(NodArb* rad) {
	if (rad != NULL) {
		afisareInOrdine(rad->stanga);
		printf("\nCod=%d, Titlu=%s, Nr. autori=%d, Pret=%5.2f",
			rad->info.cod, rad->info.titlu, rad->info.nrAutori, rad->info.pret);
		afisareInOrdine(rad->dreapta);
	}
}

//S D R
void afisarePostOrdine(NodArb* rad) {
	if (rad != NULL) {
		afisarePostOrdine(rad->stanga);
		afisarePostOrdine(rad->dreapta);
		printf("\nCod=%d, Titlu=%s, Nr. autori=%d, Pret=%5.2f",
			rad->info.cod, rad->info.titlu, rad->info.nrAutori, rad->info.pret);
	}
}

void dezalocare(NodArb* rad) {
	if (rad != NULL) {
		dezalocare(rad->stanga);
		dezalocare(rad->dreapta);
		free(rad->info.titlu);
		free(rad);
	}
}

int maxim(int a, int b) {
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

NodArb* rotatieDreaptaStanga(NodArb* rad) {
	printf("\nRotatie dreapta stanga\n");
	NodArb* nod1 = rad->dreapta;
	NodArb* nod2 = nod1->stanga;
	nod1->stanga = nod2->dreapta;
	nod2->dreapta = nod1;
	rad->dreapta = nod2->stanga;
	nod2->stanga = rad;
	rad = nod2;
	return rad;
}

NodArb* rotatieStangaDreapta(NodArb* rad) {
	printf("\nRotatie stanga dreapta\n");
	NodArb* nod1 = rad->stanga;
	NodArb* nod2 = nod1->dreapta;
	nod1->dreapta = nod2->stanga;
	nod2->stanga = nod1;
	rad->stanga = nod2->dreapta;
	nod2->dreapta = rad;
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
			else if (rad->BF <= -2 && fiuSt->BF >= 1) {
				rad = rotatieStangaDreapta(rad);
				calculBF(rad);
			}
		}
	}
	return rad;
}

void main() {
	NodArb* rad = NULL;
	Carte carte;
	int nrCarti;
	char buffer[50];

	FILE* f = fopen("carti.txt", "r");
	fscanf(f, "%d", &nrCarti);

	for (int i = 0; i < nrCarti; i++) {
		fscanf(f, "%d", &carte.cod);

		fscanf(f, "%s", buffer);
		carte.titlu = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(carte.titlu, buffer);

		fscanf(f, "%d", &carte.nrAutori);

		fscanf(f, "%f", &carte.pret);

		rad = inserareNod(rad, carte);
		free(carte.titlu);

		rad = reechilibrare(rad);
	}

	printf("--------------------PREORDINE--------------------");
	afisarePreOrdine(rad);

	dezalocare(rad);
}