#include <stdio.h>
#include <string.h>

struct Classe {
  char nome[50];
  int età;
  float altezza;
};

struct Studente {
    char nome[50];
    int età;
    float altezza;
};

int main() {

	struct Studente persona1;


	strcpy(persona1.nome, "ciao");
  persona1.età = 2;
	printf("Eta' di persona1: %d\n", persona1.età);
  printf("Eta' di persona1: %d\n", persona1.età);

  return 0;
}