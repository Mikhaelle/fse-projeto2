#include <csvLampEAc.h>
#define BUF_LEN 256

char buffer[BUF_LEN];

void time_generate3() {
  time_t current_time;
  struct tm* time_info;

  time(&current_time);
  time_info = localtime(&current_time);

  strftime(buffer, BUF_LEN, "%c", time_info);
}

void csv_lamp_e_ac_init() {
  FILE *file = fopen("lampEAcData.csv", "w");
  fprintf(file, "DATETIME,ITEM, STATE\n");
  fclose(file);
}

void write_data_lamp_e_ac (int command, int state) {
  // Update Datetime
  time_generate2();
  
  // Write file
  FILE *file = fopen("lampEAcData.csv", "a");
  char item[100];
  memset(item, '\0', sizeof(item));
  if(command == 0){
    strcpy(item,"Lampada da cozinha");
  }
  if(command == 1){
    strcpy(item,"Lampada da sala");
  }
  if(command == 2){
    strcpy(item, "Lampada do quarto1");
  }
  if(command == 3){
    strcpy(item,"Lampada do quarto 2");
  }

  if(command == 23){
    strcpy(item,"Ar-condicionado1");
  }
  if(command == 24){
    strcpy(item,"Ar-condicionad2");
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
