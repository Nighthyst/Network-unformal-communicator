#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Penser à inclure string.h pour strchr()
#include<winsock2.h>
#include<dos.h>


struct sockaddr_in server;

int send_data(char  * IP, int port, char * message, SOCKET  * s, WSADATA * wsa);
int receive_data(SOCKET * s, WSADATA * wsa);
void chat_client();

int send_data(char  * IP, int port, char * message, SOCKET * s, WSADATA * wsa)
{
    //WSADATA wsa;
    //SOCKET s;
    struct sockaddr_in server;
    //printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }
    //printf("Initialised.\n");
    //Create a socket
    if((*s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
        return 1;
    }
    //printf("Socket created.\n");
    server.sin_addr.s_addr = inet_addr(IP); //google.fr
    server.sin_family = AF_INET; // The Internet Protocol version 4 (IPv4)
    server.sin_port = htons(port); // it would be a good idea to read Course Port Number
    //Connect to remote server
    if (connect(*s , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("connect error");
        return 1;
    }
    //puts("Connected");
    //Send some data

    if( send(*s , message , strlen(message) , 0) < 0)
    {
        puts("Send failed");
        return 1;
    }
    puts("Data Send\n");
    return 0;
}

int receive_data(SOCKET * s, WSADATA * wsa)
{

    struct sockaddr_in server;
    char *message , server_reply[2000];
    int recv_size;


    //Receive a reply from the server
    if((recv_size = recv(*s , server_reply , 2000 , 0)) == SOCKET_ERROR)
    {
    puts("recv failed");
    }
    puts("Reply received\n");
    //Add a NULL terminating character to make it a proper string before printing
    server_reply[recv_size] = '\0';
    puts(server_reply);
    return 0;
}



int main(int argc , char *argv[])
{
    //viderBuffer();

    WSADATA wsa;
    SOCKET s;

    printf("Bienvenue dans HOMEWORLD CHAT\n");
    printf("Homeworld chat vous permet de chater avec vos amis\n");

    char IP[10];
    printf("Tout d'abord renseingnez l'adresse IP :\n");
    scanf("%s",&IP);
    printf("Vous avez tape : %s\n", IP);

    int port = -1;
    printf("Puis le port :\n");
    scanf("%d",&port);
    printf("Vous avez tape : %d\n", port);

    char message[200];
    //char sender[200];
    char * sender = message;
    //char * sender;
    int stop = 0;
    while(stop == 0)
    {
        printf("Tapez votre message pour %s : %d (sans espace):\n",IP,port);
        //viderBuffer();
        fgets(message,200,stdin);
        //sender = message;
        //scanf("%s",&message);
        //strncpy(sender,message,200);
        printf("Vous voulez envoyer le message : %s\n",sender);
        stop = send_data(IP,port,message,&s,&wsa);
    }
    printf("Vous n'etes plus connecte.");
    return 0;
}


void chat_client()
{

}

