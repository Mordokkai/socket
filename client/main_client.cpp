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

typedef struct adress{
	char name[256];
	char ad[256];
} ADRESS;

int main(void){
	int sock_err;

	SOCKET sock;
	SOCKADDR_IN sin;
	char buffer[256]="";
	ADRESS ad_recue;
	// Création de la socket client
	sock = socket(AF_INET, SOCK_STREAM, 0);

	// COnfiguration de la connexion
	sin.sin_addr.s_addr = inet_addr("127.0.01");
	sin.sin_family = AF_INET;
	sin.sin_port = htons(DEFAULT_PORT);

	// Tentative de connexion du client au serveur
	sock_err = connect(sock, (SOCKADDR*)&sin, sizeof(sin));
	if(sock_err == SOCKET_ERROR){
		perror("Echec de la tentative de connexion au serveur\n");
		exit(-1);
	}
	printf("Connexion à %s  sur le port %d \n", inet_ntoa(sin.sin_addr), htons(sin.sin_port));

	// Attente de réception de données
	sock_err = recv(sock, &ad_recue, sizeof(ad_recue), 0 );

	if(sock_err ==SOCKET_ERROR){
		printf("Problème lors de la réception du message\n");
		exit(-1);
	}
	printf("Recu: %s %s\n", ad_recue.name, ad_recue.ad);
	// Fermeture de la socket
	close(sock);
	getchar();
	return EXIT_SUCCESS;
}
