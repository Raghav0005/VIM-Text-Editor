#include "editing.h"

Editing::Editing(Document *document): Command(TypeOfCommand::Editing, true, document) {}

void Editing::executeCommand() { manageEditing(); }

void SCommand::manageEditing() {
    if (display->content.size() == 0) return;
    size_t &curline = display->currentCursor.line;
    display->content[curline].clear();
    display->currentCursor.column = 0;
}

void sCommand::manageEditing() {
    size_t &l = display->currentCursor.line;
    size_t &col = display->currentCursor.column;
    string &s = display->content.at(l); // string at line l
    if (col > 0) s.erase(col, 1); // more than 1 char at line;
    else if (l > 0) { // col == 0 and l > 0
        string &previous = display->content.at(l - 1);
        col = previous.size();
        previous += s;
        display->content.erase(display->content.begin() + l--);
    } else { // col == 0 and l > 0
        s.erase(0, 1);
    }
}

void oCommand::manageEditing() {
    display->content.insert(display->content.begin() + ++display->currentCursor.line, "");
    display->currentCursor.column = 0;
    display->setCommandMode(false);
}

void OCommand::manageEditing() {
    display->content.insert(display->content.begin() + display->currentCursor.line, "");
    display->currentCursor.column = 0;
    display->setCommandMode(false);
}

void JCommand::manageEditing() {
    size_t &l = display->currentCursor.line;
    if (l + 1 < display->content.size()) {
        display->currentCursor.column = display->content[l].size();
        display->content[l] += " "; // adding the space
        display->content[l] += display->content[l+1];
        display->content.erase(display->content.begin() + l + 1);
    }
}

void rcCommand::manageEditing() {
    display->content[display->currentCursor.line][display->currentCursor.column] = character;
}

void cDollarCommand::manageEditing() {
    string &s = display->content[display->currentCursor.line];
    size_t lengthToRemove = s.size() - display->currentCursor.column;
    s.erase(display->currentCursor.column, lengthToRemove);
}

void ddCommand::manageEditing() {
    if (display->content.size() == 0) return;
    size_t &curline = display->currentCursor.line;
    display->content.erase(display->content.begin() + curline);
    display->currentCursor.column = 0;
}

void dwCommand::manageEditing() {
    size_t &l = display->currentCursor.line;
    size_t &c = display->currentCursor.column;
    string &s = display->content[l];
    size_t lastIndex = c;
    bool isSpace = false;

    for (; lastIndex < s.size(); lastIndex++) {
        char& ch = s[lastIndex];
        if (ch == ' ' && !isSpace) {
            isSpace = true;
        } else if (ch != ' ' && isSpace) {
            break;
        }
    }
    s.erase(c, lastIndex - c);
}

void cwCommand::manageEditing() {
    size_t &l = display->currentCursor.line;
    size_t &c = display->currentCursor.column;
    string &s = display->content[l];
    size_t lastIndex = c;
    bool foundNonSpace = (s[c] != ' ');

    for (; lastIndex < s.size(); lastIndex++) {
        char& ch = s[lastIndex];
        if (ch == ' ' && foundNonSpace) {
            break;
        } else if (ch != ' ') {
            foundNonSpace = true;
        }
    }
    s.erase(c, lastIndex - c);
}

void dDollarCommand::manageEditing() {
    size_t &curline = display->currentCursor.line;
    string &lineText = display->content[curline];
    size_t &col = display->currentCursor.column;
    lineText.erase(col--);
}

void dlCommand::manageEditing() {
    size_t &col = display->currentCursor.column;
    string &s = display->content[display->currentCursor.line];
    s.erase(col, 1);
    if (col == display->content[display->currentCursor.line].size()) col--;
}

void dhCommand::manageEditing() {
    size_t &col = display->currentCursor.column;
    if (col == 0) return;
    string &s = display->content[display->currentCursor.line];
    s.erase(col - 1, 1);
    col--;
}

void djCommand::manageEditing() {
    size_t &col = display->currentCursor.column;
    size_t &l = display->currentCursor.line;
    if (l == display->content.size() - 1) return;

    display->content.erase(display->content.begin() + l + 1);
    display->content.erase(display->content.begin() + l);
    col = 0;
    size_t len = display->content.size();
    l = (l > len - 1) ? len - 1 : l;
}

void dkCommand::manageEditing() {
    size_t &col = display->currentCursor.column;
    size_t &l = display->currentCursor.line;
    if (l == 0) return;

    display->content.erase(display->content.begin() + l);
    display->content.erase(display->content.begin() + l - 1);

    col = 0;
    size_t len = display->content.size();
    l = (l > len - 1) ? len - 1 : l - 1;
}

void cjCommand::manageEditing() {
    size_t &col = display->currentCursor.column;
    size_t &l = display->currentCursor.line;

    if (l == display->content.size() - 1) return;

    display->content.erase(display->content.begin() + l + 1);
    display->content[l].erase();
    col = 0;
}

void ckCommand::manageEditing() {
    size_t &col = display->currentCursor.column;
    size_t &l = display->currentCursor.line;

    if (l == 0) return;
    display->content.erase(display->content.begin() + l);
    display->content[l - 1].erase();
    col = 0;
    l = l - 1;
}

void dZeroCommand::manageEditing() {
    size_t &l = display->currentCursor.line;
    size_t &col = display->currentCursor.column;
    string &s = display->content[l];

    s.erase(0, col);
    col = 0;
}

void dChevronCommand::manageEditing() {
    size_t &l = display->currentCursor.line;
    size_t &col = display->currentCursor.column;
    string &s = display->content[l];

    size_t count = 0;
    char c = s[count];
    while (c == ' ' && count < s.size()) {
        count++;
        c = s[count];
    }

    s.erase(count, col - count);
    col = count;
}
