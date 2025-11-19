#include <stdio.h>

/*
    gcc test_crittografia.c -o cry
    ./cryt.exe
    Criptazione:   enc = ((value + key) * multiplier) % modulo
    Decriptazione: dec = ((enc * inverse_multiplier) % modulo) - key
*/

// funzione per trovare l'inverso modulo (modular inverse)
int mod_inverse(int a, int modulo) {
    for (int x = 1; x < modulo; x++) {
        if ((a * x) % modulo == 1)
            return x;
    }
    return -1; // se non esiste
}

// funzione di criptazione
int encrypt(int value, int key, int multiplier, int modulo) {
    return ((value + key) * multiplier) % modulo;
}

// funzione di decriptazione
int decrypt(int encrypted, int key, int multiplier, int modulo) {
    int inv = mod_inverse(multiplier, modulo);
    if (inv == -1) {
        printf("Errore: nessun inverso modulo trovato.\n");
        return -1;
    }
    return ((encrypted * inv) % modulo) - key;
}

int main() {
    int value;
    
    printf("Inserisci un numero da criptare: ");
    scanf("%d", &value);

    // parametri della "crittografia"
    int key = 1234;
    int multiplier = 7;
    int modulo = 9973; // numero primo consigliato

    int encrypted = encrypt(value, key, multiplier, modulo);
    int decrypted = decrypt(encrypted, key, multiplier, modulo);

    printf("\n--- RISULTATI ---\n");
    printf("Valore originale: %d\n", value);
    printf("Valore criptato:  %d\n", encrypted);
    printf("Valore decriptato: %d\n", decrypted);

    return 0;
}
