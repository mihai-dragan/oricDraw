#ifndef ATTRIB_DEFINES_H
#define ATTRIB_DEFINES_H

#include "globals.h"

#define INK_0		0
#define INK_1		1
#define INK_2		2
#define INK_3		3
#define INK_4		4
#define INK_5		5
#define INK_6		6
#define INK_7		7

#define PAPER_0		16
#define PAPER_1		17
#define PAPER_2		18
#define PAPER_3		19
#define PAPER_4		20
#define PAPER_5		21
#define PAPER_6		22
#define PAPER_7		23

char *attribname[24];

void draw_attrib_line();
void load_attrib_imgs();
void draw_attribs(int selected);
void destory_attrib_imgs();
int get_attrib(int x, int y);

#endif
