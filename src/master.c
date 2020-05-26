#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include "SRfunctions.c"

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    pack_data data = {1, 0, 100, 0.00001};
    int n_slaves[4] = {1,2,4,10};

    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    int i = 0, j = 0, Ipartial = 0;
    for(i=0;i<n_slaves[j];i++) {
        if (i == n_slaves[j]) {
            i = 0;
            j++;
        }
        data.xi = data.xi + Ipartial;
        Ipartial = data.xf/n_slaves[j];
        data.xf = Ipartial + Ipartial*i;

        printf("BEFORE SEND: %d, %lf, %lf, %lf \n", data.type, data.xi, data.xf, data.j);
        pack_send(sockfd,&data);
        break;
    }

    close(sockfd);
    return 0;
}