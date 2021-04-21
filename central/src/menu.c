#include <ncurses.h>
#include <stdlib.h>
#include <menu.h>
#include <lampAc.h>
#include <sensor.h>

Bme280 bme280;
State state;
WINDOW * menuwin;
Entry entry;

void print_lampadas(WINDOW * menuwin ){
    char choicesLampAc[6][50] = {"Lampada da cozinha", "Lampada da sala", "Lampada do quarto1", "Lampada do quarto 2", "Ar-condicionado1", "Ar-condicionad2"};
    for(int i = 0; i < 6; i++){
           
            mvwprintw(menuwin, i+1, 40, choicesLampAc[i]);
        }
}

void print_sensores(WINDOW * menuwin ){
    char choicesLampAc[9][50] = {"Sensor de Presença Sala", "Sensor de Presença Cozinha", "Sensor porta cozinha", "Sensor janela cozinha", 
                                "Sensor porta sala", "Sensor janela sala", "Sensor janela quarto 1", "Sensor janela quarto 2", "Alarme"};
    for(int i = 0; i < 9; i++){
           
            mvwprintw(menuwin, i+1, 66, choicesLampAc[i]);
        }
}

void print_state(WINDOW * menuwin ){
       wattron(menuwin, COLOR_PAIR(state.lamp1 == 1 ? 3 : 2));
	   mvwprintw(menuwin, 1, 60, state.lamp1 == 1 ? "ON " : "OFF");
	   wattroff(menuwin, COLOR_PAIR(state.lamp1 == 1 ? 3 : 2));

       wattron(menuwin, COLOR_PAIR(state.lamp2 == 1 ? 3 : 2));
	   mvwprintw(menuwin, 2, 60, state.lamp2 == 1 ? "ON " : "OFF");
	   wattroff(menuwin, COLOR_PAIR(state.lamp2 == 1 ? 3 : 2));

       wattron(menuwin, COLOR_PAIR(state.lamp3 == 1 ? 3 : 2));
	   mvwprintw(menuwin, 3, 60, state.lamp3 == 1 ? "ON " : "OFF");
	   wattroff(menuwin, COLOR_PAIR(state.lamp3 == 1 ? 3 : 2));

       wattron(menuwin, COLOR_PAIR(state.lamp4 == 1 ? 3 : 2));
	   mvwprintw(menuwin, 4, 60, state.lamp4 == 1 ? "ON " : "OFF");
	   wattroff(menuwin, COLOR_PAIR(state.lamp4 == 1 ? 3 : 2));

       wattron(menuwin, COLOR_PAIR(state.ac1 == 1 ? 3 : 2));
	   mvwprintw(menuwin, 5, 60, state.ac1 == 1 ? "ON " : "OFF");
	   wattroff(menuwin, COLOR_PAIR(state.ac1 == 1 ? 3 : 2));

       wattron(menuwin, COLOR_PAIR(state.ac2 == 1 ? 3 : 2));
	   mvwprintw(menuwin, 6, 60, state.ac2 == 1 ? "ON " : "OFF");
	   wattroff(menuwin, COLOR_PAIR(state.ac2 == 1 ? 3 : 2));

      
}

void print_entry(WINDOW * menuwin ){
       wattron(menuwin, COLOR_PAIR(entry.pres1 == 1 ? 3 : 2));
	mvwprintw(menuwin, 1, 94, entry.pres1 == 1 ? "ON " : "OFF");
	wattroff(menuwin, COLOR_PAIR(entry.pres1 == 1 ? 3 : 2));

    wattron(menuwin, COLOR_PAIR(entry.pres2 == 1 ? 3 : 2));
	mvwprintw(menuwin, 2, 94, entry.pres2 == 1 ? "ON " : "OFF");
	wattroff(menuwin, COLOR_PAIR(entry.pres2 == 1 ? 3 : 2));

    wattron(menuwin, COLOR_PAIR(entry.abr1 == 1 ? 3 : 2));
	mvwprintw(menuwin, 3, 94, entry.abr1 == 1 ? "ON " : "OFF");
	wattroff(menuwin, COLOR_PAIR(entry.abr1 == 1 ? 3 : 2));

    wattron(menuwin, COLOR_PAIR(entry.abr2 == 1 ? 3 : 2));
	mvwprintw(menuwin, 4, 94, entry.abr2 == 1 ? "ON " : "OFF");
	wattroff(menuwin, COLOR_PAIR(entry.abr2 == 1 ? 3 : 2));

    wattron(menuwin, COLOR_PAIR(entry.abr3 == 1 ? 3 : 2));
	mvwprintw(menuwin, 5, 94, entry.abr3 == 1 ? "ON " : "OFF");
	wattroff(menuwin, COLOR_PAIR(entry.abr3 == 1 ? 3 : 2));

    wattron(menuwin, COLOR_PAIR(entry.abr4 == 1 ? 3 : 2));
	mvwprintw(menuwin, 6, 94, entry.abr4 == 1 ? "ON " : "OFF");
	wattroff(menuwin, COLOR_PAIR(entry.abr4 == 1 ? 3 : 2));

    wattron(menuwin, COLOR_PAIR(entry.abr5 == 1 ? 3 : 2));
	mvwprintw(menuwin, 7, 94, entry.abr5 == 1 ? "ON " : "OFF");
	wattroff(menuwin, COLOR_PAIR(entry.abr5 == 1 ? 3 : 2));

    wattron(menuwin, COLOR_PAIR(entry.abr6 == 1 ? 3 : 2));
	mvwprintw(menuwin, 8, 94, entry.abr6 == 1 ? "ON " : "OFF");
	wattroff(menuwin, COLOR_PAIR(entry.abr6 == 1 ? 3 : 2));

    wattron(menuwin, COLOR_PAIR(entry.alarm == 1 ? 3 : 2));
	mvwprintw(menuwin, 9, 94, entry.alarm == 1 ? "ON " : "OFF");
    wattroff(menuwin, COLOR_PAIR(entry.alarm == 1 ? 3 : 2));
}

void print_bme(WINDOW * menuwin){
wattron(menuwin, COLOR_PAIR(1));
        mvwprintw(menuwin, 10, 1, "TEMPERATURE: %lf", bme280.temperature);
        mvwprintw(menuwin, 11, 1, "HUMIDITY: %lf", bme280.humidity);
	    wattroff(menuwin, COLOR_PAIR(1));
}

void *menu()
{  
    initscr();
	start_color(); 
	clear();
	noecho();
	cbreak();
	curs_set(0);
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    menuwin = newwin(15, 130,1 , 15);
    box(menuwin, 0, 0);
    refresh();
    wrefresh(menuwin);

    keypad(menuwin, true);

    char choices[8][50] = {"Ligar/Desligar lampada da cozinha", "Ligar/Desligar lampaga da sala", "Ligar/Desligar lampaga do quarto1", 
                        "Ligar/Desligar lampaga do quarto2", "Ligar/Desligar ar-condicionado 01", "Ligar/Desligar ar-condicionado 02", "Ligar/Desligar alarme", "Sair"};
    
    char choicesLampAc[1][50] = {"Lampada da cozinha"};
    int choice, option = 0;
    int highlight = 0;

    while(1){
        for(int i = 0; i < 8; i++){
            if( i == highlight)
                wattron(menuwin, A_REVERSE);
            mvwprintw(menuwin, i+1, 1, choices[i]);
            wattroff(menuwin, A_REVERSE);
        }
        

       print_lampadas( menuwin );
       print_sensores( menuwin );
       print_state( menuwin );
       print_bme(menuwin);
       print_entry(menuwin );

        choice = wgetch(menuwin);

        switch(choice){
            case KEY_UP:
                highlight--;
                if(highlight == -1)
                    highlight = 0;
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight==8)
                    highlight = 7;
                break;
            case 10:    
				option = highlight;

				if (option == 0) {
                    if(state.lamp1 == 0 ){
                            state.lamp1 = 1;
                    }else{
                        state.lamp1 =0;
                    }
                    sendComand(state);
				}

				if (option == 1) {
                    if(state.lamp2 == 0 ){
                            state.lamp2 = 1;
                    }else{
                        state.lamp2 =0;
                    }
                    sendComand(state);
				}

				if (option == 2) {
                    if(state.lamp3 == 0 ){
                            state.lamp3 = 1;
                    }else{
                        state.lamp3 =0;
                    }
                    sendComand(state);
				}

				if (option == 3) {
                    if(state.lamp4 == 0 ){
                            state.lamp4 = 1;
                    }else{
                        state.lamp4 =0;
                    }
                    sendComand(state);
				}

				if (option == 4) {
                    if(state.ac1 == 0 ){
                            state.ac1 = 1;
                    }else{
                        state.ac1 =0;
                    }
                    sendComand(state);
				}

				if (option == 5) {
                    
                     if(state.ac2 == 0 ){
                            state.ac2 = 1;
                    }else{
                        state.ac2 =0;
                    }
                    sendComand(state);
				}

				if (option == 6) {
                      if(entry.alarm == 0 ){
                            entry.alarm = 1;
                            tocaAlarme(9);
                    }else{
                        entry.alarm =0;
                    }
				}
				if (option == 7) {
					char *message = "Exiting...";
					quit_handler(message);
				}

				break;
			default:
				refresh();
				break;
        }
    }

    getch();
    endwin();

    return 0;
}

void atualiza_bme280(Bme280 bme280Atualizado){
    bme280 = bme280Atualizado;
    print_bme(menuwin);
    refresh();
    wrefresh(menuwin);
}

void atualizaState(State stateAtt){
    state = stateAtt;

}

void atualiza_sensor(Entry sensorAtt){
    entry = sensorAtt;
    print_entry(menuwin );
}