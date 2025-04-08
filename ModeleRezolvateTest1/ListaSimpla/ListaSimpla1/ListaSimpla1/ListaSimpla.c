#include <stdio.h>
#include <malloc.h>

typedef struct Agentie {
	int cod;
	char* numeAgentie;
} Agentie;

typedef struct NodLS {
	Agentie info;
	struct NodLS* next;
} NodLS;

typedef struct NodLP {
	struct NodLS* info;
	struct NodLP* next;
} NodLP;

NodLS* initializareNodLS(Agentie agentie) {
	NodLS* nodNou = (NodLS*)malloc(sizeof(NodLS));
	nodNou->info.cod = agentie.cod;
	nodNou->info.numeAgentie = (char*)malloc((strlen(agentie.numeAgentie) + 1) * sizeof(char));
	strcpy(nodNou->info.numeAgentie, agentie.numeAgentie);
	nodNou->next = NULL;
	return nodNou;
}

NodLS* inserareNodLS(NodLS* capLS, Agentie agentie) {
	NodLS* nodNou = initializareNodLS(agentie);
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
		printf("\nCod: %d\nNume agentie: %s\n", 
			temp->info.cod, temp->info.numeAgentie);
		temp = temp->next;
	}
}

void dezalocareLS(NodLS* capLS) {
	NodLS* temp = capLS;
	while (temp != NULL) {
		NodLS* aux = temp->next;
		free(temp->info.numeAgentie);
		free(temp);
		temp = aux;
	}
}

void salvareListaDeListeInFisier(NodLP* capLP, const char* numeFisier) {
	FILE* f = fopen(numeFisier, "w");
	NodLP* temp = capLP;
	int i = 1;
	while (temp != NULL) {
		fprintf(f, "Sublista %d:\n", i);
		NodLS* tempLS = temp->info;
		while (tempLS != NULL) {
			fprintf(f, "Cod: %d, Nume: %s\n", tempLS->info.cod, tempLS->info.numeAgentie);
			tempLS = tempLS->next;
		}
		fprintf(f, "\n");
		temp = temp->next;
		i++;
	}
	fclose(f);
}


//stergerea agentiilor cu coduri impare
//agentiile cu coduri pare se vor salva intr-u fisier text
void stergereAgentiiCoduriImpareSalvarePare(NodLS** capLS, const char* numeFisier) {
	FILE* f = fopen(numeFisier, "w");
	NodLS* temp = (*capLS);
	NodLS* anterior = NULL;

	while (temp != NULL) {
		if (temp->info.cod % 2 != 0) {
			NodLS* deSters = temp;
			if (anterior == NULL) {
				(*capLS) = temp->next;
				temp = (*capLS);
			}
			else {
				anterior->next = temp->next;
				temp = temp->next;
			}
			free(deSters->info.numeAgentie);
			free(deSters);
		}
		else {
			fprintf(f, "\nCod: %d\nNume agentie: %s\n",
				temp->info.cod, temp->info.numeAgentie);
			anterior = temp;
			temp = temp->next;
		}
	}
	fclose(f);
}

NodLP* inserareLP(NodLP* capLP, NodLS* capLS) {
	NodLP* nodNou = (NodLP*)malloc(sizeof(NodLP));
	nodNou->info = capLS;
	nodNou->next = NULL;
	if (capLP == NULL) {
		capLP = nodNou;
	}
	else {
		NodLP* temp = capLP;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nodNou;
	}
	return capLP;
}

void transversareLP(NodLP* capLP) {
	NodLP* temp = capLP;
	int i = 0;
	while (temp != NULL) {	
		printf("\nSublista: %d.", i);
		traversareLS(temp->info);

		temp = temp->next;
		i++;
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

NodLP* conversieListaSimplaInListaDeListe(NodLS* capLS) {
	NodLS* capLSPare = NULL;
	NodLS* capLSImpare = NULL;

	NodLS* temp = capLS;
	while (temp != NULL) {
		if (temp->info.cod % 2 == 0)
			capLSPare = inserareNodLS(capLSPare, temp->info);
		else
			capLSImpare = inserareNodLS(capLSImpare, temp->info);
		temp = temp->next;
	}

	NodLP* capLP = NULL;
	capLP = inserareLP(capLP, capLSPare);
	capLP = inserareLP(capLP, capLSImpare);

	return capLP;
}

void main() {
	NodLS* capLS = NULL;
	Agentie agentie;
	int nrAgentii;
	char buffer[20];

	FILE* f = fopen("agentie.txt", "r");
	fscanf(f, "%d", &nrAgentii);
	for (int i = 0; i < nrAgentii; i++) {
		fscanf(f, "%d", &agentie.cod);

		fscanf(f, "%s", buffer);
		agentie.numeAgentie = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(agentie.numeAgentie, buffer);

		capLS = inserareNodLS(capLS, agentie);

		free(agentie.numeAgentie);
	}
	NodLP* capLP = conversieListaSimplaInListaDeListe(capLS);
	salvareListaDeListeInFisier(capLP, "agentieOutput.txt");
	traversareLS(capLS);
	printf("/-----------------LISTA DE LISTE-----------------\n");
	transversareLP(capLP);

	stergereAgentiiCoduriImpareSalvarePare(&capLS, "agentieCoduriPareOutput.txt");


	

	salvareListaDeListeInFisier(capLP, "agentieOutput.txt");

	

	dezalocareLP(capLP);
	dezalocareLS(capLS);
}

