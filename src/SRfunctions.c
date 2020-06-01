#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include "SRfunctions.h"

void pack_send(int sock, pack_data *src) {
    static char buffer[128];
    sprintf(buffer, "%g %g %g",
            src->xi,
            src->xf,
            src->j);
    send(sock, buffer, strlen(buffer), 0);
}

void pack_recv(int sock, pack_data *dest) {
    static char buffer[128];
    bzero(buffer, sizeof(buffer));
    recv(sock, buffer, 128, 0);
    sscanf(buffer, "%lf %lf %lf",
            &(dest->xi),
            &(dest->xf),
            &(dest->j));
}

void result_send(int sock, double result){
    static char buffer[128];
    bzero(buffer, sizeof(buffer));
    sprintf(buffer, "%lf", result);
    send(sock, buffer, 128, 0);
}

void result_recv(int sock, double *result){
    static char buffer[128];
    bzero(buffer, sizeof(buffer));
    recv(sock, buffer, 128, 0);
    sscanf(buffer, "%lf", result);
}