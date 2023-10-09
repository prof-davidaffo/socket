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

  // Associa il socket a una porta
  struct sockaddr_in serv_addr;
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(1234);
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  if (bind(sfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    perror("Errore nell'associazione del socket");
    return 1;
  }

  // Ascolta connessioni
  if (listen(sfd, 5) < 0) {
    perror("Errore nell'ascolto delle connessioni");
    return 1;
  }

  // Accetta una connessione
  int cfd = accept(sfd, NULL, NULL);
  if (cfd < 0) {
    perror("Errore nell'accettazione della connessione");
    return 1;
  }

  // Ricevi una stringa dal client
  char str[100];
  int len = recv(cfd, str, sizeof(str), 0);
  if (len < 0) {
    perror("Errore nella ricezione della stringa");
    return 1;
  }

  // Invia l'iniziale della stringa al client
  char iniziale = str[0];
  send(cfd, &iniziale, sizeof(iniziale), 0);

  // Chiude la connessione
  close(cfd);
  close(sfd);

  return 0;
}
