#include <Elementary.h>
#include "log.h"

void
gui_create(void)
{
   Evas_Object *win, *o;
   Evas_Object *box, *lbl, *btn, *panes;

   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

   win = o = elm_win_util_standard_add("elm-theme-viewer", "Elm Theme Viewer");
   elm_win_autodel_set(o, EINA_TRUE);
   evas_object_resize(o, 300, 400);
   evas_object_show(o);

   box = o = elm_box_add(win);
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, o);
   evas_object_show(o);

   lbl = o = elm_label_add(win);
   elm_object_text_set(o, "/usr/local/share/elementary/themes/default.edj");
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(box, o);
   evas_object_show(o);

   btn = o = elm_button_add(win);
   elm_object_text_set(o, "Select Theme");
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(box, o);
   evas_object_show(o);

   panes = o = elm_panes_add(win);
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_box_pack_end(box, o);
   evas_object_show(o);

   INF("GUI Creation Done");

   return;
}
