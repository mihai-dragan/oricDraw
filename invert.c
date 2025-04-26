#include <allegro.h>
#include "invert.h"

void draw_invert_line() {
	for(int i=0; i<6; i++) {
		putpixel(prev_screen,invert_offset_x+i,oric_mouse_y,invert_color(getpixel(oric_screen,invert_offset_x+i,oric_mouse_y)));
	}
}
