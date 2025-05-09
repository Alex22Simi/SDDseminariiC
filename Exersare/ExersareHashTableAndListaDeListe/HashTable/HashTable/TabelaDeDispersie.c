#include<stdio.h>
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

typedef struct HashT {
	struct NodLS** vector;
	int nrElementeVector;
} HashT;

//daca avem cheie id sau valoare numerica
int functieHashCheieId(int cheie, HashT tabela) {
	return cheie % tabela.nrElementeVector;
}

//daca avem cheie valoare string
int functieHashCheieNume(const char* nume, HashT tabela) {
	return nume[0] % tabela.nrElementeVector;
}

void inserareLS(NodLS** capLS, Student student) {
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

void inserareHash(HashT tabela, Student student) {
	int poz = functieHashCheieNume(student.nume, tabela);
	inserareLS(&tabela.vector[poz], student);
}

void traversareLS(NodLS* capLS) {
	NodLS* temp = capLS;
	while (temp != NULL) {
		printf("Varsta student: %d\nNume student: %s\nMedie student: %.2f\n\n",
			temp->info.varsta, temp->info.nume, temp->info.medie);
		temp = temp->next;
	}
}

void traversareHash(HashT tabela) {
	for (int i = 0; i < tabela.nrElementeVector; i++) {
		if (tabela.vector[i] != NULL) {
			printf("\nPozitia: %d\n", i);
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

void dezalocareHash(HashT tabela) {
	for (int i = 0; i < tabela.nrElementeVector; i++) {
		if (tabela.vector[i] != NULL) {
			dezalocareLS(tabela.vector[i]);
		}
	}
	free(tabela.vector);
}

//calculeaza media notelor per clustere
void calculeazaMediePerCluster(HashT tabela) {
	for (int i = 0; i < tabela.nrElementeVector; i++) {
		NodLS* temp = tabela.vector[i];
		int nr = 0;
		float suma = 0;

		while (temp != NULL) {
			suma += temp->info.medie;
			nr++;
			temp = temp->next;
		}

		if (nr > 0) {
			printf("Pozitia %d: media mediilor = %.2f\n", i, suma / nr);
		}
		else {
			printf("Pozitia %d: nu exista studenti\n", i);
		}
	}
}


//get student by cheie
void getStudentDupaCheie(HashT tabela, int cheie, Student* studentGasit ) {
	studentGasit->varsta = 0;

	int poz = functieHashCheieId(cheie, tabela);
	if (tabela.vector[poz] != NULL) {
		NodLS* p = tabela.vector[poz];
		while (p && p->info.varsta != cheie) {
			p = p->next;
		}
		if (p) {
			studentGasit->varsta = p->info.varsta;
			studentGasit->medie = p->info.medie;
			studentGasit->nume = (char*)malloc(strlen(p->info.nume) + 1);
			strcpy(studentGasit->nume, p->info.nume);
		}
	}
}

void main() {
	HashT tabela;
	tabela.nrElementeVector = 3;
	tabela.vector = (NodLS**)malloc(tabela.nrElementeVector * sizeof(NodLS*));
	for (int i = 0; i < tabela.nrElementeVector; i++) {
		tabela.vector[i] = NULL;
	}
	
	Student student;
	int nrStudenti;
	char buffer[20];
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrStudenti);
	for (int i = 0; i < nrStudenti; i++)
	{
		fscanf(f, "%d", &student.varsta);
		fscanf(f, "%s", buffer);
		student.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(student.nume, buffer);
		fscanf(f, "%f", &student.medie);
		inserareHash(tabela, student);
		free(student.nume);
	}
	fclose(f);

	traversareHash(tabela);
	Student studentGasit;
	printf("\n-----------------STUDENT DUPA CHEIE-------------\n");
	getStudentDupaCheie(tabela, 25,&studentGasit);
	if (studentGasit.varsta != 0) {
		printf("Student gasit:\nVarsta: %d\nNume: %s\nMedie: %.2f\n",
			studentGasit.varsta, studentGasit.nume, studentGasit.medie);
		free(studentGasit.nume);
	}
	else {
		printf("Nu s-a gasit student cu varsta data.\n");
	}

	printf("\n--------------------MEDIA MEDIILOR PER CLUSTERE----------------\n");
	calculeazaMediePerCluster(tabela);

	dezalocareHash(tabela);
}

/*#include<stdio.h>
#include<malloc.h>

typedef struct Fotbalist {
	int nrTricou;
	char* nume;
} Fotbalist;

typedef struct NodLS {
	Fotbalist info;
	struct NodLS* next;
} NodLS;

typedef struct HashT {
	NodLS** vector;
	int nrElementeVector;
} HashT;

int functieHashNrTricou(int nrTricou, HashT tabela) {
	return nrTricou % tabela.nrElementeVector;
}

void inserareLS(NodLS** capLS, Fotbalist fotbalist) {
	NodLS* nodNou = (NodLS*)malloc(sizeof(NodLS));
	nodNou->info.nrTricou = fotbalist.nrTricou;
	nodNou->info.nume = (char*)malloc((strlen(fotbalist.nume) + 1) * sizeof(char));
	strcpy(nodNou->info.nume, fotbalist.nume);
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

void inserareHashT(HashT tabela, Fotbalist fotbalist) {
	int poz = functieHashNrTricou(fotbalist.nrTricou, tabela);
	inserareLS(&tabela.vector[poz], fotbalist);

}

void traversareLS(NodLS* capLS) {
	NodLS* temp = capLS;
	while (temp != NULL) {
		printf("Nr de pe tricou: %d\nNumele jucatorului: %s\n\n",
			temp->info.nrTricou, temp->info.nume);
		temp = temp->next;
	}
}

void traversareHashT(HashT tabela) {
	for (int i = 0; i < tabela.nrElementeVector; i++) {
		if (tabela.vector[i] != NULL) {
			printf("\nPozitia: %d\n", i);
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

void main() {
	HashT tabela;
	tabela.nrElementeVector = 3;
	tabela.vector = (NodLS**)malloc(tabela.nrElementeVector * sizeof(NodLS*));
	for (int i = 0; i < tabela.nrElementeVector; i++) {
		tabela.vector[i] = NULL;
	}

	Fotbalist fotbalist;
	char buffer[20];
	int nrFotbalisti;

	FILE* f = fopen("Fotbalisti.txt", "r");
	fscanf(f, "%d", &nrFotbalisti);
	for (int i = 0; i < nrFotbalisti; i++) {
		fscanf(f, "%d", &fotbalist.nrTricou);
		fscanf(f, "%s", buffer);
		fotbalist.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(fotbalist.nume, buffer);
		inserareHashT(tabela, fotbalist);
	}
	fclose(f);

	traversareHashT(tabela);

	dezalocareHashT(tabela);
}*/

/*#include<stdio.h>
#include<malloc.h>

typedef struct CampionatEuropean {
	int idEchipa;
	char* numeEchipa;
} CampionatEuropean;

typedef struct NodLS {
	CampionatEuropean info;
	struct NodLS* next;
} NodLS;

typedef struct HashT {
	struct NodLS** vector;
	int nrElementeVector;
} HashT;

int functieHashDupaId(int id, HashT tabela) {
	return id % tabela.nrElementeVector;
}

int functieHashDupaNume(const char* nume, HashT tabela) {
	return nume[0] % tabela.nrElementeVector;
}

void inserareLS(NodLS** capLS, CampionatEuropean campionat) {
	NodLS* nodNou = (NodLS*)malloc(sizeof(NodLS));
	nodNou->info.idEchipa = campionat.idEchipa;
	nodNou->info.numeEchipa = (char*)malloc((strlen(campionat.numeEchipa) + 1) * sizeof(char));
	strcpy(nodNou->info.numeEchipa, campionat.numeEchipa);
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

void inserareHashT(HashT tabela, CampionatEuropean campionatEuropean) {
	int poz = functieHashDupaId(campionatEuropean.idEchipa, tabela);
	inserareLS(&tabela.vector[poz], campionatEuropean);
}

void traversareLS(NodLS* capLS) {
	NodLS* temp = capLS;
	while (temp != NULL) {
		printf("\nId: %d\nNume: %s\n",
			temp->info.idEchipa, temp->info.numeEchipa);
		temp = temp->next;
	}
}

void traversareHashT(HashT tabela) {
	for (int i = 0; i < tabela.nrElementeVector; i++) {
		if (tabela.vector[i] != NULL) {
			printf("\nPozitia: %d\n", i);
			traversareLS(tabela.vector[i]);
		}
	}
}

void dezalocareLS(NodLS* capLS) {
	NodLS* temp = capLS;
	while (temp != NULL) {
		NodLS* aux = temp->next;
		free(temp->info.numeEchipa);
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

void main() {
	HashT tabela;
	tabela.nrElementeVector = 3;
	tabela.vector = (NodLS**)malloc(tabela.nrElementeVector * sizeof(NodLS*));
	
	
	for (int i = 0; i < tabela.nrElementeVector; i++) {
		tabela.vector[i] = NULL;
	}
	

	CampionatEuropean campionat;
	int nrCampionate;
	char buffer[20];

	FILE* f = fopen("Campionat.txt", "r");
	fscanf(f, "%d", &nrCampionate);
	for (int i = 0; i < nrCampionate; i++) {
		fscanf(f, "%d", &campionat.idEchipa);
		fscanf(f, "%s", buffer);
		campionat.numeEchipa = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(campionat.numeEchipa, buffer);
		inserareHashT(tabela, campionat);
		free(campionat.numeEchipa);
	}
	fclose(f);

	traversareHashT(tabela);

	dezalocareHashT(tabela);
}*/


