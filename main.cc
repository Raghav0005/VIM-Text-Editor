#include <ncurses.h>

#include <fstream>
#include <iostream>
#include <string>

#include "command.h"
#include "document.h"
#include "keyboard.h"

using namespace std;

const int KEY_ESCAPE = 27;
const int NEW_LINE = 10;
const int BAR_HEIGHT = 1;
const int CTRLb = 2;
const int CTRLd = 4;
const int CTRLf = 6;
const int CTRLg = 7;
const int CTRLu = 21;


int main(int argc, char *argv[]) {
  int max_y, max_x;
  string filename = "";

  if (argc > 1) {
    filename = argv[1];
  }

  initscr();
  keypad(stdscr, TRUE);
  noecho();

  getmaxyx(stdscr, max_y, max_x);
  WINDOW* statusBar = newwin(BAR_HEIGHT, max_x, max_y - 1, 0);
  WINDOW* win = newwin(max_y - BAR_HEIGHT, max_x, 0, 0);
  refresh();

  Document doc(filename, max_y - BAR_HEIGHT);
  
  doc.updateContent(win, statusBar, max_y, max_x); // to load anything already existing

  while (true) {
    if (doc.quit) break;
    int ch = getch();
    Keyboard inp;
    size_t lenLine;
    switch (ch) {
      case KEY_UP:
        if (doc.currentCursor.line > 0) doc.currentCursor.line--;
        lenLine = doc.content[doc.currentCursor.line].size();
        if (lenLine < doc.currentCursor.column) doc.currentCursor.column = lenLine;
        break;
      case KEY_DOWN:
        if (doc.currentCursor.line < doc.content.size() - 1) doc.currentCursor.line++;
        lenLine = doc.content[doc.currentCursor.line].size();
        if (lenLine < doc.currentCursor.column) doc.currentCursor.column = lenLine;
        break;
      case KEY_LEFT:
        if (doc.currentCursor.column > 0) doc.currentCursor.column--;
        break;
      case KEY_RIGHT:
        if (doc.currentCursor.column < doc.content[doc.currentCursor.line].size()) doc.currentCursor.column++;
        break;
      default:
        switch (ch) {
          case KEY_BACKSPACE:
            inp = Keyboard{"backspace"};
            break;
          case KEY_ESCAPE:
            inp = Keyboard{"escape"};
            break;
          case NEW_LINE:
            inp = Keyboard{"enter"};
            break;
          case CTRLb:
            inp = Keyboard{"CTRLb"};
            break;
          case CTRLd:
            inp = Keyboard{"CTRLd"};
            break;
          case CTRLf:
            inp = Keyboard{"CTRLf"};
            break;
          case CTRLg:
            inp = Keyboard{"CTRLg"};
            break;
          case CTRLu:
            inp = Keyboard{"CTRLu"};
            break;
          default:
            inp = Keyboard{ch};
            break;
        }
        auto c = inp.convert(&doc, win, statusBar);
        c->manageCommand();
        break;
    }
    if (doc.quit) break;
    doc.updateContent(win, statusBar, max_y, max_x);
    if (doc.quit) break;
  }

  delwin(win);
  endwin();
}
