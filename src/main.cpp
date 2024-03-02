#include <ncurses.h>
#include "ui/TextBox.h"
#include "ui/Box.h"
#include "ui/TextLabel.h"
#include "ui/InputLabel.h"
#include <string>

int main() {
  initscr();
  curs_set(0);

  auto inputLabel = new InputLabel(15, 2, 3, "test label");
  auto box = new Box<InputLabel>(inputLabel);
  refresh();

  do {
      inputLabel->handle_input();
      clear();
      box->draw();
  } while (!inputLabel->get_input_flag());

  clear();
  delete inputLabel;

  endwin();
  return 0;
}
