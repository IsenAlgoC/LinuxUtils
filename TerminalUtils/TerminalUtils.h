#include <ncurses.h>
#include <stdlib.h>

void Init() ;
void Move(int x, int y) ;
void Draw(int x, int y, char ch) ;
void Write(int x, int y, char* ch) ;
void Refresh() ;
void Clear() ;
void SetTimeout(int ms) ;
void End() ;
void UseColorPair(short index) ;
void StopColorPair(short index) ;
void InitColorPair(short index, short foreground, short background) ;
bool IsColorSupported() ;
void Wait(int ms) ;