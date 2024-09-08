#include "insert.h"

#include <cstddef>
#include <iostream>
using namespace std;

Insert::Insert(string c, Document *document): Command(TypeOfCommand::Insert, true, document), c{c} {}

void Insert::executeCommand() {
    string &s = display->content.at(display->currentCursor.line);
    s.insert(display->currentCursor.column++, c);
}

Enter::Enter(Document *document): Command(TypeOfCommand::Enter, true, document) {}

void Enter::executeCommand() {
    size_t &current_column = display->currentCursor.column;
    size_t &current_line = display->currentCursor.line;
    string &current_string = display->content.at(current_line);

    // Ensure the column index is within the string length
    current_column = std::min(current_column, current_string.length());

    // Split the current line at the cursor position
    string first_half = current_string.substr(0, current_column);
    string second_half = current_string.substr(current_column);

    // Update the current line and insert the second half as a new line
    display->content[current_line] = first_half;
    display->content.insert(display->content.begin() + current_line + 1, second_half);

    // Update cursor position
    current_line++;
    current_column = 0;
}


Backspace::Backspace(Document *document): Command(TypeOfCommand::Backspace, true, document) {}

void Backspace::executeCommand() {
    size_t &current_column = display->currentCursor.column;
    size_t &current_line = display->currentCursor.line;
    if (current_line == 0 && current_column == 0) return;
    string &current_string = display->content.at(current_line);
    if (current_column > 0) {
        current_string.erase(--current_column, 1);
    } else {
        string &prev = display->content.at(current_line - 1);
        current_column = prev.size();
        prev += current_string;
        display->content.erase(display->content.begin() + current_line--);
    }
}

Escape::Escape(Document *document): Command(TypeOfCommand::Escape, true, document) {}
void Escape::executeCommand() {
    size_t &current_column = display->currentCursor.column;
    if (current_column > 0) current_column--;
    display->setCommandMode(true);
}

