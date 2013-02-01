#ifndef __INCLUDE_GUI_MOBILE__
#define __INCLUDE_GUI_MOBILE__

void gui_mobile_create(const char *edje_file,
                       int width, int height,
                       Eina_Bool fullscreen);
void gui_mobile_widget_load(void);
void gui_mobile_description_set(const char *txt);

#endif
