#include <ncurses.h>
#include <stdlib.h>

void Init() {
   initscr();
   cbreak();
   noecho();
   timeout(1000);
   start_color();
}

void Move(int x, int y) {
    move(y, x);
}

void Draw(int x, int y, char ch) {
    mvaddch(y, x, ch);
}

void Write(int x, int y, char* str) {
    mvaddstr(y, x, str);
}

void Refresh() {
    refresh();
}

void Clear() {
    clear();
}

void SetTimeout(int ms) {
    timeout(ms);
}

void End() {
   clear();
   refresh();
   endwin();
}

void UseColorPair(short index) {
    attron(COLOR_PAIR(index));
}

void StopColorPair(short index) {
    attroff(COLOR_PAIR(index));
}

void InitColorPair(short index, short foreground, short background) {
    init_pair(index, foreground, background);
}

bool IsColorSupported() {
    return has_colors();
}

#ifdef __linux__
#include <unistd.h>
#endif
#ifdef _WIN32
#include <windows.h>
#endif

void Wait(int ms) {
    #ifdef __linux__
        usleep(ms * 1000);
    #endif
    #ifdef _WIN32
        Sleep(ms);
    #endif
}