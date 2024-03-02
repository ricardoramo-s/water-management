#include <ncurses.h>
#include <string>

/*!
 * @brief main
 */
int main() {
  initscr();

  std::string message = "Hello World!";
  mvprintw(14, 40 - (message.length() / 2), message.c_str());
  getch();

  endwin();
  return 0;
}
