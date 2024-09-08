#include "keyboard.h"

#include <iostream>
#include <string>

#include "command.h"
#include "insert.h"
#include "navigation.h"
#include "clipboard.h"
#include "editing.h"
#include "search.h"
#include "file.h"
#include "scroll.h"
#include "undo.h"
#include "g.h"
#include "macro.h"

#include <algorithm>

using namespace std;

const vector<string> navigation{"h", "j", "k", "l", "$", "0", "b", "w", "^", "%"};
// using direct checking to see if it is "F" or "f", no vector required
const vector<string> switchToInsert{"a", "i", "A", "I"};
const vector<string> editing = {"S", "s", "c", "d", "o", "O", "J", "r"};
const vector<string> clipboard = {"x", "X", "p", "P", "y"};
const vector<string> searching = {"/", "?", "n", "N"};

Keyboard::Keyboard(char c) {input += c;}
Keyboard::Keyboard(const string &str): input{str} {}

shared_ptr<Command> Keyboard::Nav(Document *document) {
 if (input == "h") {
  return make_shared<hCommand>(document);
 } else if (input == "j") {
  return make_shared<jCommand>(document);
 } else if (input == "k") {
  return make_shared<kCommand>(document);
 } else if (input == "l") {
  return make_shared<lCommand>(document);
 } else if (input == "$") {
  return make_shared<Dollar>(document);
 } else if (input == "b") {
  return make_shared<bCommand>(document);
 } else if (input == "w") {
  return make_shared<wCommand>(document);
 } else if (input == "^") {
  return make_shared<Chevron>(document);
 } else if (input == "0") {
  return make_shared<ZeroCommand>(document);
 } else if (input == "%") {
  return make_shared<Percent>(document);
 }
 return make_shared<InvalidCommand>(document);
}

shared_ptr<Command> Keyboard::navWithInsert(Document *document) {
  document->setCommandMode(false);
  if (input == "a") {
    return make_shared<aCommand>(document);
  } else if (input == "i") {
    return make_shared<iCommand>(document);
  } else if (input == "A") {
    return make_shared<Dollar>(document); // performs the same action as $, just puts it to insert mode
  } else if (input == "I") {
    return make_shared<Chevron>(document); // performs the same action as ^, just puts it to insert mode
  }
  return make_shared<InvalidCommand>(document);
}

shared_ptr<Command> Keyboard::clipboardCommands(Document *document) {
  if (input == "x") {
    return make_shared<xCommand>(document);
  } else if (input == "X") {
    return make_shared<XCommand>(document);
  } else if (input == "p") {
    return make_shared<pCommand>(document);
  } else if (input == "P") {
    return make_shared<PCommand>(document);
  } else if (input == "y") {
    input += getch();
    if (input == "yy") {
      return make_shared<yyCommand>(document);
    } else if (input == "y$") {
      return make_shared<yDollarCommand>(document);
    } else if (input == "yh") {
      return make_shared<yhCommand>(document);
    } else if (input == "yl") {
      return make_shared<ylCommand>(document);
    } else if (input == "yj") {
      return make_shared<yjCommand>(document);
    } else if (input == "yk") {
      return make_shared<ykCommand>(document);
    } else if (input == "y0") {
      return make_shared<yZero>(document);
    } else if (input == "y^") {
      return make_shared<yChevron>(document);
    }

  }
  return make_shared<InvalidCommand>(document);
}

shared_ptr<Command> Keyboard::colonCommands(Document *document, WINDOW *window, WINDOW *statusBar) {
  int nextChar;
  document->intermediateCommand = input;
  mvwprintw(statusBar, 0, 25, document->intermediateCommand.c_str());
  wrefresh(statusBar);
  while ((nextChar = getch()) != '\n') {
    input += nextChar;
    document->intermediateCommand += nextChar;
    mvwprintw(statusBar, 0, 25, document->intermediateCommand.c_str());
    wrefresh(statusBar);
  }

  document->intermediateCommand = "";
  mvwprintw(statusBar, 0, 25, "");
  wrefresh(statusBar);  
  if (input == ":0") return make_shared<ColonFirstLine>(document);
  else if (input == ":$") return make_shared<ColonLastLine>(document);
  else if (input.length() == 2 && input == ":w") {
    return make_shared<WriteCommand>(document);
  }
  else if (input.substr(0, 3) == ":w ") {
    document->filename = input.substr(3);
    return make_shared<WriteCommand>(document);

  }
  else if (input == ":q") {
    return make_shared<QuitCommand>(document);
  }
  else if (input == ":wq") {
    return make_shared<WriteandQuitCommand>(document);
  }
  else if (input == ":q!") {
    return make_shared<ForceQuitCommand>(document);
  }
  else if (input.substr(0, 3) == ":r ") {
    cout << input.substr(3);
    return make_shared<ReadCommand>(document, input.substr(3));
  }
  else {
    string linenum = input.substr(1);
    bool number = true;
    size_t num = 0;
    for (auto &i: linenum) {
      if (i < '0' || i > '9') {
        number = false;
        break;
      }
      num = num * 10 + (i - '0');
    }
    if (number) return make_shared<ColonSpecificLine>(document, num - 1, document->content.size() - 1);
  }
  return make_shared<InvalidCommand>(document);
}

shared_ptr<Command> Keyboard::editingCommands(Document *document) {
  if (input == "O") {
    return make_shared<OCommand>(document);
  } else if (input == "o") {
    return make_shared<oCommand>(document);
  } else if (input == "J") {
    return make_shared<JCommand>(document);
  } else if (input == "r") {
    char c = getch();
    return make_shared<rcCommand>(document, c);
  } else if (input == "S") {
    document->setCommandMode(false);
    return make_shared<SCommand>(document);
  } else if (input == "s") {
    document->setCommandMode(false);
    return make_shared<sCommand>(document);
  } else if (input == "c") {
    document->setCommandMode(false);
    input += getch();
    if (input == "cc") {
      return make_shared<SCommand>(document);
    } else if (input == "c$") {
      return make_shared<cDollarCommand>(document);
    } else if (input == "cw") {
      return make_shared<cwCommand>(document);
    } else if (input == "ch") {
      return make_shared<dhCommand>(document);
    } else if (input == "cl") {
      return make_shared<dlCommand>(document);
    } else if (input == "cj") {
      return make_shared<cjCommand>(document);
    } else if (input == "ck") {
      return make_shared<ckCommand>(document);
    } else if (input == "c^") {
      return make_shared<dChevronCommand>(document);
    } else if (input == "c0") {
      return make_shared<dZeroCommand>(document);
    }
  } else if (input == "d") {
    input += getch();
    if (input == "dd") {
      return make_shared<ddCommand>(document);
    } else if (input == "d$") {
      return make_shared<dDollarCommand>(document);
    } else if (input == "dw") {
      return make_shared<dwCommand>(document);
    } else if (input == "dl") {
      return make_shared<dlCommand>(document);
    } else if (input == "dh") {
      return make_shared<dhCommand>(document);
    } else if (input == "dj") {
      return make_shared<djCommand>(document);
    } else if (input == "dk") {
      return make_shared<dkCommand>(document);
    } else if (input == "d^") {
      return make_shared<dChevronCommand>(document);
    } else if (input == "d0") {
      return make_shared<dZeroCommand>(document);
    }
  }
  return make_shared<InvalidCommand>(document);
}

shared_ptr<Command> Keyboard::searchCommands(Document *document, WINDOW *window, WINDOW *statusBar) {
  if (input == "n") {
    return make_shared<nCommand>(document);
  } else if (input == "N") {
    return make_shared<NCommand>(document);
  } else {
    int nextChar;
    document->intermediateCommand = input;
    mvwprintw(statusBar, 0, 25, document->intermediateCommand.c_str());
    wrefresh(statusBar);
    while ((nextChar = getch()) != '\n') {
      input += nextChar;
      document->intermediateCommand += nextChar;
      mvwprintw(statusBar, 0, 25, document->intermediateCommand.c_str());
      wrefresh(statusBar);
    }
    document->intermediateCommand = "";
    mvwprintw(statusBar, 0, 25, "");
    wrefresh(statusBar); 
    
    if (input[0] == '/') {
      return make_shared<Slash>(document, input.substr(1));
    } else if (input[0] == '?') {
      return make_shared<Question>(document, input.substr(1));
    }
  }
  return make_shared<InvalidCommand>(document);
}

shared_ptr<Command> Keyboard::macroCommands(Document *document) {
  int nextChar;
  while((nextChar = getch()) != '\n') {
    input += nextChar;
  }

  if (input == "q") {
    macroOn = false; // now we are finishing recording macros

    shared_ptr<Command> toReturn = make_shared<qCommand>(document);
    macros[macroRegister] = commandsMacro; // put it in the map, once it has been finalized

    while (!commandsMacro.empty()) { // empty the queue
      commandsMacro.pop();
    }
    macroRegister = ""; // reset the register key

    return toReturn;

  } else if (input.size() > 1 && input.at(0) == 'q') {
    macroOn = true; // we are now recording macros
    commandsMacro = queue<shared_ptr<Command>>(); // initialize the macro queue
    macroRegister = input.substr(1);
    
    return make_shared<qRegister>(document);

  } else if (input == "@@") {
    return make_shared<atRegister>(document, macros[lastKey]);

  } else if (input.size() > 1 && input.at(0) == '@') {
    string key = input.substr(1); // obtain the register name
    lastKey = key; // place the last tried key in lastKey
    if (macros.count(key) == 0) return make_shared<InvalidCommand>(document);
    return make_shared<atRegister>(document, macros[key]);
    
  }
  return make_shared<InvalidCommand>(document);
}

shared_ptr<Command> Keyboard::convert(Document *document, WINDOW *window, WINDOW *statusBar) {
  shared_ptr<Command> invalidCommand = make_shared<InvalidCommand>(document);
  if (document->getCommandMode()) { // it is in command mode
    if (find(navigation.begin(), navigation.end(), input) != navigation.end()) {
        lastCommand = Nav(document);

        if (macroOn) {
          commandsMacro.push(lastCommand);
          return invalidCommand;
        }

        return lastCommand;

    } else if (input == "F") { // since these commands can be rerun with ';
        char c = getch();
        lastCommand = make_shared<FcCommand>(document, c);

        if (macroOn) {
          commandsMacro.push(lastCommand);
          return invalidCommand;
        }

        return lastCommand;

    } else if (input == "f") {
        char c = getch();
        lastCommand = make_shared<fcCommand>(document, c);

        if (macroOn) {
          commandsMacro.push(lastCommand);
          return invalidCommand;
        }

        return lastCommand;

    } else if ((find(switchToInsert.begin(), switchToInsert.end(), input) != switchToInsert.end())) {
        lastCommand = navWithInsert(document);

        if (macroOn) {
          commandsMacro.push(lastCommand);
          return invalidCommand;
        }
        
        return lastCommand;

    } else if ((find(clipboard.begin(), clipboard.end(), input) != clipboard.end())) {
        lastCommand = clipboardCommands(document);
        document->saved = false;

        if (macroOn) {
          commandsMacro.push(lastCommand);
          return invalidCommand;
        }
        return lastCommand;

    } else if ((find(editing.begin(), editing.end(), input) != editing.end())) {
        lastCommand = editingCommands(document);
        document->saved = false;

        if (macroOn) {
          commandsMacro.push(lastCommand);
          return invalidCommand;
        }
        return lastCommand;

    } else if ((find(searching.begin(), searching.end(), input) != searching.end())) {
        lastCommand = searchCommands(document, window, statusBar);

        if (macroOn) {
          commandsMacro.push(lastCommand);
          return invalidCommand;
        }
        return lastCommand;

    } else if (input == ":") {
        lastCommand = colonCommands(document, window, statusBar); // not recording colon commands
        return lastCommand;

    } else if (input == "CTRLb") {
        lastCommand = make_shared<CtrlBCommand>(document);

        if (macroOn) {
          commandsMacro.push(lastCommand);
          return invalidCommand;
        }
        return lastCommand;

    } else if (input == "CTRLd") {
        lastCommand = make_shared<CtrlDCommand>(document);

        if (macroOn) {
          commandsMacro.push(lastCommand);
          return invalidCommand;
        }
        return lastCommand;

    } else if (input == "CTRLf") {
        lastCommand = make_shared<CtrlFCommand>(document);

        if (macroOn) {
          commandsMacro.push(lastCommand);
          return invalidCommand;
        }
        return lastCommand;

    } else if (input == "CTRLg") { // CTRLg is not recorded for a macro
        lastCommand = make_shared<CtrlG>(document);
        return lastCommand;

    } else if (input == "CTRLu") {
        lastCommand = make_shared<CtrlUCommand>(document);

        if (macroOn) {
          commandsMacro.push(lastCommand);
          return invalidCommand;
        }
        return lastCommand;

    } else if (input == ".") {
      if (lastCommand) {
        if (macroOn) {
          commandsMacro.push(lastCommand);
          return invalidCommand;
        }

        return lastCommand;
      }

    } else if (input == ";") {
      if (auto F = dynamic_pointer_cast<FcCommand>(lastCommand)) {
        if (macroOn) {
          commandsMacro.push(lastCommand);
          return invalidCommand;
        }
        return lastCommand;

      } else if (auto f = dynamic_pointer_cast<fcCommand>(lastCommand)) {
        if (macroOn) {
          commandsMacro.push(lastCommand);
          return invalidCommand;
        }

        return lastCommand;
      }

    } else if (input == "u") {
      shared_ptr<Command> c = make_shared<Undo>(document);
      if (macroOn) {
          commandsMacro.push(c);
          return invalidCommand;
      }

      return c;

    } else if (input == "q" || input == "@") {
      return macroCommands(document);
    }
 
  } else {
    // insert mode is on
    document->saved = false;
    shared_ptr<Command> c = nullptr;

    if (input == "enter") {
      c = make_shared<Enter>(document);
    } else if (input == "escape") {
      c = make_shared<Escape>(document);
    } else if (input == "backspace") {
      c = make_shared<Backspace>(document);
    } else {
      c = make_shared<Insert>(input, document);
    }

    if (macroOn) {
      commandsMacro.push(c);
      return invalidCommand;
    }
    return c;

  }
  return invalidCommand;
}
