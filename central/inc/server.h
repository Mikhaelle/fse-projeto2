
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>


typedef struct {
  double temperature;
  double humidity;
} Bme280;

#define SERV_PORT 10004
#define CLIENT_IP "192.168.0.52"
#define CLIENT_PORT 10104

void *criaServidor() ;
Bme280 request_sensor();
void enviaDistribuido(int item, int status);
