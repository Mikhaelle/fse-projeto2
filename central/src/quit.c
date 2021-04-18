#include <quit.h>
#include <signal.h>

void quit_handler(char *message) {
  refresh();
  endwin();
  int len = strlen(message);
  if (len > 0) {
    printf("%s\n", message);
  }
  exit(0);
}

void quit_handler_signal() {
  refresh();
  endwin();
  exit(0);
}

void quit_init() {
  signal(SIGINT, quit_handler_signal);
}
