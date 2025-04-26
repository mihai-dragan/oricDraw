#include <allegro.h>
#include "attributes.h"

BITMAP *paper;
BITMAP *ink;
BITMAP *check;
PALETTE palette;

char *attribname[24] = { "INK BLACK", "INK RED", "INK GREEN", "INK YELLOW", "INK BLUE", "INK MAGENTA", "INK CYAN", "INK WHITE",
	"","","","","","","","",
	"PAPER BLACK", "PAPER RED", "PAPER GREEN", "PAPER YELLOW", "PAPER BLUE", "PAPER MAGENTA", "PAPER CYAN", "PAPER WHITE" };

void draw_startattr(BITMAP* bmp, byte cur_ink, byte cur_paper) {
	putpixel(bmp,attrib_offset_x,oric_mouse_y,GREY);
	if(selattrib<16) {
		putpixel(bmp,attrib_offset_x+1,oric_mouse_y,ocolor[cur_ink]);
		putpixel(bmp,attrib_offset_x+2,oric_mouse_y,ocolor[cur_ink]);
		putpixel(bmp,attrib_offset_x+3,oric_mouse_y,GREY);
		putpixel(bmp,attrib_offset_x+4,oric_mouse_y,GREY);
	} else {
		putpixel(bmp,attrib_offset_x+1,oric_mouse_y,GREY);
		putpixel(bmp,attrib_offset_x+2,oric_mouse_y,GREY);
		putpixel(bmp,attrib_offset_x+3,oric_mouse_y,ocolor[cur_paper]);
		putpixel(bmp,attrib_offset_x+4,oric_mouse_y,ocolor[cur_paper]);
	}
	putpixel(bmp,attrib_offset_x+5,oric_mouse_y,GREY);
}

void draw_attrib_line() {
	if(oric_mouse_x<0) return;
	byte cur_ink, cur_paper;
	attrib_offset_x = (oric_mouse_x/6)*6;
	if(selattrib<16) cur_ink = selattrib;
	else if(selattrib<24) cur_paper = selattrib-16;
	draw_startattr(prev_screen, cur_ink, cur_paper);
}

void load_attrib_imgs() {
	paper = load_bitmap("toolicons/paper.pcx", palette);
	if (!paper) allegro_message("Couldn't load image toolicons/paper.pcx!",allegro_error, 10, 10, 8);
	ink = load_bitmap("toolicons/ink.pcx", palette);
	if (!ink) allegro_message("Couldn't load image toolicons/ink.pcx!",allegro_error, 10, 10, 8);
	check = load_bitmap("toolicons/check.pcx", palette);
	if (!check) allegro_message("Couldn't load image toolicons/check.pcx!",allegro_error, 10, 10, 8);
}

void draw_attribs(int selected) {
	draw_sprite(buffer, ink, 482, 573);
	draw_sprite(buffer, paper, 482, 587);
	for(int i=0; i<8; i++) {
		rectfill(buffer, 495+(i*13), 573, 508+(i*13), 585, ocolor[i]);
		rectfill(buffer, 495+(i*13), 587, 508+(i*13), 599, ocolor[i]);
		if(i==selected) draw_sprite(buffer, check, 495+(i*13), 573);
		if(i==(selected-16)) draw_sprite(buffer, check, 495+(i*13), 587);
	}
	hline(buffer, 482, 572, 599 ,GREY);
	hline(buffer, 482, 586, 599 ,GREY);
	vline(buffer, 494,573,599 ,GREY);
}

int get_attrib(int x, int y) {
	int i = 0;
	i = (x-495)/13;
	if(y>586 && y<600) i=i+16;
	return i;
}

void destory_attrib_imgs() {
	destroy_bitmap(paper);
	destroy_bitmap(ink);
}
