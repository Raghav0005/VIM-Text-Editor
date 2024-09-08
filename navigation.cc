#include "navigation.h"

Navigation::Navigation(Document *document): 
Command(TypeOfCommand::Navigation, true, document),
column{document->currentCursor.column}, line{document->currentCursor.line} {}
// above contructor constructs command first, then constructs the fields of Navigation

void Navigation::executeCommand() { manageNavigation(); }

void iCommand::manageNavigation() {} // will handle conversion to insert mode before conversion

void hCommand::manageNavigation() {
    if (column > 0) column--; // changing this column shuld change the currentCursor.column as well
    // as this is a reference
}

void jCommand::manageNavigation() {
    if (line < display->content.size() - 1) line++; // change cursor to the next line
    size_t len = display->content[line].size();
    if (len < column) column = len; // go to the end of the current line
}

void kCommand::manageNavigation() {
    if (line > 0) line--;
    size_t len = display->content[line].size();
    if (len < column) column = len;
}

void lCommand::manageNavigation() {
    if (column < display->content[line].size() - 1) column++;
}

void aCommand::manageNavigation() { // will handle toggling to insert mode before converting
    if (column < display->content[line].size()) column++;
}

void Dollar::manageNavigation() {
    column = display->content[line].size() - 1;
}

void Chevron::manageNavigation() {
    string &s = display->content[line];
    if (s.size() == 0) {
        column = 0;
        return;
    }
    column = 0;
    char c = s[column];
    while (c == ' ' && column < s.size()) {
        column++;
        c = s[column];
    }
}

void ZeroCommand::manageNavigation() {
    column = 0;
}

void bCommand::manageNavigation() { // jump backwards to start of word
    string s = display->content[line];
    bool done = false;
    bool whitespace = false;

    while (!done) {
        if (column == 0) {
            if (line == 0 || (s[column] != ' ' && whitespace)) {
                done = true;
            } else {
                s = display->content[--line];
                column = 0;
                whitespace = true;
            }
        } else if (s[column] != ' ' && whitespace) {
            done = true;
        } else {
            if (s[column] == ' ') whitespace = true;
            column--;
        }
    }
}

void wCommand::manageNavigation() { // jump forwards to start of word (opposite of the b command)
    string s = display->content[line];
    bool done = false;
    bool whitespace = false;
    while (!done) {
        if (column == s.size()) {
            if (line + 1 == display->content.size()) {
                done = true;
            } else {
                s = display->content[++line];
                column = 0;
                whitespace = true;
            }
        } else if (s[column] != ' ' && whitespace) {
            done = true;
        } else {
            if (s[column] == ' ') whitespace = true;
            column++;
        }
    }
}

void ColonFirstLine::manageNavigation() {
    line = 0;
    column = 0;
}

void ColonLastLine::manageNavigation() {
    column = 0;
    line = display->content.size() - 1;
}

void ColonSpecificLine::manageNavigation() {
    column = 0;
    line = lineToNavigate > lengthOfFile ? lengthOfFile : lineToNavigate;
}

void fcCommand::manageNavigation() {
    string &s = display->content[display->currentCursor.line];
    size_t c = s.find(character, display->currentCursor.column + 1);
    if (c != string::npos) display->currentCursor.column = c;
}

void FcCommand::manageNavigation() {
    if (display->currentCursor.column == 0) return;
    string &s = display->content[display->currentCursor.line];
    size_t c = display->currentCursor.column - 1;
    while (c > 0 && s[c] != character) c--;
    if (s[c] == character) display->currentCursor.column = c;
}

bool isOpening(char c) {
    return c == '(' || c == '[' || c == '{';
}

bool isClosing(char c) {
    return c == ')' || c == ']' || c == '}';
}

void Percent::manageNavigation() {
    stack<char> brackets = stack<char>();
    size_t &l = display->currentCursor.line;
    size_t &c = display->currentCursor.column;
    
    // check the type of current bracket
    char current_char = display->content[l][c];
    brackets.push(current_char);

    if (isClosing(current_char)) {
        // code to process backwards
        size_t lineIndex = l;
        bool firstLine = true;

        if (c == 0) {
            --lineIndex;
            firstLine = false;
        }    

        while(lineIndex >= 0) {
            string currentLine = display->content[lineIndex];

            size_t i;
            if (!firstLine) {
                i = currentLine.size();
            } else {
                i = c;
            }

            for (size_t index = i; index > 0;) {
                --index;

                current_char = currentLine[index];

                if (isClosing(current_char)) {
                    brackets.push(current_char);

                } else if (isOpening(current_char)) {
                    char top = brackets.top();
                    if (forward.at(current_char) == top) {
                        brackets.pop();
                        if (brackets.empty()) {
                            l = lineIndex;
                            c = index;
                            return;
                        }
                    } else {
                        return; // non-matching brackets
                    }
                }
            }
            --lineIndex;
            firstLine = false;
        }

    } else if (isOpening(current_char)) {
        // code to process forwards
        size_t lineIndex = l;
        bool firstLine = true;

        while (lineIndex < display->content.size()) {
            string currentLine = display->content[lineIndex]; // content at current line

            size_t i = c + 1;
            if (!firstLine) {
                i = 0;
            }

            for (; i < currentLine.size(); ++i) { // start at next column index
                current_char = currentLine[i];

                if (isOpening(current_char)) {
                    brackets.push(current_char);

                } else if (isClosing(current_char)) {
                    char top = brackets.top();
                    if (backward.at(current_char) == top) {
                        brackets.pop();
                        if (brackets.empty()) {
                            l = lineIndex;
                            c = i;
                            return;
                        }
                    } else {
                        return; // non-matching bracket in between - stop the search here
                    }
                } 
            }

            ++lineIndex;
            firstLine = false;
        }
    } else {
        return; // do not proceed further if the currentCursor is not on any required bracket
    }
}
