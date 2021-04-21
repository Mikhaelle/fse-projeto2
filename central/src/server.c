#include "server.h"
#include <sensor.h>

void comunicacaoClienteTCP(int socketCliente) {
	char buffer[16];
    memset(buffer, 0, sizeof buffer);
	int tamRecebido;
	if((tamRecebido = recv(socketCliente, buffer, 16, 0)) < 0)
		printf("Erro no recv1(): %d\n", tamRecebido);

    buffer[15] = '\0';
	while (tamRecebido > 0) {
		if(send(socketCliente, buffer, tamRecebido, 0) != tamRecebido)
			printf("Erro no envio - send()\n");
		
		if((tamRecebido = recv(socketCliente, buffer, 16, 0)) < 0)
			printf("Erro no recv2()\n");
	}
  	int command;
		sscanf(buffer, "%d", &command);
    state_entry_handler(command);
}

void *criaServidor() {
    int socketServidor, socketCliente;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    
    if(( socketServidor = socket(AF_INET, SOCK_STREAM, 0)) <0)
        printf("Erro ao abrir o socket\n");

   
	memset(&serverAddr, '0', sizeof(serverAddr)); // Zerando a estrutura de dados
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);//qualquer endereço
	serverAddr.sin_port = htons(SERV_PORT);

    //Bind
    if (bind(socketServidor, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
        printf("erro binding\n");
    
    //Listen
    if (listen(socketServidor, 10) < 0)
        printf("listen error\n");
    
    while (1) {
        unsigned int len = sizeof(clientAddr);
        socketCliente = accept(socketServidor, (struct sockaddr *)&clientAddr, &len);
        if (socketCliente < 0)
            printf("ERROR on accept:%d\n", socketCliente);
        
        comunicacaoClienteTCP(socketCliente);
        close(socketCliente);
    }
    
    close(socketServidor);
    return NULL;
}

void enviaDistribuido(int item, int status)
{
   struct sockaddr_in client;

  int socketid = socket(AF_INET, SOCK_STREAM, 0);
  if (socketid == -1) {
    char *message = "ERROR: Você deve inicializar o sistema distribuído! (code: 1)";
    quit_handler(message);
  }

  client.sin_family = AF_INET;
  client.sin_addr.s_addr = inet_addr(CLIENT_IP);
  client.sin_port = htons(CLIENT_PORT);

  if (connect(socketid, (struct sockaddr*) &client, sizeof(client)) < 0) {
    char *message = "ERROR: Você deve inicializar o sistema distribuído! (code: 2)";
    quit_handler(message);
  }

  char buf[6];
  snprintf(buf, 6, "%d %d %d", 1, item, status);
  int size = strlen(buf);
  if (send(socketid, buf, size, 0) != size) {
		char *message = "ERROR: Você deve inicializar o sistema distribuído! (code: 3)";
    quit_handler(message);
  }

  char buffer[16];
  int size_rec = recv(socketid, buffer, 16, 0);
  if (size_rec < 0) {
    char *message = "ERROR: Você deve inicializar o sistema distribuído! (code: 4)";
    quit_handler(message);
  }
 
  buffer[15] = '\0';

  int res;
  sscanf(buffer, "%d", &res);

  close(socketid);

  return res;
}

Bme280 request_sensor() {
  struct sockaddr_in client;
  int socketid;
  Bme280 bme280;
  bme280.temperature = 0;
  bme280.humidity = 0;

  if((socketid = socket(AF_INET, SOCK_STREAM, 0))<0){
    printf("error in socket\n");
    return bme280;
  };

  client.sin_family = AF_INET;
  client.sin_addr.s_addr = inet_addr(CLIENT_IP);
  client.sin_port = htons(CLIENT_PORT);

  if (connect(socketid, (struct sockaddr*) &client, sizeof(client)) < 0) {
    return bme280;
  }

  char buf[2];
  snprintf(buf, 2, "%d", 2);
  int size = strlen(buf);
  if (send(socketid, buf, size, 0) != size) {
    close(socketid);
    return bme280;
  }

  char buffer[16];
  int size_rec = recv(socketid, buffer, 16, 0);
  if (size_rec < 0) {
    close(socketid);
    return bme280;
  }
    
  buffer[15] = '\0';
	
  int command;
  double temperature;
  double humidity;
  sscanf(buffer, "%d %lf %lf", &command, &temperature, &humidity);
  bme280.temperature = temperature;
  bme280.humidity = humidity;

  close(socketid);

  return bme280;
}