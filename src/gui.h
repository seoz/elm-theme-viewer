#ifndef __INCLUDE_GUI__
#define __INCLUDE_GUI__

#define WIN_WIDTH 500
#define WIN_HEIGHT 600

extern Evas_Object *win, *viewer_box;
extern Evas_Object *gui_layout, *preview_box, *option_frame, *list;

void gui_create(const char *edje_file,
                Evas_Coord width, Evas_Coord height,
                Eina_Bool fullscreen);
Evas_Object *gui_preview_create(Evas_Object *parent);
Evas_Object *gui_left_menu_create(Evas_Object *parent);

void gui_widget_load(void);

void gui_version_set(Eina_Bool version);

void gui_option_finger_size_create(Evas_Object *box);
void gui_option_scale_create(Evas_Object *box);
void gui_option_force_resize_create(Evas_Object *box);
void gui_option_width_size_create(Evas_Object *box);
void gui_option_height_size_create(Evas_Object *box);

#endif
