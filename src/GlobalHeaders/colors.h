#ifndef COLORS_H
#define COLORS_H

#define BLACK   "0"
#define RED     "1"
#define GREEN   "2"
#define YELLOW  "3"
#define BLUE    "4"
#define PURPLE  "5"
#define CYAN    "6"
#define WHITE   "7"

#define SETCOLOR(code)              "\033[0;3"  code "m"
#define SETLIGHTCOLOR(code)         "\033[1;3"  code "m"
#define SETBACKGROUNDCOLOR(code)    "\033[4"    code "m"

#define CLOSECOLOR()            "\033[39m"
#define CLOSEBACKGROUNDCOLOR()  "\033[49m"

#define WRITECOLOR(code, ...)                     SETCOLOR(code) __VA_ARGS__ CLOSECOLOR()
#define WRITELIGHTCOLOR(code, ...)           SETLIGHTCOLOR(code) __VA_ARGS__ CLOSECOLOR()
#define WRITEBACKGROUNDCOLOR(code, ...) SETBACKGROUNDCOLOR(code) __VA_ARGS__ CLOSEBACKGROUNDCOLOR()

#define RESETCOLOR() "\033[0m"

#endif // !COLORS_H