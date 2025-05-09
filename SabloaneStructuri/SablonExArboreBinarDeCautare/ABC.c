/*#include<malloc.h>
#include<stdio.h>

typedef struct Data {
	int zi;
	int luna;
	int an;
} Data;

typedef struct Zbor {
	int cod;
	char* companie;
	float pret;
	Data data;
} Zbor;

typedef struct NodArb {
	Zbor info;
	struct NodArb* stanga;
	struct NodArb* dreapta;
} NodArb;

NodArb* creareNod(Zbor z, NodArb* stanga, NodArb* dreapta) {
	NodArb* nou = (NodArb*)malloc(sizeof(NodArb));
	nou->info.cod = z.cod;
	nou->info.companie = (char*)malloc((strlen(z.companie) + 1) * sizeof(char));
	strcpy(nou->info.companie, z.companie);
	nou->info.pret = z.pret;
	nou->info.data.zi = z.data.zi;
	nou->info.data.luna = z.data.luna;
	nou->info.data.an = z.data.an;
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
		else if(zbor.cod > rad->info.cod){
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

//pre ordine
//radacina stanga dreapta
void preordine(NodArb* rad) {
	if (rad != NULL) {
		printf("Cod = %d, Companie = %s, Pret = %2.5f, Data = %d/%d/%d\n",
			rad->info.cod, rad->info.companie, rad->info.pret, rad->info.data.zi, rad->info.data.luna, rad->info.data.an);
		preordine(rad->stanga);
		preordine(rad->dreapta);
	}
}

//in ordine
//stanga radacina dreapta
void inordine(NodArb* rad) {
	if (rad != NULL) {
		inordine(rad->stanga);
		printf("Cod = %d, Companie = %s, Pret = %2.5f, Data = %d/%d/%d\n",
			rad->info.cod, rad->info.companie, rad->info.pret, rad->info.data.zi, rad->info.data.luna, rad->info.data.an);
		inordine(rad->dreapta);
	}
}

//post ordine
//stanga dreapta radacina
void postordine(NodArb* rad) {
	if (rad != NULL) {
		postordine(rad->stanga);
		postordine(rad->dreapta);
		printf("Cod = %d, Companie = %s, Pret = %2.5f, Data = %d/%d/%d\n",
			rad->info.cod, rad->info.companie, rad->info.pret, rad->info.data.zi, rad->info.data.luna, rad->info.data.an);
	}
}

void dezalocare(NodArb* rad) {
	//post ordine
	if (rad != NULL) {
		dezalocare(rad->stanga);
		dezalocare(rad->dreapta);
		free(rad->info.companie);
		free(rad);
	}
}

void salvareZboruriVector(NodArb* rad, Zbor* vect, int* nr, int anPrag) {
	if (rad != NULL) {
		if (rad->stanga == NULL && rad->dreapta == NULL && rad->info.data.an == anPrag) {
			vect[*nr].cod = rad->info.cod;
			vect[*nr].companie = (char*)malloc((strlen(rad->info.companie) + 1) * sizeof(char));
			strcpy(vect[*nr].companie, rad->info.companie);
			vect[*nr].pret = rad->info.pret;
			vect[*nr].data.zi = rad->info.data.zi;
			vect[*nr].data.luna = rad->info.data.luna;
			vect[*nr].data.an = rad->info.data.an;
			(*nr)++;
		}
		salvareZboruriVector(rad->stanga, vect, nr, anPrag);
		salvareZboruriVector(rad->dreapta, vect, nr, anPrag);
	}
}

void sumaPreturilor(NodArb* rad, float* suma) {
	if (rad != NULL) {
		*suma += rad->info.pret;
		sumaPreturilor(rad->stanga, suma);
		sumaPreturilor(rad->dreapta, suma);
	}
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
		fscanf(f, "%d", &zbor.data.zi);
		fscanf(f, "%d", &zbor.data.luna);
		fscanf(f, "%d", &zbor.data.an);

		rad = inserareNod(rad, zbor);
		free(zbor.companie);
	}
	fclose(f);

	printf("----------------POSTORDINE-----------------\n");
	postordine(rad);
	printf("----------------PREORDINE-----------------\n");
	preordine(rad);
	printf("----------------INORDINE-----------------\n");
	inordine(rad);

	printf("------------------VECTOR--------------\n");
	Zbor* vect = (Zbor*)malloc(nrZboruri * sizeof(Zbor));
	int nr = 0;
	salvareZboruriVector(rad, vect, &nr, 2023);
	for (int i = 0; i < nr; i++) {
		printf("Cod = %d, Companie = %s, Pret = %2.5f, Data = %d/%d/%d\n",
			vect[i].cod, vect[i].companie, vect[i].pret,
			vect[i].data.zi, vect[i].data.luna, vect[i].data.an);
	}
	for (int i = 0; i < nr; i++) {
		free(vect[i].companie);
	}
	free(vect);



	float suma = 0;
	sumaPreturilor(rad, &suma);
	printf("Suma: %5.2f", suma);

	dezalocare(rad);
}*/

#include<malloc.h>
#include<stdio.h>

typedef struct EchipaNationala{
	int id;
	char* numeEchipa;
} EchipaNationala;

typedef struct NodArb {
	EchipaNationala info;
	struct NodArb* stanga;
	struct NodArb* dreapta;
} NodArb;

NodArb* creareNod(EchipaNationala echipa, NodArb* stanga, NodArb* dreapta) {
	NodArb* nou = (NodArb*)malloc(sizeof(NodArb));
	nou->info.id = echipa.id;
	nou->info.numeEchipa = (char*)malloc((strlen(echipa.numeEchipa) + 1) * sizeof(char));
	strcpy(nou->info.numeEchipa, echipa.numeEchipa);
	nou->stanga = stanga;
	nou->dreapta = dreapta;
	return nou;
}

NodArb* inserareNod(NodArb* rad, EchipaNationala echipa) {
	if (rad != NULL) {
		if (echipa.id < rad->info.id) {
			rad->stanga = inserareNod(rad->stanga, echipa);
			return rad;
		}
		else if (echipa.id > rad->info.id) {
			rad->dreapta = inserareNod(rad->dreapta, echipa);
			return rad;
		}
		else {
			return rad;
		}
	}
	else {
		return creareNod(echipa, NULL, NULL);
	}
}

//preordine-> radacina stanga dreapta 
void afisarePreordine(NodArb* rad) {
	if (rad != NULL) {
		printf("Id: %d, Nume: %s\n",
			rad->info.id, rad->info.numeEchipa);
		afisarePreordine(rad->stanga);
		afisarePreordine(rad->dreapta);
	}
}

//inordine -> stanga radacina dreapta
void afisareInordine(NodArb* rad) {
	if (rad != NULL) {
		afisareInordine(rad->stanga);
		printf("Id: %d, Nume: %s\n",
			rad->info.id, rad->info.numeEchipa);
		afisareInordine(rad->dreapta);
	}
}

//postordine ->  stanga dreapta radacina
void afisarePostordine(NodArb* rad) {
	if (rad != NULL) {
		afisarePostordine(rad->stanga);
		afisarePostordine(rad->dreapta);
		printf("Id: %d, Nume: %s\n",
			rad->info.id, rad->info.numeEchipa);
	}
}

//afisare
void sumaID(NodArb* rad, int* suma) {
	if (rad != NULL) {
		*suma += rad->info.id;
		sumaID(rad->stanga, suma);
		sumaID(rad->dreapta, suma);
	}
}

void salvareInVector(NodArb* rad, EchipaNationala* vect, int* nr, int pragId) {
	if (rad != NULL) {
		if (rad->stanga == NULL && rad->dreapta == NULL &&rad->info.id > pragId) {
			vect[*nr].id = rad->info.id;
			vect[*nr].numeEchipa = (char*)malloc((strlen(rad->info.numeEchipa) + 1) * sizeof(char));
			strcpy(vect[*nr].numeEchipa, rad->info.numeEchipa);
			(*nr)++;
		}
		salvareInVector(rad->stanga, vect, nr, pragId);
		salvareInVector(rad->dreapta, vect, nr, pragId);
	}
	
}

void dezalocare(NodArb* rad) {
	if (rad != NULL) {
		dezalocare(rad->stanga);
		dezalocare(rad->dreapta);
		free(rad->info.numeEchipa);
		free(rad);
	}
}

void main() {
	NodArb* rad = NULL;
	EchipaNationala echipa;
	int nrEchipe;
	char buffer[30];

	FILE* f = fopen("EchipaNationala.txt", "r");
	fscanf(f, "%d", &nrEchipe);

	for (int i = 0; i < nrEchipe; i++) {
		fscanf(f, "%d", &echipa.id);
		fscanf(f, "%s", buffer);
		echipa.numeEchipa = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(echipa.numeEchipa, buffer);

		rad = inserareNod(rad, echipa);
	}
	fclose(f);

	printf("----------------POSTORDINE-----------------\n");
	afisarePostordine(rad);
	printf("----------------PREORDINE-----------------\n");
	afisarePreordine(rad);
	printf("----------------INORDINE-----------------\n");
	afisareInordine(rad);

	printf("--------------------VECTOR---------------\n");
	EchipaNationala* vect = (EchipaNationala*)malloc(nrEchipe * sizeof(EchipaNationala));
	int nr = 0;
	salvareInVector(rad, vect, &nr, 4);
	
	for (int i = 0; i < nr; i++) {
		printf("Id: %d, Nume: %s\n",
			vect[i].id, vect[i].numeEchipa);
	}
	for (int i = 0; i < nr; i++) {
		free(vect[i].numeEchipa);
	}
	free(vect);

	int suma = 0;
	sumaID(rad, &suma);
	printf("Suma ID: %d", suma);

	dezalocare(rad);
}





