#include<stdio.h>
#include<malloc.h>

typedef struct Student {
	int codN;
	char* nume;
	float medie;
	int varsta;
	int nrRestante;
} Student;

typedef struct NodLD {
	Student info;
	struct NodLD* next;
	struct NodLD* prev;
} NodLD;

typedef struct NodLP {
	struct NodLD* info;
	struct NodLP* next;
} NodLP;

NodLD* initializareNodLD(Student student) {
	NodLD* nodNou = (NodLD*)malloc(sizeof(NodLD));
	nodNou->info.codN = student.codN;
	nodNou->info.nume = (char*)malloc((strlen(student.nume) + 1) * sizeof(char));
	strcpy(nodNou->info.nume, student.nume);
	nodNou->info.medie = student.medie;
	nodNou->info.varsta = student.varsta;
	nodNou->info.nrRestante = student.nrRestante;
	nodNou->next = NULL;
	nodNou->prev = NULL;
	return nodNou;
}

NodLD* inserareNodLD(NodLD* capLD,NodLD** coadaLD, Student student) {
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
	return capLD;
}

void traversareLD(NodLD* capLD) {
	NodLD* temp = capLD;
	while (temp != NULL) {
		printf("\nCod: %d\nNume: %s\nMedie: %.2f\nVarsta: %d\nNumar restante: %d\n\n",
			temp->info.codN, temp->info.nume, temp->info.medie,
			temp->info.varsta, temp->info.nrRestante);
		temp = temp->next;
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

//stergerea studenti cu media cuprinsa intre doua vall date ca parametru
void stergereStudentMedieInterval(NodLD** capLD, NodLD** coadaLD, float pragMin, float pragMax) {
	NodLD* temp = *capLD;
	while (temp != NULL) {
		if (temp->info.medie >= pragMin && temp->info.medie <= pragMax) {
			NodLD* deSters = temp;
			temp = temp->next;

			if (deSters == *capLD) {
				*capLD = deSters->next;
				if (*capLD != NULL)
					(*capLD)->prev = NULL;
				else
					*coadaLD = NULL;
			}
			else if (deSters == *coadaLD) {
				*coadaLD = deSters->prev;
				if (*coadaLD != NULL)
					(*coadaLD)->next = NULL;
				else
					*capLD = NULL;
			}
			else {
				deSters->prev->next = deSters->next;
				deSters->next->prev = deSters->prev;
			}
			free(deSters->info.nume);
			free(deSters);
		}
		else {
			temp = temp->next;
		}
	}
}

NodLP* inserareLP(NodLP* capLP, NodLD* capLD) {
	NodLP* nodNou = (NodLP*)malloc(sizeof(NodLP));
	nodNou->info = capLD;
	nodNou->next = NULL;
	if (capLP == NULL) {
		return nodNou;
	}
	else {
		NodLP* temp = capLP;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nodNou;
	}
	return capLP;
}

NodLD* copiazaStudent(NodLD* lista, Student student) {
	NodLD* nod = (NodLD*)malloc(sizeof(NodLD));
	nod->info.codN = student.codN;
	nod->info.nume = (char*)malloc(strlen(student.nume) + 1);
	strcpy(nod->info.nume, student.nume);
	nod->info.medie = student.medie;
	nod->info.varsta = student.varsta;
	nod->info.nrRestante = student.nrRestante;
	nod->next = NULL;
	nod->prev = NULL;
	if (lista == NULL) {
		return nod;
	}
	NodLD* temp = lista;
	while (temp->next) {
		temp = temp->next;
	}
	temp->next = nod;
	nod->prev = temp;
	return lista;
}

NodLP* conversieListaDubluInListaDeListe(NodLD* capLD) {
	NodLD* faraRestante = NULL;
	NodLD* cuRestante = NULL;
	NodLD* temp = capLD;
	while (temp) {
		if (temp->info.nrRestante == 0) {
			faraRestante = copiazaStudent(faraRestante, temp->info);
		}
		else {
			cuRestante = copiazaStudent(cuRestante, temp->info);
		}
		temp = temp->next;
	}

	NodLP* capLP = NULL;
	capLP = inserareLP(capLP, faraRestante);
	capLP = inserareLP(capLP, cuRestante);
	return capLP;
}

void traversareLP(NodLP* capLP) {
	int i = 1;
	while (capLP != NULL) {
		printf("\nSublista %d:\n", i);
		traversareLD(capLP->info);
		capLP = capLP->next;
		i++;
	}
}

void dezalocareLP(NodLP* capLP) {
	NodLP* temp = capLP;
	while (temp != NULL) {
		NodLP* aux = temp->next;
		dezalocareLD(temp->info); 
		free(temp);               
		temp = aux;
	}
}





void main() {
	NodLD* capLD = NULL;
	NodLD* coadaLD = NULL;

	Student student;
	int nrStudenti;
	char buffer[20];

	FILE* f = fopen("studenti.txt", "r");
	fscanf(f, "%d", &nrStudenti);
	for (int i = 0; i < nrStudenti; i++) {
		fscanf(f, "%d", &student.codN);
		fscanf(f, "%s", buffer);
		student.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(student.nume, buffer);
		fscanf(f, "%f", &student.medie);
		fscanf(f, "%d", &student.varsta);
		fscanf(f, "%d", &student.nrRestante);

		capLD = inserareNodLD(capLD, &coadaLD, student);
		free(student.nume);
	}
	fclose(f);
	traversareLD(capLD);
	printf("\n---------------LISTA de LISTE------------\n");
	NodLP* capLP = conversieListaDubluInListaDeListe(capLD);
	traversareLP(capLP);
	printf("\n---------------STERGERE STUDENTI------------\n");
	stergereStudentMedieInterval(&capLD, &coadaLD, 9, 10);
	traversareLD(capLD);

	


	dezalocareLD(capLD);
	dezalocareLP(capLP);

}