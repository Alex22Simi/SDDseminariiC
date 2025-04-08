#include<stdio.h>
#include<malloc.h>

typedef struct Persoana{
	int varsta;
	char* nume;
	int ziNastere;
	int lunaNastere;
} Persoana;

typedef struct NodCoada {
	Persoana info;
	struct NodCoada* next;
} NodCoada;

typedef struct NodStiva {
    Persoana info;
    struct NodStiva* next;
} NodStiva;

void put(NodCoada** prim, NodCoada** ultim, Persoana p) {
    NodCoada* nodNou = (NodCoada*)malloc(sizeof(NodCoada));
    nodNou->info.varsta = p.varsta;
    nodNou->info.nume = (char*)malloc(strlen(p.nume) + 1);
    strcpy(nodNou->info.nume, p.nume);
    nodNou->info.ziNastere = p.ziNastere;
    nodNou->info.lunaNastere = p.lunaNastere;
    nodNou->next = NULL;

    if (*prim == NULL) {
        *prim = *ultim = nodNou;
    }
    else {
        (*ultim)->next = nodNou;
        *ultim = nodNou;
    }
}

void push(NodStiva** varf, Persoana p) {
    NodStiva* nodNou = (NodStiva*)malloc(sizeof(NodStiva));
    nodNou->info.varsta = p.varsta;
    nodNou->info.nume = (char*)malloc(strlen(p.nume) + 1);
    strcpy(nodNou->info.nume, p.nume);
    nodNou->info.ziNastere = p.ziNastere;
    nodNou->info.lunaNastere = p.lunaNastere;
    nodNou->next = *varf;
    *varf = nodNou;
}


void afisareCoada(NodCoada* prim) {
    NodCoada* temp = prim;
    while (temp != NULL) {
        printf("Nume: %s | Varsta: %d | Data nasterii: %d %d\n",
            temp->info.nume, temp->info.varsta,
            temp->info.ziNastere, temp->info.lunaNastere);
        temp = temp->next;
    }
}
void impletireCozi(NodCoada* prim1, NodCoada* prim2, NodCoada** primRez, NodCoada** ultimRez) {
    while (prim1 != NULL || prim2 != NULL) {
        if (prim1 != NULL) {
            put(primRez, ultimRez, prim1->info);
            prim1 = prim1->next;
        }
        if (prim2 != NULL) {
            put(primRez, ultimRez, prim2->info);
            prim2 = prim2->next;
        }
    }
}

void afisareStiva(NodStiva* varf) {
    while (varf != NULL) {
        printf("Nume: %s | Varsta: %d | Data nasterii: %d %d\n",
            varf->info.nume, varf->info.varsta,
            varf->info.ziNastere, varf->info.lunaNastere);
        varf = varf->next;
    }
}

int numaraPestePrag(NodStiva* varf, int prag) {
    int contor = 0;
    while (varf != NULL) {
        if (varf->info.varsta > prag) {
            contor++;
        }
        varf = varf->next;
    }
    return contor;
}

void dezalocareStiva(NodStiva** varf) {
    while (*varf != NULL) {
        NodStiva* temp = *varf;
        *varf = (*varf)->next;
        free(temp->info.nume);
        free(temp);
    }
}


void main() {
    NodCoada* prim = NULL;
    NodCoada* ultim = NULL;
    Persoana persoana;
    char buffer[100];
    int nrPersoane;

    FILE* f = fopen("persoane.txt", "r");
        fscanf(f, "%d", &nrPersoane);
        for (int i = 0; i < nrPersoane; i++) {
            fscanf(f, "%d %s %d %d", &persoana.varsta, buffer, &persoana.ziNastere, &persoana.lunaNastere);
            persoana.nume = (char*)malloc(strlen(buffer) + 1);
            strcpy(persoana.nume, buffer);
            put(&prim, &ultim, persoana);
            free(persoana.nume); 
        }
        fclose(f);
  

    printf("\n--- Coada citita din fisier ---\n");
    afisareCoada(prim);


    NodCoada* prim2 = NULL;
    NodCoada* ultim2 = NULL;
    int nrPersoane2;
    printf("\nIntrodu numarul de persoane pentru coada 2: ");
    scanf("%d", &nrPersoane2);

    for (int i = 0; i < nrPersoane2; i++) {
        printf("Persoana %d:\n", i + 1);
        printf("Varsta: "); scanf("%d", &persoana.varsta);
        printf("Nume: "); scanf("%s", buffer);
        printf("Zi nastere: "); scanf("%d", &persoana.ziNastere);
        printf("Luna nastere: "); scanf("%d", &persoana.lunaNastere);

        persoana.nume = (char*)malloc(strlen(buffer) + 1);
        strcpy(persoana.nume, buffer);
        put(&prim2, &ultim2, persoana);
        free(persoana.nume);
    }

    printf("\n--- Coada citita de la tastatura ---\n");
    afisareCoada(prim2);

    NodCoada* primRez = NULL;
    NodCoada* ultimRez = NULL;

    impletireCozi(prim, prim2, &primRez, &ultimRez);

    printf("\n--- Coada rezultata prin impletire ---\n");
    afisareCoada(primRez);

    NodStiva* varf = NULL;
    NodCoada* temp = primRez;
    while (temp != NULL) {
        if (temp->info.varsta > 30) {
            push(&varf, temp->info);
        }
        temp = temp->next;
    }

    printf("\n--- Stiva persoanelor cu varsta > 30 ---\n");
    afisareStiva(varf);

    int prag = 40;
    int pestePrag = numaraPestePrag(varf, prag);
    printf("\nNumar persoane din stiva cu varsta peste %d: %d\n", prag, pestePrag);

    
    dezalocareStiva(&varf);

}



