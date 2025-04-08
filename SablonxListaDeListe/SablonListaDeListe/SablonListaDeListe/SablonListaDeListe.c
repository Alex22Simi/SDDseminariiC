#include<stdio.h>
#include<malloc.h>

typedef struct Campionat {
	char* nume;
	int venit;
} Campionat;

typedef struct NodLS {
	Campionat info;
	struct NodLS* next;
} NodLS;

typedef struct NodLP {
	struct NodLS* info;
	struct NodLP* next;
} NodLP;

void inserareLS(NodLS** capLS, Campionat campionat) {
	NodLS* nodNou = (NodLS*)malloc(sizeof(NodLS));
	nodNou->info.nume = (char*)malloc((strlen(campionat.nume) + 1) * sizeof(char));
	strcpy(nodNou->info.nume, campionat.nume);
	nodNou->info.venit = campionat.venit;
	nodNou->next = NULL;
	if ((*capLS) == NULL) {
		(*capLS) = nodNou;
	}
	else {
		NodLS* temp = (*capLS);
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nodNou;
	}
}

void inserareLP(NodLP** capLP, NodLS* capLS) {
	NodLP* nodNou = (NodLP*)malloc(sizeof(NodLP));
	nodNou->info = capLS;
	nodNou->next = NULL;
	if ((*capLP) == NULL) {
		(*capLP) = nodNou;
	}
	else {
		NodLP* temp = (*capLP);
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nodNou;
	}
}

void traversareLS(NodLS* capLS) {
	NodLS* temp = capLS;
	while (temp != NULL) {
		printf("\nNume: %s\nVenit: %d\n",
			temp->info.nume, temp->info.venit);
		temp = temp->next;
	}
}

void traversareLP(NodLP* capLP) {
	NodLP* temp = capLP;
	int i = 1;
	while (temp != NULL) {
		printf("\nSublista campionate: %d\n", i);
		traversareLS(temp->info);
		temp = temp->next;
		i++;
	}
}

void dezalocareLS(NodLS* capLS) {
	NodLS* temp = capLS;
	while (temp != NULL) {
		NodLS* aux = temp->next;
		free(temp->info.nume);
		free(temp);
		temp = aux;
	}
}

void dezalocareLP(NodLP* capLP) {
	NodLP* temp = capLP;
	while (temp != NULL) {
		NodLP* aux = temp->next;
		dezalocareLS(temp->info);
		free(temp);
		temp = aux;
	}
}

void main() {
	NodLS* capLSCampionateScumpe = NULL;
	NodLS* capLSCampionateIeftine = NULL;
	NodLP* capLP = NULL;

	Campionat campionat;
	int nrCampionate;
	char buffer[20];

	FILE* f = fopen("Campionate.txt", "r");
	fscanf(f, "%d", &nrCampionate);
	for (int i = 0; i < nrCampionate; i++) {
		fscanf(f, "%s", buffer);
		campionat.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(campionat.nume, buffer);
		fscanf(f, "%d", &campionat.venit);

		if (campionat.venit >= 100) {
			inserareLS(&capLSCampionateScumpe, campionat);
		}
		else {
			inserareLS(&capLSCampionateIeftine, campionat);
		}

		free(campionat.nume);
	}
	fclose(f);

	inserareLP(&capLP, capLSCampionateScumpe);
	inserareLP(&capLP, capLSCampionateIeftine);

	traversareLP(capLP);

	dezalocareLP(capLP);
}