#ifndef TOOLS_DEFINES_H
#define TOOLS_DEFINES_H

#include "globals.h"

#define TOOL_DRAW	0
#define TOOL_INV	1
#define TOOL_ATTR	2
#define TOOL_ZOOM	3
#define TOOL_LOAD	4
#define TOOL_SAVE	5
#define TOOL_SAVES	6
#define TOOL_AIC	7

char *toolname1[8];
char *toolname2[8];

void load_tool_imgs();
void draw_tools();
void destory_tool_imgs();
int get_tool(int x, int y);

#endif
