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
}

