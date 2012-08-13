#include <Elementary.h>

void
gui_create(void)
{
   Evas_Object *win, *box, *o;

   win = elm_win_util_standard_add("elm-theme-viewer", "Elm Theme Viewer");
   evas_object_resize(win, 300, 400);
   evas_object_show(win);

   box = o = elm_box_add(win);
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, o);
   evas_object_show(o);

   return;
}
