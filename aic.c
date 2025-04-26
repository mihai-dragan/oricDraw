#include <allegro.h>
#include "aic.h"
#include "paint.h"

static char *color_names[] = { "BLACK", "RED", "GREEN", "YELLOW", "BLUE", "MAGENTA", "CYAN", "WHITE" };

char *get_colors(int index, int *list_size) {
   if (index < 0) {
      *list_size = 8;
      return NULL;
   } else {
      return color_names[index];
   }
}

DIALOG aicdlg[] = {
	{ d_clear_proc,        0,   0,    0,    0,   0,  0,    0,      0,       0,   0,    NULL,                   NULL, NULL  },  //0
	{ d_box_proc,          0,   0,  155,  150,   0,  0,    0,      0,       0,   0,    NULL,                   NULL, NULL  },  //1
	{ d_text_proc,         5,   5,    0,    0,   0,  0,    0,      0,       0,   0,    "color1: ",		       NULL, NULL  },  //2
	{ d_list_proc,         70,  5,   80,   55,   0,  0,    0,      0,       2,   0,    (void*)get_colors, 	   NULL, NULL  },  //3
	{ d_text_proc,         5,  60,    0,    0,   0,  0,    0,      0,       0,   0,    "color2: ",  	       NULL, NULL  },  //4
	{ d_list_proc,         70, 60,   80,   55,   0,  0,    0,      0,       2,   0,    (void*)get_colors,	   NULL, NULL  },  //5
	{ d_button_proc,       5, 120,   30,   15,   0,  0,  's', D_EXIT,       0,   0,    "&Set",                 NULL, NULL  },  //6
	{ d_button_proc,       40,120,   45,   15,   0,  0,  'l', D_EXIT,       0,   0,    "C&lear",               NULL, NULL  },  //7
	{ d_button_proc,       90,120,   60,   15,   0,  0,  'c', D_EXIT,       0,   0,    "&Cancel",              NULL, NULL  },  //8 
	{ d_yield_proc,        0,   0,    0,    0,   0,  0,    0,      0,       0,   0,    NULL,                   NULL, NULL  },
	{ NULL,                0,   0,    0,    0,   0,  0,    0,      0,       0,   0,    NULL,                   NULL, NULL  }
};

void setup_AIC() {
	byte fg1, fg2;
	set_dialog_color(aicdlg,ocolor[WHITE],ocolor[BLACK]);
	switch(popup_dialog(aicdlg,-1)) {
		case 6: fg1 = aicdlg[3].d1;
				fg2 = aicdlg[5].d1;
				for(int i=0; i<200; i++) {
					if((i&1) == 0) oattrib[0][i] = fg1;
					else oattrib[0][i] = fg2;
					for(int j=0; j<6; j++) obitmap[j][i] = 0;
					redraw_line(i);
				}
				break;
		case 7: for(int i=0; i<200; i++) { oattrib[0][i] = 255; redraw_line(i); } break;
	}
}
