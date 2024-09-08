#include "document.h"

#include <iostream>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

const int BAR_HEIGHT = 1;

Document::Document(const Document &other) :
clipboard{other.clipboard},
search{other.search},
content{other.content},
currentCursor{other.currentCursor},
topLine{other.topLine},
copyLine{other.copyLine},
copyMultiple{other.copyMultiple},
searchForward{other.searchForward},
saved{other.saved},
quit{other.quit},
filename{other.filename},
windowSize{other.windowSize} {}

Document &Document::operator=(Document other) {
    clipboard = other.clipboard;
    search = other.search;
    content = other.content;
    currentCursor = other.currentCursor;
    topLine = other.topLine;
    copyLine = other.copyLine;
    copyMultiple = other.copyMultiple;
    filename = other.filename;
    searchForward = other.searchForward;
    saved = other.saved;
    quit = other.quit;
    windowSize = other.windowSize;
    return *this;
}

void Document::updateContent(WINDOW *window, WINDOW *statusBar, int max_y, int max_x) {
    wclear(statusBar);
    wclear(window);

    mvwprintw(statusBar, 0, 1, commandMode ? filename.c_str() : "Insert");
    mvwprintw(statusBar, 0, 14, saved ? "Saved" : "Unsaved");
    mvwprintw(statusBar, 0, max_x - 15, "Column: %zu", currentCursor.column + 1);
    mvwprintw(statusBar, 0, max_x - 25, "Line: %zu", currentCursor.line + topLine);

    if (ctrlgPressed) printInfo(statusBar);
    ctrlgPressed = false;
    
    wrefresh(statusBar);
    
    int i = 1;
    size_t startIndex = topLine - 1;
    for (size_t j = startIndex; j < content.size() && i < max_y - BAR_HEIGHT; ++j) {
        mvwprintw(window, i, 1, content[j].substr(0, max_x - 2).c_str());
        i++;
    }

    wmove(window, currentCursor.line + 1, currentCursor.column + 1);
    wrefresh(window);
}

void Document::setCommandMode(bool commandMode) {this->commandMode = commandMode;}
bool Document::getCommandMode() const {return this->commandMode;}


void Document::saveToFile(const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& line : content) {
            file << line << "\n";
        }
    }
}

void Document::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        content.clear();
        while (getline(file, line)) {
            content.push_back(line);
        }
    }
}

void Document::undoPush(Document d) {
    undoHistory.push(d);
}

void Document::doUndo() {
    if (undoHistory.empty()) return;
    *this = undoHistory.top();
    undoHistory.pop();
}

void Document::printInfo(WINDOW *statusBar) {
    mvwprintw(statusBar, 0, 40, filename.c_str());
    size_t numLines = content.size();
    mvwprintw(statusBar, 0, 50, "%zu lines", numLines);
    double percent = (static_cast<double>(currentCursor.line + topLine) * 100.0) / static_cast<double>(numLines);
    mvwprintw(statusBar, 0, 65, "%.2f%%", percent);
}
