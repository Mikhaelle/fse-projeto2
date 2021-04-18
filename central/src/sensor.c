#include <sensor.h>
#include <lampAc.h>
#include <menu.h>

Entry _entry;

void init_sensor(){
  _entry.pres1 = 0;
  _entry.pres2 = 0;
  _entry.abr1 = 0;
  _entry.abr2 = 0;
  _entry.abr3 = 0;
  _entry.abr4 = 0;
  _entry.abr5 = 0;
  _entry.abr6 = 0;
  atualiza_sensor(_entry);
}

void state_entry_handler(int command) {
  if (command == 1) {
    if(_entry.pres1 == 0){
      _entry.pres1 = 1;
    }else{
      _entry.pres1 = 0;
    }
    atualiza_sensor(_entry);
  }
  if (command == 2) {
    _entry.pres2 = _entry.pres2 == 1 ? 0 : 1;
    atualiza_sensor(_entry);
  }
  if (command == 3) {
    _entry.abr1 = _entry.abr1 == 1 ? 0 : 1;
    atualiza_sensor(_entry);
  }
  if (command == 4) {
    _entry.abr2 = _entry.abr2 == 1 ? 0 : 1;
    atualiza_sensor(_entry);
  }
  if (command == 5) {
    _entry.abr3 = _entry.abr3 == 1 ? 0 : 1;
    atualiza_sensor(_entry);
  }
  if (command == 6) {
    _entry.abr4 = _entry.abr4 == 1 ? 0 : 1;
    atualiza_sensor(_entry);
  }
  if (command == 7) {
    _entry.abr5 = _entry.abr5 == 1 ? 0 : 1;
    atualiza_sensor(_entry);
  }
  if (command == 8) {
    _entry.abr6 = _entry.abr6 == 1 ? 0 : 1;
    atualiza_sensor(_entry);
  }

  
}