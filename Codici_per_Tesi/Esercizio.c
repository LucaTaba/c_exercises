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

//----------------------------------------------------------------

// funzione crittografia


// funzione di criptazione
int encrypt(int v, int key, int modulo) {
    return (v + key) % modulo;
}

int decrypt(int encrypted, int key, int modulo) {
    int r = (encrypted - key) % modulo;
    if (r > modulo/2)
        return r - modulo;   // converte i rappresentanti alti in negativi
    return r;
}

int cripta(int v, int key, int modulo) {
    return encrypt(v, key, modulo);
}

// r = (encrypted_sum - (total_shares * key)) mod mod
int decrypt_total(int encrypted_sum, int key, int total_shares, int mod) {
    int sub = (total_shares * key) % mod;    // evita numeri grandi, lo riduciamo subito
    int r = (encrypted_sum - sub) % mod;
    if (r < 0) r += mod;
    return r;
}




//----------------------------------------------------------------

int main() {
  
    
    int n = 3;
    int v[n];
    char line[256];

    // parametri della "crittografia"
    int key = 1234;
    int modulo = 9973; // numero primo consigliato

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
//aggiunta per test



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

    // ogni partecipante cripta i propri share
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int encrypted_share = cripta(shares[i][j], key, modulo);
            shares[i][j] = encrypted_share;
        }
    }
    // ogni partecipante somma ciò che riceve
    int received_sum[n];
    for (int j = 0; j < n; ++j) received_sum[j] = 0; // inizializzo a zero

    int somma_tutti = 0;
    for (int i = 0; i < n; ++i) { 
        for (int j = 0; j < n; ++j) {
            somma_tutti += shares[i][j];
        }
    }

    for (int i = 0; i < n; ++i) { 
        for (int j = 0; j < n; ++j) {
            printf("Partecipante %d invia share %d = %d\n", i, j, shares[i][j]);
            int decrypted_share = decrypt(shares[i][j], key, modulo);
            printf("  -> decriptato = %d\n", decrypted_share);
            received_sum[j] += decrypted_share;

        }
    }

    printf("Valori somme (pubblici):\n");
    int final_sum = 0;
    for (int j = 0; j < n; ++j) {
        printf("  sum_%d = %d\n", j + 1, received_sum[j]);
        final_sum += received_sum[j];
    }

    printf("\nSomma totale ottenuta = %d\n", final_sum);
    printf("somma_tutti calcolata = %d\n", somma_tutti);
    int decrypted_total = decrypt_total(somma_tutti, key, n*n, modulo);
    printf("Somma totale decriptata = %d\n", decrypted_total);

    return 0;

}

