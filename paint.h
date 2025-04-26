#ifndef PAINT_DEFINES_H
#define PAINT_DEFINES_H

#include "globals.h"

void put_fg_pixel(int x, int y);
void put_bg_pixel(int x, int y);
void draw_paint_cursors();
void redraw_line(byte y);

#endif
