#ifndef __INCLUDE_THEME__
#define __INCLUDE_THEME__

extern Eina_List *widget_list;
extern Elm_Theme *th;

typedef struct _Widget_Data Widget_Data;
struct _Widget_Data
{
   const char *widget; // widget name
   Eina_List *styles; // list of styles
};

void theme_init(void);
void theme_set(const char *edje_file);
void theme_unset(const char *edje_file);
void theme_load(const char *edje_file);
void theme_widgets_print(void);
Eina_List * theme_widget_styles_get(const char *widget);
void theme_widget_styles_print(const char *widget);

#endif