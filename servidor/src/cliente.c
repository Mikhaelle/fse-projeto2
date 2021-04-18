#include "cliente.h"

void *enviaServidor(char *mensagem )
{
    int clientSocket;
    struct sockaddr_in servidorAddr;
    char buffer[16];
    unsigned int tamanhoMensagem;

    int bytesRecebidos;
    int totalBytesRecebidos;

    //Cria Socket
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        printf("Erro no socket()\n");

    //Construir struct sockaddr_in
    memset(&servidorAddr, 0, sizeof(servidorAddr));
    servidorAddr.sin_family = AF_INET;
    servidorAddr.sin_addr.s_addr = inet_addr(IP_Servidor);
    servidorAddr.sin_port = htons(servidorPorta);

    //Connect
    if (connect(clientSocket, (struct sockaddr *)&servidorAddr, sizeof(servidorAddr)) < 0)
        printf("Erro no connect()\n");

    tamanhoMensagem = strlen(mensagem);
    printf("%d\n", tamanhoMensagem);

    if (send(clientSocket, mensagem, tamanhoMensagem, 0) != tamanhoMensagem)
        printf("Erro no envio: numero de bytes enviados diferente do esperado\n");

    close(clientSocket);
}

void comunicacaoServidorTCP(int socketServidor)
{
    printf("comunicou\n");
    char buffer[16];
    memset(buffer, 0, sizeof buffer);
	int tamRecebido;
	if((tamRecebido = recv(socketServidor, buffer, 16, 0)) < 0)
		printf("Erro no recv1(): %d\n", tamRecebido);

    buffer[15] = '\0';

    int command;
    sscanf(buffer, "%d", &command);
    
    if (command == 1)
    {
        

        int item;
        int status;
        sscanf(buffer, "%d %d %d", &command, &item, &status);
        printf("Recebida requisição de alteração de equipamentos: %d, %d\n", item, status);
        toggle(item, status);
        char buf[2];
        snprintf(buf, 2, "%d", 1);
        int size = strlen(buf);
        printf("Enviando resultado de alteração...\n");
        if (send(socketServidor, buf, size, 0) != size)
        {
            printf("Error: Send failed\n");
        }
    }
    // Leitura Sensor BME280
    if (command == 2)
    {
        printf("Recebida requisição de leitura de humidade e temperatura\n");
        char buf[16];
        int T, P, H; 
        bme280ReadValues(&T,&P,&H);
        snprintf(buf, 16, "%d %lf %lf", 2, T/100.0, H/1000.0);
        int size = strlen(buf);
        printf("Enviando dados de temperatura: %lf e humidade %lf.\n", T/100.0, H/1000.0);
        if (send(socketServidor, buf, size, 0) != size)
        {
            printf("Error: Send failed\n");
        }
    }

}

void *criaCliente()
{
    int socketServidor, socketCliente;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;

    if ((socketCliente = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        printf("Erro ao abrir o socket\n");

    memset(&clientAddr, '0', sizeof(clientAddr));

    clientAddr.sin_family = AF_INET;
    clientAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    clientAddr.sin_port = htons(clientePorta);

    if (bind(socketCliente, (struct sockaddr *)&clientAddr, sizeof(clientAddr)) < 0)
        printf("erro binding\n");

    if (listen(socketCliente, 10) < 0)
        printf("listen error\n");

    while (1)
    {
        unsigned int len = sizeof(serverAddr);
        socketServidor = accept(socketCliente, (struct sockaddr *)&serverAddr, &len);

        if (socketServidor < 0)
            printf("ERROR on accept:%d\n", socketServidor);

        comunicacaoServidorTCP(socketServidor);
        close(socketServidor);
    }

    close(socketCliente);
}