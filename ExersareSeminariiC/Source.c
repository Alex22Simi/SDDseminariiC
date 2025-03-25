/*
//Exersare seminar 1
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

#include<stdio.h>
#include<malloc.h>

typedef struct
{
	int* cod;
	char* denumire;
	float pret;
	float cantitate;
} produs;

void citireVectorProduse(produs* vp, int nr)
{
	char buffer[20];
	for (int i = 0; i < nr; i++)
	{
		printf("Cod=");
		vp[i].cod = (int*)malloc(sizeof(int));
		scanf("%d", vp[i].cod);
		printf("Denumire=");
		scanf("%s", buffer);
		vp[i].denumire = (char*)malloc((strlen(buffer) + 1) *
			sizeof(char));
		strcpy(vp[i].denumire, buffer);
		printf("Pret=");
		scanf("%f", &vp[i].pret);
		printf("Cantitate=");
		scanf("%f", &vp[i].cantitate);
	}
}

void afisareVectorProduse(produs* vp, int nr)
{
	for (int i = 0; i < nr; i++)
		printf("\nCod = %d, Denumire = %s, Pret = %5.2f, Cantitate = %5.2f",
			*(vp[i].cod), vp[i].denumire, vp[i].pret, vp[i].cantitate);
}

void dezalocareVectorProduse(produs* vp, int nr)
{
	for (int i = 0; i < nr; i++)
	{
		free(vp[i].cod);
		free(vp[i].denumire);
	}
	free(vp);
}

void citireMatrice(float** mat, char** denumiri, int nr)
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
}

void main()
{
	int nrProd;
	printf("Nr. produse = ");
	scanf("%d", &nrProd);
	//produs* vp = (produs*)malloc(nrProd * sizeof(produs));
	/*citireVectorProduse(vp, nrProd);
	afisareVectorProduse(vp, nrProd);
	dezalocareVectorProduse(vp, nrProd);*/

	float** mat = (float**)malloc(nrProd * sizeof(float*));
	for (int i = 0; i < nrProd; i++)
		mat[i] = (float*)malloc(3 * sizeof(float));
	char** denumiri = (char**)malloc(nrProd * sizeof(char*));
	citireMatrice(mat, denumiri, nrProd);
	afisareMatrice(mat, denumiri, nrProd);
	dezalocareMatrice(mat, denumiri, nrProd);
}