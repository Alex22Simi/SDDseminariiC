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
		printf("Varsta: %d\nNume: %s\nMedie: %.2f\n\n",
			temp->info.varsta, temp->info.nume, temp->info.medie);
		temp = temp->next;
	}
}

void traversareLDinvers(NodLD* coadaLD) {
	NodLD* temp = coadaLD;
	while (temp != NULL) {
		printf("Varsta: %d\nNume: %s\nMedie: %.2f\n\n",
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

//adaugare student la sfarsit
NodLD* adaugareStudentSfarsit(NodLD* capLD, NodLD** coadaLD, int varsta, const char* nume, float medie) {
	Student student;
	
	student.varsta = varsta;
	student.nume = (char*)malloc((strlen(nume) + 1) * sizeof(nume));
	strcpy(student.nume, nume);
	student.medie = medie;

	NodLD* nodNou = initializareNodLD(student);
	if (capLD == NULL) {
		capLD = nodNou;
		(*coadaLD) = nodNou;
	}
	else {
		(*coadaLD)->next = nodNou;
		nodNou->prev = (*coadaLD);
		(*coadaLD) = nodNou;
	}
	free(student.nume);
	return capLD;
}
NodLD* adaugaStudentInceput(NodLD* capLD, NodLD** coadaLD, int varsta, const char* nume, float medie) {
	Student student;
	student.varsta = varsta;
	student.nume = (char*)malloc((strlen(nume) + 1) * sizeof(char));
	strcpy(student.nume, nume);
	student.medie = medie;

	NodLD* nodNou = initializareNodLD(student);

	nodNou->prev = NULL;
	nodNou->next = capLD;

	if (capLD == NULL) {
		capLD = nodNou;
		(*coadaLD) = nodNou;
	}
	else {
		capLD->prev = nodNou;
		capLD = nodNou;
	}
	free(student.nume);
	return capLD;
}
//calculeaza media mediilor studentilor
float mediaMediilor(NodLD* capLD) {
	NodLD* temp = capLD;
	float valoare = 0.0f;
	int contor = 0;
	while (temp != NULL) {
		valoare += temp->info.medie;
		contor++;
		temp = temp->next;
	 }
	if (valoare > 0) {
		return valoare / contor;
	}
	else {
		return 0;
	}
}

//get nume student medie cea mai mare
float medieMax(NodLD* capLD) {
	float medieMax = 0.0f;

	NodLD* temp = capLD;
	while (temp != NULL) {
		if (temp->info.medie > medieMax) {
			medieMax = temp->info.medie;
		}
		temp = temp->next;
	}
	if (medieMax > 0) {
		return medieMax;
	}
	else {
		return 0;
	}
}

//stergere student dupa nume
void stergereStudentDupaNume(NodLD** capLD, NodLD** coadaLD, const char* nume) {
	if (strcmp((*capLD)->info.nume, nume) == 0) {
		NodLD* deSters = (*capLD);
		(*capLD) = (*capLD)->next;
		if ((*capLD) != NULL) {
			(*capLD)->prev = NULL;
		}
		free(deSters->info.nume);
		free(deSters);
		return;
	}
	else {
		if (strcmp((*coadaLD)->info.nume, nume) == 0) {
			NodLD* deSters = (*coadaLD);
			(*coadaLD) = (*coadaLD)->prev;
			if ((*coadaLD) != NULL) {
				(*coadaLD)->next = NULL;
			}
			free(deSters->info.nume);
			free(deSters);
			return;
		}
		else {
			NodLD* deSters = (*capLD);
			while (deSters != NULL) {
				if (strcmp(deSters->info.nume, nume) == 0) {
					NodLD* anterior = deSters->prev;
					NodLD* urmator = deSters->next;
					anterior->next = urmator;
					urmator->prev = anterior;
					free(deSters->info.nume);
					free(deSters);
					return;
				}
				else {
					deSters = deSters->next;
				}
			}
		}
	}
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

	printf("\n-------------------ADAUGARE SFARSIT-------------------\n");
	capLD = adaugareStudentSfarsit(capLD, &coadaLD, 22, "David", 7);
	traversareLD(capLD);

	printf("\n------------------ADAUGARE INCEPUT--------------------\n");
	capLD = adaugaStudentInceput(capLD, &coadaLD, 20, "Bogdan", 10);
	traversareLD(capLD);

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

	float medie;
	medie = mediaMediilor(capLD);
	printf("\nMedia mediilor: %.2f\n", medie);

	float medieMaxima;
	medieMaxima = medieMax(capLD);
	printf("\nMedia maxima a unui student este: %.2f\n", medieMaxima);

	printf("\n-------------------------------STERGERE STUDENT---------------------------\n");
	stergereStudentDupaNume(&capLD, &coadaLD, "Bogdan");
	traversareLD(capLD);

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

//adaugare Masina la sfarsit
NodLD* adaugaMasinaLaSfarsit(NodLD* capLD, NodLD** coadaLD, int id, int nrUsi, float pret, const char* model) {
	Masina masina;

	masina.id = id;
	masina.nrUsi = nrUsi;
	masina.pret = pret;
	masina.model = (char*)malloc((strlen(model) + 1) * sizeof(char));
	strcpy(masina.model, model);

	NodLD* nodNou = initializareNodLD(masina);
	if (capLD == NULL) {
		capLD = nodNou;
		(*coadaLD) = nodNou;
	}
	else {
		(*coadaLD)->next = nodNou;
		nodNou->prev = (*coadaLD);
		(*coadaLD) = nodNou;
	}
	free(masina.model);
	return capLD;
}

//adaugare Masina la inceput
NodLD* adaugaMasinaInceput(NodLD* capLD, NodLD** coadLD, int id, int nrUsi, float pret, const char* model) {
	Masina masina;

	masina.id = id;
	masina.nrUsi = nrUsi;
	masina.pret = pret;
	masina.model = (char*)malloc((strlen(model) + 1) * sizeof(char));
	strcpy(masina.model, model);

	NodLD* nodNou = initializareNodLD(masina);
	
	nodNou->prev = NULL;
	nodNou->next = capLD;

	if (capLD != NULL) {
		capLD->prev = nodNou;
	}
	else {
		(*coadLD) = nodNou;
	}
	free(masina.model);
	capLD = nodNou;
	return capLD;
}

//sa se se faca media usilor masinilor
float mediaUsiMasini(NodLD* capLD) {
	int valoare = 0;
	int contor = 0;

	NodLD* temp = capLD;
	while (temp != NULL) {
		valoare += temp->info.nrUsi;
		contor++;
		temp = temp->next;
	}
	if (valoare > 0) {
		return valoare / contor;
	}
	else {
		return 0;
	}
}

//sa se afiseze numele modelului cel mai scump
char* afiseazaNumeModelScump(NodLD* capLD) {
	float pretMax = 0.0;
	char* numeModel = NULL;
	NodLD* temp = capLD;
	while (temp != NULL) {
		if (temp->info.pret > pretMax) {
			numeModel = temp->info.model;
			pretMax = temp->info.pret;
		}
		temp = temp->next;
	}
	if (pretMax > 0) {
		return numeModel;
	}
	else {
		return "Nu exista masini.";
	}
}

//stergere masina dupa nume
void stergereMasinaDupaNume(NodLD** capLD, NodLD** coadaLD, const char* modelMasina) {
	if (strcmp((*capLD)->info.model, modelMasina) == 0) {
		NodLD* deSters = (*capLD);
		(*capLD) = (*capLD)->next;
		if ((*capLD) != NULL) {
			(*capLD)->prev = NULL;
		}
		free(deSters->info.model);
		free(deSters);
		return;
	}
	else {
		NodLD* deSters = (*coadaLD);
		if (strcmp((*coadaLD)->info.model, modelMasina) == 0) {
			(*coadaLD) = (*coadaLD)->prev;
			if ((*coadaLD) != NULL) {
				(*coadaLD)->next = NULL;
			}
			free(deSters->info.model);
			free(deSters);
			return;
		}
		else {
			NodLD* deSters = (*capLD);
			while (deSters != NULL) {
				if (strcmp(deSters->info.model, modelMasina) == 0) {
					NodLD* anterior = deSters->prev;
					NodLD* urmator = deSters->next;
					anterior->next = urmator;
					urmator->prev = anterior;
					free(deSters->info.model);
					free(deSters);
					return;
				}
				else {
					deSters = deSters->next;
				}
			}
		}
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

	printf("\n-----------------ADAUGARE SFARSIT----------------------\n");
	capLD = adaugaMasinaLaSfarsit(capLD, &coadaLD, 222, 2, 1010, "Cielo");
	traversareNodLD(capLD);

	printf("\n------------------ADAUGARE INCEPUT---------------------\n");
	capLD = adaugaMasinaInceput(capLD, &coadaLD, 9900, 3, 56767, "Duster");
	traversareNodLD(capLD);

	float medie;
	medie = mediaUsiMasini(capLD);
	printf("Media usilor este %.2f\n", medie);

	char* nume;
	nume = afiseazaNumeModelScump(capLD);
	printf("Modelul cel mai scump este: %s", nume);

	printf("\n-----------------------------STERGERE MASINA DUPA NUME-------------------------\n");
	stergereMasinaDupaNume(&capLD, &coadaLD, "Logan");
	traversareNodLD(capLD);

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
		capLD = nodNou;
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
	free(echipa.numeEchipa);
	capLD = nodNou;
	return capLD;

}

//sa se arate nr mediu de jucatori ale echipelor
float medieNrJucatori(NodLD* capLD) {
	int nrJuc = 0;
	int contor = 0;

	NodLD* temp = capLD;

	while (temp) {
		nrJuc += temp->info.nrJucatori;
		contor++;
		temp = temp->next;
	}
	if (nrJuc > 0) {
		return nrJuc / contor;
	}
	else {
		return 0;
	}
}

//sa se arate numele echipei cu venitul cel mai mare
char* arataNumeEchipaScumpa(NodLD* capLD) {
	char* numeEchipa = NULL;
	float venitMax = 0.0;

	NodLD* temp = capLD;

	while (temp != NULL) {
		if (temp->info.venit > venitMax) {
			venitMax = temp->info.venit;
			numeEchipa = temp->info.numeEchipa;
		}
		temp = temp->next;
	}
	if (venitMax > 0) {
		return numeEchipa;
	}
	else {
		return NULL;
	}
}

//stergere echipa de fotbal dupa nr de jucatori
void stergereEchipaDupaNrJucatori(NodLD** capLD, NodLD** coadaLD, int nrJucatori) {
	if ((*capLD)->info.nrJucatori == nrJucatori) {
		NodLD* deSters = (*capLD);
		(*capLD) = (*capLD)->next;
		if ((*capLD) != NULL) {
			(*capLD)->prev = NULL;
		}
		free(deSters->info.numeEchipa);
		free(deSters);
		return;
	}
	else {
		if ((*coadaLD)->info.nrJucatori == nrJucatori) {
			NodLD* deSters = (*coadaLD);
			(*coadaLD) = (*coadaLD)->prev;
			if ((*coadaLD) != NULL) {
				(*coadaLD)->next = NULL;
			}
			free(deSters->info.numeEchipa);
			free(deSters);
			return;
		}
		else {
			NodLD* deSters = (*capLD);
			while (deSters != NULL) {
				if (deSters->info.nrJucatori == nrJucatori) {
					NodLD* anterior = deSters->prev;
					NodLD* urmator = deSters->next;
					anterior->next = urmator;
					urmator->prev = anterior;
					free(deSters->info.numeEchipa);
					free(deSters);
					return;
				}
				else {
					deSters = deSters->next;
				}
			}
		}
	}
}

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

	traversareLD(capLD);
	printf("---------------------TRAVERSARE INVERSA---------------------\n");
	traversareInversaLD(coadaLD);

	printf("\n------------------------ADAUGARE SFARSIT----------------------\n");
	capLD = adaugaEchipaFotbalFinal(capLD, &coadaLD, "Farul", 44, 12091);
	traversareLD(capLD);

	printf("\n------------------------ADAUGARE INCEPUT----------------------\n");
	capLD = adaugareEchipaFotbalInceput(capLD, &coadaLD, "CFRcluj", 33, 1265216);
	traversareLD(capLD);

	float medieJuc;
	medieJuc = medieNrJucatori(capLD);
	printf("\nMedia jucatorilor este: %.2f", medieJuc);

	char* numeEchip;
	numeEchip = arataNumeEchipaScumpa(capLD);
	printf("\nNumeleEchipei cea mai scumpa este: %s", numeEchip);

	printf("\n----------------------------STERGERE ECHIPA DUPA NR JUCATORI------------------\n");
	stergereEchipaDupaNrJucatori(&capLD, &coadaLD, 20);
	traversareLD(capLD);

	dezalocareLD(capLD);
}