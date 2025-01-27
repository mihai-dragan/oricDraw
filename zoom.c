#include <allegro.h>
#include "zoom.h"

void move_zoom_area() {
	if(key[KEY_RIGHT]&&lens_offset_x+lens_max_x<240) {
		lens_offset_x = lens_offset_x+6;
		get_mouse_mickeys(&mik_x, &mik_y);
		rest(100);
	}
	if(key[KEY_LEFT]&&lens_offset_x>12) {
		lens_offset_x = lens_offset_x-6;
		get_mouse_mickeys(&mik_x, &mik_y);
		rest(100);
	}
	if(key[KEY_DOWN]&&lens_offset_y+lens_max_y<200) {
		lens_offset_y = lens_offset_y+1;
		get_mouse_mickeys(&mik_x, &mik_y);
		rest(100);
	}
	if(key[KEY_UP]&&lens_offset_y>1) {
		lens_offset_y = lens_offset_y-1;
		get_mouse_mickeys(&mik_x, &mik_y);
		rest(100);
	}
	if(key[KEY_ENTER]) {
		is_zoom_set = 0;
	}
	get_mouse_mickeys(&mik_x, &mik_y);
	if(oric_mouse_x+lens_max_x<=240 && oric_mouse_x>5 && (mik_x!=0 || mik_y!=0)) {
		lens_offset_x = (oric_mouse_x/6)*6;
	}
	if(oric_mouse_y+lens_max_y<=200 && oric_mouse_y>-1 && (mik_x!=0 || mik_y!=0)) {
		lens_offset_y = oric_mouse_y;
	}
	if(mouse_b & 1) { 
		is_zoom_set = 0;
		while(mouse_b & 1) rest(100);
	}
}

void draw_zoom_win() {
	rect(buffer,lens_offset_x*screen_zoom,lens_offset_y*screen_zoom,
		(lens_offset_x+lens_max_x)*screen_zoom,(lens_offset_y+lens_max_y)*screen_zoom,GREY);
}
