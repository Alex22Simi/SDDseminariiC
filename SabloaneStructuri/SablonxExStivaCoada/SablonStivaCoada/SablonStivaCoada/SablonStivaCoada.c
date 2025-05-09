#include<stdio.h>
#include<malloc.h>

typedef struct DataReceptionare {
	int zi;
	int luna;
	int an;
} DataReceptionare;

typedef struct Notificare {
	DataReceptionare data;
	char* denumireAplicatie;
	float durata;
} Notificare;

typedef struct NodStiva {
	Notificare info;
	struct NodStiva* next;
} NodStiva;

typedef struct NodCoada {
	Notificare info;
	struct NodCoada* next;
} NodCoada;

//inserare nod in stiva
void push(NodStiva** varf, Notificare notificare) {
	NodStiva* nodNou = (NodStiva*)malloc(sizeof(NodStiva));
	nodNou->info.data.zi = notificare.data.zi;
	nodNou->info.data.luna = notificare.data.luna;
	nodNou->info.data.an = notificare.data.an;
	nodNou->info.denumireAplicatie = (char*)malloc((strlen(notificare.denumireAplicatie) + 1) * sizeof(char));
	strcpy(nodNou->info.denumireAplicatie, notificare.denumireAplicatie);
	nodNou->info.durata = notificare.durata;
	nodNou->next = NULL;
	if (*varf == NULL) {
		(*varf) = nodNou;
	}
	else {
		nodNou->next = (*varf);
		(*varf) = nodNou;
	}
}

//fct extragere nod din stiva
int pop(NodStiva** varf, Notificare* notificare) {
	if (*varf == NULL) {
		return -1;
	}
	else {
		(*notificare).data.zi = (*varf)->info.data.zi;
		(*notificare).data.luna = (*varf)->info.data.luna;
		(*notificare).data.an = (*varf)->info.data.an;
		(*notificare).denumireAplicatie = (char*)malloc((strlen((*varf)->info.denumireAplicatie) + 1) * sizeof(char));
		strcpy((*notificare).denumireAplicatie, (*varf)->info.denumireAplicatie);
		(*notificare).durata = (*varf)->info.durata;
		NodStiva* temp = (*varf);
		(*varf) = (*varf)->next;
		free(temp->info.denumireAplicatie);
		free(temp);
		return 0;
	}
}

void afisareStiva(NodStiva* varf) {
	NodStiva* temp = varf;
	while (temp != NULL) {
		printf("\nData: %d/%d/%d, Denumire aplicatie: %s, Durata: %5.2f",
			temp->info.data.zi, temp->info.data.luna, temp->info.data.an,
			temp->info.denumireAplicatie, temp->info.durata);
		temp = temp->next;
	}
}

void dezalocareStiva(NodStiva* varf) {
	Notificare notificare;
	while (pop(&varf, &notificare) == 0) {
		free(notificare.denumireAplicatie);
	}
}

//inserare in coada
void put(NodCoada** prim, NodCoada** ultim, Notificare notificare) {
	NodCoada* nodNou = (NodCoada*)malloc(sizeof(NodCoada));
	nodNou->info.data.zi = notificare.data.zi;
	nodNou->info.data.luna = notificare.data.luna;
	nodNou->info.data.an = notificare.data.an;
	nodNou->info.denumireAplicatie = (char*)malloc((strlen(notificare.denumireAplicatie) + 1) * sizeof(char));
	strcpy(nodNou->info.denumireAplicatie, notificare.denumireAplicatie);
	nodNou->info.durata = notificare.durata;
	nodNou->next = NULL;
	if ((*prim) == NULL || (*ultim) == NULL) {
		(*prim) = nodNou;
		(*ultim) = nodNou;
	}
	else {
		(*ultim)->next = nodNou;
		(*ultim) = nodNou;
	}
}

//parcurgere nod din coada
int get(NodCoada** prim, NodCoada** ultim, Notificare* notificare) {
	if ((*prim) != NULL && (*ultim) != NULL) {
		(*notificare).data.zi = (*prim)->info.data.zi;
		(*notificare).data.luna = (*prim)->info.data.luna;
		(*notificare).data.an = (*prim)->info.data.an;
		(*notificare).denumireAplicatie = (char*)malloc((strlen((*prim)->info.denumireAplicatie) + 1) * sizeof(char));
		strcpy((*notificare).denumireAplicatie, (*prim)->info.denumireAplicatie);
		(*notificare).durata = (*prim)->info.durata;
		NodCoada* temp = (*prim);
		(*prim) = (*prim)->next;
		free(temp->info.denumireAplicatie);
		free(temp);
		return 0;
	}
	if (*prim == NULL) {
		*ultim = NULL;
		return -1;
	}
}

//afisare coada
void afisareCoada(NodCoada* prim) {
	NodCoada* temp = prim;
	while (temp != NULL) {
		printf("\nData: %d/%d/%d, Denumire aplicatie: %s, Durata: %5.2f",
			temp->info.data.zi, temp->info.data.luna, temp->info.data.an,
			temp->info.denumireAplicatie, temp->info.durata);
		temp = temp->next;
	}
}

void dezalocareCoada(NodCoada* prim, NodCoada* ultim) {

	Notificare notificare;
	while (get(prim, ultim, &notificare) == 0) {
		free(notificare.denumireAplicatie);
	}
}

void conversieStivaCoada(NodStiva* varf, NodCoada** prim, NodCoada** ultim) {
	Notificare notificare;
	while (pop(&varf, &notificare) == 0) {
		put(prim, ultim, notificare);
	}
}

void conversieCoadaStiva(NodStiva** varf, NodCoada** prim, NodCoada** ultim) {
	Notificare notificare;
	while (get(prim, ultim, &notificare) == 0) {
		push(&varf, notificare);

	}
}

void filtrareNotificariDupaDurata(NodCoada* prim, NodCoada* ultim, Notificare* vectNotificari, int* nr, float prag) {
	Notificare notificare;
	while (get(&prim, &ultim, &notificare) == 0) {
		if (notificare.durata >= prag) {
			vectNotificari[*nr] = notificare;
			(*nr)++;
		}
	}

}

void main() {
	int nrNotificari;
	NodStiva* varf = NULL;
	NodCoada* prim = NULL;
	NodCoada* ultim = NULL;
	Notificare notificare;
	char buffer[20];
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrNotificari);
	for (int i = 0; i < nrNotificari; i++) {
		fscanf(f, "%d", &notificare.data.zi);
		fscanf(f, "%d", &notificare.data.luna);
		fscanf(f, "%d", &notificare.data.an);
		fscanf(f, "%s", buffer);
		notificare.denumireAplicatie = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(notificare.denumireAplicatie, buffer);
		fscanf(f, "%f", &notificare.durata);
		//inserare in stiva:
		push(&varf, notificare);

		//inserare in coada:
		put(&prim, &ultim, notificare);

		free(notificare.denumireAplicatie);
	}
	fclose(f);

	printf("\n----------------STIVA------------");
	afisareStiva(varf);


	printf("\n----------------COADA------------");
	//conversieStivaCoada(varf, &prim, &ultim);
	afisareCoada(prim);

	printf("\n------------------CONVERSIE COADA IN STIVA---------\n");
	conversieCoadaStiva(&varf, &prim, &ultim);
	afisareStiva(varf);

	printf("\n------------------CONVERSIE STIVA IN COADA---------\n");
	conversieStivaCoada(varf, &prim, &ultim);
	afisareCoada(prim);

	printf("\n------------------VECTOR------------------\n");
	Notificare* vectorNotificare = (Notificare*)malloc(nrNotificari * sizeof(notificare));
	int nr = 0;
	filtrareNotificariDupaDurata(prim, ultim, vectorNotificare, &nr, 2);
	for (int i = 0; i < nr; i++) {
		printf("\nData: %d/%d/%d, Denumire aplicatie: %s, Durata: %5.2f",
			vectorNotificare[i].data.zi, vectorNotificare[i].data.luna, vectorNotificare[i].data.an,
			vectorNotificare[i].denumireAplicatie, vectorNotificare[i].durata);
	}
	for (int i = 0; i < nr; i++) {
		free(vectorNotificare[i].denumireAplicatie);
	}
	free(vectorNotificare);

	//dezalocareStiva(varf);
	//dezalocareCoada(prim, ultim);
}
