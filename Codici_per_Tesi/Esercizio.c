#include <stdio.h>
#include <stdlib.h> 

/*
    cd C:/Users/tabar/OneDrive/Desktop/GitHub/c_exercises/Codici_per_Tesi
    gcc Esercizio.c -o Esercizio
    ./Esercizio.exe

*/

int main() {
  
    
    int n = 3;
    int v[n];
    char line[256];

    printf("Inserisci i valore delle 3 aziende");
    printf("\n");


    for (int i = 0; i < n; ++i) {
        printf("Valore segreto partecipante %d: ", i+1);
        fgets(line, sizeof(line), stdin);
        v[i] = atoll(line);
    }

    return 0;
    



}

