#include <stdio.h>
#include <stdlib.h> // rand()
#include <stdint.h> // int64_t
#include <time.h>
#include <inttypes.h>
#include <string.h>

#define MAXN 128

/* random in range [lo, hi] */
static int64_t rand_range(int64_t lo, int64_t hi) {
    if (lo > hi) {
        int64_t t = lo; lo = hi; hi = t;
    }
    uint64_t r = ((uint64_t)rand() << 31) ^ rand();
    int64_t diff = hi - lo + 1;
    if (diff <= 0) return lo;
    return (int64_t)(r % (uint64_t)diff) + lo;
}

int main(int argc, char **argv) {

    int n = 3;
    if (argc >= 2) {
        n = atoi(argv[1]);
        if (n < 2) n = 2;
        if (n > MAXN) n = MAXN;
    }

    srand((unsigned int)time(NULL));

    printf("Additive Secret Sharing demo - %d partecipanti\n\n", n);

    int64_t v[MAXN];
    char line[256];

    printf("Vuoi inserire i valori manualmente? (s/n) ");
    fgets(line, sizeof(line), stdin);

    if (line[0] == 's' || line[0] == 'S') {
        for (int i = 0; i < n; ++i) {
            printf("Valore segreto partecipante %d: ", i+1);
            fgets(line, sizeof(line), stdin);
            v[i] = atoll(line);
        }
    } else {
        printf("Genero valori casuali (range -100..100) per demo.\n");
        for (int i = 0; i < n; ++i) {
            v[i] = rand_range(-100, 100);
        }
    }

    printf("\nValori segreti (solo demo):\n");
    int64_t true_sum = 0;
    for (int i = 0; i < n; ++i) {
        printf("  P%d: %" PRId64 "\n", i+1, v[i]);
        true_sum += v[i];
    }
    printf("Somma reale = %" PRId64 "\n\n", true_sum);

    /* shares[i][j]: share di i inviato a j */
    int64_t shares[MAXN][MAXN];
    memset(shares, 0, sizeof(shares));

    /* ogni partecipante genera gli share */
    for (int i = 0; i < n; ++i) {
        int64_t sum = 0;
        for (int j = 0; j < n-1; ++j) {
            int64_t r = rand_range(-1000, 1000);
            shares[i][j] = r;
            sum += r;
        }
        shares[i][n-1] = v[i] - sum;
    }

    /* ogni partecipante somma ciò che riceve */
    int64_t received_sum[MAXN];
    for (int j = 0; j < n; ++j) received_sum[j] = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            received_sum[j] += shares[i][j];
        }
    }

    printf("Valori sum_j (pubblici):\n");
    int64_t final_sum = 0;
    for (int j = 0; j < n; ++j) {
        printf("  sum_%d = %" PRId64 "\n", j+1, received_sum[j]);
        final_sum += received_sum[j];
    }

    printf("\nSomma totale ottenuta = %" PRId64 "\n", final_sum);

    if (final_sum == true_sum)
        printf("OK: la somma è corretta!\n");
    else
        printf("ERRORE: la somma NON coincide!\n");

    /* DEBUG: mostra le share */
    printf("\nDEBUG (share generate):\n");
    for (int i = 0; i < n; ++i) {
        printf("  shares P%d: ", i+1);
        for (int j = 0; j < n; ++j) {
            printf("%" PRId64 "%s", shares[i][j], (j+1==n) ? "" : ", ");
        }
        printf("\n");
    }

    return 0;
}
