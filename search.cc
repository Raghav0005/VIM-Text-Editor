#include "search.h"

Search::Search(Document *document): Command(TypeOfCommand::Search, false, document) {}

void Search::executeCommand() { manageSearch(); }

void Slash::manageSearch() {
    size_t &curLine = display->currentCursor.line;
    size_t &curCol = display->currentCursor.column;
    bool patternFound = false;

    // Loop through each line starting from the current line
    for (size_t line = curLine; line < display->content.size() && !patternFound; ++line) {
        string &s = display->content[line];
        size_t startPos = (line == curLine) ? curCol : 0; // Start from currentColumn in the current line, 0 in others
        size_t pos = s.find(pattern, startPos);

        // If pattern is found
        if (pos != string::npos) {
            // Update cursor position
            curLine = line;
            curCol = pos;
            patternFound = true; // Pattern found, break the loop
        }
    }
}

void Question::manageSearch() {
    size_t &curLine = display->currentCursor.line;
    size_t &curCol = display->currentCursor.column;

    // Flag to indicate if the pattern is found
    bool patternFound = false;

    // Iterate backwards starting from the current line
    for (size_t line = curLine; line >= 0 && !patternFound; --line) {
        string &s = display->content[line];

        // Determine the start position for search
        size_t startPos;
        if (line == curLine) {
            // In the current line, start just before the current column
            startPos = (curCol > 0) ? curCol - 1 : string::npos;
        } else {
            // In previous lines, start from the end of the line
            startPos = s.length();
        }

        // Search for the pattern
        size_t pos = (startPos != string::npos) ? s.rfind(pattern, startPos) : string::npos;

        // If pattern is found
        if (pos != string::npos) {
            // Update cursor position
            curLine = line;
            curCol = pos;
            patternFound = true; // Pattern found, stop the loop
        }
    }
}

void nCommand::manageSearch() {
    if (display->searchForward) {
        searchForward(display->getSearch(), display);
    } else {
        searchBackward(display->getSearch(), display);
    }
}

void NCommand::manageSearch() {
    if (display->searchForward) {
        searchBackward(display->getSearch(), display);
    } else {
        searchForward(display->getSearch(), display);
    }
}

void searchForward(const string& pattern, Document *display) {
    size_t &curLine = display->currentCursor.line;
    size_t &curCol = display->currentCursor.column;
    bool patternFound = false;

    for (size_t line = curLine; line < display->content.size() && !patternFound; ++line) {
        string &s = display->content[line];
        size_t startPos = (line == curLine) ? curCol + 1 : 0;
        size_t pos = s.find(pattern, startPos);

        if (pos != string::npos) {
            curLine = line;
            curCol = pos;
            patternFound = true;
        }
    }
}

void searchBackward(const string& pattern, Document *display) {
    size_t &curLine = display->currentCursor.line;
    size_t &curCol = display->currentCursor.column;
    bool patternFound = false;

    for (size_t line = curLine; line >= 0 && !patternFound; --line) {
        string &s = display->content[line];

        // For the current line, start the search just before the current cursor position
        // For previous lines, start from the end of the line
        size_t startPos = (line == curLine && curCol > 0) ? curCol - 1 : s.length();

        // Search the pattern
        size_t pos = s.rfind(pattern, startPos);

        // Check if the pattern is found and is before the current cursor position
        if (pos != string::npos && (line < curLine || pos < curCol)) {
            curLine = line;
            curCol = pos;
            patternFound = true;
        }
    }
}
