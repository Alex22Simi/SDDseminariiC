/*#include<stdio.h>
#include<malloc.h>

typedef struct Student {
	int varsta;
	char* nume;
	float medie;
} Student;

typedef struct NodLD {
	Student info;
	struct NodLD* next;
	struct NodLD* prev;
} NodLD;

NodLD* initializareNodLD(Student student) {
	NodLD* nodNou = (NodLD*)malloc(sizeof(NodLD));
	nodNou->info.varsta = student.varsta;
	nodNou->info.nume = (char*)malloc((strlen(student.nume) + 1) * sizeof(char));
	strcpy(nodNou->info.nume, student.nume);
	nodNou->info.medie = student.medie;
	nodNou->next = NULL;
	nodNou->prev = NULL;
	return nodNou;
}


NodLD* inserareNodLD(NodLD* capLD, NodLD** coadaLD, Student student) {
	NodLD* nodNou = initializareNodLD(student);
	if (capLD == NULL) {
		capLD = nodNou;
		*coadaLD = nodNou;
	}
	else {
		(*coadaLD)->next = nodNou;
		nodNou->prev = *coadaLD;
		*coadaLD = nodNou;
	}
	return capLD;
}

void traversareLD(NodLD* capLD) {
	NodLD* temp = capLD;
	while (temp != NULL) {
		printf("Varsta: %d\nNume: %s\nMedie: %.2f\n\n\n",
			temp->info.varsta, temp->info.nume, temp->info.medie);
		temp = temp->next;
	}
}

void traversareLDinvers(NodLD* coadaLD) {
	NodLD* temp = coadaLD;
	while (temp != NULL) {
		printf("Varsta: %d\nNume: %s\nMedie: %.2f\n\n\n",
			temp->info.varsta, temp->info.nume, temp->info.medie);
		temp = temp->prev;
	}
}

void dezalocareLD(NodLD* capLD) {
	NodLD* temp = capLD;

	while (temp != NULL) {
		NodLD* aux = temp->next;
		free(temp->info.nume);
		free(temp);
		temp = aux;
	}
}



void salvareStudentiInVectorDupaMedie(NodLD* capLD, Student* vectorStudenti, int* nrElemente, float mediePrag) {
	NodLD* temp = capLD;
	while (temp != NULL) {
		if (temp->info.medie >= mediePrag) {
			vectorStudenti[*nrElemente].varsta = temp->info.varsta;
			vectorStudenti[*nrElemente].nume = (char*)malloc((strlen(temp->info.nume) + 1) * sizeof(char));
			strcpy(vectorStudenti[*nrElemente].nume, temp->info.nume);
			vectorStudenti[*nrElemente].medie = temp->info.medie;
			(*nrElemente)++;
		}
		temp = temp->next;
	}

}


//sterge student dupa nume!!
void stergereStudentDupaNume(NodLD** capLD, NodLD** coadaLD, const char* numeStudent) {
	if(strcmp())
}


void main() {
	NodLD* capLD = NULL;
	NodLD* coadaLD = NULL;
	int nrStudenti;
	Student student1;
	char buffer[20];

	FILE* f = fopen("studenti.txt", "r");
	fscanf(f, "%d", &nrStudenti);

	for (int i = 0; i < nrStudenti; i++) {
		fscanf(f, "%d", &student1.varsta);

		fscanf(f, "%s", buffer);
		student1.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(student1.nume, buffer);

		fscanf(f, "%f", &student1.medie);

		capLD = inserareNodLD(capLD, &coadaLD, student1);
		free(student1.nume);
	}
	fclose(f);

	traversareLD(capLD);
	printf("\n-------------Traversare inversa--------------\n");
	traversareLDinvers(coadaLD);



	printf("-----------------------VECTOR--------------------------\n");
	Student* vectorStudenti = (Student*)malloc(nrStudenti * sizeof(Student));
	int nrElem = 0;
	salvareStudentiInVectorDupaMedie(capLD, vectorStudenti, &nrElem, 9.1);
	for (int i = 0; i < nrElem; i++) {
		printf("Varsta: %d\nNume: %s\nMedie: %.2f\n\n",
			vectorStudenti[i].varsta, vectorStudenti[i].nume, vectorStudenti[i].medie);
	}
	for (int i = 0; i < nrElem; i++) {
		free(vectorStudenti[i].nume);
	}
	free(vectorStudenti);

	dezalocareLD(capLD);
}*/

/*#include<malloc.h>
#include<stdio.h>

typedef struct Masina {
	int id;
	int nrUsi;
	float pret;
	char* model;
} Masina;

typedef struct NodLD {
	Masina info;
	struct NodLD* next;
	struct NodLD* prev;
} NodLD;

NodLD* initializareNodLD(Masina masina) {
	NodLD* nodNou = (NodLD*)malloc(sizeof(NodLD));
	nodNou->info.id = masina.id;
	nodNou->info.nrUsi = masina.nrUsi;
	nodNou->info.pret = masina.pret;
	nodNou->info.model = (char*)malloc((strlen(masina.model) + 1) * sizeof(char));
	strcpy(nodNou->info.model, masina.model);
	nodNou->next = NULL;
	nodNou->prev = NULL;
	return nodNou;
}

NodLD* inserareNodLD(NodLD* capLD, NodLD** coadaLD, Masina masina) {
	NodLD* nodNou = initializareNodLD(masina);
	if (capLD == NULL) {
		capLD = nodNou;
		*coadaLD = nodNou;
	}
	else {
		(*coadaLD)->next = nodNou;
		nodNou->prev = (*coadaLD);
		(*coadaLD) = nodNou;
	}
	return capLD;
}

void traversareNodLD(NodLD* capLD) {
	NodLD* temp = capLD;
	while (temp != NULL) {
		printf("\nId-ul masinii: %d\nNumarul de usi: %d\nPretul: %.2f\nModelul: %s\n\n",
			temp->info.id, temp->info.nrUsi, temp->info.pret, temp->info.model);
		temp = temp->next;
	}
}

void traversareInversaLD(NodLD* coadaLD) {
	NodLD* temp = coadaLD;
	while (temp != NULL) {
		printf("\nId-ul masinii: %d\nNumarul de usi: %d\nPretul: %.2f\nModelul: %s\n\n",
			temp->info.id, temp->info.nrUsi, temp->info.pret, temp->info.model);
		temp = temp->prev;
	}
}

void dezalocare(NodLD* capLD) {
	NodLD* temp = capLD;
	while (temp != NULL) {
		NodLD* aux = temp->next;
		free(temp->info.model);
		free(temp);
		temp = aux;
	}
}

void salvareMasiniInVectorCuPretMare(NodLD* capLD, Masina* vectMasini, int* nrElem, float prag) {
	NodLD* temp = capLD;
	while (temp != NULL) {
		if (temp->info.pret > prag) {
			vectMasini[*nrElem].id = temp->info.id;
			vectMasini[*nrElem].nrUsi = temp->info.nrUsi;
			vectMasini[*nrElem].pret = temp->info.pret;
			vectMasini[*nrElem].model = (char*)malloc((strlen(temp->info.model) + 1) * sizeof(char));
			strcpy(vectMasini[*nrElem].model, temp->info.model);
			(*nrElem)++;
		}
		temp = temp->next;
	}
}

void main() {
	NodLD* capLD = NULL;
	NodLD* coadaLD = NULL;
	Masina masina;
	int nrElementeFisier;
	char buffer[20];
	
	FILE* f = fopen("masini.txt", "r");
	fscanf(f, "%d", &nrElementeFisier);
	for (int i = 0; i < nrElementeFisier; i++) {
		fscanf(f, "%d", &masina.id);
		fscanf(f, "%d", &masina.nrUsi);
		fscanf(f, "%f", &masina.pret);
		fscanf(f, "%s", buffer);
		masina.model = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(masina.model, buffer);
		capLD = inserareNodLD(capLD, &coadaLD, masina);
		free(masina.model);
	}
	fclose(f);

	traversareNodLD(capLD);
	printf("-------------------TRANVERSARE INVERSA------------------\n");
	traversareInversaLD(coadaLD);

	printf("----------------------VECTOR----------------");
	Masina* vectMasini = (Masina*)malloc(nrElementeFisier * sizeof(Masina));
	int nrElementeVect = 0;
	salvareMasiniInVectorCuPretMare(capLD, vectMasini, &nrElementeVect, 10000);
	for (int i = 0; i < nrElementeVect; i++) {
		printf("\nId-ul masinii: %d\nNumarul de usi: %d\nPretul: %.2f\nModelul: %s\n\n",
			vectMasini[i].id, vectMasini[i].nrUsi, vectMasini[i].pret, vectMasini[i].model);
	}
	for (int i = 0; i < nrElementeVect; i++) {
		free(vectMasini[i].model);
	}
	free(vectMasini);

	

	dezalocare(capLD);
}*/

#include<stdio.h>
#include<malloc.h>

typedef struct EchipaFotbal {
	char* numeEchipa;
	int nrJucatori;
	float venit;
} EchipaFotbal;

typedef struct NodLD {
	EchipaFotbal info;
	struct NodLD* next;
	struct NodLD* prev;
} NodLD;

NodLD* initializareLD(EchipaFotbal echipa) {
	NodLD* nodNou = (NodLD*)malloc(sizeof(NodLD));

	nodNou->info.numeEchipa = (char*)malloc((strlen(echipa.numeEchipa) + 1) * sizeof(char));
	strcpy(nodNou->info.numeEchipa, echipa.numeEchipa);

	nodNou->info.nrJucatori = echipa.nrJucatori;

	nodNou->info.venit = echipa.venit;

	nodNou->next = NULL;
	nodNou->prev = NULL;

	return nodNou;
}

NodLD* inserareLD(NodLD* capLD, NodLD** coadaLD, EchipaFotbal echipa) {
	NodLD* nodNou = initializareLD(echipa);
	if (capLD == NULL) {
		capLD = nodNou;
		(*coadaLD) = capLD;
	}
	else {
			(*coadaLD)->next = nodNou;
			nodNou->prev = (*coadaLD);
			(*coadaLD) = nodNou;
	}
	return capLD;
}

void traversareLD(NodLD* capLD) {
	NodLD* temp = capLD;
	while (temp != NULL) {
		printf("Nume echipa: %s\nNumar jucatori echipa: %d\nVenit echipa: %.2f\n\n",
			temp->info.numeEchipa, temp->info.nrJucatori, temp->info.venit);
		temp = temp->next;
	}
}

void traversareInversaLD(NodLD* coadaLD) {
	NodLD* temp = coadaLD;
	while (temp != NULL) {
		printf("Nume echipa: %s\nNumar jucatori echipa: %d\nVenit echipa: %.2f\n\n",
			temp->info.numeEchipa, temp->info.nrJucatori, temp->info.venit);
		temp = temp->prev;
	}
}

void dezalocareLD(NodLD* capLD) {
	NodLD* temp = capLD;
	while (temp != NULL) {
		NodLD* aux = temp->next;
		free(temp->info.numeEchipa);
		free(temp);
		temp = aux;
	}
}

NodLD* adaugaEchipaFotbalFinal(NodLD* capLD, NodLD** coadLD, const char* numeEchipa, int nrJucatori, float venit) {
	EchipaFotbal echipa;

	echipa.numeEchipa = (char*)malloc((strlen(numeEchipa) + 1) * sizeof(char));
	strcpy(echipa.numeEchipa, numeEchipa);

	echipa.nrJucatori = nrJucatori;

	echipa.venit = venit;

	NodLD* nodNou = initializareLD(echipa);

	if (capLD == NULL) {
		nodNou = capLD;
		(*coadLD) = nodNou;
	}
	else {
		(*coadLD)->next = nodNou;
		nodNou->prev = (*coadLD);
		(*coadLD) = nodNou;
	}
	free(echipa.numeEchipa);

	return capLD;
}

NodLD* adaugareEchipaFotbalInceput(NodLD* capLD, NodLD** coadaLD, const char* numeEchipa, int nrJucatori, float venit) {
	EchipaFotbal echipa;

	echipa.numeEchipa = (char*)malloc((strlen(numeEchipa) + 1) * sizeof(char));
	strcpy(echipa.numeEchipa, numeEchipa);

	echipa.nrJucatori = nrJucatori;

	echipa.venit = venit;

	NodLD* nodNou = initializareLD(echipa);

	nodNou->prev = NULL;
	nodNou->next = capLD;

	if (capLD != NULL) {
		capLD->prev = nodNou;
	}
	else {
		(*coadaLD) = nodNou;      
	}

	capLD = nodNou;
	return capLD;

}

//calcul venit mediu

void main() {
	NodLD* capLD = NULL;
	NodLD* coadaLD = NULL;
	EchipaFotbal echipa;
	int nrElementeFisier;
	char buffer[20];

	FILE* f = fopen("EchipeFotbal.txt", "r");

	fscanf(f, "%d", &nrElementeFisier);

	for (int i = 0; i < nrElementeFisier; i++) {
		fscanf(f, "%s", buffer);
		echipa.numeEchipa = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(echipa.numeEchipa, buffer);

		fscanf(f, "%d", &echipa.nrJucatori);

		fscanf(f, "%f", &echipa.venit);

		capLD = inserareLD(capLD, &coadaLD, echipa);

		free(echipa.numeEchipa);
	}
	fclose(f);

	capLD = adaugaEchipaFotbalFinal(capLD, &coadaLD, "Farul", 44, 12091);
	capLD = adaugareEchipaFotbalInceput(capLD, &coadaLD, "CFRcluj", 33, 1265216);

	traversareLD(capLD);
	printf("---------------------TRAVERSARE INVERSA---------------------\n");
	traversareInversaLD(coadaLD);

	dezalocareLD(capLD);
}