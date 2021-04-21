#include <csvSensors.h>

#define BUF_LEN 256

char buffer[BUF_LEN];

void time_generate2() {
  time_t current_time;
  struct tm* time_info;

  time(&current_time);
  time_info = localtime(&current_time);

  strftime(buffer, BUF_LEN, "%c", time_info);
}

void csv_sensors_init() {
  FILE *file = fopen("sensorsData.csv", "w");
  fprintf(file, "DATETIME,ITEM, STATE\n");
  fclose(file);
}

void write_data_sensors (int command, int state) {
  // Update Datetime
  time_generate2();
  
  // Write file
  FILE *file = fopen("sensorsData.csv", "a");
  char item[100];
  memset(item, '\0', sizeof(item));
  if(command == 1){
    strcpy(item,"Sensor de Presença Sala");
  }
  if(command == 2){
    strcpy(item,"Sensor de Presença Cozinha");
  }
  if(command == 3){
    strcpy(item,"Sensor porta cozinha");
  }
  if(command == 4){
    strcpy(item,"Sensor janela cozinha");
  }

  if(command == 5){
    strcpy(item,"Sensor porta sala");
  }
  if(command == 6){
    strcpy(item,"Sensor janela sala");
  }
  if(command == 7){
    strcpy(item,"Sensor janela quarto 1");
  }
  if(command == 8){
    strcpy(item,"Sensor janela quarto 2");
  }

  fprintf(
    file,
    "%s,%s,%d\r\n",
    buffer,
    item,
    state
  );
  fclose(file);
}
