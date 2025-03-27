#include <stdio.h>
#include <string.h>

#define MAX_STUDENTI 30 // Numero massimo di studenti per classe

// Struttura per rappresentare uno studente
typedef struct {
    char nome[50];
    int età;
    float altezza;
} Studente;

// Struttura per rappresentare una classe
typedef struct {
    char nomeClasse[20];
    Studente studenti[MAX_STUDENTI];
    int numeroStudenti;
} Classe;

int main() {
    Classe classeA;

    // Inizializzazione della classe
    strcpy(classeA.nomeClasse, "Classe A");
    classeA.numeroStudenti = 0;

    // Aggiunta di Mario alla classe
    strcpy(classeA.studenti[classeA.numeroStudenti].nome, "Mario");
    classeA.studenti[classeA.numeroStudenti].età = 20;
    classeA.studenti[classeA.numeroStudenti].altezza = 1.75;
    classeA.numeroStudenti++;

    // Aggiunta di Giuseppe alla classe
    strcpy(classeA.studenti[classeA.numeroStudenti].nome, "Giuseppe");
    classeA.studenti[classeA.numeroStudenti].età = 21;
    classeA.studenti[classeA.numeroStudenti].altezza = 1.80;
    classeA.numeroStudenti++;

    // Stampa delle informazioni sulla classe
    printf("Classe: %s\n", classeA.nomeClasse);
    printf("Numero studenti: %d\n", classeA.numeroStudenti);

    // Stampa delle informazioni sugli studenti
    for (int i = 0; i < classeA.numeroStudenti; i++) {
        printf("Studente %d:\n", i + 1);
        printf("  Nome: %s\n", classeA.studenti[i].nome);
        printf("  Età: %d\n", classeA.studenti[i].età);
        printf("  Altezza: %.2f\n", classeA.studenti[i].altezza);
    }

    return 0;
}