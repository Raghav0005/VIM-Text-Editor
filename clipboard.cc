#include "clipboard.h"
#include <sstream>

Clipboard::Clipboard(Document *document, bool undo)
    : Command(TypeOfCommand::Clipboard, undo, document) {}

void Clipboard::executeCommand() { manageClipboard(); }

void xCommand::manageClipboard() {
  display->copyLine = false;
  display->copyMultiple = false;
  string &s = display->content[display->currentCursor.line];
  size_t &c = display->currentCursor.column;
  string toCopy;
  toCopy = s[c];
  s.erase(c, 1);
  display->setClipboard(toCopy);
}

void XCommand::manageClipboard() {
  display->copyLine = false;
  display->copyMultiple = false;
  string &s = display->content[display->currentCursor.line];
  size_t &c = display->currentCursor.column;
  string toCopy;
  if (c > 0) {
    toCopy = s[c - 1];
    s.erase(c - 1, 1);
    display->setClipboard(toCopy);
  }
  if (c > 0) c--;
}

void PCommand::manageClipboard() {
    size_t &l = display->currentCursor.line;
    string toPaste = display->getClipboard();
    if (toPaste.empty()) return;

    if (display->copyLine || display->copyMultiple) {
        std::istringstream ss(toPaste);
        std::string line;
        std::vector<std::string> lines;
        while (std::getline(ss, line)) {
            lines.push_back(line);
        }
        for (auto it = lines.rbegin(); it != lines.rend(); ++it) {
            display->content.insert(display->content.begin() + l, *it);
        }
        display->currentCursor.column = 0;
    } else {
        string &s = display->content[l];
        size_t &c = display->currentCursor.column;
        c = std::min(c, s.size());
        s.insert(c, toPaste);
        display->currentCursor.column = c;
    }
}

void pCommand::manageClipboard() {
    size_t &l = display->currentCursor.line;
    size_t &c = display->currentCursor.column;
    string &s = display->content[l];
    string toPaste = display->getClipboard();
    if (toPaste.empty()) return;

    if (display->copyMultiple) {
        std::istringstream ss(toPaste);
        std::string line;
        std::vector<std::string> lines;
        while (std::getline(ss, line)) {
            lines.push_back(line);
        }

        for (auto it = lines.rbegin(); it != lines.rend(); ++it) {
            display->content.insert(display->content.begin() + l + 1, *it);
        }
        display->currentCursor.column = 0;
    } else if (display->copyLine) {
        display->content.insert(display->content.begin() + l, toPaste);
        display->currentCursor.column = 0;
    } else {
        if (s.empty() || c >= s.size()) {
            s.append(toPaste);
            display->currentCursor.column = s.size();
            
        } else {
            s.insert(c + 1, toPaste);
            display->currentCursor.column = c + toPaste.size();
        }
    }
}

void yyCommand::manageClipboard() {
  display->copyLine = true;
  display->copyMultiple = false;
  string &s = display->content[display->currentCursor.line];
  if (s.size() > 0) display->setClipboard(s);
}

void yDollarCommand::manageClipboard() {
  display->copyLine = false;
  display->copyMultiple = false;
  string &s = display->content[display->currentCursor.line];
  size_t &col = display->currentCursor.column;
  display->setClipboard(s.substr(col));
}

void yhCommand::manageClipboard() {
  display->copyLine = false;
  display->copyMultiple = false;
  string &s = display->content[display->currentCursor.line];
  size_t &col = display->currentCursor.column;
  if (col != 0) display->setClipboard(s.substr(col - 1, 1));
}

void ylCommand::manageClipboard() {
  display->copyLine = false;
  display->copyMultiple = false;
  string &s = display->content[display->currentCursor.line];
  size_t &col = display->currentCursor.column;
  if (col != display->content.size() - 1) display->setClipboard(s.substr(col + 1, 1));
}

void yjCommand::manageClipboard() {
  display->copyMultiple = true;
  size_t curLine = display->currentCursor.line;
  if (curLine != display->content.size() - 1) {
    string s = display->content[curLine];
    string nexts = display->content[curLine + 1];
    display->setClipboard(s + "\n" + nexts);
  }
}

void ykCommand::manageClipboard() {
  display->copyMultiple = true;
  size_t curLine = display->currentCursor.line;
  if (curLine != 0) {
    string s = display->content[curLine];
    string befores = display->content[curLine - 1];
    display->setClipboard(befores + "\n" + s);
  }
}

void yChevron::manageClipboard() {
  display->copyLine = false;
  display->copyMultiple = false;
  size_t &curLine = display->currentCursor.line;
  size_t &curColumn = display->currentCursor.column;

  string &s = display->content[curLine];
  if (s.size() == 0) {
      curColumn = 0;
      return;
  }
  size_t i = 0;
  char c = s[i];
  while (c == ' ' && i < s.size()) {
      i++;
      c = s[i];
  }

  string subs = s.substr(i, curColumn - i);
  display->setClipboard(subs);
}

void yZero::manageClipboard() {
  display->copyLine = false;
  display->copyMultiple = false;
  size_t curLine = display->currentCursor.line;
  size_t curColumn = display->currentCursor.column;
  
  if (curColumn > 0) {
      string &s = display->content[curLine];
      string toCopy = s.substr(0, curColumn);
      display->setClipboard(toCopy);
  }
}
