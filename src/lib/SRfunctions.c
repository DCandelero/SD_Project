#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include "SRfunctions.h"

void pack_send(int sock, pack_data *src) {
    static char buffer[128];
    sprintf(buffer, "%d %g %g %g",
            src->type,
            src->xi,
            src->xf,
            src->j);
    send(sock, buffer, strlen(buffer), 0);
}

void pack_recv(int sock, pack_data *dest) {
    static char buffer[128];
    bzero(buffer, sizeof(buffer));
    recv(sock, buffer, 128, 0);
    sscanf(buffer, "%d %lf %lf %lf",
            &(dest->type),
            &(dest->xi),
            &(dest->xf),
            &(dest->j));
}