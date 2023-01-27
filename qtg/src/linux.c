#include "linux.h"
#include <termios.h>

void set_stdin_no_buffer() {
  struct termios tios;
  tcgetattr(0, &tios);
  tios.c_lflag &= ~(ICANON);
  tcsetattr(0, TCSAFLUSH, &tios);
}
