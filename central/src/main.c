#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <menu.h>
#include <signal.h>
#include <bme280.h>
#include <quit.h>
#include <lampAc.h>
int main(int argc, char const *argv[])
{

  	quit_init();
    bme280_init();
    csv_init();
    state_init();
    csv_sensors_init();
    csv_lamp_e_ac_init();

    pthread_t menu_tid;
    pthread_t server_tid; //server thread
    pthread_t bme280_tid; //server thread
    pthread_create(&menu_tid, NULL, menu, NULL);
    pthread_create(&server_tid, NULL, criaServidor, NULL);
    pthread_create(&bme280_tid, NULL, bme280_handler, NULL);
    pthread_join(bme280_tid, NULL);
    pthread_join(server_tid, NULL);
    pthread_join(menu_tid, NULL);
    

    return 0;
}
