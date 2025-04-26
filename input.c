#include <allegro.h>
#include "input.h"
#include "utils.h"
#include "tools.h"
#include "zoom.h"
#include "fileio.h"
#include "attributes.h"
#include "invert.h"
#include "paint.h"
#include "aic.h"

void read_keys() {
	if(key[KEY_Z]) {						// start moving zoom window
		if(seltool == TOOL_ZOOM) seltool = TOOL_DRAW;
		else seltool = TOOL_ZOOM;
		if(seltool == TOOL_ZOOM) position_mouse(40,40);
		while(key[KEY_Z]) rest(100);
	}
	if(key[KEY_I]) {						// start set invert bit
		if(seltool == TOOL_INV) seltool = TOOL_DRAW;
		else  seltool = TOOL_INV;
		while(key[KEY_I]) rest(100);
	}
	if(key[KEY_A]) {						// start set attribute
		if(seltool == TOOL_ATTR) seltool = TOOL_DRAW;
		else  seltool = TOOL_ATTR;
		while(key[KEY_A]) rest(100);
	}
	if (key_shifts & KB_CTRL_FLAG) {
		if (key_shifts & KB_SHIFT_FLAG) {
			if(key[KEY_S]) {				// saves sprite
				save_sprite();
			}
		} else {
			if(key[KEY_S]) {				// saves
				save();
			}
		}
	}
	if(key[KEY_L]) {						// loads
		if (key_shifts & KB_CTRL_FLAG) {
			load();
		}
	}
}

void read_mouse_tools() {
	if((mouse_b & 1) && mouse_x>488 && mouse_x<592 && mouse_y > 40 && mouse_y<92) {
		if(seltool == get_tool(mouse_x, mouse_y)) {
			seltool = TOOL_DRAW;
			position_mouse(40,40);
		} else seltool = get_tool(mouse_x, mouse_y);
		switch(seltool) {
			case TOOL_INV: seltool = TOOL_INV; position_mouse(40,40); break;
			case TOOL_ZOOM: seltool = TOOL_ZOOM; position_mouse(40,40); break;
			case TOOL_ATTR: seltool = TOOL_ATTR; break;
			case TOOL_LOAD: load(); seltool = 0; break;
			case TOOL_SAVE: save(); seltool = 0; break;
			case TOOL_SAVES: save_sprite(); seltool = 0; break;
			case TOOL_AIC: setup_AIC(); seltool = 0; break;
		}
		while(mouse_b & 1) rest(100);
	}
	if(seltool == TOOL_ATTR && (mouse_b & 1) && mouse_x>495 && mouse_x<599 && mouse_y > 572 && mouse_y<599) {
		selattrib = get_attrib(mouse_x, mouse_y);
	}
}

void read_mouse_draw() {
	if ((mouse_b & 1)&&seltool!=TOOL_ZOOM) {		// mouse button 1 pressed
		if(seltool==TOOL_INV) {					// set invert bit and draw
			if(oric_mouse_x>-1 && oric_mouse_y>-1 ) {
				oinvert[invert_offset_x/6][oric_mouse_y] = !oinvert[invert_offset_x/6][oric_mouse_y];
				redraw_line(oric_mouse_y);
			}
			while(mouse_b & 1) rest(100);
		} else if(seltool == TOOL_ATTR) {  // put attribute in table and on screen
			if(oric_mouse_x>-1 && oric_mouse_y>-1) {
				oattrib[attrib_offset_x/6][oric_mouse_y] = selattrib;
				for(int i=0; i<6; i++) obitmap[attrib_offset_x+i][oric_mouse_y] = 0;
				redraw_line(oric_mouse_y);
			}
			while(mouse_b & 1) rest(100);
		} else {							// paint foreground
			if(oric_mouse_x>-1 && oric_mouse_y>-1) {
				put_fg_pixel(oric_mouse_x,oric_mouse_y);
			}
		}
	}
	if ((mouse_b & 2)&&seltool!=TOOL_ZOOM && oric_mouse_x>-1 && oric_mouse_y>-1) {		// mouse button 2 pressed
		if(seltool == TOOL_ATTR) {
			if(oric_mouse_x>-1 && oric_mouse_y>-1) {
				oattrib[attrib_offset_x/6][oric_mouse_y] = 255;
				redraw_line(oric_mouse_y);
			}
		} else {  // paint background
			put_bg_pixel(oric_mouse_x,oric_mouse_y);
		}
	}
}

void get_input() {
	// get mouse coordinates on oric screen
	oric_mouse_x = get_oric_mouse_x(mouse_x, mouse_y);
	oric_mouse_y = get_oric_mouse_y(mouse_x, mouse_y);
	read_keys();
	if(seltool==TOOL_ZOOM) {						// keep moving zoom window
		move_zoom_area();
		if(seltool!=TOOL_ZOOM) seltool = TOOL_DRAW;
	}
	if(seltool==TOOL_INV) {						// get invert bit position
		invert_offset_x = (oric_mouse_x/6)*6;
	}
	if(seltool == TOOL_ATTR) {
		attrib_offset_x = (oric_mouse_x/6)*6;
	}
	
	read_mouse_tools();
	read_mouse_draw();
}
