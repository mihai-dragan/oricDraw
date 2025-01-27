#include <allegro.h>
#include "invert.h"

void invert_ocolors(int x, int y) {
	for(int i=0; i<6; i++) {
		putpixel(oric_screen,x+i,y,invert_color(getpixel(oric_screen,x+i,y)));
	}
}

void draw_invert_line() {
	for(int i=0; i<6; i++) {
		rectfill(buffer,(invert_offset_x+i)*screen_zoom,oric_mouse_y*screen_zoom,
			(invert_offset_x+i)*screen_zoom+1,oric_mouse_y*screen_zoom+1,invert_color(getpixel(oric_screen,invert_offset_x+i,oric_mouse_y)));
		if(oric_mouse_x>=lens_offset_x && oric_mouse_x < lens_max_x+lens_offset_x 
			&& oric_mouse_y>=lens_offset_y && oric_mouse_y < lens_max_y+lens_offset_y) {
				rectfill(buffer,(invert_offset_x+i-lens_offset_x)*lens_zoom,(oric_mouse_y-lens_offset_y)*lens_zoom+401,
					(invert_offset_x+i-lens_offset_x)*lens_zoom+lens_zoom-1,(oric_mouse_y-lens_offset_y)*lens_zoom+401+lens_zoom-1,
					invert_color(getpixel(oric_screen,invert_offset_x+i,oric_mouse_y)));
		}
	}
}
