#include "globals.h"
#include "utils.h"
#include "zoom.h"
#include "paint.h"
#include "invert.h"
#include "fileio.h"
#include "tools.h"
#include "attributes.h"
#include "input.h"

byte screen_zoom = 2;
byte lens_zoom = 8;
byte lens_offset_x = 6;
byte lens_offset_y = 0;
int mik_x, mik_y = 0;
const byte BLACK = 0;
const byte RED = 1;
const byte GREEN = 2;
const byte YELLOW = 3;
const byte BLUE = 4;
const byte MAGENTA = 5;
const byte CYAN = 6;
const byte WHITE = 7;
byte seltool = 0;

volatile int update_count = 0;
volatile int close_button_pressed = FALSE;

byte selattrib = 0;

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
	prev_screen = create_bitmap(240,200);
		
	/* set up colors */
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
	clear_bitmap(prev_screen);
	
	for(int i=0; i<40; i++) for(int j=0; j<200; j++) oinvert[i][j] = 0;
	for(int i=0; i<240; i++) for(int j=0; j<200; j++) obitmap[i][j] = 0;
	for(int i=0; i<40; i++) for(int j=0; j<200; j++) oattrib[i][j] = 255;

	clear_to_color(mouse_bmp, 0);
	line(mouse_bmp,0,0,9,9, ocolor[WHITE]);
	hline(mouse_bmp,0,0,4, ocolor[WHITE]);
	vline(mouse_bmp,0,0,4, ocolor[WHITE]);
	
	load_tool_imgs();
	load_attrib_imgs();

	// main loop
	while(!key[KEY_ESC]&&!close_button_pressed) {
		get_input();
		// update oric screen and drawing buffer
		if(update_count>0) {
			clear_to_color(buffer,ocolor[BLACK]);
			clear_bitmap(prev_screen);
			hline(buffer,0,400,480,GREY);
			vline(buffer,480,0,600,GREY);
			draw_tools(seltool);
			if(seltool == TOOL_ATTR) draw_attribs(selattrib);
			stretch_blit(oric_screen, buffer, 0,0,240,200,0,0,screen_max_x,screen_max_y);
			stretch_blit(oric_screen, buffer, 0+lens_offset_x,0+lens_offset_y,lens_max_x,lens_max_y,0,401,480,200);
			if(seltool == TOOL_ATTR && mouse_x>495 && mouse_x<599 && mouse_y > 572 && mouse_y<599) {
				textprintf_ex(buffer, font, 482, 1, ocolor[WHITE], -1, "%s", attribname[get_attrib(mouse_x,mouse_y)]);
			}
			if(mouse_x>488 && mouse_x<592 && mouse_y > 40 && mouse_y<92) {
				textprintf_ex(buffer, font, 482, 1, ocolor[WHITE], -1, "%s", toolname1[get_tool(mouse_x,mouse_y)]);
				textprintf_ex(buffer, font, 482, 12, ocolor[WHITE], -1, "%s", toolname2[get_tool(mouse_x,mouse_y)]);
			}
			if(oric_mouse_x>=0 && oric_mouse_y>=0) {
				textprintf_ex(buffer, font, 482, 1, ocolor[WHITE], -1, "x: %d, y: %d", oric_mouse_x, oric_mouse_y);
				textprintf_ex(buffer, font, 482, 12, ocolor[WHITE], -1, "i:%d,a:%d,b:%d", oinvert[oric_mouse_x/6][oric_mouse_y], oattrib[oric_mouse_x/6][oric_mouse_y],obitmap[oric_mouse_x][oric_mouse_y]);
				if(seltool==TOOL_ZOOM) {
					draw_zoom_win();
				} else if(seltool==TOOL_INV) {
					draw_invert_line();
				} else if(seltool==TOOL_ATTR) {
					draw_attrib_line();
				} else {
					draw_paint_cursors();
				}
			} else {
				draw_mouse_arrow();
			}
			masked_stretch_blit(prev_screen, buffer, 0,0,240,200,0,0,screen_max_x,screen_max_y);
			masked_stretch_blit(prev_screen, buffer, 0+lens_offset_x,0+lens_offset_y,lens_max_x,lens_max_y,0,401,480,200);
			vsync();
			blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
			update_count = 0;
		}
	}
	destory_tool_imgs();
	destory_attrib_imgs();
	destroy_bitmap(oric_screen);
	destroy_bitmap(prev_screen);
	destroy_bitmap(mouse_bmp);
	destroy_bitmap(buffer);

	return 0;
}
END_OF_MAIN()
