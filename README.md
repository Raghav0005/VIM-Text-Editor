# VM-Text-Editor

This is a fully interactive text editor, developed with a thorough object-oriented design in C++.

### Notable Design Principles and Patterns
- MVC Design Principle
- Factory Method Pattern
- Inheritance and Polymorphism
- SOLID Principles
- RAII (Use of Shared Pointers)
- Cohesion and Coupling

### Features and Command Types
1. Navigation
   - h, j, k, l, $, 0, b, w, ^, %, a, i, A, I, :0, :line-number, f{c}, F{c}
2. Editing
   - S, s, c[all motions], d[all motions], o, O, J, r{c}
3. Clipboard
   - x, X, p, P, yy, y[all motions]
4. Search
   - /, ?, n, N
5. Page Scrolling
   - CtrlB, CtrlF, CtrlD, CtrlU
6. Macros
   - @@, @{register}, q{register}, q
7. Insert Mode
   - Normal Text Editing, Backspace, Enter, Escape
8. File Management
   - :w, :r, :wq, :q!
9. Undo
   - u
10. File Information Display
    - CtrlG
12. Repetition
    - ;, .

Please contact to view and run code (r2vasude@uwaterloo.ca or vasuraghav04@gmail.com).

### Compilation
`
make
`
(Makefile is provided)

### Execution
`
./vm [optional filename]
`

