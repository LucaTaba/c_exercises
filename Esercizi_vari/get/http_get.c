#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <hostname>\n", argv[0]);
        exit(1);
    }

    char *hostname = argv[1];
    int sockfd, portno = 80;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char request[BUFFER_SIZE];
    char response[BUFFER_SIZE];

    // 1. Creazione del socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    // 2. Risoluzione del nome host
    server = gethostbyname(hostname);
    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(1);
    }

    // 3. Configurazione dell'indirizzo del server
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    // 4. Connessione al server
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }

    // 5. Formattazione della richiesta HTTP GET
    sprintf(request, "GET / HTTP/1.1\r\nHost: %s\r\n\r\n", hostname);

    // 6. Invio della richiesta
    if (send(sockfd, request, strlen(request), 0) < 0) {
        perror("ERROR writing to socket");
        exit(1);
    }

    // 7. Ricezione della risposta
    bzero(response, BUFFER_SIZE);
    int n = read(sockfd, response, BUFFER_SIZE - 1);
    if (n < 0) {
        perror("ERROR reading from socket");
        exit(1);
    }

    // 8. Analisi e visualizzazione della risposta
    printf("%s\n", response);

    // 9. Chiusura del socket
    close(sockfd);
    return 0;
}