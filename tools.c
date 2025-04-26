#include <allegro.h>
#include "tools.h"

BITMAP *draw;
BITMAP *invert;
BITMAP *attrib;
BITMAP *zoom;
BITMAP *loadicn;
BITMAP *saveicn;
BITMAP *savespr;
BITMAP *aic;
BITMAP *invdraw;
BITMAP *invinvert;
BITMAP *invattrib;
BITMAP *invzoom;
BITMAP *icons[8];
BITMAP *inv_icons[4];
PALETTE palette;

char *toolname1[8] = { "DRAW", "INVERT (i)", "ATTRIBUTE (a)", "ZOOM (z)", 
					"LOAD (ctrl+l)", "SAVE (ctrl+s)", "SAVE SPR", "AIC" };
char *toolname2[8] = { " ", " ", " ", " ", 
					" ", " ", "(ctrl+shift+s)", " " };

BITMAP* create_inverted(BITMAP *srcbmp) {
	BITMAP* dstbmp = create_bitmap(srcbmp->w, srcbmp->h);
	blit(srcbmp, dstbmp, 0,0, 0, 0, srcbmp->w, srcbmp->h);
	for(int y=0; y<srcbmp->h; y++) {
		for(int x=0; x<srcbmp->w; x++) {
			if(getpixel(dstbmp,x,y)==0) { putpixel(dstbmp,x,y,ocolor[WHITE]);
			} else { if(getpixel(dstbmp,x,y)==ocolor[WHITE]) putpixel(dstbmp,x,y,0); }
		}
	}
	return dstbmp;
}

void load_tool_imgs() {
	draw = load_bitmap("toolicons/draw.pcx", palette);
	if (!draw) allegro_message("Couldn't load image toolicons/draw.pcx!",allegro_error, 10, 10, 8);
	icons[0] = draw;
	invdraw = create_inverted(draw);
	inv_icons[0] = invdraw;
	invert = load_bitmap("toolicons/invert.pcx", palette);
	if (!invert) allegro_message("Couldn't load image toolicons/invert.pcx!",allegro_error, 10, 10, 8);
	icons[1] = invert;
	invinvert = create_inverted(invert);
	inv_icons[1] = invinvert;
	attrib = load_bitmap("toolicons/attrib.pcx", palette);
	if (!attrib) allegro_message("Couldn't load image toolicons/attrib.pcx!",allegro_error, 10, 10, 8);
	icons[2] = attrib;
	invattrib = create_inverted(attrib);
	inv_icons[2] = invattrib;
	zoom = load_bitmap("toolicons/zoom.pcx", palette);
	if (!zoom) allegro_message("Couldn't load image toolicons/zoom.pcx!",allegro_error, 10, 10, 8);
	icons[3] = zoom;
	invzoom = create_inverted(zoom);
	inv_icons[3] = invzoom;
	loadicn = load_bitmap("toolicons/load.pcx", palette);
	if (!loadicn) allegro_message("Couldn't load image toolicons/loadicn.pcx!",allegro_error, 10, 10, 8);
	icons[4] = loadicn;
	saveicn = load_bitmap("toolicons/save.pcx", palette);
	if (!saveicn) allegro_message("Couldn't load image toolicons/save.pcx!",allegro_error, 10, 10, 8);
	icons[5] = saveicn;
	savespr = load_bitmap("toolicons/savespr.pcx", palette);
	if (!savespr) allegro_message("Couldn't load image toolicons/savespr.pcx!",allegro_error, 10, 10, 8);
	icons[6] = savespr;
	aic = load_bitmap("toolicons/aic.pcx", palette);
	if (!aic) allegro_message("Couldn't load image toolicons/aic.pcx!",allegro_error, 10, 10, 8);
	icons[7] = aic;
}

void draw_tools(int selected) {
	for(int i=0; i<5; i++) {
		vline(buffer,488+(i*26),40,92,GREY);
	}
	for(int i=0; i<3; i++) {
		hline(buffer,488,40+(i*26),592,GREY);
	}
	for(int i=0; i<8; i++) {
		if(i<4) {
			if(i==selected && i<4) draw_sprite(buffer, inv_icons[i], 489+(i*26),41);
			else draw_sprite(buffer, icons[i], 489+(i*26),41);
		} else {
			if(i==selected && i<4) draw_sprite(buffer, inv_icons[i], 489+((i-4)*26),67);
			else draw_sprite(buffer, icons[i], 489+((i-4)*26),67);
		}
	}
}

int get_tool(int x, int y) {
	int i = 0;
	i = (x-489)/26;
	if(y>67 && y<92) i=i+4;
	return i;
}

void destory_tool_imgs() {
	destroy_bitmap(draw);
	destroy_bitmap(invert);
	destroy_bitmap(attrib);
	destroy_bitmap(zoom);
	destroy_bitmap(loadicn);
	destroy_bitmap(saveicn);
	destroy_bitmap(savespr);
	destroy_bitmap(aic);
	destroy_bitmap(invdraw);
	destroy_bitmap(invinvert);
	destroy_bitmap(invattrib);
	destroy_bitmap(invzoom);
}
