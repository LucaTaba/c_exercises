#include <stdio.h>

/*
    gcc test_crittografia.c -o cry
    ./cryt.exe
    Criptazione:   enc = ((v + key) * moltiplicatore) % modulo
    Decriptazione: dec = ((enc * inverse_moltiplicatore) % modulo) - key
*/


// funzione di criptazione
int encrypt(int v, int key, int modulo) {
    return (v + key) % modulo;
}

// funzione di decriptazione
int decrypt(int encrypted, int key, int modulo) {
    int r = (encrypted - key) % modulo;
    if (r < 0) r += modulo;  // correzione per valori negativi
    return r;
}
int normalize(int x, int mod) {
    if (x > mod/2)
        return x - mod;   // converte i rappresentanti alti in negativi
    return x;
}


int main() {
    int v;
    
    printf("Inserisci un numero da criptare: ");
    scanf("%d", &v);

    // parametri della "crittografia"
    int key = 1234;
    int modulo = 9973; // numero primo consigliato
    int decrypted2 = decrypt(v, key, modulo);

    int encrypted = encrypt(v, key, modulo);
    int decrypted = decrypt(encrypted, key, modulo);
    decrypted = normalize(decrypted, modulo);

    printf("\n--- RISULTATI ---\n");
    printf("Valore originale: %d\n", v);
    printf("Valore criptato:  %d\n", encrypted);
    printf("Valore decriptato: %d\n", decrypted);
    printf("Valore decriptato2: %d\n", decrypted2);

    return 0;
}
