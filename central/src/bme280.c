#include <menu.h>

#define SECOND 1000000

void bme280_init() {
  Bme280 bme280;
  bme280.temperature = 0;
  bme280.humidity = 0;
}

void* bme280_handler() {
  while (1) {
   Bme280 bme280 = request_sensor();
    write_data(bme280);
    atualiza_bme280(bme280);
    usleep(SECOND);
  }

  return NULL;
}