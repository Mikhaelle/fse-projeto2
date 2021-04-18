#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define IP_Servidor "192.168.0.53"
#define servidorPorta 10004
#define clientePorta 10104

void *enviaServidor( ) ;
void *criaCliente( ) ;