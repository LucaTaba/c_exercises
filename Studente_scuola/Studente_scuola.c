#include <stdio.h>
#include <string.h>

#define MAX_STUDENTI 30
#define MAX_VOTI 10

typedef struct {
    char nome[50];
    int età;
    float altezza;
    float voti[MAX_VOTI];
    int numeroVoti;
} Studente;

typedef struct {
    char nomeClasse[20];
    Studente studenti[MAX_STUDENTI];
    int numeroStudenti;
} Classe;

int main() {
    Classe classeA;
    char stringa[100];

    

    printf("Inserisci il nome della classe ");
    scanf("%s", stringa);

    strcpy(classeA.nomeClasse, stringa);
    classeA.numeroStudenti = 0;

    // Aggiunta di Mario
    strcpy(classeA.studenti[classeA.numeroStudenti].nome, "Mario");
    classeA.studenti[classeA.numeroStudenti].età = 20;
    classeA.studenti[classeA.numeroStudenti].altezza = 1.75;
    classeA.studenti[classeA.numeroStudenti].numeroVoti = 0; // Inizializzazione numeroVoti
    classeA.numeroStudenti++;

    // Aggiunta voti a Mario
    classeA.studenti[0].voti[classeA.studenti[0].numeroVoti++] = 8.5;
    classeA.studenti[0].voti[classeA.studenti[0].numeroVoti++] = 9.0;

    // Aggiunta di Giuseppe
    strcpy(classeA.studenti[classeA.numeroStudenti].nome, "Giuseppe");
    classeA.studenti[classeA.numeroStudenti].età = 21;
    classeA.studenti[classeA.numeroStudenti].altezza = 1.80;
    classeA.studenti[classeA.numeroStudenti].numeroVoti = 0; // Inizializzazione numeroVoti
    classeA.numeroStudenti++;

    // Aggiunta voti a Giuseppe
    classeA.studenti[1].voti[classeA.studenti[1].numeroVoti++] = 7.5;
    classeA.studenti[1].voti[classeA.studenti[1].numeroVoti++] = 8.0;

    // Stampa delle informazioni
    printf("Classe: %s\n", classeA.nomeClasse);
    printf("Numero studenti: %d\n", classeA.numeroStudenti);

    for (int i = 0; i < classeA.numeroStudenti; i++) {
        printf("Studente %d:\n", i + 1);
        printf("  Nome: %s\n", classeA.studenti[i].nome);
        printf("  Età: %d\n", classeA.studenti[i].età);
        printf("  Altezza: %.2f\n", classeA.studenti[i].altezza);
        printf("  Voti: ");
        for (int j = 0; j < classeA.studenti[i].numeroVoti; j++) {
            printf("%.2f ", classeA.studenti[i].voti[j]);
        }
        printf("\n");
    }

    return 0;
}