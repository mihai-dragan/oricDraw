#include <allegro.h>
#include <stdio.h>
#include "fileio.h"

void save() {
	FILE *fptr;
	int i, x, y;
	unsigned char o;
	int bg;
	unsigned char head[21] = { 0x16,0x16,0x16,0x24,0x00,0x00,0x80,0x00,0xbf,0x3f,0xa0,0x00,0x00,0x4f,0x55,0x54,0x2e,0x48,0x52,0x53, 0 };
	char path[512] = "./";
	char buf[512];
	if(file_select_ex("Save file:", path, "HRS", 256, 400, 200) == 0) return;
	if ((strlen(path) != 0) && (exists(path))) {
		sprintf(buf, "%s already exists, overwrite?", path);
		if (alert(buf, NULL, NULL, "Yes", "No", 'y', 'n') != 1) return;
	}
	fptr = fopen(path, "w");
	for(i=0; i<21; i++) fputc(head[i], fptr);
	for(y=0; y<200; y++) {
		for(x=0; x<240; x=x+6) {
			if(x==0) {
				if((y&1) == 0) fputc(6, fptr);
				else fputc(3, fptr);
			} else {
				if(oinvert[x/6][y] == 0) {
					bg = ocolor[BLACK];
					o = 64;
				} else {
					bg = invert_color(ocolor[BLACK]);
					o = 192;
				}
				for(i=0; i<6; i++) {
					if(getpixel(oric_screen, x+i, y) != bg) o = o + (2<<(5-i))/2;
				}
				fputc(o, fptr);
			}
		}
	}
	fclose(fptr);
}

char widths[9] = "24";
char heights[9] = "18";
char framess[9] = "3";

DIALOG dlg[] = {
	{ d_clear_proc,        0,   0,    0,    0,   0,  0,    0,      0,       0,   0,    NULL,                   NULL, NULL  },  //0
	{ d_box_proc,          0,   0,  120,   60,   0,  0,    0,      0,       0,   0,    NULL,                   NULL, NULL  },  //1
	{ d_text_proc,         5,   5,    0,    0,   0,  0,    0,      0,       0,   0,    "width: ",              NULL, NULL  },  //2
	{ d_edit_proc,         70,  5,   30,    8,   0,  0,    0,      0,       2,   0,    widths,     			   NULL, NULL  },  //3
	{ d_text_proc,         5,  15,    0,    0,   0,  0,    0,      0,       0,   0,    "height: ",             NULL, NULL  },  //4
	{ d_edit_proc,         70, 15,   30,    8,   0,  0,    0,      0,       2,   0,    heights,     			   NULL, NULL  },  //5
	{ d_text_proc,         5,  25,    0,    0,   0,  0,    0,      0,       0,   0,    "frames: ",             NULL, NULL  },  //6
	{ d_edit_proc,         70, 25,   30,    8,   0,  0,    0,      0,       2,   0,    framess,      		   NULL, NULL  },  //7
	{ d_button_proc,       10, 40,   40,   15,   0,  0,  'o', D_EXIT,       0,   0,    "&Ok",                  NULL, NULL  },
	{ d_yield_proc,        0,   0,    0,    0,   0,  0,    0,      0,       0,   0,    NULL,                   NULL, NULL  },
	{ NULL,                0,   0,    0,    0,   0,  0,    0,      0,       0,   0,    NULL,                   NULL, NULL  }
};

void save_sprite() {
	int width = 24;
	int height = 18;
	int frames = 3;
	int xabs;
	int bg;
	unsigned char o;
	FILE *fptr;
	char path[512] = "./";
	char buf[512];
	
	set_dialog_color(dlg,ocolor[WHITE],ocolor[BLACK]);
	popup_dialog(dlg,-1);
	width = atoi(dlg[3].dp);
	height = atoi(dlg[5].dp);
	frames = atoi(dlg[7].dp);
	
	if(file_select_ex("Save sprite:", path, "h", 256, 400, 200) == 0) return;
	if ((strlen(path) != 0) && (exists(path))) {
		sprintf(buf, "%s already exists, overwrite?", path);
		if (alert(buf, NULL, NULL, "Yes", "No", 'y', 'n') != 1) return;
	}
	fptr = fopen(path, "w");
	sprintf(buf,"byte walk[%d] = { ",(width/6)*height*frames);
	fputs(buf, fptr);
	for(int f=0; f<frames; f++) {
		for(int y=0; y<height; y++) {
			for(int x=0; x<width; x=x+6) {
				xabs = 6 + x + f*width;
				if(oinvert[xabs/6][y] == 0) {
					bg = ocolor[BLACK];
					o = 64;
				} else {
					bg = invert_color(ocolor[BLACK]);
					o = 192;
				}
				for(int i=0; i<6; i++) {
					if(getpixel(oric_screen, xabs+i, y) != bg) o = o + (2<<(5-i))/2;
				}
				if(f==(frames-1) && y==(height-1) && x==(width-6)) {
					sprintf(buf,"%d ", o);
					fputs(buf, fptr);
				} else {
					sprintf(buf,"%d, ", o);
					fputs(buf, fptr);
				}
			}
		}
		fputc('\n',fptr);
	}
	fputs("};", fptr);
	fclose(fptr);
}

void load() {
	FILE *fptr;
	int i, x, y;
	int fg, bg;
	unsigned char o;
	char path[512] = "./";
	char buf[512];
	if(file_select_ex("Load file:", path, "HRS", 256, 400, 200) == 0) return;
	if (!(exists(path))) {
		sprintf(buf, "%s does not exist", path);
		if (alert(buf, NULL, NULL, "Ok", NULL, 0, 0) != 1) return;
	}
	fptr = fopen(path, "r");
	clear_to_color(oric_screen,ocolor[BLACK]);
	for(int i=0; i<40; i++) for(int j=0; j<200; j++) oinvert[i][j] = 0;
	for(i=0; i<13; i++) fgetc(fptr); // discard header
	while((o=fgetc(fptr)) != 0) { }  // discard file name
	for(y=0; y<200; y++) {
		for(x=0; x<240; x=x+6) {
			if(x==0) {
				fgetc(fptr);  // discard first byte of each line (color attribute in AIC)
			} else {
				o = fgetc(fptr);
				if(o>>7 == 1) {
					oinvert[x/6][y] = 1;
					if((y&1) == 0) fg = invert_color(ocolor[AIC_FG1]);
					else fg = invert_color(ocolor[AIC_FG2]);
					bg = invert_color(ocolor[BLACK]);
				} else {
					if((y&1) == 0) fg = ocolor[AIC_FG1];
					else fg = ocolor[AIC_FG2];
					bg = ocolor[BLACK];
				}
				for(i=0; i<6; i++) {
					if(o&((2<<(5-i))/2)) putpixel(oric_screen,x+i,y,fg);
					else putpixel(oric_screen,x+i,y,bg);
				}
			}
		}
	}
	fclose(fptr);
}
