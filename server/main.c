// Bind socket to port 8888 on localhost
//LINKER with library -lws2_32
#pragma comment(lib,"ws2_32.lib") //Winsock Library
#include<stdio.h>
#include<winsock2.h>


int receive_data(SOCKET * s, WSADATA * wsa)
{

    struct sockaddr_in server;
    char *message , server_reply[2000];
    int recv_size;

    //Receive a reply from the server or client
    if((recv_size = recv(*s , server_reply , 2000 , 0)) == SOCKET_ERROR)
    {
        puts("recv failed");
    }
    server_reply[recv_size] = '\0';
    puts(server_reply);
    return 0;
}

int main(int argc , char *argv[])
{
    int port = -1;
    printf("Sur quel port souhaitez-vous que le serveur ecoute ?");
    scanf("%d",&port);
    char *client_ip = "";
    int client_port = -1;
    WSADATA wsa;
    SOCKET s , new_socket;
    struct sockaddr_in server , client;
    int c;
    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }
    printf("Initialised.\n");
    //Create a socket
    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
    }
    printf("Socket created.\n");
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);
    printf("The IP address if this server is 127.0.0.1, its port number is %d \n",port);
    //Bind
    if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d" , WSAGetLastError());
    }
    puts("Bind done");
    //Listen to incoming connections
    listen(s , 3);
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);

    int start = 0;
    while( (new_socket = accept(s , (struct sockaddr *)&client, &c)) != INVALID_SOCKET )
    {
        if(start == 0)
        {
            puts("Connection accepted\n\n");
            start = 1;
        }

        //Print client message
        client_ip = inet_ntoa(client.sin_addr);
        client_port = ntohs(client.sin_port);
        printf("Incomming message from IP:%s port:%d :\n",client_ip,client_port);
        receive_data(&new_socket,&wsa);
    }
    puts("End of the connexion");
    closesocket(s);
    WSACleanup();

    return 0;

}
