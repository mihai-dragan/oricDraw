#include "utils.h"

int get_oric_mouse_x(int x, int y) {
	if(x<480 && y<400) return x/screen_zoom;
	if(x<480 && y>401) return x/lens_zoom + lens_offset_x;
	return -1;
}

int get_oric_mouse_y(int x, int y) {
	if(x<480 && y<400) return y/screen_zoom;
	if(x<480 && y>401) return (y-401)/lens_zoom + lens_offset_y;
}

int invert_color(int color) {
	if(color==ocolor[WHITE]) return ocolor[BLACK];
	if(color==ocolor[BLACK]) return ocolor[WHITE];
	if(color==ocolor[RED]) return ocolor[CYAN];
	if(color==ocolor[CYAN]) return ocolor[RED];
	if(color==ocolor[YELLOW]) return ocolor[BLUE];
	if(color==ocolor[BLUE]) return ocolor[YELLOW];
	if(color==ocolor[MAGENTA]) return ocolor[GREEN];
	if(color==ocolor[GREEN]) return ocolor[MAGENTA];
}
