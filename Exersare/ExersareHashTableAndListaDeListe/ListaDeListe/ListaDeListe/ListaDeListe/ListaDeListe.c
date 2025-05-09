/*#include<stdio.h>
#include<malloc.h>

typedef struct Student {
	int varsta;
	char* nume;
	float medie;
} Student;

typedef struct NodLS {
	Student info;
	struct NodLS* next;
} NodLS;

typedef struct NodLP {
	struct NodLS* info;
	struct NodLP* next;
} NodLP;

void inserareLS(NodLS** capLS, Student student)
{
	NodLS* nodNou = (NodLS*)malloc(sizeof(NodLS));
	nodNou->info.varsta = student.varsta;
	nodNou->info.nume = (char*)malloc((strlen(student.nume) + 1) * sizeof(char));
	strcpy(nodNou->info.nume, student.nume);
	nodNou->info.medie = student.medie;
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
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nodNou;
	}
}

void traversareLS(NodLS* capLS) {
	NodLS* temp = capLS;
	while (temp != NULL) {
		printf("\nVarsta: %d\nNume: %s\nMedie: %.2f\n",
			temp->info.varsta, temp->info.nume, temp->info.medie);
		temp = temp->next;
	}
}

void traversareLP(NodLP* capLP) {
	NodLP* temp = capLP;
	int i = 1;
	while (temp != NULL) {
		printf("\nSublista: %d", i);
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
	Student student;
	NodLS* capLSpromovati = NULL;
	NodLS* capLSnepromovati = NULL;
	NodLP* capLP = NULL;
	char buffer[20];
	int nrStudenti;
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrStudenti);
	for (int i = 0; i < nrStudenti; i++) {
		fscanf(f, "%d", &student.varsta);
		fscanf(f, "%s", buffer);
		student.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(student.nume, buffer);
		fscanf(f, "%f", &student.medie);
		if (student.medie >= 5) {
			inserareLS(&capLSpromovati, student);
		}
		else {
			inserareLS(&capLSnepromovati, student);
		}
		free(student.nume);
	}
	fclose(f);

	inserareLP(&capLP, capLSpromovati);
	inserareLP(&capLP, capLSnepromovati);
	traversareLP(capLP);

	dezalocareLP(capLP);
}*/


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

