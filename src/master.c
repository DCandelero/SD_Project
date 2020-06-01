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
    int socks[10], portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    double result[10], finalResult = 0;

    double j;
    j = atof(argv[4]);


    pack_data data = {0, 100, j};

    /*if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }*/

    portno = atoi(argv[2]);
    int n_slaves= atoi(argv[3]);
    

    int i;
    for(i = 0; i < n_slaves; i++) { // abrir conexoes com todos os slaves
      socks[i] = socket(AF_INET, SOCK_STREAM, 0);
      if (socks[i] < 0)
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
      serv_addr.sin_port = htons(portno+i);
      if (connect(socks[i],(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
          error("ERROR connecting");
    }

    int Ipartial = 0;
    Ipartial = data.xf/n_slaves;
    for(i=0;i<n_slaves;i++) { // enviar a solicitacao a cada slave
        if (i == n_slaves) {
            i = 0;
        }
        data.xi = Ipartial*i;
        data.xf = Ipartial + Ipartial*i;

        printf("\nSolicitando cálculo ao escravo No %d...\nDados de entrada: %.1lf, %.1lf, %lf \n",i, data.xi, data.xf, data.j);
        pack_send(socks[i],&data);
    }
    printf("\n");
    for(i = 0; i < n_slaves; i++) { // receber a resposta de cada slave e fechar a conexao
      result_recv(socks[i], &result[i]);
      close(socks[i]);
      printf("slave No %d, result[%d] = %lf\n", i, i, result[i]);
      finalResult += result[i];
    }


    printf("\nResultado da integral: %lf\n", finalResult);

    return 0;
}
