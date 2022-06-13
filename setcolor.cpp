#include "./setcolor.h"

void setcolor( unsigned char color ){
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
