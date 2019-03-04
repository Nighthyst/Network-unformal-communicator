//This is the code for windows

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include<dos.h>

int co = 0;
struct sockaddr_in server;

int send_data(char  * IP, int port, char * message, SOCKET  * s, WSADATA * wsa);
int receive_data(SOCKET * s, WSADATA * wsa);

/*
The purpose of this function is to send a small message to a
a server identified by its IP address and its port number.

This function return 0 if the message was sent, 1 if not.
*/

int activate(WSADATA * wsa, SOCKET * s,char  * IP, int port)
{

    //Initialising Winsock...
    if (WSAStartup(MAKEWORD(2,2),wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }
    //Initialised

    //Create a socket
    if((*s = socket(AF_INET , SOCK_STREAM, 6)) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
        return 1;
    }
    //Socket created
    server.sin_addr.s_addr = inet_addr(IP); //The IP address of the server
    server.sin_family = AF_INET; // The Internet Protocol version 4 (IPv4)
    server.sin_port = htons(port); // The port number of the server
    //Connect to remote server

    if (connect(*s , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("connect error");
        return 1;
    }

    //Connected
    return 0;
}

int send_data(char  * IP, int port, char * message, SOCKET * s, WSADATA * wsa)
{


        if(co == 0)
        {
            activate(wsa,s,IP,port);
            co += 1;
        }




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

    char message[280+1];

    int stop = 0;
    while(stop == 0)
    {
        printf("Tapez votre message pour %s : %d:\n",IP,port);
        fgets(message,280,stdin);
        stop = send_data(IP,port,message,&s,&wsa);
    }
    printf("Vous n'etes plus connecte.");
    return 0;
}


