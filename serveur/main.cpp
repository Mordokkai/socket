#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define NB_CONN_MAX  5

#define DEFAULT_PORT 23
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

int main(void){
	int sock_err;
	//Coté serveur
	SOCKADDR_IN sin;
	SOCKET sock;
	socklen_t sock_len_serv = sizeof(sin);

	//Coté client
	SOCKADDR_IN csin;
	SOCKET csock;
	socklen_t sock_len_client = sizeof(csin);

	// Création socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == INVALID_SOCKET){
		perror("Création de socket ratée\n");
		exit(-1);
	}

	// Configuration
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(DEFAULT_PORT);
	sock_err = bind(sock, (SOCKADDR*)&sin, sock_len_serv); // On associe la structure de données au socket
	if(sock_err == SOCKET_ERROR){
		perror("Bind du socket raté\n");
		exit(-1);
	}

	// On met le socket serveur en état d'écoute
	// il accepte maximum NB_CONN_MAX connections simultanées
	printf("Début de l'écoute du serveur\n");
	sock_err = listen(sock,NB_CONN_MAX);
	if(sock_err == SOCKET_ERROR){
		perror("Ecoute impossible\n");
		exit(-1);
	}

	// Attente de conexion d'un client
	printf("En attente de connexion\n");
	csock = accept(sock,(SOCKADDR*)&csin, &sock_len_client); //Ceci est un appel bloquant
	printf("Un client se connecte avec la socket %d de %s: %d\n", csock, inet_ntoa(csin.sin_addr),htons(csin.sin_port));

	//Fermetures
	printf("Fermeture de la socket client\n");
	close(csock);

	printf("Fermeture de la socket serveur\n");
	close(sock);

	printf("Terminé\n");

	return EXIT_SUCCESS;
}
