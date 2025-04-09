#include <allegro.h>
#include "zoom.h"
#include "paint.h"
#include "invert.h"
#include "fileio.h"

byte screen_zoom = 2;
byte lens_zoom = 8;
byte lens_offset_x = 6;
byte lens_offset_y = 0;
byte is_zoom_set = 0;
byte is_invert_set = 0;
int mik_x, mik_y = 0;
const byte BLACK = 0;
const byte RED = 1;
const byte GREEN = 2;
const byte YELLOW = 3;
const byte BLUE = 4;
const byte MAGENTA = 5;
const byte CYAN = 6;
const byte WHITE = 7;

byte AIC_FG1 = CYAN;
byte AIC_FG2 = YELLOW;

volatile int update_count = 0;
volatile int close_button_pressed = FALSE;

void close_button_handler(void)
{
 close_button_pressed = TRUE;
}
END_OF_FUNCTION(close_button_handler)

/* timer callback for controlling the program speed */
void timer_proc(void) {
   update_count++;
}
END_OF_FUNCTION(timer_proc)

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

void get_input() {
	// get mouse coordinates on oric screen
	oric_mouse_x = get_oric_mouse_x(mouse_x, mouse_y);
	oric_mouse_y = get_oric_mouse_y(mouse_x, mouse_y);
	if(key[KEY_Z]) {						// start moving zoom window
		is_zoom_set = 1;
	}
	if(is_zoom_set) {						// keep moving zoom window
		move_zoom_area();
	}
	if(key[KEY_I]) {						// start set invert bit
		is_invert_set = !is_invert_set;
		while(key[KEY_I]) rest(100);
	}
	if(is_invert_set) {						// get invert bit position
		invert_offset_x = (oric_mouse_x/6)*6;
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
	if ((mouse_b & 1)&&!is_zoom_set) {		// mouse button 1 pressed
		if(is_invert_set) {					// set invert bit and draw
			if(oric_mouse_x>5 && oric_mouse_y>-1) {
				oinvert[invert_offset_x/6][oric_mouse_y] = !oinvert[invert_offset_x/6][oric_mouse_y];
				invert_ocolors(invert_offset_x, oric_mouse_y);
			}
			while(mouse_b & 1) rest(100);
		} else {							// paint foreground
			if(oric_mouse_x>5 && oric_mouse_y>-1) {
				put_fg_pixel(oric_mouse_x,oric_mouse_y);
			}
		}
	}
	if ((mouse_b & 2)&&!is_zoom_set) {		// mouse button 2 pressed
		if(oric_mouse_x>5 && oric_mouse_y>-1) { // paint background
			put_bg_pixel(oric_mouse_x,oric_mouse_y);
		}
	}
}

void draw_mouse_arrow() {
	masked_blit(mouse_bmp, screen, 0, 0, mouse_x, mouse_y, mouse_bmp->w, mouse_bmp->h);
}

int main(void) {
	lens_max_x = 480/lens_zoom;
	lens_max_y = 200/lens_zoom;
	screen_max_x = 240*screen_zoom;
	screen_max_y = 200*screen_zoom;

	if (allegro_init() != 0)
	  return 1;
	install_keyboard();
    install_timer();
    LOCK_VARIABLE(update_count);
    LOCK_FUNCTION(timer_proc);
    LOCK_FUNCTION(close_button_handler);
    set_close_button_callback(close_button_handler);
    install_int_ex(timer_proc, BPS_TO_TIMER(60));
	if (install_mouse() < 0) {
      allegro_message("No mouse detected, but you need one!", 10, 10, 8);
      exit(-1);
   }

	/* set the graphics mode */
	if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, screen_max_x+121, 300*screen_zoom+1, 0, 0) != 0) {
	  allegro_message("Unable to set mode %ix%i with %ibpp\n", 10, 10, 8);
	  exit(-1);           
	}
	
	set_window_title("Oric Draw");
	
	buffer = create_bitmap(SCREEN_W, SCREEN_H);
	mouse_bmp = create_bitmap(10,10);
	oric_screen = create_bitmap(240,200);
		
	/* set up colors */
	const RGB whitec = {255,255,255};
	GREY = makecol(128, 128, 128);
	ocolor[WHITE] = makecol(255, 255, 255);
	ocolor[BLACK] = makecol(0, 0, 0);
	ocolor[RED] = makecol(255, 0, 0);
	ocolor[GREEN] = makecol(0, 255, 0);
	ocolor[BLUE] = makecol(0, 0, 255);
	ocolor[YELLOW] = makecol(255, 255, 0);
	ocolor[CYAN] = makecol(0, 255, 255);
	ocolor[MAGENTA] = makecol(255, 0, 255);
	
	clear_to_color(oric_screen,ocolor[BLACK]);
	
	for(int i=0; i<40; i++) for(int j=0; j<200; j++) oinvert[i][j] = 0;
	
	clear_to_color(mouse_bmp, 0);
	line(mouse_bmp,0,0,9,9, ocolor[WHITE]);
	hline(mouse_bmp,0,0,4, ocolor[WHITE]);
	vline(mouse_bmp,0,0,4, ocolor[WHITE]);

	// main loop
	while(!key[KEY_ESC]&&!close_button_pressed) {
		get_input();

		// update oric screen and drawing buffer
		if(update_count>0) {
			clear_to_color(buffer,ocolor[BLACK]);
			hline(buffer,0,400,480,GREY);
			vline(buffer,480,0,600,GREY);
			stretch_blit(oric_screen, buffer, 0,0,240,200,0,0,screen_max_x,screen_max_y);
			stretch_blit(oric_screen, buffer, 0+lens_offset_x,0+lens_offset_y,lens_max_x,lens_max_y,0,401,480,200);
			if(oric_mouse_x>=0 && oric_mouse_y>=0) {
				textprintf_ex(buffer, font, 482, 1, ocolor[WHITE], -1, "x: %d, y: %d", oric_mouse_x, oric_mouse_y);
				if(is_zoom_set) {
					draw_zoom_win();
				} else if(is_invert_set) {
					draw_invert_line();
				} else {
					draw_paint_cursors();
				}
			} else {
				draw_mouse_arrow();
			}
			vsync();
			blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
			update_count = 0;
		}
	}
	
	destroy_bitmap(oric_screen);
	destroy_bitmap(mouse_bmp);
	destroy_bitmap(buffer);

	return 0;
}
END_OF_MAIN()
