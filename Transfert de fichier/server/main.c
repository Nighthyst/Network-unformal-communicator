#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <winsock2.h>

#define SERV_PORT 49312
#define MAXLINE   1024

char * END_FLAG = "================END";

void run(int sockfd, struct sockaddr *cliaddr, socklen_t clilen)
{
    int n, fd;
    socklen_t len;
    char buf[MAXLINE];

    len = clilen;
    n = recvfrom(sockfd, buf, MAXLINE, 0, cliaddr, &len);
    buf[n] = 0;
    printf("Received from client: [%s]\n", buf);
    sendto(sockfd, "ok", strlen("ok"), 0, cliaddr, len);
    fd = open(buf, O_RDWR | O_CREAT, 0666);

    while ((n = recvfrom(sockfd, buf, MAXLINE, 0, cliaddr, &len))) {
        buf[n] = 0;
        printf("%s", buf);
        if (!(strcmp(buf, END_FLAG))) {
            break;
        }
        write(fd, buf, n);
    }
    close(fd);
}

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    //bzero(&servaddr, sizeof(servaddr));
    for(int i = 0; i < sizeof(servaddr); i++)
    {
        *servaddr[i] = 0;
    }
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    run(sockfd, (struct sockaddr *) &cliaddr, sizeof(cliaddr));

    return 0;
}
