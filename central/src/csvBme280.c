#include <csvBme280.h>

#define BUF_LEN 256

char buffer[BUF_LEN];

void time_generate() {
  time_t current_time;
  struct tm* time_info;

  time(&current_time);
  time_info = localtime(&current_time);

  strftime(buffer, BUF_LEN, "%c", time_info);
}

void csv_init() {
  FILE *file = fopen("bme280Data.csv", "w");
  fprintf(file, "DATETIME,TEMPERATURE, HUMIDITY\n");
  fclose(file);
}

void write_data(Bme280 bme280) {
  // Update Datetime
  time_generate();

  // Write file
  FILE *file = fopen("bme280Data.csv", "a");
  fprintf(
    file,
    "%s,%f,%f\r\n",
    buffer,
    bme280.temperature,
    bme280.humidity
  );
  fclose(file);
}
