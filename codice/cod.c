#include <stdio.h>

// tabella di conversione
char* table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// funzione che converte 
char convert(char byte) {
	return table[byte];		
}


//funzione che effettua la codifica 
//prende len caratteri dal buffer in, li converte in base64 e li inserisce nel buffer out 
void compute_64(unsigned char* in, int len, char* out){
	
	//se ho 3 caratteri => no padding
	if(len == 3) {

		//in[0] >> 2 <-> unsigned shift a DX di 2 bit del char salvato in in[0], così facendo prendo i primi 6 bit di in[0], li metto come ultimi 6 bit e ci metto davanti 00,
		//passo il risultato binario  alla funzione convert che lo usa come intero per accedere all'array table e così facendo accede al rispettivo carattere in base64 
		out[0] = convert(in[0] >> 2);

		//analogo a su ma con le maschere e shift
		out[1] = convert(((in[0] & 0x03) << 4) | ((in[1] & 0xF0) >> 4));
		///analogo a su ma con le maschere e shift
		out[2] = convert(((in[1] & 0x0F) << 2) | ((in[2] & 0xC0) >> 6));
		//analogo a su ma con le maschere e shift
		out[3] = convert(in[2] & 0x3F);
	
	}
	else if(len == 2) {
		
		//analogo a su ma con le maschere e shift
		out[0] = convert(in[0] >> 2);
		out[1] = convert(((in[0] & 0x03) << 4) | ((in[1] & 0xF0) >> 4));
		out[2] = convert((in[1] & 0x0F) << 2);

		//metto l'ultimo carattere di output a '=' per il padding
		out[3] = '=';

	}
	else if(len == 1) {
		out[0] = convert(in[0] >> 2);
		out[1] = convert((in[0] & 0x03) << 4);
		
		//metto gli ultimi 2 caratteri di output a '=' per il padding
		out[2] = '=';
		out[3] = '=';

	}

}

int main(void) {
	//bueffer di input dove metto la stringa (3 byte = 24bit)
	char in[3];
	//bueffer dove mettere la stringa di output (4byte +1 terminatore('\0'))
	char out[5];
	//metto l'ultimo carattere a terminatore di stringa (4o carattere perchè parto da 0)
	out[4] = '\0';

	//per contare i caratteri inseriti nell'stdin
	int counter = 0;

	//variabile dove inserire il carattere letto da stdin, uso un unsigned int perchè i caratteri in ascii sono tutti interi positivi (quindi risparmio memoria
	//rispetto ad un int
	unsigned int c;

	//leggo tutto lo standard input finchè non premo invio, prendendo un carattere alla volta ad ogni iterazione e lo salvo in c
	//fgetc ritorna l'intero decimale corrispondente (alla codifica binaria) dell'ASCII del carattere inserito
	//!=0 EOF <->leggi finchè non viene inserito il carattere invio (fgetc ritorna un valore speciale corrispondente a EOF quano viene premuto invio)
	while((c = fgetc(stdin)) != EOF) {
		
		//salvo nel buffer in (dei caratteri inseriti) il carattere c inserito ma castato a unsigned char (prima era un unsigned int)
		//metto unsigned char e non char perchè sono tutti interi positivi e quindi risparmio spazio 
		in[counter++] = (unsigned char) c;

		//se l'utente ha inserito esattamente 3 caratteri (=3byte =24bit)
		if(counter == 3) {
			//converto i 3 caratteri del bueffer in, in 4 simboli in base64 e li inserisco nel bueffer out
			compute_64(in, 3, out);
			
			//stampa la codifica
			printf("%s", out);
			//e azzera il counter, quindi posso codificare la prossima tripletta di caratteri
			counter = 0;
		}

	}
	
	//una volta uscito dal while, se il counter = 1 o 2 => sono rimasti 1 o 2 caratteri NON convertiti nel buffer => li converto 
	if(counter != 0){
	       	compute_64(in, counter, out);
		printf("%s\n", out);	
	}
}