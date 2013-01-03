#ifndef __INCLUDE_THEME__
#define __INCLUDE_THEME__

#include "widget.h"

extern Eina_List *widget_list;
extern Elm_Theme *th;

void theme_init(void);
void theme_set(const char *edje_file);
void theme_unset(const char *edje_file);
void theme_load(const char *edje_file);
void theme_widgets_print(void);
Eina_List * theme_widget_styles_get(Widget_Type widget);
void theme_widget_styles_print(Widget_Type widget);

#endif
