#ifndef GLOBAL_DEFINES_H
#define GLOBAL_DEFINES_H

#define byte unsigned char

byte screen_zoom;
byte lens_zoom;
byte lens_offset_x;
byte lens_offset_y;
byte invert_offset_x;
byte is_zoom_set;
byte is_invert_set;
int lens_max_x, lens_max_y;
int screen_max_x, screen_max_y;
int oric_mouse_x, oric_mouse_y;
int mik_x, mik_y;

int GREY;
const byte BLACK;
const byte RED;
const byte GREEN;
const byte YELLOW;
const byte BLUE;
const byte MAGENTA;
const byte CYAN;
const byte WHITE;
int ocolor[8];
byte oinvert[40][200];

byte AIC_FG1;
byte AIC_FG2;

BITMAP *buffer;
BITMAP *mouse_bmp;
BITMAP *oric_screen;

int invert_color(int color);

#endif // GLOBAL_DEFINES_H
