#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
  // Crea un socket TCP
  int sfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sfd < 0) {
    perror("Errore nella creazione del socket");
    return 1;
  }

  // Connetti al server
  struct sockaddr_in serv_addr;
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(1234);
  serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  if (connect(sfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    perror("Errore nella connessione al server");
    return 1;
  }

  // Invia una stringa al server
  char str[100];
  printf("Inserisci una stringa: ");
  scanf("%s", str);
  int len = send(sfd, str, sizeof(str), 0);
  if (len < 0) {
    perror("Errore nell'invio della stringa");
    return 1;
  }

  // Ricevi l'iniziale della stringa dal server
  char iniziale;
  int len2 = recv(sfd, &iniziale, sizeof(iniziale), 0);
  if (len2 < 0) {
    perror("Errore nella ricezione della stringa");
    return 1;
  }

  // Stampa l'iniziale della stringa ricevuta
  printf("L'iniziale della stringa è: %c\n", iniziale);

  // Chiude la connessione
  close(sfd);

  return 0;
}
