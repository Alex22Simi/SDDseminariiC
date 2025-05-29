#include<stdio.h>
#include<malloc.h>

typedef struct DataReceptionare{
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

//inserare in nod Stiva
/*void push(NodStiva** varf, Notificare notif) {
	NodStiva* nou = (NodStiva*)malloc(sizeof(NodStiva));
	nou->info.data.zi = notif.data.zi;
	nou->info.data.luna = notif.data.luna;
	nou->info.data.an = notif.data.an;
	nou->info.denumireAplicatie = (char*)malloc((strlen(notif.denumireAplicatie) + 1) * sizeof(char));
	strcpy(nou->info.denumireAplicatie, notif.denumireAplicatie);
	nou->info.durata = notif.durata;

	nou->next = NULL;

	if (*varf == NULL) {
		*varf = nou;
	}
	else {
		nou->next = *varf;
		*varf = nou;
	}
}*/

void push(NodStiva** varf, Notificare notif) {
	NodStiva* nou = (NodStiva*)malloc(sizeof(NodStiva));
	nou->info.data.zi = notif.data.zi;
	nou->info.data.luna = notif.data.luna;
	nou->info.data.an = notif.data.an;
	nou->info.denumireAplicatie = (char*)malloc((strlen(notif.denumireAplicatie) + 1) * sizeof(char));
	strcpy(nou->info.denumireAplicatie, notif.denumireAplicatie);
	nou->info.durata = notif.durata;

	nou->next = NULL;

	if (*varf == NULL) {
		(*varf) = nou;
	}
	else {
		nou->next = (*varf);
		(*varf) = nou;
	}
}

//extragere nod din stiva
/*int pop(NodStiva** varf, Notificare* notif) {
	if (*varf == NULL) {
		return - 1;
	}
	else {
		(*notif).data.zi = (*varf)->info.data.zi;
		(*notif).data.luna = (*varf)->info.data.luna;
		(*notif).data.an = (*varf)->info.data.an;
		(*notif).denumireAplicatie = (char*)malloc((strlen((*varf)->info.denumireAplicatie) + 1) * sizeof(char));
		strcpy((*notif).denumireAplicatie, (*varf)->info.denumireAplicatie);
		(*notif).durata = (*varf)->info.durata;
		NodStiva* temp = *varf;
		*varf = (*varf)->next;
		free(temp->info.denumireAplicatie);
		free(temp);
		return 0;
	}
}*/

int pop(NodStiva** varf, Notificare* notif) {
	if ((*varf) == NULL) {
		return -1;
	}
	else {
		(*notif).data.zi = (*varf)->info.data.zi;
		(*notif).data.luna = (*varf)->info.data.luna;
		(*notif).data.an = (*varf)->info.data.an;

		(*notif).denumireAplicatie = (char*)malloc((strlen((*varf)->info.denumireAplicatie) + 1) * sizeof(char));
		strcpy((*notif).denumireAplicatie, (*varf)->info.denumireAplicatie);

		(*notif).durata = (*varf)->info.durata;

		NodStiva* temp = *varf;

		(*varf) = (*varf)->next;
		free(temp->info.denumireAplicatie);
		free(temp);
		return 0;
	}
}

void afisareStiva(NodStiva* varf) {
	NodStiva* temp = varf;
	while (temp) {
		printf("\nData: %d/%d/%d, Denumire aplicatie: %s, Durata: %5.2f",
			temp->info.data.zi, temp->info.data.luna, temp->info.data.an,
			temp->info.denumireAplicatie, temp->info.durata);
		temp = temp->next;
	}
}

void dezalocareStuva(NodStiva* varf) {
	Notificare notif;
	while (pop(&varf, &notif) == 0) {
		free(notif.denumireAplicatie);
	}
}

//fct de inserare nod in coada
void put(NodCoada** prim, NodCoada** ultim, Notificare notif) {
	NodCoada* nou = (NodCoada*)malloc(sizeof(NodCoada));
	nou->info.data.zi = notif.data.zi;
	nou->info.data.luna = notif.data.luna;
	nou->info.data.an = notif.data.an;
	nou->info.denumireAplicatie = (char*)malloc((strlen(notif.denumireAplicatie) + 1) * sizeof(char));
	strcpy(nou->info.denumireAplicatie, notif.denumireAplicatie);
	nou->info.durata = notif.durata;

	nou->next = NULL;

	if (*prim == NULL || *ultim == NULL) {
		(*prim) = nou;
		(*ultim) = nou;
	}
	else {
		(*ultim)->next = nou;
		(*ultim) = nou;
	}
}

int get(NodCoada** prim, NodCoada** ultim, Notificare* notif)
{
	if (*prim != NULL && *ultim != NULL)
	{
		(*notif).data.zi = (*prim)->info.data.zi;
		(*notif).data.luna = (*prim)->info.data.luna;
		(*notif).data.an = (*prim)->info.data.an;
		(*notif).denumireAplicatie = (char*)malloc((strlen((*prim)->info.denumireAplicatie) + 1) * sizeof(char));
		strcpy((*notif).denumireAplicatie, (*prim)->info.denumireAplicatie);
		(*notif).durata = (*prim)->info.durata;
		NodCoada* temp = *prim;
		*prim = (*prim)->next;
		free(temp->info.denumireAplicatie);
		free(temp);
		return 0;
	}
	if (*prim == NULL)
	{
		*ultim = NULL;
		return -1;
	}
}

void afisareCoada(NodCoada* prim)
{
	NodCoada* temp = prim;
	while (temp)
	{
		printf("\nData: %d/%d/%d, Denumire aplicatie: %s, Durata: %5.2f",
			temp->info.data.zi, temp->info.data.luna, temp->info.data.an,
			temp->info.denumireAplicatie, temp->info.durata);
		temp = temp->next;
	}
}

void dezalocareCoada(NodCoada* prim, NodCoada* ultim)
{
	Notificare notif;
	while (get(&prim, &ultim, &notif) == 0)
		free(notif.denumireAplicatie);
}



void main() {

}