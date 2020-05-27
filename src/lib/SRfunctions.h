#include <stdio.h>
#include <stdlib.h>

// Package structure
typedef struct {
    int type;
    double xi;
    double xf;
    double j;
} pack_data;

// Sends a package over a socket
void pack_send(int sock, pack_data *src);
// Receives a package from a socket
void pack_recv(int sock, pack_data *dest);