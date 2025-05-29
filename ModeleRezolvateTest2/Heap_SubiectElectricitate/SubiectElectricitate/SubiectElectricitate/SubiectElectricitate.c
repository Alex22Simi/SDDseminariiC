/*#include<stdio.h>
#include<malloc.h>

typedef enum CanalIncasare {
	ELECTRONIC,
	GHISEU
} CanalIncasare;

typedef struct Factura {
	char* codClient;
	unsigned int valoare; //%u numeric fara semn
	char* dataEmiterii;
	char* dataScadenta;
	CanalIncasare canal;
} Factura;

typedef struct Heap {
	Factura* vect;
	int nrElem;
} Heap;

typedef struct NodCoada {
	Factura info;
	struct NodCoada* next;
} NodCoada;

typedef struct NodLista {
	Factura info;
	struct NodLista* next;
} NodLista;


void filtrare(Heap h, int index) {
	int indexRad = index;
	int indexSt = 2 * index + 1;
	int indexDr = 2 * index + 2;

	if (indexSt < h.nrElem && strcmp(h.vect[indexSt].dataScadenta, h.vect[indexRad].dataScadenta) < 0) {
		indexRad = indexSt;
	} 
	if (indexDr < h.nrElem && strcmp(h.vect[indexDr].dataScadenta, h.vect[indexRad].dataScadenta) < 0) {
		indexRad = indexDr;
	}
	if (indexRad != index) {
		Factura aux = h.vect[index];
		h.vect[index] = h.vect[indexRad];
		h.vect[indexRad] = aux;

		filtrare(h, indexRad);
	}
}

Heap inserare(Heap h, Factura factura) {
	Factura* vectNou = (Factura*)malloc((h.nrElem + 1) * sizeof(Factura));
	for (int i = 0; i < h.nrElem; i++) {
		 vectNou[i] = h.vect[i];
	}
	h.nrElem++;
	vectNou[h.nrElem - 1] = factura;
	free(h.vect);

	h.vect = vectNou;

	for (int i = (h.nrElem - 1) / 2; i >= 0; i--) {
		filtrare(h, i);
	}

	return h;
	
}

Heap extragere(Heap h, Factura* extrasa) {
	Factura* vectNou = (Factura*)malloc((h.nrElem - 1) * sizeof(Factura));
	Factura aux = h.vect[0];
	h.vect[0] = h.vect[h.nrElem - 1];
	h.vect[h.nrElem - 1] = aux;
	*extrasa = h.vect[h.nrElem - 1];
	h.nrElem--;
	
	for (int i = 0; i < h.nrElem; i++) {
		vectNou[i] = h.vect[i];
	}

	free(h.vect);

	h.vect = vectNou;


	for (int i = (h.nrElem - 1) / 2; i >= 0; i--) {
		filtrare(h, i);
	}
	return h;
}

void afisare(Heap h) {
	for (int i = 0; i < h.nrElem; i++) {
		printf("Cod: %s, Valoare: %u, Data emiterii: %s, Data scadenta: %s, Canal: %s\n",
			h.vect[i].codClient, h.vect[i].valoare,
			h.vect[i].dataEmiterii, h.vect[i].dataScadenta,
			h.vect[i].canal == ELECTRONIC ? "Electronic":  "Ghiseu");
	}
}

void dezalocare(Heap h) {
	for (int i = 0; i < h.nrElem; i++) {
		free(h.vect[i].codClient);
		free(h.vect[i].dataEmiterii);
		free(h.vect[i].dataScadenta);
	}
	free(h.vect);
}

//Ex2.
//sa se scrie functia 
//pt actualizarea canalului de incasare al unei facturi
//daca o factura devine scadenta(extragere din min-heap)
//aceasta este eliminata din heap si este
//plasata intr o sturctura de date dinamica
//secventiala FIFO
void put(NodCoada** prim, NodCoada** ultim, Factura f) {
	NodCoada* nou = (NodCoada*)malloc(sizeof(NodCoada));
	nou->info.codClient = (char*)malloc((strlen(f.codClient) + 1) * sizeof(char));
	strcpy(nou->info.codClient, f.codClient);

	nou->info.valoare = f.valoare;

	nou->info.dataEmiterii = (char*)malloc((strlen(f.dataEmiterii) + 1) * sizeof(char));
	strcpy(nou->info.dataEmiterii, f.dataEmiterii);

	nou->info.dataScadenta = (char*)malloc((strlen(f.dataScadenta) + 1) * sizeof(char));
	strcpy(nou->info.dataScadenta, f.dataScadenta);

	nou->info.canal = f.canal;

	nou->next = NULL;

	if (*prim == NULL || *ultim == NULL) {
		*prim  = nou;
		*ultim = nou;
	}
	else {
		(*ultim)->next = nou;
		*ultim = nou;
	}
}

void actualizareCanalIncasare(Heap* h, NodCoada** prim, NodCoada** ultim) {
	Factura extrasa;
	while (h->nrElem > 0) {
		*h = extragere(*h, &extrasa);
		put(prim, ultim, extrasa);

		free(extrasa.codClient);
		free(extrasa.dataEmiterii);
		free(extrasa.dataScadenta);
	}
}

void afisareCoada(NodCoada* prim) {
	while (prim) {
		printf("Cod: %s, Valoare: %u, Data emiterii: %s, Data scadenta: %s, Canal: %s\n",
			prim->info.codClient, prim->info.valoare,
			prim->info.dataEmiterii, prim->info.dataScadenta,
			prim->info.canal == ELECTRONIC ? "Electronic" : "Ghiseu");
		prim = prim->next;
	}
}
void dezalocareCoada(NodCoada* prim) {
	while (prim) {
		NodCoada* temp = prim;
		prim = prim->next;
		free(temp->info.codClient);
		free(temp->info.dataEmiterii);
		free(temp->info.dataScadenta);
		free(temp);
	}
}

//EX. 3
//functia pt salvarea intr o lista simpla a fac scadente
//prin consultarea structurii FIFO
void inserareListaFinal(NodLista** cap, Factura f) {
	NodLista* nou = (NodLista*)malloc(sizeof(NodLista));
	nou->info.codClient = (char*)malloc(strlen(f.codClient) + 1);
	strcpy(nou->info.codClient, f.codClient);

	nou->info.valoare = f.valoare;

	nou->info.dataEmiterii = (char*)malloc(strlen(f.dataEmiterii) + 1);
	strcpy(nou->info.dataEmiterii, f.dataEmiterii);

	nou->info.dataScadenta = (char*)malloc(strlen(f.dataScadenta) + 1);
	strcpy(nou->info.dataScadenta, f.dataScadenta);

	nou->info.canal = f.canal;
	nou->next = NULL;

	if (*cap == NULL)
		*cap = nou;
	else {
		NodLista* temp = *cap;
		while (temp->next)
			temp = temp->next;
		temp->next = nou;
	}
}

void salveazaInLista(NodCoada* coada, NodLista** lista) {
	while (coada != NULL) {
		inserareListaFinal(lista, coada->info);
		coada = coada->next;
	}
}

void afisareLista(NodLista* cap) {
	while (cap) {
		printf("Cod: %s, Valoare: %u, Emisa: %s, Scadenta: %s, Canal: %s\n",
			cap->info.codClient, cap->info.valoare,
			cap->info.dataEmiterii, cap->info.dataScadenta,
			cap->info.canal == ELECTRONIC ? "Electronic" : "Ghiseu");
		cap = cap->next;
	}
}

void dezalocareLista(NodLista* cap) {
	while (cap) {
		NodLista* temp = cap;
		cap = cap->next;
		free(temp->info.codClient);
		free(temp->info.dataEmiterii);
		free(temp->info.dataScadenta);
		free(temp);
	}
}



void main() {
	Heap h;
	h.nrElem = 0;
	h.vect = NULL;

	Factura f1;
	f1.codClient = (char*)malloc(strlen("CL001") + 1);
	strcpy(f1.codClient, "CL001");
	f1.valoare = 200;
	f1.dataEmiterii = (char*)malloc(strlen("2024-01-01") + 1);
	strcpy(f1.dataEmiterii, "2024-01-01");
	f1.dataScadenta = (char*)malloc(strlen("2024-05-20") + 1);
	strcpy(f1.dataScadenta, "2024-05-20");
	f1.canal = ELECTRONIC;
	h = inserare(h, f1);

	Factura f2;
	f2.codClient = (char*)malloc(strlen("CL002") + 1);
	strcpy(f2.codClient, "CL002");
	f2.valoare = 150;
	f2.dataEmiterii = (char*)malloc(strlen("2024-02-01") + 1);
	strcpy(f2.dataEmiterii, "2024-02-01");
	f2.dataScadenta = (char*)malloc(strlen("2024-03-15") + 1);
	strcpy(f2.dataScadenta, "2024-03-15");
	f2.canal = GHISEU;
	h = inserare(h, f2);

	
	Factura facturaFisier;
	int nrFacturiFisier;
	char buffer[50];

	FILE* f = fopen("factura.txt", "r");
	fscanf(f, "%d", &nrFacturiFisier);

	for (int i = 0; i < nrFacturiFisier; i++) {
		fscanf(f, "%s", buffer);
		facturaFisier.codClient = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(facturaFisier.codClient, buffer);

		fscanf(f, "%u", &facturaFisier.valoare);

		fscanf(f, "%s", buffer);
		facturaFisier.dataEmiterii = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(facturaFisier.dataEmiterii, buffer);

		fscanf(f, "%s", buffer);
		facturaFisier.dataScadenta = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(facturaFisier.dataScadenta, buffer);

		fscanf(f, "%s", buffer);
		if (strcmp(buffer, "ELECTRONIC") == 0) {
			facturaFisier.canal = ELECTRONIC;
		}
		else {
			facturaFisier.canal = GHISEU;
		}

		h = inserare(h, facturaFisier);

	}
	fclose(f);

	for (int i = (h.nrElem - 1) / 2; i >= 0; i--) {
		filtrare(h, i);
	}

	afisare(h);

	printf("--------------------EX. 2---------------\n");
	NodCoada* prim = NULL;
	NodCoada* ultim = NULL;

	actualizareCanalIncasare(&h, &prim, &ultim);
	printf("Factura extrase din heap si puse in FIFO:\n");
	afisareCoada(prim);
	printf("--------------------EX. 3---------------\n");
	NodLista* listaScadente = NULL;
	salveazaInLista(prim, &listaScadente);
	afisareLista(listaScadente);


	dezalocareLista(listaScadente);



	dezalocareCoada(prim);

	dezalocare(h);
}*/


#include<stdio.h>
#include<malloc.h>

typedef enum CanalInscriere {

} CanalInscriere;

typedef struct Factura {
	char* codClient;
	unsigned int valoare;
	char* dataEmiterii;
	char* dataScadenta;

} Factura;

void main() {

}