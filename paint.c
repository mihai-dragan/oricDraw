#include <allegro.h>
#include "paint.h"
#include "attributes.h"

void redraw_line(byte y) {
	byte cur_ink, cur_paper;
	cur_ink = 7; cur_paper = 0;
	for(int j=0; j<40; j++) {
		if(oattrib[j][y] < 16) {
			cur_ink = oattrib[j][y];
			for(int i=0; i<6; i++) {
				obitmap[j*6+i][y] = 0;
				if(oinvert[j][y]) putpixel(oric_screen, j*6+i, y, invert_color(ocolor[cur_paper]));
				else putpixel(oric_screen, j*6+i, y, ocolor[cur_paper]);
			}
			continue;
		} else if(oattrib[j][y] < 24) {
			cur_paper = oattrib[j][y]-16;
			for(int i=0; i<6; i++) {
				obitmap[j*6+i][y] = 0;
				if(oinvert[j][y]) putpixel(oric_screen, j*6+i, y, invert_color(ocolor[cur_paper]));
				else putpixel(oric_screen, j*6+i, y, ocolor[cur_paper]);
			}
			continue;
		}
		for(int i=0; i<6; i++) {
			if(oinvert[j][y]) {
				if(obitmap[j*6+i][y]) putpixel(oric_screen, j*6+i, y, invert_color(ocolor[cur_ink]));
				else putpixel(oric_screen, j*6+i, y, invert_color(ocolor[cur_paper]));
			} else {
				if(obitmap[j*6+i][y]) putpixel(oric_screen, j*6+i, y, ocolor[cur_ink]);
				else putpixel(oric_screen, j*6+i, y, ocolor[cur_paper]);
			}
		}
	}
}

void put_fg_pixel(int x, int y) {
	obitmap[x][y] = 1;
	oattrib[x/6][y] = 255;
	redraw_line(y);
}

void put_bg_pixel(int x, int y) {
	obitmap[x][y] = 0;
	oattrib[x/6][y] = 255;
	redraw_line(y);
}

void draw_paint_cursors() {
	putpixel(prev_screen, oric_mouse_x, oric_mouse_y, GREY);
}
