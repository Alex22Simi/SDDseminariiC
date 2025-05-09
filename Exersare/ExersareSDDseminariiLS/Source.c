/*
#include<stdio.h>
#include<malloc.h>

typedef struct {
	int* cod;
	char* denumire;
	float pret;
	float cantitate;
}Produs;


void citireVectorProduse(Produs* vector, int nrElemente) {
	char buffer[20];
	for (int i = 0; i < nrElemente; i++) {
		printf("Cod=");
		vector[i].cod = (int*)malloc(sizeof(int));
		scanf("%d", vector[i].cod);
		printf("Denumire=");
		scanf("%s", buffer);
		vector[i].denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(vector[i].denumire, buffer);
		printf("Pret=");
		scanf("%f", &vector[i].pret);
		printf("Cantitate=");
		scanf("%f", &vector[i].cantitate);
	}
}

void afisareVectorProduse(Produs* p, int nrElemente) {
	for (int i = 0; i < nrElemente; i++) {
		printf("Cod %d \n Denumire %s \n Pret %.2f \n Cantitate %.2f \n",
			*p[i].cod, p[i].denumire, p[i].pret, p[i].cantitate);
	}
}

void dezalocareVectorProduse(Produs* vector, int nrElemente) {
	for (int i = 0; i < nrElemente; i++) {
		free(vector[i].cod);
		free(vector[i].denumire);
	}
	free(vector);
}



/*void citireMatrice(float** mat, char** denumiri, int nr)
{
	char buffer[20];
	for (int i = 0; i < nr; i++)
	{
		printf("Cod=");
		scanf("%f", &mat[i][0]);
		printf("Denumire = ");
		scanf("%s", buffer);
		denumiri[i] = (char*)malloc((strlen(buffer) + 1) *
			sizeof(char));
		strcpy(denumiri[i], buffer);
		printf("Pret=");
		scanf("%f", &mat[i][1]);
		printf("Cantitate=");
		scanf("%f", &mat[i][2]);
	}
}

void afisareMatrice(float** mat, char** denumiri, int nr)
{
	for (int i = 0; i < nr; i++)
		printf("\nCod = %5.2f, Denumire = %s, Pret = %5.2f, Cantitate = %5.2f",
			mat[i][0], denumiri[i], mat[i][1], mat[i][2]);
}

void dezalocareMatrice(float** mat, char** denumiri, int nr)
{
	for (int i = 0; i < nr; i++)
	{
		free(mat[i]);
		free(denumiri[i]);
	}
	free(mat);
	free(denumiri);
}*/

/*void citireMatrice(float** mat, char** denumire, int nrElem) {
	char buffer[20];
	for (int i = 0; i < nrElem; i++) {
		printf("Cod=");
		scanf("%f", &mat[i][0]);
		printf("Denumire=");
		scanf("%s", buffer);
		denumire[i] = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy(denumire[i], buffer);
		printf("Pret=");
		scanf("%f", &mat[i][1]);
		printf("Cantitate=");
		scanf("%f", &mat[i][2]);
	}
}

void afisareMatrice(float** mat, char** denumiri, int nrElem) {
	for (int i = 0; i < nrElem; i++) {
		printf("Cod %f Denumire %s Pret %f Cantitate %f", mat[i][0], denumiri[i], mat[i][1], mat[i][2]);
	}
}

void dezalocareMatrice(float** mat, char** denumire, int nrElem) {
	for (int i = 0; i < nrElem; i++) {
		free(mat[i]);
		free(denumire[i]);
	}
	free(mat);
	free(denumire);
}

void citireMatrice(float** mat, char** denumire, int nr) {
	char buffer[20];
	for (int i = 0; i < nr; i++) {
		printf("Cod=");
		scanf("%f", &mat[i][0]);
		printf("Denumire=");
		scanf("%s", buffer);
		denumire[i] = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy(denumire[i], buffer);
		printf("Pret=");
		scanf("%f", &mat[i][1]);
		printf("Cantitate=");
		scanf("%f", &mat[i][2]);
	}
}

void afisareMatrice(float** mat, char** denumire, int nr) {
	for (int i = 0; i < nr; i++) {
		printf("\nCod = %f Denumire = %s Pret = %f Cantitate = %f", mat[i][0], denumire[i], mat[i][1], mat[i][2]);
	}
}

void dezalocareMatrice(float** mat, char** denumiri, int nr) {
	for (int i = 0; i < nr; i++) {
		free(mat[i]);
		free(denumiri[i]);
	}
	free(mat);
	free(denumiri);
}

int main() {
	int nrProd;
	printf("Nr. produse = ");
	scanf("%d", &nrProd);
	//produs* vp = (produs*)malloc(nrProd * sizeof(produs));
	/*citireVectorProduse(vp, nrProd);
	afisareVectorProduse(vp, nrProd);
	dezalocareVectorProduse(vp, nrProd);

	float** mat = (float**)malloc(nrProd * sizeof(float*));
	for (int i = 0; i < nrProd; i++)
		mat[i] = (float*)malloc(3 * sizeof(float));
	char** denumiri = (char**)malloc(nrProd * sizeof(char*));
	citireMatrice(mat, denumiri, nrProd);
	afisareMatrice(mat, denumiri, nrProd);
	dezalocareMatrice(mat, denumiri, nrProd);

}*/

/*#include<stdio.h>
#include<malloc.h>

typedef struct Masina{
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
} Masina;

typedef struct NodLS {
	Masina info;
	struct NodLS* next;
} NodLS;

NodLS* initializareNodLS(Masina m) {
	NodLS* nou = (NodLS*)malloc(sizeof(NodLS));
	nou->info.id = m.id;
	nou->info.nrUsi = m.nrUsi;
	nou->info.pret = m.pret;
	nou->info.model = (char*)malloc((strlen(m.model) + 1) * sizeof(char));
	strcpy(nou->info.model, m.model);
	nou->info.numeSofer = (char*)malloc((strlen(m.numeSofer) + 1) * sizeof(char));
	strcpy(nou->info.numeSofer, m.numeSofer);
	nou->info.serie = m.serie;
	nou->next = NULL;
	return nou;
}

NodLS* inserareNodLS(NodLS* capLS, Masina m) {
	NodLS* nou = initializareNodLS(m);
	if (capLS == NULL) {
		capLS = nou;
	}
	else {
		NodLS* temp = capLS;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nou;
	}
	return capLS;
}

void traversareLista(NodLS* capLS) {
	NodLS* temp = capLS;
	while (temp != NULL) {
		printf("\nID masina: %d\n Numar usi: %d\n Pret: %.2f\n Model: %s\n Nume Sofer: %s\n Serie: %c\n",
			temp->info.id, temp->info.nrUsi, temp->info.pret, temp->info.model, temp->info.numeSofer, temp->info.serie);
		temp = temp->next;
	}
}

void dezalocareLS(NodLS* capLS) {
	NodLS* temp = capLS;
	while (temp != NULL) {
		NodLS* aux = temp->next;
		free(temp->info.model);
		free(temp->info.numeSofer);
		free(temp);
		temp = aux;
	}
}

void adaugareInVectorMasiniCuPretMare(NodLS* capLS, Masina* vectorMasini, int* nrElemente, float prag) {
	NodLS* temp = capLS;
	while (temp) {
		if (temp->info.pret > prag) {
			vectorMasini[*nrElemente].id = temp->info.id;

			vectorMasini[*nrElemente].nrUsi = temp->info.nrUsi;

			vectorMasini[*nrElemente].pret = temp->info.pret;

			vectorMasini[*nrElemente].model = (char*)malloc((strlen(temp->info.model) + 1) * sizeof(char));
			strcpy(vectorMasini[*nrElemente].model, temp->info.model);

			vectorMasini[*nrElemente].numeSofer = (char*)malloc((strlen(temp->info.numeSofer) + 1) * sizeof(char));
			strcpy(vectorMasini[*nrElemente].numeSofer);

			vectorMasini[*nrElemente].serie = temp->info.serie;
			(*nrElemente)++;
		}
		temp = temp->next;
	}
}

float pretMediuMasini(NodLS* capLS) {
	float pret = 0.0f;
	int nrMasini = 0;

	NodLS* temp = capLS;

	while (temp != NULL) {
		pret += temp->info.pret;
		nrMasini++;

		temp = temp->next;
	}
	if (nrMasini > 0) {
		return pret / nrMasini;
	}
	else {
		return 0;
	}
}

//calculeaza pretul masinilor unui sofer
float pretMasiniSofer(NodLS* capLS, const char* sofer) {
	NodLS* temp = capLS;
	float suma = 0.0f;

	while (temp) {
		if (strcmp(temp->info.numeSofer, sofer) == 0) {
			suma += temp->info.pret;
			
		}
		temp = temp->next;
	}
	if (suma == 0.0f) {
		printf("Soferul %s nu are nicio masina inregistrata.\n", sofer);
	}
	return suma;
}

//de aici
//sa se afiseze nr de usi la cea mai scumpa masina
int getNrUsiMasinaScumpa(NodLS* capLS) {
	NodLS* temp = capLS;
	float pretMaxim = 0;
	int nrUsi = 0;

	while (temp) {
		if (temp->info.pret > pretMaxim) {
			pretMaxim = temp->info.pret;
			nrUsi = temp->info.nrUsi;
			
		}
		temp = temp->next;
	}
	if (nrUsi > 0) {
		return nrUsi;
	}
	else {
		return 0;
	}
}



//sa se afiseze modelul celei mai scumpe masini
void afiseazaModelulMasiniiScumpe(NodLS* capLS) {
	if (capLS == NULL) {
		return;
	}
	NodLS* temp = capLS;
	float pretScump = temp->info.pret;
	Masina* modelMax = &temp->info;

	temp = temp->next;

	while (temp != NULL) {
		if (temp->info.pret > pretScump) {
			pretScump = temp->info.pret;
			modelMax = &temp->info;
		}
		temp = temp->next;
	}

	printf("\nMasina in valoare de %.2f este cea mai scumpa si are modelul %s", modelMax->pret, modelMax->model);
}

//stergere in LS


void stergereMasiniDupaNumeProprietar(NodLS** capLS, const char* numeProprietar) {
	NodLS* temp = *capLS;
	NodLS* anterior = NULL;

	while (temp != NULL) {
		
		if (strcmp(temp->info.numeSofer, numeProprietar) == 0) {
			NodLS* nodDeSters = temp;
			//daca primul nod respecta conditia
			if (anterior == NULL) {
				*capLS = temp->next;
				temp = *capLS;
			}

			if (anterior != NULL) {
				//daca un nod din mijloc sau final respecta conditia
				anterior->next = temp->next;
				temp = temp->next;
			}

			free(nodDeSters->info.numeSofer);
			free(nodDeSters->info.model);
			free(nodDeSters);
		}
		else {
			anterior = temp;
			temp = temp->next;
		}
	}

	printf("\nNodul s-a sters cu succes!");
}




void main() {
	int nrMasini;
	Masina masina1;
	NodLS* capLS = NULL;
	char buffer[20];
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrMasini);

	for (int i = 0; i < nrMasini; i++) {
		fscanf(f, "%d", &masina1.id);

		fscanf(f, "%d", &masina1.nrUsi);

		fscanf(f, "%f", &masina1.pret);

		fscanf(f, "%s", buffer);
		masina1.model = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(masina1.model, buffer);

		fscanf(f, " %s", buffer);
		masina1.numeSofer = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(masina1.numeSofer, buffer);

		fscanf(f, " %c", &masina1.serie); 
		capLS = inserareNodLS(capLS, masina1);
	}
	fclose(f);

	traversareLista(capLS);

	printf("---------------------------VECTOR---------------------------");
	Masina* vectMasini = (Masina*)malloc(nrMasini * sizeof(Masina));
	int nrElemente = 0;
	adaugareInVectorMasiniCuPretMare(capLS, vectMasini, &nrElemente, 9000);
	for (int i = 0; i < nrElemente; i++) {
		printf("\nID masina : % d\n Numar usi : % d\n Pret : % .2f\n Model : % s\n Nume Sofer : % s\n Serie : % c\n",
			vectMasini[i].id, vectMasini[i].nrUsi, vectMasini[i].pret, vectMasini[i].model, vectMasini[i].numeSofer, vectMasini[i].serie);
	}
	for (int i = 0; i < nrElemente; i++) {
		free(vectMasini[i].model);
		free(vectMasini[i].numeSofer);
	}
	free(vectMasini);

	float valoare;
	valoare = pretMediuMasini(capLS);
	printf("\nValoare medie a masinilor este de: %2.f", valoare);

	float suma;
	suma = pretMasiniSofer(capLS, "Ionescu");
	printf("\nPretul masinilor lui Ionescu au fost: %.2f EURO.", suma);

	int nrUsi;
	nrUsi = getNrUsiMasinaScumpa(capLS);
	printf("\nMasina cea mai scumpa are un numar de %d usi", nrUsi);

	afiseazaModelulMasiniiScumpe(capLS);

	stergereMasiniDupaNumeProprietar(&capLS, "Ionescu");
	traversareLista(capLS);

	dezalocareLS(capLS);
}*/

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
}NodLS;

NodLS* initializareNodLS(Student student) {
	NodLS* nodNou = (NodLS*)malloc(sizeof(NodLS));
	nodNou->info.varsta = student.varsta;
	nodNou->info.nume = (char*)malloc((strlen(student.nume) + 1) * sizeof(char));
	strcpy(nodNou->info.nume, student.nume);
	nodNou->info.medie = student.medie;
	nodNou->next = NULL;
	return nodNou;
}


NodLS* inserareNodLS(NodLS* capLS, Student student) {
	NodLS* nodNou = initializareNodLS(student);
	if (capLS == NULL) {
		capLS = nodNou;
	}
	else {
		NodLS* temp = capLS;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nodNou;
	}
	return capLS;
}

void traversareLS(NodLS* capLS) {
	NodLS* temp = capLS;
	while (temp != NULL) {
		printf("Varsta: %d\nNume: %s\nMedie: %.2f\n\n\n",
			temp->info.varsta, temp->info.nume, temp->info.medie);
		temp = temp->next;
	}
}




void salvareStudentiInVectorDupaMedie(NodLS* capLS, Student* vectorStudenti, int* nrElemente, float mediePrag) {
	NodLS* temp = capLS;
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

float mediaMedilorStudentilor(NodLS* capLS) {
	float medie = 0.0f;
	int nrStudenti = 0;
	NodLS* temp = capLS;

	while (temp) {
		medie += temp->info.medie;
		nrStudenti++;
		temp = temp->next;
	}
	if (nrStudenti > 0) {
		return medie / nrStudenti;
	}
	else {
		return 0;
	}
}


//care este cea a mai medie a studentilor de aceeasi varsta, sa se afiseze media si nume studentului
void medieMareDupaVarsta(NodLS* capLS, int varsta) {
	NodLS* temp = capLS;
	float maxMedie = 0.0f;
	Student* studentMax = NULL;

	while (temp) {
		if (temp->info.varsta == varsta) {
			if (temp->info.medie > maxMedie) {
				maxMedie = temp->info.medie;
				studentMax = &temp->info;
			}
		}
		temp = temp->next;
	}

	if (studentMax == NULL) {
		printf("Nu exista studenti cu varsta %d\n", varsta);
	}
	else {
		printf("Studentul cu numele %s are cea mai mare medie %.2f dintre toti studentii care au varsta de %d ani.\n",
			studentMax->nume, studentMax->medie, varsta);
	}
}

//sa se faca suma mediei studentilor cu varsta data
float sumaMedii(NodLS* capLS, int varsta) {
	NodLS* temp = capLS;
	float sumaMedii = 0;
	while (temp) {
		if (temp->info.varsta == varsta) {
			sumaMedii += temp->info.medie;
		}
		temp = temp->next;
	}
	if (sumaMedii == 0) {
		printf("Nu exista student cu varsta de %d ani", varsta);
	} else{
		return sumaMedii;
	}
}

//sa se afiseze varsta studentului cu cea mai mare medie
int afiseazaVarstaStudentuluiCuMediaMare(NodLS* capLS) {
	NodLS* temp = capLS;
	float medieMax = 0.0f;
	int varsta = 0;

	while (temp != NULL) {
		if (temp->info.medie > medieMax) {
			medieMax = temp->info.medie;
			varsta = temp->info.varsta;
		}
		temp = temp->next;
	}
	if (varsta > 0) {
		return varsta;
	}
	else {
		return 0;
	}
}

//sa se afiseze numele studentului cu cea mai mare medie

void afiseazaNumeStudentMedieMare(NodLS* capLS) {
	if (capLS == NULL) {
		return;
	} 
	NodLS* temp = capLS;
	float medieMax = temp->info.medie;
	Student* studentMax = &temp->info;

	temp = temp->next;
	while (temp != NULL) {
		if (temp->info.medie > medieMax) {
			medieMax = temp->info.medie;
			studentMax = &temp->info;
		}
		temp = temp->next;
	}
	printf("Studentul cu media cea mai mare: %.2f se numeste %s", studentMax->medie, studentMax->nume);
}



void dezalocareLS(NodLS* capLS) {
	NodLS* temp = capLS;

	while (temp != NULL) {
		NodLS* aux = temp->next;

		if (temp->info.nume != NULL)
			free(temp->info.nume);

		free(temp);
		temp = aux;
	}
}

//stergere student cu media data
void stergereStudentCuMediaData(NodLS** capLS, float medieStud) {
	NodLS* temp = *capLS;
	NodLS* anterior = NULL;

	while (temp != NULL) {
		if (temp->info.medie == medieStud) {
			NodLS* nodDeSters = temp;
			if (anterior == NULL) {
				*capLS = temp->next;
				temp = *capLS;
			}
			if(anterior != NULL) {
				anterior->next = temp->next;
				temp = temp->next;
			}
			free(nodDeSters->info.nume);
			free(nodDeSters);
		}
		else {
			anterior = temp;
			temp = temp->next;
		}
	}
	printf("\nNodul a fost sters cu succes!");
}



void main() {
	NodLS* capLS = NULL;
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

		capLS = inserareNodLS(capLS, student1);
		//free(student1.nume);
	}
	fclose(f);

	traversareLS(capLS);



	printf("-----------------------VECTOR--------------------------\n");
	Student* vectorStudenti = (Student*)malloc(nrStudenti * sizeof(Student));
	int nrElem = 0;
	salvareStudentiInVectorDupaMedie(capLS, vectorStudenti, &nrElem, 9.1);
	for (int i = 0; i < nrElem; i++) {
		printf("Varsta: %d\nNume: %s\nMedie: %.2f\n\n",
			vectorStudenti[i].varsta, vectorStudenti[i].nume, vectorStudenti[i].medie);
	}
	for (int i = 0; i < nrElem; i++) {
		free(vectorStudenti[i].nume);
	}
	free(vectorStudenti);

	float medie;
	medie = mediaMedilorStudentilor(capLS);
	printf("Media medilor studentilor este: %.2f\n", medie);

	medieMareDupaVarsta(capLS, 21);

	float sumaMedie;
	sumaMedie = sumaMedii(capLS, 21);
	printf("Suma mediilor Studentilor cu varsta data este %.2f", sumaMedie);

	int varstaMedieMare;
	varstaMedieMare = afiseazaVarstaStudentuluiCuMediaMare(capLS);
	printf("\nStudentul care are cea mai mare medie, are varsta de: %d\n", varstaMedieMare);

	afiseazaNumeStudentMedieMare(capLS);

	stergereStudentCuMediaData(&capLS, 8.9);
	traversareLS(capLS);

	dezalocareLS(capLS);
}*/

#include<stdio.h>
#include<malloc.h>

typedef struct EchipaFotbal {
	char* nume;
	int nrJucatori;
	float venit;
	char* antrenor;
} EchipaFotbal;

typedef struct NodLS {
	EchipaFotbal info;
	struct NodLS* next;
} NodLS;

NodLS* initializareNodLS(EchipaFotbal echipaFotbal) {
	NodLS* nodNou = (NodLS*)malloc(sizeof(NodLS));
	nodNou->info.nume = (char*)malloc((strlen(echipaFotbal.nume) + 1) * sizeof(char));
	strcpy(nodNou->info.nume, echipaFotbal.nume);
	nodNou->info.nrJucatori = echipaFotbal.nrJucatori;
	nodNou->info.venit = echipaFotbal.venit;
	nodNou->info.antrenor = (char*)malloc((strlen(echipaFotbal.antrenor) + 1) * sizeof(char));
	strcpy(nodNou->info.antrenor, echipaFotbal.antrenor);
	nodNou->next = NULL;
	return nodNou;
}

NodLS* inserareNodLS(NodLS* capLS, EchipaFotbal echipaFotbal) {
	NodLS* nodNou = initializareNodLS(echipaFotbal);

	if (capLS == NULL) {
		capLS = nodNou;
	}
	else {
		NodLS* temp = capLS;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nodNou;
	}
	return capLS;
}

void traversareLS(NodLS* capLS) {
	NodLS* temp = capLS;
	while (temp != NULL) {
		printf("Numele echipei de fotbal: %s\nNumarul de jucatori echipa: %d\nVenituri echipa: %.2f\nAntrenorul echipei: %s\n\n",
			temp->info.nume, temp->info.nrJucatori, temp->info.venit, temp->info.antrenor);
		temp = temp->next;
	}
}

void dezalocareNodLS(NodLS* capLS) {
	NodLS* temp = capLS;
	while (temp != NULL) {
		NodLS* aux = temp->next;
		free(temp->info.nume);
		free(temp->info.antrenor);
		free(temp);
		temp = aux;
	}
}

void adaugareInVectorEchipeCuMultiJucatori(NodLS* capLS, EchipaFotbal* vectorEchipeFotbal, int* nrElemente, float prag) {
	NodLS* temp = capLS;
	while(temp != NULL) {
		if (temp->info.nrJucatori >= prag) {
			vectorEchipeFotbal[*nrElemente].nume = (char*)malloc((strlen(temp->info.nume) + 1) * sizeof(char));
			strcpy(vectorEchipeFotbal[*nrElemente].nume, temp->info.nume);

			vectorEchipeFotbal[*nrElemente].nrJucatori = temp->info.nrJucatori;

			vectorEchipeFotbal[*nrElemente].venit = temp->info.venit;

			vectorEchipeFotbal[*nrElemente].antrenor = (char*)malloc((strlen(temp->info.antrenor) + 1) * sizeof(char));
			strcpy(vectorEchipeFotbal[*nrElemente].antrenor, temp->info.antrenor);

			(*nrElemente)++;
		}
		temp = temp->next;
	}
}

float venitMediuEchipeDeFotbal(NodLS* capLS) {
	int nrEchipe = 0;
	float suma = 0.0f;

	NodLS* temp = capLS;
	while (temp) {
		suma += temp->info.venit;
		nrEchipe++;
		temp = temp->next;
	}
	if (nrEchipe > 0) {
		return suma / nrEchipe;
	}
	else {
		return 0;
	}
}

//sa se afiseze numarul total de jucatori al echipelor care au acelasi antrenor
int numarJucatoriTotalPerAntrenor(NodLS* capLS, const char* numeAntrenor) {
	NodLS* temp = capLS;
	int nrJucatoriTotal = 0;
	
	while (temp) {
		if (strcmp(temp->info.antrenor, numeAntrenor) == 0) {
			nrJucatoriTotal += temp->info.nrJucatori;
		}
		temp = temp->next;
	}
	if (nrJucatoriTotal == 0) {
		return 0;
	}
	else {
		return nrJucatoriTotal;
	}
}
//afiseaza nr de jucatorii ale celei mai scumpe echipe
void afiseazaNrJucatoriEchipaScumpa(NodLS* capLS) {
	if (capLS == NULL) {
		return;
	}
	NodLS* temp = capLS;
	float venitMax = temp->info.venit;
	EchipaFotbal* echipaScumpa = &temp->info;

	temp = temp->next;
	while (temp) {
		if (temp->info.venit > venitMax) {
			venitMax = temp->info.venit;
			echipaScumpa = &temp->info;
		}
		temp = temp->next;
	}
	printf("\nNumarul de jucatori ale celei mai scumpe echipe  este de %d si are un venit de %.2f", echipaScumpa->nrJucatori,
		echipaScumpa->venit);
}

//afiseaza nume echipa cea mai scumpa
void afisareNumeEchipaCeaMaiScumpa(NodLS* capLS) {
	if (capLS == NULL) {
		return;
	}
	NodLS* temp = capLS;
	float venitMax = temp->info.venit;
	EchipaFotbal* echipaScumpa = &temp->info;

	temp = temp->next;
	while (temp) {
		if (temp->info.venit > venitMax) {
			venitMax = temp->info.venit;
			echipaScumpa = &temp->info;
		}
		temp = temp->next;
	}
	printf("\nNumele celei mai scumpe echipe este %s si are un venit de %.2f", echipaScumpa->nume, echipaScumpa->venit);
}
//stergere echipa dupa nume antrenor
void stergereEchipaDupaAntrenor(NodLS** capLS, const char* numeAntrenor) {
	NodLS* temp = *capLS;
	NodLS* anterior = NULL;

	while (temp != NULL) {
		if (strcmp(temp->info.antrenor, numeAntrenor) == 0) {
			NodLS* deSters = temp;
			if (anterior == NULL) {
				*capLS = temp->next;
				temp = temp->next;
			}
			if (anterior != NULL) {
				anterior->next = temp->next;
				temp = temp->next;
			}
			free(deSters->info.nume);
			free(deSters->info.antrenor);
			free(deSters);
		}
		else {
			anterior = temp;
			temp = temp->next;
		}
	}
	printf("\nNodul a fost sters cu succes!\n");
}

//stergere echipa de fotbal cu cu cei mai multi jucatori
void stergereEchipaNrMareDeFotbalisti(NodLS** capLS) {
	NodLS* temp = *capLS;
	NodLS* anterior = NULL;
	int nrJucatoriMax = temp->info.nrJucatori;

	while (temp != NULL) {
		if (temp->info.nrJucatori > nrJucatoriMax) {
			nrJucatoriMax = temp->info.nrJucatori;
		}
		temp = temp->next;
	}

	temp = (*capLS);

	while (temp != NULL) {
		if (temp->info.nrJucatori == nrJucatoriMax) {
			NodLS* nodDeSters = temp;
			if (anterior == NULL) {
				*capLS = temp->next;
				temp = *capLS;
			}
			else {
				anterior->next = temp->next;
				temp = temp->next;
			}
			free(nodDeSters->info.nume);
			free(nodDeSters->info.antrenor);
			free(nodDeSters);
		}
		else {
			anterior = temp;
			temp = temp->next;
		}
	}
	printf("\nEchipa cu cei mai multi jucatori nu mai are voie sa joace!\n");
}

void main() {
	EchipaFotbal echipaFotbal;
	NodLS* capLS = NULL;
	char buffer[20];
	int nrJucatori;

	FILE* f = fopen("EchipeFotbal.txt", "r");
	fscanf(f, "%d", &nrJucatori);

	for (int i = 0; i < nrJucatori; i++) {
		fscanf(f, "%s", buffer);
		echipaFotbal.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(echipaFotbal.nume, buffer);

		fscanf(f, "%d", &echipaFotbal.nrJucatori);

		fscanf(f, "%f", &echipaFotbal.venit);

		fscanf(f, "%s", buffer);
		echipaFotbal.antrenor = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(echipaFotbal.antrenor, buffer);

		capLS = inserareNodLS(capLS, echipaFotbal);

		free(echipaFotbal.nume);
		free(echipaFotbal.antrenor);
	}
	fclose(f);

	traversareLS(capLS);

	printf("-------------------VECTOR----------------");
	EchipaFotbal* vectorEchipe = (EchipaFotbal*)malloc(nrJucatori * sizeof(EchipaFotbal));
	int nrElemente = 0;
	adaugareInVectorEchipeCuMultiJucatori(capLS, vectorEchipe, &nrElemente, 21);

	for (int i = 0; i < nrElemente; i++) {
		printf("\nNumele echipei: %s\nNumarul de jucatori: %d\nVenitul: %.2f\nAntrenor: %s\n\n",
			vectorEchipe[i].nume, vectorEchipe[i].nrJucatori, vectorEchipe[i].venit, vectorEchipe[i].antrenor);
	}
	for (int i = 0; i < nrElemente; i++) {
		free(vectorEchipe[i].nume);
		free(vectorEchipe[i].antrenor);
	}
	free(vectorEchipe);

	float medie = 0;
	medie = venitMediuEchipeDeFotbal(capLS);
	printf("Venitul mediu al echipelor este de: %.2f EURO.", medie);

	int nrJucPerAntrenor;
	nrJucPerAntrenor = numarJucatoriTotalPerAntrenor(capLS, "Sumudica");
	printf("\nAntrenorul dat are %d jucatori", nrJucPerAntrenor);

	afiseazaNrJucatoriEchipaScumpa(capLS);
	afisareNumeEchipaCeaMaiScumpa(capLS);

	stergereEchipaDupaAntrenor(&capLS, "Charalampous");
	traversareLS(capLS);

	stergereEchipaNrMareDeFotbalisti(&capLS);
	traversareLS(capLS);

	dezalocareNodLS(capLS);

}

/*#include<stdio.h>
#include<malloc.h>

typedef struct EchipaNationale {
	char* nume;
	int mondialeCastigate;
	int continentaleCastigate;
	char* antrenor;
} EchipaNationala;

typedef struct NodLS {
	EchipaNationala info;
	struct NodLS* next;
} NodLS;

NodLS* initializareNodLS(EchipaNationala echipaNationala) {
	NodLS* nodNou = (NodLS*)malloc(sizeof(NodLS));
	nodNou->info.nume = (char*)malloc((strlen(echipaNationala.nume) + 1) * sizeof(char));
	strcpy(nodNou->info.nume, echipaNationala.nume);
	nodNou->info.mondialeCastigate = echipaNationala.mondialeCastigate;
	nodNou->info.continentaleCastigate = echipaNationala.continentaleCastigate;
	nodNou->info.antrenor = (char*)malloc((strlen(echipaNationala.antrenor) + 1) * sizeof(char));
	strcpy(nodNou->info.antrenor, echipaNationala.antrenor);
	nodNou->next = NULL;
	return nodNou;
}

NodLS* inserareNodLS(NodLS* capLS, EchipaNationala echipaNationala) {
	NodLS* nodNou = initializareNodLS(echipaNationala);
	if (capLS == NULL) {
		capLS = nodNou;
	}
	else {
		NodLS* temp = capLS;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nodNou;
	}
	return capLS;
}

void traversareLS(NodLS* capLS) {
	NodLS* temp = capLS;
	while (temp != NULL) {
		printf("Numele Nationalei: %s\nMondiale castigate: %d\nContinentale castigate: %d\nAntrenorul echipei nationale: %s\n\n",
			temp->info.nume, temp->info.mondialeCastigate, temp->info.continentaleCastigate, temp->info.antrenor);

		temp = temp->next;
	}
	
}

void dezalocareLS(NodLS* capLS) {
	NodLS* temp = capLS;
	while (temp != NULL) {
		NodLS* aux = temp->next;
		free(temp->info.nume);
		free(temp->info.antrenor);
		free(temp);
		temp = aux;
	}
}

void salvareInVectorEchipeCuMondialeMulte(NodLS* capLS, EchipaNationala* vectorEchipe, int* nrElemente, float prag) {
	NodLS* temp = capLS;
	while (temp != NULL) {
		if (temp->info.mondialeCastigate >= prag) {
			vectorEchipe[*nrElemente].nume = (char*)malloc((strlen(temp->info.nume) + 1) * sizeof(char));
			strcpy(vectorEchipe[*nrElemente].nume, temp->info.nume);

			vectorEchipe[*nrElemente].mondialeCastigate = temp->info.mondialeCastigate;

			vectorEchipe[*nrElemente].continentaleCastigate = temp->info.continentaleCastigate;

			vectorEchipe[*nrElemente].antrenor = (char*)malloc((strlen(temp->info.antrenor) + 1) * sizeof(char));
			strcpy(vectorEchipe[*nrElemente].antrenor, temp->info.antrenor);

			(*nrElemente)++;
		}
		temp = temp->next;
	}
}

float calculeazaValoareaMedieAMondialelorCastigate(NodLS* capLS) {
	int nrEchipe = 0;
	int nrMondiale = 0;
	NodLS* temp = capLS;

	while (temp) {
		nrMondiale += temp->info.mondialeCastigate;
		nrEchipe++;
		temp = temp->next;
	}
	if (nrEchipe > 0) {
		return nrMondiale / nrEchipe;
	}
	else {
		return 0;
	}
}



//sa se calculeze nr de campionate continentale castigate ale unui antrenor
int nrCampionateContinentalePerAntrenor(NodLS* capLS, const char* antrenor) {
	NodLS* temp = capLS;
	int nrContinentale = 0;
	while (temp) {
		if (strcmp(temp->info.antrenor, antrenor) == 0) {
			nrContinentale += temp->info.continentaleCastigate;
		}
		temp = temp->next;
	}
	if (nrContinentale > 0) {
		return nrContinentale;
	}
	else {
		return 0;
	}
}

//afiseaza nr de continentale castigate ale echipei cu cele mai multe mondiale
void afiseazaContinentalePentruCeleMaiMulteMondiale(NodLS* capLS) {
	if (capLS == NULL) {
		return;
	}
	NodLS* temp = capLS;
	int nrMondialeMax = temp->info.mondialeCastigate;
	EchipaNationala* echipaNationalaMax = &temp->info;

	temp = temp->next;

	while (temp) {
		if (temp->info.mondialeCastigate > nrMondialeMax) {
			nrMondialeMax = temp->info.mondialeCastigate;
			echipaNationalaMax = &temp->info;
		}
		temp = temp->next;
	}
	printf("\nNationala %s cu cele mai multe mondiale castigate %d are un numar de %d continentale castigate.",
		echipaNationalaMax->nume, echipaNationalaMax->mondialeCastigate, echipaNationalaMax->continentaleCastigate);
}

//stergere echipa nationala dupa antrenor
void stergereEchipaDupaNume(NodLS** capLS, const char* numeAntrenor) {
	NodLS* temp = *capLS;
	NodLS* anterior = NULL;

	while (temp != NULL) {
		if (strcmp(temp->info.antrenor, numeAntrenor) == 0) {
			NodLS* nodDeSters = temp;
			if (anterior == NULL) {
				*capLS = temp->next;
				temp = *capLS;
			}
			if (anterior != NULL) {
				anterior->next = temp->next;
				temp = temp->next;
			}
			free(nodDeSters->info.nume);
			free(nodDeSters->info.antrenor);
			free(nodDeSters);
		}
		else {
			anterior = temp;
			temp = temp->next;
		}
	}
	printf("\nNodul a fost sters cu succes!\n");

}

//stergere echipa de fotbal cu cele mai multe continentale
void stergereEchipaNrContinentaleMare(NodLS** capLS) {
	NodLS* temp = *capLS;
	NodLS* anterior = NULL;
	float nrContMax = temp->info.continentaleCastigate;

	while (temp != NULL) {
		if (temp->info.continentaleCastigate > nrContMax) {
			nrContMax = temp->info.continentaleCastigate;
		}
		temp = temp->next;
	}

	temp = (*capLS);

	while (temp != NULL) {
		if (temp->info.continentaleCastigate == nrContMax) {
			NodLS* nodDeSters = temp;
			if (anterior == NULL) {
				*capLS = temp->next;
				temp = *capLS;
			}
			else {
				anterior->next = temp->next;
				temp = temp->next;
			}
			free(nodDeSters->info.nume);
			free(nodDeSters->info.antrenor);
			free(nodDeSters);
		}
		else {
			anterior = temp;
			temp = temp->next;
		}
	}
	printf("\nEchipa cu celele mai multe continentale castigate nu mai are voie sa joace!\n");
}

void main() {
	NodLS* capLS = NULL;
	int nrEchipe;
	EchipaNationala echipaNationala;
	char buffer[20];

	FILE* f = fopen("EchipaNationalaFotbal.txt", "r");
	fscanf(f, "%d", &nrEchipe);

	for (int i = 0; i < nrEchipe; i++) {
		fscanf(f, "%s", buffer);
		echipaNationala.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(echipaNationala.nume, buffer);

		fscanf(f, "%d", &echipaNationala.mondialeCastigate);

		fscanf(f, "%d", &echipaNationala.continentaleCastigate);

		fscanf(f, "%s", buffer);
		echipaNationala.antrenor = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(echipaNationala.antrenor, buffer);

		capLS = inserareNodLS(capLS, echipaNationala);
		free(echipaNationala.nume);
		free(echipaNationala.antrenor);
	}
	fclose(f);

	traversareLS(capLS);

	printf("----------------------------VECTOR-----------------------\n");
	EchipaNationala* vectorEchipe = (EchipaNationala*)malloc(nrEchipe *  sizeof(EchipaNationala));
	int nrElem = 0;

	salvareInVectorEchipeCuMondialeMulte(capLS, vectorEchipe, &nrElem, 4);
	for (int i = 0; i < nrElem; i++) {
		printf("Numele Nationalei: %s\nMondiale castigate: %d\nContinentale castigate: %d\nAntrenorul echipei nationale: %s\n\n",
			vectorEchipe[i].nume, vectorEchipe[i].mondialeCastigate, vectorEchipe[i].continentaleCastigate, vectorEchipe[i].antrenor);
	}
	for (int i = 0; i < nrElem; i++) {
		free(vectorEchipe[i].nume);
		free(vectorEchipe[i].antrenor);
	}
	free(vectorEchipe);

	float medie;
	medie = calculeazaValoareaMedieAMondialelorCastigate(capLS);
	printf("Valoarea medie a mondialelor castigate este: %.f", medie);

	int nrContCastPerAntrenor;
	nrContCastPerAntrenor = nrCampionateContinentalePerAntrenor(capLS, "Lucescu");
	printf("\nAntrenorul dat a castigat un numar de %d campionate continentale.", nrContCastPerAntrenor);

	afiseazaContinentalePentruCeleMaiMulteMondiale(capLS);

	stergereEchipaDupaNume(&capLS, "Lucescu");
	traversareLS(capLS);

	stergereEchipaNrContinentaleMare(&capLS);
	traversareLS(capLS);

	dezalocareLS(capLS);
}*/

/*#include<stdio.h>
#include<malloc.h>

typedef struct CampionatFotbal {
	char* numeCampionat;
	int nrEchipe;
	float valoarePremiu;
} CampionatFotbal;

typedef struct NodLS {
	CampionatFotbal info;
	struct NodLS* next;
}NodLS;

NodLS* initalizareNodLS(CampionatFotbal campionat) {
	NodLS* nodNou = (NodLS*)malloc(sizeof(NodLS));

	nodNou->info.numeCampionat = (char*)malloc((strlen(campionat.numeCampionat) + 1) * sizeof(char));
	strcpy(nodNou->info.numeCampionat, campionat.numeCampionat);

	nodNou->info.nrEchipe = campionat.nrEchipe;

	nodNou->info.valoarePremiu = campionat.valoarePremiu;

	nodNou->next = NULL;

	return nodNou;
}

NodLS* inserareNodLS(NodLS* capLS, CampionatFotbal campionat) {
	NodLS* nodNou = initalizareNodLS(campionat);

	if (capLS == NULL) {
		capLS = nodNou;
	}
	else {
		NodLS* temp = capLS;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nodNou;
	}
	return capLS;
}

void traversareLS(NodLS* capLS) {
	NodLS* temp = capLS;
	while (temp != NULL) {
		printf("Nume campionat: %s\nNumar de echipe: %d\nPremiul in valoare de %.2f EURO\n\n",
			temp->info.numeCampionat, temp->info.nrEchipe, temp->info.valoarePremiu);
		temp = temp->next;
	}
}

void dezalocareLS(NodLS* capLS) {
	NodLS* temp = capLS;
	while (temp != NULL) {
		NodLS* aux = temp->next;
		free(temp->info.numeCampionat);
		free(temp);
		temp = aux;
	}
}

void selectareInVectorCampionateScumpe(NodLS* capLS, CampionatFotbal* vectorCampionate, int* nrElemente, float prag) {
	NodLS* temp = capLS;
	while (temp) {
		if (temp->info.valoarePremiu >= prag) {
			vectorCampionate[*nrElemente].numeCampionat = (char*)malloc((strlen(temp->info.numeCampionat) + 1) * sizeof(char));
			strcpy(vectorCampionate[*nrElemente].numeCampionat, temp->info.numeCampionat);

			vectorCampionate[*nrElemente].nrEchipe = temp->info.nrEchipe;

			vectorCampionate[*nrElemente].valoarePremiu = temp->info.valoarePremiu;

			(*nrElemente)++;
		}
		temp = temp->next;
	}
}

float calculeazaValoareMediePremiu(NodLS* capLS) {
	int nrCampionate = 0;
	float suma = 0.0f;

	NodLS* temp = capLS;
	while (temp != NULL) {
		suma += temp->info.valoarePremiu;
		nrCampionate++;
		temp = temp->next;
	}
	if (nrCampionate > 0) {
		return suma / nrCampionate;
	}
	else {
		return 0;
	}
}


//sa se calculeze valoarea premiilor din ligiile care au acelasi nr de echipe, cu cel dat in param
float calculPremiuPeNrJucator(NodLS* capLS, int nrEchipe) {
	NodLS* temp = capLS;
	float premiu = 0.0f;
	while (temp != NULL) {
		if (temp->info.nrEchipe == nrEchipe) {
			premiu += temp->info.valoarePremiu;
		}
		temp = temp->next;
	}
	if (premiu > 0) {
		return premiu;
	}
	else {
		return 0;
	}
}

//sa se afiseze nr de echipe din campionatul cu premiul cel mai mare
void afiseazaNrEchipeDinCampionatPremiuCelMaiMare(NodLS* capLS) {
	if (capLS == NULL) {
		return;
	}
	NodLS* temp = capLS;
	float premiuMax = temp->info.valoarePremiu;
	CampionatFotbal* capionatFotbalMax = &temp->info;

	temp = temp->next;

	while (temp) {
		if (temp->info.valoarePremiu > premiuMax) {
			premiuMax = temp->info.valoarePremiu;
			capionatFotbalMax = &temp->info;
		}
		temp = temp->next;
	}
	printf("\nCampionatul %s are premiul cel mai mare %.2f si are un numar de %d echipe", capionatFotbalMax->numeCampionat,
		capionatFotbalMax->valoarePremiu, capionatFotbalMax->nrEchipe);
}

//stergere campionat cu premiul cel mai mic
void stergereCampionatPremiuMic(NodLS** capLS) {
	NodLS* temp = *capLS;
	NodLS* anterior = NULL;
	float premiuMin = temp->info.valoarePremiu;

	while (temp != NULL) {
		if (temp->info.valoarePremiu <= premiuMin) {
			premiuMin = temp->info.valoarePremiu;
		}
		temp = temp->next;
	}

	temp = *capLS;

	while (temp != NULL) {

		if (temp->info.valoarePremiu == premiuMin) {
			NodLS* nodDeSters = temp;


			if (anterior == NULL) {
				*capLS = temp->next;
				temp = *capLS;
			}
			if (anterior != NULL) {
				anterior->next = temp->next;
				temp = temp->next;
			}
			free(nodDeSters->info.numeCampionat);
			free(nodDeSters);
		}
		else {
			anterior = temp;
			temp = temp->next;
		}
	}
	printf("\nCampionatul cu premiul cel mai mic a fost sters!\n");
}





int main() {
	NodLS* capLS = NULL;
	CampionatFotbal campionat;
	int nrCampionate;
	char buffer[20];

	FILE* f = fopen("CampionatFotbal.txt", "r");

	fscanf(f, "%d", &nrCampionate);

	for (int i = 0; i < nrCampionate; i++) {
		fscanf(f, "%s", buffer);
		campionat.numeCampionat = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(campionat.numeCampionat, buffer);

		fscanf(f, "%d", &campionat.nrEchipe);

		fscanf(f, "%f", &campionat.valoarePremiu);

		capLS = inserareNodLS(capLS, campionat);

		free(campionat.numeCampionat);
	}
	fclose(f);

	traversareLS(capLS);

	printf("----------------------VECTOR--------------------\n");
	CampionatFotbal* vectorCampionate = (CampionatFotbal*)malloc(nrCampionate * sizeof(CampionatFotbal));
	int nrElemente = 0;
	selectareInVectorCampionateScumpe(capLS, vectorCampionate, &nrElemente, 220000);
	for (int i = 0; i < nrElemente; i++) {
		printf("Nume campionat: %s\nNumar de echipe: %d\nPremiul in valoare de %.2f EURO\n\n",
			vectorCampionate[i].numeCampionat, vectorCampionate[i].nrEchipe, vectorCampionate[i].valoarePremiu);
	}
	for (int i = 0; i < nrElemente; i++) {
		free(vectorCampionate[i].numeCampionat);
	}
	free(vectorCampionate);

	float valoare;
	valoare = calculeazaValoareMediePremiu(capLS);
	printf("Valoare medie a premilor este de: %.2f EURO.\n", valoare);
	
	float premiu;
	premiu = calculPremiuPeNrJucator(capLS, 20);
	printf("Liga cu numarul dat de echipe, ofera un premiu de %.2f", premiu);

	afiseazaNrEchipeDinCampionatPremiuCelMaiMare(capLS);
	stergereCampionatPremiuMic(&capLS);
	traversareLS(capLS);

	dezalocareLS(capLS);

	return 0;
}*/

