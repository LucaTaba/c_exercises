#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>

/*
    cd C:/Users/tabar/OneDrive/Desktop/GitHub/c_exercises/Codici_per_Tesi
    gcc Esercizio.c -o Esercizio
    ./Esercizio.exe

*/
// restituisce un numero casuale tra min e max (inclusi)
int rand_range(int min, int max) {
    return min + rand() % (max - min + 1);
}


int main() {
  
    
    int n = 3;
    int v[n];
    char line[256];

    srand(time(NULL));

    printf("Inserisci i valore delle 3 aziende");
    printf("\n");


    for (int i = 0; i < n; ++i) {
        printf("Valore segreto partecipante %d: ", i+1);
        fgets(line, sizeof(line), stdin);
        v[i] = atoi(line); //converto in intero
    }

    for (int i = 0; i < 3; i++) { //stampo i valori inseriti
        printf("v[%d] = %d\n", i, v[i]);
    }

    int shares[n][n];
    memset(shares, 0, sizeof(shares)); //inizializza a zero

    // faccio piu somme consegcutive prendendo un valore casuale ogni volta da ciascuno
    for (int i = 0; i < n; ++i) {
        int sum = 0;
        for (int j = 0; j < n-1; ++j) {
            int r = rand_range(-1000, 1000);
            shares[i][j] = r;
            sum += r;
        }
        shares[i][n-1] = v[i] - sum; // calcolo l'ultimo share in modo che la somma sia v[i]
    }

    // ogni partecipante somma ciò che riceve
    int received_sum[n];
    for (int j = 0; j < n; ++j) received_sum[j] = 0; // inizializzo a zero

    for (int i = 0; i < n; ++i) { 
        for (int j = 0; j < n; ++j) {
            printf("Partecipante %d invia share %d = %d\n", i+1, j+1, shares[i][j]);
            received_sum[j] += shares[i][j];
        }
    }

    printf("Valori somme (pubblici):\n");
    int final_sum = 0;
    for (int j = 0; j < n; ++j) {
        printf("  sum_%d = %d\n", j + 1, received_sum[j]);
        final_sum += received_sum[j];
    }

    printf("\nSomma totale ottenuta = %d\n", final_sum);

    return 0;

}

