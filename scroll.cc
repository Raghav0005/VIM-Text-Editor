#include "scroll.h"

using namespace std;

void Scroll::executeCommand() { manageScroll(); }

void CtrlBCommand::manageScroll() {
    if (tpLine > windowSize) {
        tpLine -= windowSize;
    } else {
        tpLine = 1;
    }

    display->currentCursor.line = 0;
    display->currentCursor.column = 0;
}

void CtrlDCommand::manageScroll() {
    size_t halfWindowHeight = windowSize / 2;
    size_t maxTpLine = display->content.size() > windowSize ? display->content.size() - windowSize + 1 : 1;

    if (tpLine <= maxTpLine - halfWindowHeight) {
        tpLine += halfWindowHeight;
    } else {
        tpLine = maxTpLine;
    }

    display->currentCursor.line = 0;
    display->currentCursor.column = 0; 
}

void CtrlFCommand::manageScroll() {
    size_t maxTpLine = display->content.size() > windowSize ? display->content.size() - windowSize + 1 : 1;

    if (tpLine <= maxTpLine - windowSize) {
        tpLine += windowSize;
    } else {
        tpLine = maxTpLine;
    }

    display->currentCursor.line = 0;
    display->currentCursor.column = 0;
}

void CtrlUCommand::manageScroll() {
    size_t halfWindowHeight = windowSize / 2;

    if (tpLine > halfWindowHeight) {
        tpLine -= halfWindowHeight;
    } else {
        tpLine = 1;
    }

    display->currentCursor.line = 0;
    display->currentCursor.column = 0;
}
