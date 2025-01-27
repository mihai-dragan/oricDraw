#include <allegro.h>
#include "paint.h"

void put_fg_pixel(int x, int y) {
	if((y&1) == 0) {
		if(oinvert[x/6][y]) putpixel(oric_screen, oric_mouse_x, oric_mouse_y, invert_color(ocolor[AIC_FG1]));
		else putpixel(oric_screen, oric_mouse_x, oric_mouse_y, ocolor[AIC_FG1]);
	} else {
		if(oinvert[x/6][y]) putpixel(oric_screen, oric_mouse_x, oric_mouse_y, invert_color(ocolor[AIC_FG2]));
		else putpixel(oric_screen, oric_mouse_x, oric_mouse_y, ocolor[AIC_FG2]);
	}
}

void put_bg_pixel(int x, int y) {
	if(oinvert[(x/6)][y]) putpixel(oric_screen, oric_mouse_x, oric_mouse_y, invert_color(ocolor[BLACK]));
	else putpixel(oric_screen, oric_mouse_x, oric_mouse_y, ocolor[BLACK]);
}

void draw_paint_cursors() {
	rectfill(buffer,oric_mouse_x*screen_zoom,oric_mouse_y*screen_zoom,oric_mouse_x*screen_zoom+1,oric_mouse_y*screen_zoom+1,GREY);
	if(oric_mouse_x>=lens_offset_x && oric_mouse_x < lens_max_x+lens_offset_x 
		&& oric_mouse_y>=lens_offset_y && oric_mouse_y < lens_max_y+lens_offset_y) {
		rectfill(buffer,(oric_mouse_x-lens_offset_x)*lens_zoom,(oric_mouse_y-lens_offset_y)*lens_zoom+401,
			(oric_mouse_x-lens_offset_x)*lens_zoom+lens_zoom-1,(oric_mouse_y-lens_offset_y)*lens_zoom+401+lens_zoom-1,GREY);
	}
}
