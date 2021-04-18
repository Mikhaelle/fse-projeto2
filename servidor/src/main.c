#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <bme280.h>
#include <cliente.h>
#include <gpio.h>

// Define some device parameters
#define I2C_ADDR 0x76 // I2C device address
#define I2C_CH 1      // I2C device channel

void quit_handler()
{
  all_off();
  exit(0);
}

int main(int argc, char const *argv[])
{
  gpio_init();
  signal(SIGINT, quit_handler);
  bme280Init(I2C_CH, I2C_ADDR);

  all_off();
  pthread_t client_tid, gpio_tid;
  pthread_create(&client_tid, NULL, criaCliente, NULL);
  pthread_create(&gpio_tid, NULL, gpio_handler, NULL);
  pthread_join(client_tid, NULL);
  pthread_join(gpio_tid, NULL);
  quit_handler();

  return 0;
}
