#include <stdio.h>
#include <malloc.h>

typedef struct Student {
	int cod;
	char* nume;
	int varsta;
	float medie;
} Student;

typedef struct NodLS {
	Student info;
	struct NodLS* next;
} NodLS;

typedef struct HashT {
	struct NodLS** vector;
	int nrElementeVector;
} HashT;

typedef struct NodLP {
	struct NodLS* info;        
	struct NodLP* next; 
} NodLP;


int functieHashDupaCod(int cheie, HashT tabela) {
	return cheie % tabela.nrElementeVector;
}

void inserareLS(NodLS** capLS, Student student) {
	NodLS* nodNou = (NodLS*)malloc(sizeof(NodLS));
	nodNou->info.cod = student.cod;
	nodNou->info.nume = (char*)malloc((strlen(student.nume) + 1) * sizeof(char));
	strcpy(nodNou->info.nume, student.nume);
	nodNou->info.varsta = student.varsta;
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
void inserareHashT(HashT tabela, Student student) {
	int poz = functieHashDupaCod(student.cod, tabela);
	inserareLS(&tabela.vector[poz], student);
}

void traversareLS(NodLS* capLS) {
	NodLS* temp = capLS;
	while (temp != NULL) {
		printf("\nCod: %d\nNume: %s\nVarsta: %d\nMedie: %2.f\n\n",
			temp->info.cod, temp->info.nume, temp->info.varsta, temp->info.medie);
		temp = temp->next;
	}
}

void traversareHashT(HashT tabela) {
	for (int i = 0; i < tabela.nrElementeVector; i++) {
		if (tabela.vector[i] != NULL) {
			printf("\nPozitia: %d.\n", i);
			traversareLS(tabela.vector[i]);
		}
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

void dezalocareHashT(HashT tabela) {
	for (int i = 0; i < tabela.nrElementeVector; i++) {
		if (tabela.vector[i] != NULL) {
			dezalocareLS(tabela.vector[i]);
		}
	}
	free(tabela.vector);
}

void salvareInFisier(HashT tabela, const char* numeFisier) {
	FILE* f = fopen(numeFisier, "w");
	for (int i = 0; i < tabela.nrElementeVector; i++) {
		if (tabela.vector[i] != NULL) {
			fprintf(f, "\nPozitia: %d\n", i);
			NodLS* temp = tabela.vector[i];
			while (temp != NULL) {
				fprintf(f, "Cod: %d\nNume: %s\nVarsta: %d\nMedie: %.2f\n\n",
					temp->info.cod, temp->info.nume, temp->info.varsta, temp->info.medie);
				temp = temp->next;
			}
		}
	}
	fclose(f);
}



//stergere student cu cea mai mare medie din tabela
void stergeStudentMedieMare(HashT tabela) {
	float medieMax = 0.0f;
	int pozMax = -1;
	NodLS* nodMax = NULL;
	NodLS* nodPrecedent = NULL;

	//parcurgere tabela
	for (int i = 0; i < tabela.nrElementeVector; i++) {
		NodLS* temp = tabela.vector[i];
		NodLS* prev = NULL;

		while (temp != NULL) {
			if (temp->info.medie > medieMax) {
				medieMax = temp->info.medie;
				pozMax = i;
				nodMax = temp;
				nodPrecedent = prev;
			}
			prev = temp;
			temp = temp->next;
		}
	}

	//stergere student cu media max
	if (nodMax != NULL) {
		if (nodPrecedent == NULL) {
			tabela.vector[pozMax] = nodMax->next;
		}
		else {
			nodPrecedent->next = nodMax->next;
		}

		printf("\nStudentul cu cea mai mare medie (%.2f) a fost sters: %s\n", medieMax, nodMax->info.nume);
		free(nodMax->info.nume);
		free(nodMax);
	}
	else {
		printf("\nNu exista studenti in tabela.\n");
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

void conversieTabelaInListaDeListe(HashT tabela, NodLP** capLP) {
	NodLS* listaPeste5 = NULL;
	NodLS* listaSub5 = NULL;

	for (int i = 0; i < tabela.nrElementeVector; i++) {
		NodLS* temp = tabela.vector[i];
		while (temp != NULL) {
			Student student;
			student.cod = temp->info.cod;
			student.nume = (char*)malloc(strlen(temp->info.nume) + 1);
			strcpy(student.nume, temp->info.nume);
			student.varsta = temp->info.varsta;
			student.medie = temp->info.medie;

			if (student.medie >= 5) {
				inserareLS(&listaPeste5, student);
			}
			else {
				inserareLS(&listaSub5, student);
			}
			temp = temp->next;
		}
	}

	if (listaPeste5) {
		inserareLP(capLP, listaPeste5);
	}
	if (listaSub5) {
		inserareLP(capLP, listaSub5);
	}
}

void traversareListaDeListe(NodLP* capLP) {
	int i = 1;
	while (capLP) {
		printf("\nSublista %d:\n", i++);
		traversareLS(capLP->info);
		capLP = capLP->next;
	}
}

void dezalocareListaDeListe(NodLP* capLP) {
	while (capLP) {
		NodLP* aux = capLP->next;
		dezalocareLS(capLP->info);
		free(capLP);
		capLP = aux;
	}
}




void main() {
	HashT tabela;
	tabela.nrElementeVector = 4;
	tabela.vector = (NodLS**)malloc(tabela.nrElementeVector * sizeof(NodLS*));
	for (int i = 0; i < tabela.nrElementeVector; i++) {
		tabela.vector[i] = NULL;
	}

	Student student;
	char buffer[20];
	int nrStudenti;
	FILE* f = fopen("studenti.txt", "r");
	fscanf(f, "%d", &nrStudenti);

	for (int i = 0; i < nrStudenti; i++) {
		fscanf(f, "%d", &student.cod);

		fscanf(f, "%s", buffer);
		student.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(student.nume, buffer);

		fscanf(f, "%d", &student.varsta);

		fscanf(f, "%f", &student.medie);

		inserareHashT(tabela, student);
	}
	fclose(f);

	traversareHashT(tabela);

	stergeStudentMedieMare(tabela);
	printf("\n-----Dupa stergerea studentului cu media maxima -----\n");
	traversareHashT(tabela);

	NodLP* capLP = NULL;
	conversieTabelaInListaDeListe(tabela, &capLP);

	printf("\n--- Lista de liste ---\n");
	traversareListaDeListe(capLP);

	dezalocareListaDeListe(capLP);

	salvareInFisier(tabela, "outputStudenti.txt");

	dezalocareHashT(tabela);
}