#ifndef __INCLUDE_GUI__
#define __INCLUDE_GUI__

#define WIN_WIDTH 500
#define WIN_HEIGHT 600

extern Evas_Object *win, *viewer_box;

void gui_create(const char *edje_file, Evas_Coord width, Evas_Coord height);
void gui_widget_load(void);

Eina_Bool option_is_force_resize(void);
void option_preview_size_get(Evas_Coord *w, Evas_Coord *h);

#endif
